#pragma once
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    uint8_t* items; 
    size_t count;
} ByteSpan;

typedef struct {
    uint32_t items[3];
} uint32x3;

#define ALL_MIPS (0xFF)
#define ALL_LAYERS (0xFFFF)

// Opaque handles
typedef struct GpuPipelineBase {} GpuPipelineBase;
typedef struct GpuTextureBase {} GpuTextureBase;
typedef struct GpuDepthStencilStateBase {} GpuDepthStencilStateBase;
typedef struct GpuBlendStateBase {} GpuBlendStateBase;
typedef struct GpuQueueBase {} GpuQueueBase;
typedef struct GpuCommandBufferBase {} GpuCommandBufferBase;
typedef struct GpuSemaphoreBase {} GpuSemaphoreBase;
typedef struct GpuDeviceBase {} GpuDeviceBase;

typedef GpuPipelineBase           *GpuPipeline;
typedef GpuTextureBase            *GpuTexture;
typedef GpuDepthStencilStateBase  *GpuDepthStencilState;
typedef GpuBlendStateBase         *GpuBlendState;
typedef GpuQueueBase              *GpuQueue;
typedef GpuCommandBufferBase      *GpuCommandBuffer;
typedef GpuSemaphoreBase          *GpuSemaphore;
// typedef uint32_t GpuSemaphore;
typedef GpuDeviceBase             *GpuDevice;

// Enums
typedef enum MEMORY { MEMORY_DEFAULT, MEMORY_GPU, MEMORY_READBACK } MEMORY;
typedef enum CULL { CULL_CCW, CULL_CW, CULL_ALL, CULL_NONE } CULL;
typedef enum DEPTH_FLAGS { DEPTH_READ = 0x1, DEPTH_WRITE = 0x2 } DEPTH_FLAGS;
typedef enum OP { OP_NEVER, OP_LESS, OP_EQUAL, OP_LESS_EQUAL, OP_GREATER, OP_NOT_EQUAL, OP_GREATER_EQUAL, OP_ALWAYS, OP_KEEP } OP; 
typedef enum BLEND { BLEND_ADD, BLEND_SUBTRACT, BLEND_REV_SUBTRACT, BLEND_MIN, BLEND_MAX } BLEND;
typedef enum FACTOR { FACTOR_ZERO, FACTOR_ONE, FACTOR_SRC_COLOR, FACTOR_DST_COLOR, FACTOR_SRC_ALPHA } FACTOR;
typedef enum TOPOLOGY { TOPOLOGY_TRIANGLE_LIST, TOPOLOGY_TRIANGLE_STRIP, TOPOLOGY_TRIANGLE_FAN } TOPOLOGY;
typedef enum TEXTURE { TEXTURE_1D, TEXTURE_2D, TEXTURE_3D, TEXTURE_CUBE, TEXTURE_2D_ARRAY, TEXTURE_CUBE_ARRAY } TEXTURE;
typedef enum USAGE_FLAGS { USAGE_SAMPLED, USAGE_STORAGE, USAGE_COLOR_ATTACHMENT, USAGE_DEPTH_STENCIL_ATTACHMENT } USAGE_FLAGS;
typedef enum STAGE { STAGE_TRANSFER, STAGE_COMPUTE, STAGE_RASTER_COLOR_OUT, STAGE_PIXEL_SHADER, STAGE_VERTEX_SHADER } STAGE;
typedef enum HAZARD_FLAGS { HAZARD_DRAW_ARGUMENTS = 0x1, HAZARD_DESCRIPTORS = 0x2, HAZARD_DEPTH_STENCIL = 0x4 } HAZARD_FLAGS;
typedef enum SIGNAL { SIGNAL_ATOMIC_SET, SIGNAL_ATOMIC_MAX, SIGNAL_ATOMIC_OR } SIGNAL;
typedef enum QUEUE { QUEUE_GRAPHICS, QUEUE_COMPUTE, QUEUE_TRANSFER } QUEUE;
typedef enum TARGETOP { LOAD, STORE, CLEAR, DONT_CARE } TARGETOP;

