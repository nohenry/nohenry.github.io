#!/usr/bin/env node
'use strict';

// ── Core (shared with web) ────────────────────────────────────────────────────

const FORMATS = {
  8:  { expBits: 4,  mantBits: 3,  bias: 7    },
  16: { expBits: 5,  mantBits: 10, bias: 15   },
  32: { expBits: 8,  mantBits: 23, bias: 127  },
  64: { expBits: 11, mantBits: 52, bias: 1023 },
};

// Uses DataView so this function is identical in Node and browser.
function toBits(value, bits) {
  if (bits === 32 || bits === 64) {
    const buf  = new ArrayBuffer(bits / 8);
    const view = new DataView(buf);
    if (bits === 32) view.setFloat32(0, value, false);
    else             view.setFloat64(0, value, false);
    let s = '';
    for (let i = 0; i < bits / 8; i++) s += view.getUint8(i).toString(2).padStart(8, '0');
    return s;
  }
  return smallFloat(value, FORMATS[bits]);
}

function smallFloat(value, { expBits, mantBits, bias }) {
  const maxBE = (1 << expBits) - 1;
  if (Object.is(value,  0))  return '0' + '0'.repeat(expBits + mantBits);
  if (Object.is(value, -0))  return '1' + '0'.repeat(expBits + mantBits);
  if (Number.isNaN(value))   return '0' + '1'.repeat(expBits) + '1' + '0'.repeat(mantBits - 1);
  const sign = value < 0 ? '1' : '0';
  const abs  = Math.abs(value);
  if (!isFinite(abs)) return sign + '1'.repeat(expBits) + '0'.repeat(mantBits);
  const e = Math.floor(Math.log2(abs));
  let bE  = e + bias;
  if (bE >= maxBE) return sign + '1'.repeat(expBits) + '0'.repeat(mantBits);
  if (bE <= 0) {
    const mant = Math.round(abs * Math.pow(2, bias - 1 + mantBits));
    return sign + '0'.repeat(expBits) + mant.toString(2).padStart(mantBits, '0').slice(-mantBits);
  }
  let mant = Math.round((abs / Math.pow(2, e) - 1) * Math.pow(2, mantBits));
  if (mant >= (1 << mantBits)) {
    mant = 0; bE++;
    if (bE >= maxBE) return sign + '1'.repeat(expBits) + '0'.repeat(mantBits);
  }
  return sign + bE.toString(2).padStart(expBits, '0') + mant.toString(2).padStart(mantBits, '0');
}

const POOLS = {
  easy: {
    8:  [0, 1, -1, 2, -2, 4, -4, 0.5, -0.5, 0.25, -0.25, 1.5, -1.5],
    16: [0, 1, -1, 2, -2, 4, -4, 8, -8, 0.5, -0.5, 0.25, -0.25, 1.5, -1.5],
    32: [0, 1, -1, 2, -2, 4, -4, 8, -8, 16, -16, 0.5, -0.5, 0.25, -0.25, 1.5, -1.5],
    64: [0, 1, -1, 2, -2, 4, -4, 8, -8, 16, -16, 0.5, -0.5, 0.25, -0.25, 1.5, -1.5],
  },
  medium: {
    8:  [3, -3, 6, -6, 7, -7, 0.75, -0.75, 1.25, -1.25, 0.375, -0.375, 1.875, -1.875, 3.5, -3.5],
    16: [3, -3, 6, -6, 100, -100, 0.75, -0.75, 1.25, -1.25, 0.375, -0.375, 0.0625, -0.0625, 1024, -1024],
    32: [3, -3, 100, -100, 1000, -1000, 0.75, -0.75, 0.125, -0.125, 255, -255, 0.0625, -0.0625],
    64: [3, -3, 100, -100, 1000, -1000, 0.75, -0.75, 0.125, -0.125, 255, -255, 0.0625, -0.0625],
  },
  hard: {
    8:  [11, -11, 13, -13, 14, -14, 7.5, -7.5, 0.4375, -0.4375, 0.001953125, 1.875, -1.875],
    16: [3.140625, -3.140625, 100.5, -100.5, 0.001953125, -0.001953125, 65504, -65504, 6.103515625e-5],
    32: [Math.PI, -Math.PI, 1/3, 255.5, 1e10, -1e10, Infinity, -Infinity, 1.17549435e-38],
    64: [Math.PI, -Math.PI, Math.E, -Math.E, 1/7, 1e100, -1e100, 1e-100, Number.MAX_SAFE_INTEGER],
  },
};

function randPick(pool) { return pool[Math.floor(Math.random() * pool.length)]; }

function segmented(bits, bin) {
  const { expBits } = FORMATS[bits];
  return `${bin[0]} | ${bin.slice(1, 1 + expBits)} | ${bin.slice(1 + expBits)}`;
}

