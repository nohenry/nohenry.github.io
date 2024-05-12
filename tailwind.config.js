/** @type {import('tailwindcss').Config} */
module.exports = {
    content: ["index.html", "scripts/**/*.js"],
    theme: {
        extend: {
            fontFamily: {
                sans: ['"Open Sans"'],
                body: ['"Open Sans"'],
                source: ['source-code', 'mono']
            }
        },
    },
    plugins: [],
}