typedef enum FORMAT {
   FORMAT_NONE,

   /* Vertex formats must be first and must be <= 255 */
   FORMAT_R64_UINT,
   FORMAT_VERTEX_START = FORMAT_R64_UINT,
   FORMAT_R64G64_UINT,
   FORMAT_R64G64B64_UINT,
   FORMAT_R64G64B64A64_UINT,
   FORMAT_R64_SINT,
   FORMAT_R64G64_SINT,
   FORMAT_R64G64B64_SINT,
   FORMAT_R64G64B64A64_SINT,
   FORMAT_R64_FLOAT,
   FORMAT_R64G64_FLOAT,
   FORMAT_R64G64B64_FLOAT,
   FORMAT_R64G64B64A64_FLOAT,
   FORMAT_R32_UINT,
   FORMAT_R32G32_UINT,
   FORMAT_R32G32B32_UINT,
   FORMAT_R32G32B32A32_UINT,
   FORMAT_R32_SINT,
   FORMAT_R32G32_SINT,
   FORMAT_R32G32B32_SINT,
   FORMAT_R32G32B32A32_SINT,
   FORMAT_R32_FLOAT,
   FORMAT_R32G32_FLOAT,
   FORMAT_R32G32B32_FLOAT,
   FORMAT_R32G32B32A32_FLOAT,
   FORMAT_R32_UNORM,
   FORMAT_R32G32_UNORM,
   FORMAT_R32G32B32_UNORM,
   FORMAT_R32G32B32A32_UNORM,
   FORMAT_R32_SNORM,
   FORMAT_R32G32_SNORM,
   FORMAT_R32G32B32_SNORM,
   FORMAT_R32G32B32A32_SNORM,
   FORMAT_R32_USCALED,
   FORMAT_R32G32_USCALED,
   FORMAT_R32G32B32_USCALED,
   FORMAT_R32G32B32A32_USCALED,
   FORMAT_R32_SSCALED,
   FORMAT_R32G32_SSCALED,
   FORMAT_R32G32B32_SSCALED,
   FORMAT_R32G32B32A32_SSCALED,
   FORMAT_R32_FIXED,
   FORMAT_R32G32_FIXED,
   FORMAT_R32G32B32_FIXED,
   FORMAT_R32G32B32A32_FIXED,
   FORMAT_R16_UINT,
   FORMAT_R16G16_UINT,
   FORMAT_R16G16B16_UINT,
   FORMAT_R16G16B16A16_UINT,
   FORMAT_R16_SINT,
   FORMAT_R16G16_SINT,
   FORMAT_R16G16B16_SINT,
   FORMAT_R16G16B16A16_SINT,
   FORMAT_R16_FLOAT,
   FORMAT_R16G16_FLOAT,
   FORMAT_R16G16B16_FLOAT,
   FORMAT_R16G16B16A16_FLOAT,
   FORMAT_R16_UNORM,
   FORMAT_R16G16_UNORM,
   FORMAT_R16G16B16_UNORM,
   FORMAT_R16G16B16A16_UNORM,
   FORMAT_R16_SNORM,
   FORMAT_R16G16_SNORM,
   FORMAT_R16G16B16_SNORM,
   FORMAT_R16G16B16A16_SNORM,
   FORMAT_R16_USCALED,
   FORMAT_R16G16_USCALED,
   FORMAT_R16G16B16_USCALED,
   FORMAT_R16G16B16A16_USCALED,
   FORMAT_R16_SSCALED,
   FORMAT_R16G16_SSCALED,
   FORMAT_R16G16B16_SSCALED,
   FORMAT_R16G16B16A16_SSCALED,
   FORMAT_R8_UINT,
   FORMAT_R8G8_UINT,
   FORMAT_R8G8B8_UINT,
   FORMAT_R8G8B8A8_UINT,
   FORMAT_R8_SINT,
   FORMAT_R8G8_SINT,
   FORMAT_R8G8B8_SINT,
   FORMAT_R8G8B8A8_SINT,
   FORMAT_R8_UNORM,
   FORMAT_R8G8_UNORM,
   FORMAT_R8G8B8_UNORM,
   FORMAT_R8G8B8A8_UNORM,
   FORMAT_R8_SNORM,
   FORMAT_R8G8_SNORM,
   FORMAT_R8G8B8_SNORM,
   FORMAT_R8G8B8A8_SNORM,
   FORMAT_R8_USCALED,
   FORMAT_R8G8_USCALED,
   FORMAT_R8G8B8_USCALED,
   FORMAT_R8G8B8A8_USCALED,
   FORMAT_R8_SSCALED,
   FORMAT_R8G8_SSCALED,
   FORMAT_R8G8B8_SSCALED,
   FORMAT_R8G8B8A8_SSCALED,
   FORMAT_B8G8R8_UINT,
   FORMAT_B8G8R8_SINT,
   FORMAT_B8G8R8_UNORM,
   FORMAT_B8G8R8_SNORM,
   FORMAT_B8G8R8_USCALED,
   FORMAT_B8G8R8_SSCALED,
   FORMAT_B8G8R8A8_UINT,
   FORMAT_B8G8R8A8_SINT,
   FORMAT_B8G8R8A8_UNORM,
   FORMAT_B8G8R8A8_SNORM,
   FORMAT_B8G8R8A8_USCALED,
   FORMAT_B8G8R8A8_SSCALED,
   FORMAT_A8B8G8R8_USCALED,
   FORMAT_A8B8G8R8_SSCALED,
   FORMAT_A8R8G8B8_UNORM,
   FORMAT_R10G10B10A2_UINT,
   FORMAT_R10G10B10A2_SINT,
   FORMAT_R10G10B10A2_UNORM,
   FORMAT_R10G10B10A2_SNORM,
   FORMAT_R10G10B10A2_USCALED,
   FORMAT_R10G10B10A2_SSCALED,
   FORMAT_B10G10R10A2_UINT,
   FORMAT_B10G10R10A2_SINT,
   FORMAT_B10G10R10A2_UNORM,
   FORMAT_B10G10R10A2_SNORM,
   FORMAT_B10G10R10A2_USCALED,
   FORMAT_B10G10R10A2_SSCALED,
   FORMAT_R11G11B10_FLOAT,
   FORMAT_VERTEX_END = FORMAT_R11G11B10_FLOAT,

   /* YUV formats. */
   FORMAT_U8Y8V8Y8_422_UNORM,
   FORMAT_YUV_START = FORMAT_U8Y8V8Y8_422_UNORM,
   FORMAT_V8Y8U8Y8_422_UNORM,
   FORMAT_Y8U8Y8V8_422_UNORM,
   FORMAT_Y8V8Y8U8_422_UNORM,
   FORMAT_A8Y8U8V8_444_UNORM,
   FORMAT_X8Y8U8V8_444_UNORM,
   FORMAT_Y8_V8_U8_420_UNORM,
   FORMAT_Y8_V8_U8_422_UNORM,
   FORMAT_Y8_U8_V8_420_UNORM,
   FORMAT_Y8_U8V8_420_UNORM,
   FORMAT_Y8_V8U8_420_UNORM,
   FORMAT_Y8_400_UNORM,
   FORMAT_Y10_U10V10_420_UNORM,
   FORMAT_Y10_U10V10_422_UNORM,
   FORMAT_Y16_U16V16_444_UNORM,
   FORMAT_Y8_U8_V8_422_UNORM,
   FORMAT_Y8_U8V8_422_UNORM,
   FORMAT_Y8_V8U8_422_UNORM,
   FORMAT_Y8_U8V8_444_UNORM,
   FORMAT_Y8_V8U8_444_UNORM,
   FORMAT_Y8_U8_V8_444_UNORM,
   FORMAT_Y8_U8_V8_440_UNORM,
   FORMAT_Y10X6_U10X6_V10X6_420_UNORM,
   FORMAT_Y12X4_U12X4_V12X4_420_UNORM,
   FORMAT_Y16_U16_V16_420_UNORM,
   FORMAT_Y10X6_U10X6_V10X6_422_UNORM,
   FORMAT_Y12X4_U12X4_V12X4_422_UNORM,
   FORMAT_Y16_U16_V16_422_UNORM,
   FORMAT_Y10X6_U10X6_V10X6_444_UNORM,
   FORMAT_Y12X4_U12X4_V12X4_444_UNORM,
   FORMAT_Y16_U16_V16_444_UNORM,
   FORMAT_Y16_U16V16_422_UNORM,
   FORMAT_X6Y10_X6U10X6V10_420_UNORM,
   FORMAT_X4Y12_X4U12X4V12_420_UNORM,
   FORMAT_Y16_U16V16_420_UNORM,
   FORMAT_Y10Y10Y10X2_U10V10U10X2V10U10V10X2_420_UNORM,
   FORMAT_X6Y10X6U10X6Y10X6V10_422_UNORM,
   FORMAT_X4Y12X4U12X4Y12X4V12_422_UNORM,
   FORMAT_Y16U16Y16V16_422_UNORM,
   FORMAT_U10Y10V10A2_444_UNORM,
   FORMAT_X4U12X4Y12X4V12X4A12_444_UNORM,
   FORMAT_U16Y16V16A16_444_UNORM,
   FORMAT_Y8U8V8_420_UNORM_PACKED,
   FORMAT_Y10U10V10_420_UNORM_PACKED,
   FORMAT_YUV_END = FORMAT_Y10U10V10_420_UNORM_PACKED,

   /* Depth/stencil formats. */
   FORMAT_S8_UINT,
   FORMAT_ZS_START = FORMAT_S8_UINT,
   FORMAT_Z16_UNORM,
   FORMAT_Z16_UNORM_S8_UINT,
   FORMAT_Z32_UNORM,
   FORMAT_Z32_FLOAT,
   FORMAT_Z24_UNORM_S8_UINT,
   FORMAT_S8_UINT_Z24_UNORM,
   FORMAT_X24S8_UINT,
   FORMAT_S8X24_UINT,
   FORMAT_Z24X8_UNORM,
   FORMAT_X8Z24_UNORM,
   FORMAT_Z24_UNORM_PACKED,
   FORMAT_Z32_FLOAT_S8X24_UINT,
   FORMAT_X32_S8X24_UINT,
   FORMAT_ZS_END = FORMAT_X32_S8X24_UINT,

   /* Other formats. */
   FORMAT_B8G8R8X8_UNORM,
   FORMAT_B8G8R8X8_SNORM,
   FORMAT_B8G8R8X8_UINT,
   FORMAT_B8G8R8X8_SINT,
   FORMAT_A8R8G8B8_SNORM,
   FORMAT_A8R8G8B8_SINT,
   FORMAT_X8R8G8B8_UNORM,
   FORMAT_X8R8G8B8_SNORM,
   FORMAT_X8R8G8B8_SINT,
   FORMAT_A8B8G8R8_UNORM,
   FORMAT_X8B8G8R8_UNORM,
   FORMAT_R8G8B8X8_UNORM,
   FORMAT_R5G5B5A1_UNORM,
   FORMAT_R5G5B5X1_UNORM,
   FORMAT_B5G5R5X1_UNORM,
   FORMAT_B5G5R5A1_UNORM,
   FORMAT_X1B5G5R5_UNORM,
   FORMAT_A1R5G5B5_UNORM,
   FORMAT_X1R5G5B5_UNORM,
   FORMAT_A1B5G5R5_UNORM,
   FORMAT_R4G4B4A4_UNORM,
   FORMAT_R4G4B4X4_UNORM,
   FORMAT_B4G4R4A4_UNORM,
   FORMAT_B4G4R4X4_UNORM,
   FORMAT_A4R4G4B4_UNORM,
   FORMAT_A4B4G4R4_UNORM,
   FORMAT_R5G6B5_UNORM,
   FORMAT_B5G6R5_UNORM,
   FORMAT_R10G10B10X2_UNORM,
   FORMAT_A2R10G10B10_UNORM,
   FORMAT_A2B10G10R10_UNORM,
   FORMAT_R3G3B2_UNORM,
   FORMAT_B2G3R3_UNORM,
   FORMAT_L8_UNORM,
   FORMAT_A8_UNORM,
   FORMAT_I8_UNORM,
   FORMAT_L4A4_UNORM,
   FORMAT_L8A8_UNORM,
   FORMAT_L16_UNORM,
   FORMAT_A16_UNORM,
   FORMAT_I16_UNORM,
   FORMAT_L16A16_UNORM,
   FORMAT_A8_SNORM,
   FORMAT_L8_SNORM,
   FORMAT_L8A8_SNORM,
   FORMAT_I8_SNORM,
   FORMAT_A16_SNORM,
   FORMAT_L16_SNORM,
   FORMAT_L16A16_SNORM,
   FORMAT_I16_SNORM,
   FORMAT_A16_FLOAT,
   FORMAT_L16_FLOAT,
   FORMAT_L16A16_FLOAT,
   FORMAT_I16_FLOAT,
   FORMAT_A32_FLOAT,
   FORMAT_L32_FLOAT,
   FORMAT_L32A32_FLOAT,
   FORMAT_I32_FLOAT,
   FORMAT_L8_SRGB,
   FORMAT_R8_SRGB,
   FORMAT_L8A8_SRGB,
   FORMAT_R8G8_SRGB,
   FORMAT_R8G8B8_SRGB,
   FORMAT_B8G8R8_SRGB,
   FORMAT_R8G8B8A8_SRGB,
   FORMAT_A8B8G8R8_SRGB,
   FORMAT_X8B8G8R8_SRGB,
   FORMAT_B8G8R8A8_SRGB,
   FORMAT_B8G8R8X8_SRGB,
   FORMAT_A8R8G8B8_SRGB,
   FORMAT_X8R8G8B8_SRGB,
   FORMAT_R8SG8SB8UX8U_NORM,
   FORMAT_R10SG10SB10SA2U_NORM,
   FORMAT_R5SG5SB6U_NORM,
   FORMAT_Z24_UNORM_S8_UINT_AS_R8G8B8A8,
   FORMAT_R8G8_B8G8_422_UNORM,
   FORMAT_G8R8_G8B8_422_UNORM,
   FORMAT_G8R8_B8R8_422_UNORM,
   FORMAT_R8G8_R8B8_422_UNORM,
   FORMAT_B8R8_G8R8_422_UNORM,
   FORMAT_R8B8_R8G8_422_UNORM,
   FORMAT_G8B8_G8R8_422_UNORM,
   FORMAT_B8G8_R8G8_422_UNORM,
   FORMAT_R16G16_R16B16_422_UNORM,
   FORMAT_X6R10X6G10_X6R10X6B10_422_UNORM,
   FORMAT_R9G9B9E5_FLOAT,
   FORMAT_R1_UNORM,
   FORMAT_R8G8Bx_SNORM,
   FORMAT_R10G10B10X2_USCALED,
   FORMAT_R10G10B10X2_SNORM,
   FORMAT_R10G10B10X2_SINT,
   FORMAT_R8_G8B8_420_UNORM,
   FORMAT_R8_B8G8_420_UNORM,
   FORMAT_G8_B8R8_420_UNORM,
   FORMAT_R8_G8B8_422_UNORM,
   FORMAT_R8_B8G8_422_UNORM,
   FORMAT_G8_B8R8_422_UNORM,
   FORMAT_R10_G10B10_420_UNORM,
   FORMAT_R10_G10B10_422_UNORM,
   FORMAT_R8_G8_B8_420_UNORM,
   FORMAT_R8_B8_G8_420_UNORM,
   FORMAT_G8_B8_R8_420_UNORM,
   FORMAT_R8_G8_B8_444_UNORM,
   FORMAT_X6G10_X6B10X6R10_420_UNORM,
   FORMAT_X4G12_X4B12X4R12_420_UNORM,
   FORMAT_G8_B8R8_444_UNORM,
   FORMAT_X6G10_X6B10X6R10_444_UNORM,
   FORMAT_X4G12_X4B12X4R12_444_UNORM,
   FORMAT_R8G8B8_420_UNORM_PACKED,
   FORMAT_R10G10B10_420_UNORM_PACKED,
   FORMAT_X6R10X6G10X6B10X6A10_UNORM,
   FORMAT_X6R10_UNORM,
   FORMAT_X6R10X6G10_UNORM,
   FORMAT_X4R12_UNORM,
   FORMAT_X4R12X4G12_UNORM,
   FORMAT_A4R4_UNORM,
   FORMAT_R4A4_UNORM,
   FORMAT_R8A8_UNORM,
   FORMAT_A8R8_UNORM,
   FORMAT_A8_UINT,
   FORMAT_I8_UINT,
   FORMAT_L8_UINT,
   FORMAT_L8A8_UINT,
   FORMAT_A8_SINT,
   FORMAT_I8_SINT,
   FORMAT_L8_SINT,
   FORMAT_L8A8_SINT,
   FORMAT_A16_UINT,
   FORMAT_I16_UINT,
   FORMAT_L16_UINT,
   FORMAT_L16A16_UINT,
   FORMAT_A16_SINT,
   FORMAT_I16_SINT,
   FORMAT_L16_SINT,
   FORMAT_L16A16_SINT,
   FORMAT_A32_UINT,
   FORMAT_I32_UINT,
   FORMAT_L32_UINT,
   FORMAT_L32A32_UINT,
   FORMAT_A32_SINT,
   FORMAT_I32_SINT,
   FORMAT_L32_SINT,
   FORMAT_L32A32_SINT,
   FORMAT_A8R8G8B8_UINT,
   FORMAT_A8B8G8R8_UINT,
   FORMAT_A2R10G10B10_UINT,
   FORMAT_A2B10G10R10_UINT,
   FORMAT_R5G6B5_UINT,
   FORMAT_B5G6R5_UINT,
   FORMAT_R3G3B2_UINT,
   FORMAT_B2G3R3_UINT,
   FORMAT_R4G4B4A4_UINT,
   FORMAT_B4G4R4A4_UINT,
   FORMAT_A4R4G4B4_UINT,
   FORMAT_A4B4G4R4_UINT,
   FORMAT_A1R5G5B5_UINT,
   FORMAT_A1B5G5R5_UINT,
   FORMAT_R5G5B5A1_UINT,
   FORMAT_B5G5R5A1_UINT,
   FORMAT_R8G8B8X8_SNORM,
   FORMAT_R8G8B8X8_SRGB,
   FORMAT_R8G8B8X8_UINT,
   FORMAT_R8G8B8X8_SINT,
   FORMAT_B10G10R10X2_UNORM,
   FORMAT_B10G10R10X2_SNORM,
   FORMAT_B10G10R10X2_SINT,
   FORMAT_R16G16B16X16_UNORM,
   FORMAT_R16G16B16X16_SNORM,
   FORMAT_R16G16B16X16_FLOAT,
   FORMAT_R16G16B16X16_UINT,
   FORMAT_R16G16B16X16_SINT,
   FORMAT_R32G32B32X32_FLOAT,
   FORMAT_R32G32B32X32_UINT,
   FORMAT_R32G32B32X32_SINT,
   FORMAT_R8A8_SNORM,
   FORMAT_R16A16_UNORM,
   FORMAT_R16A16_SNORM,
   FORMAT_R16A16_FLOAT,
   FORMAT_R32A32_FLOAT,
   FORMAT_R8A8_UINT,
   FORMAT_R8A8_SINT,
   FORMAT_R16A16_UINT,
   FORMAT_R16A16_SINT,
   FORMAT_R32A32_UINT,
   FORMAT_R32A32_SINT,
   FORMAT_B5G6R5_SRGB,
   FORMAT_R5G6B5_SRGB,
   FORMAT_G8R8_UNORM,
   FORMAT_G8R8_SNORM,
   FORMAT_G8R8_SINT,
   FORMAT_G16R16_UNORM,
   FORMAT_G16R16_SNORM,
   FORMAT_G16R16_SINT,
   FORMAT_A8B8G8R8_SNORM,
   FORMAT_A8B8G8R8_SINT,
   FORMAT_X8B8G8R8_SNORM,
   FORMAT_X8B8G8R8_SINT,
   FORMAT_COUNT,
} FORMAT;