function numLabel(n) {
  if (Number.isNaN(n)) return 'NaN';
  if (n === Infinity)  return 'Infinity';
  if (n === -Infinity) return '-Infinity';
  return String(n);
}

function hexToBin(hex, bits) {
  if (bits <= 32) return parseInt(hex, 16).toString(2).padStart(bits, '0');
  const hi = parseInt(hex.slice(0, 8), 16);
  const lo = parseInt(hex.slice(8), 16);
  return hi.toString(2).padStart(32, '0') + lo.toString(2).padStart(32, '0');
}

function binToHex(bin, bits) {
  if (bits <= 32) return parseInt(bin, 2).toString(16).padStart(bits / 4, '0').toUpperCase();
  const hi = parseInt(bin.slice(0, 32), 2);
  const lo = parseInt(bin.slice(32), 2);
  return (hi.toString(16).padStart(8, '0') + lo.toString(16).padStart(8, '0')).toUpperCase();
}

// ── Quiz engine (renderer-agnostic) ──────────────────────────────────────────
//
// Renderer interface (all methods required):
//   showMenu()                      → Promise<{ bits, diff, inputMode }>
//   renderQuestion(ctx)             → void
//   getInput()                      → Promise<string>   raw line, Quiz normalises
//   showError(msg)                  → void              inline, no redraw
//   quit(score, asked)              → void

class Quiz {
  constructor(renderer) {
    this.renderer  = renderer;
    this.bits      = 32;
    this.diff      = 'easy';
    this.inputMode = 'binary';
    this.score     = 0;
    this.asked     = 0;
    this.last      = null;
  }

  async start() {
    const cfg      = await this.renderer.showMenu();
    this.bits      = cfg.bits;
    this.diff      = cfg.diff;
    this.inputMode = cfg.inputMode;
    this.score     = 0;
    this.asked     = 0;
    this.last      = null;
    await this.run();
  }

  async run() {
    while (true) {
      const num    = randPick(POOLS[this.diff][this.bits]);
      const answer = toBits(num, this.bits);
      const F      = FORMATS[this.bits];
      const maxBE  = (1 << F.expBits) - 1;
      const hexLen = this.bits / 4;

      this.renderer.renderQuestion({
        bits: this.bits, diff: this.diff, inputMode: this.inputMode,
        score: this.score, asked: this.asked, last: this.last,
        num, answer, F, maxBE, hexLen,
      });

      while (true) {
        const raw = await this.renderer.getInput();
        const inp = raw.trim().replace(/[\s|]+/g, '').toLowerCase();

        if (inp === 'q' || inp === 'quit') {
          this.renderer.quit(this.score, this.asked);
          return;
        }
        if (inp === 'menu') { await this.start(); return; }
        if (inp === 'skip') { this.last = { type: 'skip', num, answer }; break; }

        let userBin;
        if (this.inputMode === 'hex') {
          const h = inp.replace(/^0x/, '');
          if (!/^[0-9a-f]+$/.test(h) || h.length !== hexLen) {
            this.renderer.showError(`Need exactly ${hexLen} hex digits (0x prefix optional).`);
            continue;
          }
          userBin = hexToBin(h, this.bits);
        } else {
          if (!/^[01]+$/.test(inp) || inp.length !== this.bits) {
            this.renderer.showError(`Need exactly ${this.bits} binary digits (spaces and '|' are stripped).`);
            continue;
          }
          userBin = inp;
        }

        this.asked++;
        if (userBin === answer) {
          this.score++;
          this.last = { type: 'ok', num, answer };
        } else {
          this.last = { type: 'wrong', num, answer, yours: userBin };
        }
        break;
      }
    }
  }
}

// ── Terminal renderer ─────────────────────────────────────────────────────────

const readline = require('readline');

const C = {
  r:   '\x1b[0m',
  b:   '\x1b[1m',
  dim: '\x1b[2m',
  red: '\x1b[31m',
  grn: '\x1b[32m',
  yel: '\x1b[33m',
  cyn: '\x1b[36m',
  wht: '\x1b[97m',
};
const cls = () => process.stdout.write('\x1b[2J\x1b[H');
const out = s  => process.stdout.write(s);

class TerminalRenderer {
  constructor() {
    this.rl = readline.createInterface({ input: process.stdin, output: process.stdout });
  }

  _ask(q) { return new Promise(r => this.rl.question(q, r)); }