// Structs
typedef struct {
    OP test;
    OP failOp;
    OP passOp;
    OP depthFailOp;
    uint8_t reference;
} Stencil;

typedef struct {
    DEPTH_FLAGS depthMode;
    OP depthTest;
    float depthBias;
    float depthBiasSlopeFactor;
    float depthBiasClamp;
    uint8_t stencilReadMask;
    uint8_t stencilWriteMask;
    Stencil stencilFront;
    Stencil stencilBack;
} GpuDepthStencilDesc;

typedef struct {
    BLEND colorOp;
    FACTOR srcColorFactor;
    FACTOR dstColorFactor;
    BLEND alphaOp;
    FACTOR srcAlphaFactor;
    FACTOR dstAlphaFactor;
    uint8_t colorWriteMask;
} GpuBlendDesc;

typedef struct {
    FORMAT format;
    uint8_t writeMask;
} ColorTarget;

typedef struct {
    TOPOLOGY topology;
    CULL cull;
    bool alphaToCoverage;
    bool supportDualSourceBlending;
    uint8_t sampleCount;
    FORMAT depthFormat;
    FORMAT stencilFormat;
    ColorTarget* colorTargets;
    size_t colorTargetsCount;
    GpuBlendDesc* blendstate; // optional embedded blend state
} GpuRasterDesc;

typedef struct { 
    TEXTURE type;
    uint32x3 dimensions;
    uint32_t mipCount;
    uint32_t layerCount;
    uint32_t sampleCount;
    FORMAT format; 
    USAGE_FLAGS usage;
} GpuTextureDesc;

typedef struct {
    FORMAT format;
    uint8_t baseMip;
    uint8_t mipCount;
    uint16_t baseLayer;
    uint16_t layerCount;
} GpuViewDesc;

typedef struct {
    GpuTexture texture;
    TARGETOP loadOp;
    TARGETOP storeOp;
    union {
        float clearColor[4];
        float clearValue;
    };
} GpuRenderPassTargetDesc;

typedef struct {
    GpuRenderPassTargetDesc depthTarget;
    GpuRenderPassTargetDesc stencilTarget;
    GpuRenderPassTargetDesc colorTargets[8];
} GpuRenderPassDesc;

typedef struct { size_t size; size_t align; } GpuTextureSizeAlign;
typedef struct { size_t width; size_t height; size_t row_stride; } GpuTextureLayout;
typedef struct { uint64_t data[4]; } GpuTextureDescriptor;

GpuDevice gpuCreateDevice(const char* path);

// Memory
// void* gpuMalloc(GpuDevice device, size_t bytes, MEMORY memory);
void* gpuMalloc(GpuDevice device, size_t bytes, size_t align, MEMORY memory);
void gpuFree(GpuDevice device, void *ptr);
void* gpuHostToDevicePointer(GpuDevice device, void *ptr);