  async showMenu() {
    cls();
    out(`\n${C.b}${C.cyn}  ┌──────────────────────────────────────┐\n`);
    out(`  │      IEEE 754 Float → Binary Quiz      │\n`);
    out(`  └──────────────────────────────────────┘${C.r}\n\n`);
    out(`  ${C.dim}Commands during quiz:  skip · menu · q${C.r}\n\n`);

    const bIn = (await this._ask(`  Bit width  ${C.dim}8 · 16 · 32 · 64${C.r}  [32]: `)).trim();
    const b   = parseInt(bIn);
    const bits = [8, 16, 32, 64].includes(b) ? b : 32;

    const dIn = (await this._ask(`  Difficulty ${C.dim}easy · medium · hard${C.r}  [easy]: `)).trim().toLowerCase();
    const diff = ['easy', 'medium', 'hard'].includes(dIn) ? dIn : 'easy';

    const mIn = (await this._ask(`  Input mode ${C.dim}binary · hex${C.r}          [binary]: `)).trim().toLowerCase();
    const inputMode = (mIn === 'hex' || mIn === 'h') ? 'hex' : 'binary';

    return { bits, diff, inputMode };
  }

  renderQuestion({ bits, diff, inputMode, score, asked, last, num, F, maxBE, hexLen }) {
    cls();
    const modeTag = inputMode === 'hex' ? `${C.dim}[hex]${C.r}` : `${C.dim}[bin]${C.r}`;
    out(`\n${C.b}  IEEE754${C.r}  ${C.cyn}${bits}-bit${C.r}  ${C.yel}${diff}${C.r}  ${modeTag}`);
    out(`    score ${C.grn}${score}${C.r}${C.dim}/${asked}${C.r}\n`);
    out(`  ${'─'.repeat(54)}\n`);

    if (last) {
      const L = last;
      if (L.type === 'ok') {
        const disp = inputMode === 'hex' ? binToHex(L.answer, bits) : segmented(bits, L.answer);
        out(`\n  ${C.grn}✓ Correct!${C.r}  ${C.dim}${numLabel(L.num)} → ${disp}${C.r}\n`);
      } else {
        const expStr  = L.answer.slice(1, 1 + F.expBits);
        const mantStr = L.answer.slice(1 + F.expBits);
        const bE      = parseInt(expStr, 2);
        const aE      = bE === 0 ? 1 - F.bias : bE - F.bias;
        const kind    = bE === 0 ? 'denormal/zero' : bE === maxBE ? 'inf/NaN' : 'normal';
        if (L.type === 'skip') {
          out(`\n  ${C.yel}↷ Skipped${C.r}   ${C.b}${numLabel(L.num)}${C.r}\n`);
          if (inputMode === 'hex') {
            out(`  ${C.grn}answer:  ${binToHex(L.answer, bits)}${C.r}\n`);
            out(`  ${C.dim}binary:  ${segmented(bits, L.answer)}${C.r}\n`);
          } else {
            out(`  ${C.grn}answer:  ${segmented(bits, L.answer)}${C.r}\n`);
          }
        } else {
          out(`\n  ${C.red}✗ Wrong!${C.r}   ${C.b}${numLabel(L.num)}${C.r}\n`);
          if (inputMode === 'hex') {
            out(`  ${C.dim}yours:   ${binToHex(L.yours, bits)}${C.r}\n`);
            out(`  ${C.grn}correct: ${binToHex(L.answer, bits)}${C.r}\n`);
            out(`  ${C.dim}binary:  ${segmented(bits, L.answer)}${C.r}\n`);
          } else {
            out(`  ${C.dim}yours:   ${segmented(bits, L.yours)}${C.r}\n`);
            out(`  ${C.grn}correct: ${segmented(bits, L.answer)}${C.r}\n`);
          }
        }
        out(`  ${C.dim}  sign=${L.answer[0]}  exp=${expStr}(=${bE})→actual ${aE}  mant=${mantStr}  [${kind}]${C.r}\n`);
      }
    }

    out(`\n  Convert to ${bits}-bit IEEE754:\n\n`);
    out(`    ${C.b}${C.wht}${numLabel(num)}${C.r}\n\n`);
    out(`  ${C.dim}Format: 1 sign  |  ${F.expBits} exponent bits (bias ${F.bias})  |  ${F.mantBits} mantissa bits${C.r}\n`);
    if (inputMode === 'hex') {
      out(`  ${C.dim}Enter ${hexLen} hex digits (0x optional) — or 'skip' to reveal:${C.r}\n\n`);
    } else {
      out(`  ${C.dim}Enter ${bits} bits (spaces/'|' ignored) — or 'skip' to reveal:${C.r}\n\n`);
    }
  }

  async getInput() { return this._ask(`  ${C.b}›${C.r} `); }

  showError(msg) { out(`  ${C.red}✗${C.r}  ${msg}\n`); }

  quit(score, asked) {
    cls();
    out(`\n  Final: ${C.grn}${score}${C.r} correct out of ${asked}\n\n`);
    this.rl.close();
  }
}

// ── Boot ──────────────────────────────────────────────────────────────────────

new Quiz(new TerminalRenderer()).start().catch(e => { console.error(e); process.exit(1); });