// Textures
GpuTextureSizeAlign gpuTextureSizeAlign(GpuTextureDesc desc);
GpuTextureLayout gpuTextureLayout(GpuTexture texture);
GpuTexture gpuCreateTexture(GpuTextureDesc desc, void* ptrGpu);
GpuTexture gpuCreateTextureImported(GpuDevice device, GpuTextureDesc desc, int fd);
void* gpuTextureRead(GpuDevice device, GpuTexture texture);
GpuTextureDescriptor gpuTextureViewDescriptor(GpuTexture texture, GpuViewDesc desc);
GpuTextureDescriptor gpuRWTextureViewDescriptor(GpuTexture texture, GpuViewDesc desc);

// Pipelines
GpuPipeline gpuCreateComputePipeline(ByteSpan computeIR);
GpuPipeline gpuCreateGraphicsPipeline(GpuDevice device, ByteSpan vertexIR, ByteSpan pixelIR, GpuRasterDesc desc);
GpuPipeline gpuCreateGraphicsMeshletPipeline(ByteSpan meshletIR, ByteSpan pixelIR, GpuRasterDesc desc);
void gpuFreePipeline(GpuPipeline pipeline);

// State objects
GpuDepthStencilState gpuCreateDepthStencilState(GpuDepthStencilDesc desc);
GpuBlendState gpuCreateBlendState(GpuBlendDesc desc);
void gpuFreeDepthStencilState(GpuDepthStencilState state);
void gpuFreeBlendState(GpuBlendState state);

// Queue
GpuQueue gpuCreateQueue(GpuDevice device, QUEUE queue);
GpuCommandBuffer gpuStartCommandRecording(GpuQueue queue);
void gpuSubmitSimple(GpuQueue queue, GpuCommandBuffer* commandBuffers, size_t commandBuffersCount);
void gpuSubmit(GpuQueue queue, GpuCommandBuffer* commandBuffers, size_t commandBuffersCount, GpuSemaphore signalSemaphore, uint64_t signalSetValue);

// Semaphores
GpuSemaphore gpuCreateSemaphore(GpuDevice device, uint64_t initValue);
void gpuWaitSemaphore(GpuSemaphore sema, uint64_t value);
void gpuDestroySemaphore(GpuSemaphore sema);

// Commands
void gpuMemCpy(GpuCommandBuffer transferBuffer, void* destGpu, void* srcGpu);
void gpuCopyToTexture(GpuCommandBuffer transferBuffer, void* destGpu, void* srcGpu, GpuTexture texture);
void gpuCopyFromTexture(GpuCommandBuffer transferBuffer, void* destGpu, void* srcGpu, GpuTexture texture);

void gpuSetActiveTextureHeapPtr(GpuCommandBuffer cb, void *ptrGpu);

void gpuBarrier(GpuCommandBuffer cb, STAGE before, STAGE after, HAZARD_FLAGS hazards);
void gpuSignalAfter(GpuCommandBuffer cb, STAGE before, void *ptrGpu, uint64_t value, SIGNAL signal);
void gpuWaitBefore(GpuCommandBuffer cb, STAGE after, void *ptrGpu, uint64_t value, OP op, HAZARD_FLAGS hazards, uint64_t mask);

void gpuSetPipeline(GpuCommandBuffer cb, GpuPipeline pipeline);
void gpuSetDepthStencilState(GpuCommandBuffer cb, GpuDepthStencilState state);
void gpuSetBlendState(GpuCommandBuffer cb, GpuBlendState state); 

void gpuDispatch(GpuCommandBuffer cb, void* dataGpu, uint32x3 gridDimensions);
void gpuDispatchIndirect(GpuCommandBuffer cb, void* dataGpu, void* gridDimensionsGpu);

void gpuBeginRenderPass(GpuCommandBuffer cb, GpuRenderPassDesc desc);
void gpuEndRenderPass(GpuCommandBuffer cb);

void gpuDraw(GpuCommandBuffer cb, void* vertexDataGpu, void* pixelDataGpu, uint32_t vertex_count, uint32_t instanceCount);
void gpuDrawIndexed(GpuCommandBuffer cb, void* vertexDataGpu, void* pixelDataGpu, void* indicesGpu, uint32_t indexCount, uint32_t instanceCount);
void gpuDrawIndexedIndirect(GpuCommandBuffer cb, void* vertexDataGpu, void* pixelDataGpu, void* indicesGpu, void* argsGpu);
void gpuDrawIndexedIndirectMulti(GpuCommandBuffer cb, void* dataVxGpu, uint32_t vxStride, void* dataPxGpu, uint32_t pxStride, void* argsGpu, void* drawCountGpu);

void gpuDrawMeshlets(GpuCommandBuffer cb, void* meshletDataGpu, void* pixelDataGpu, uint32x3 dim);
void gpuDrawMeshletsIndirect(GpuCommandBuffer cb, void* meshletDataGpu, void* pixelDataGpu, void *dimGpu);

