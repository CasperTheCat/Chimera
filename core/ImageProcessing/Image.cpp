#include "Image.h"
#include <fstream>
#include "ImageConverters.h"

std::vector<float> ProcessImage(
    std::vector<uint8_t>& pData,
    FTextureInfo& stFormat
)
{
	// First, what type of data is this?
	//std::vector<float> outVec;

	auto asFormat = static_cast<EDXGIFormat>(stFormat.uFormat);

	// Switch...
	switch (asFormat)
	{
    case EDXGIFormat::DXGI_FORMAT_UNKNOWN:
        // What happened here?
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32B32A32_TYPELESS:
        // Do nothing, it's 1. Typeless, 2. RGBA_T32 anyway
        return Raw<uint8_t, float>(pData);
    case EDXGIFormat::DXGI_FORMAT_R32G32B32A32_FLOAT:
        return Raw<uint8_t, float>(pData);
    case EDXGIFormat::DXGI_FORMAT_R32G32B32A32_UINT:
        return C4_U32ToC4_F32<uint8_t>(pData, stFormat);
    case EDXGIFormat::DXGI_FORMAT_R32G32B32A32_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32B32_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32B32_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32B32_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32B32_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16B16A16_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16B16A16_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16B16A16_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16B16A16_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16B16A16_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16B16A16_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G32_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32G8X24_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R10G10B10A2_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R10G10B10A2_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R10G10B10A2_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R11G11B10_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8B8A8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8B8A8_UNORM:
    case EDXGIFormat::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case EDXGIFormat::DXGI_FORMAT_R8G8B8A8_UINT:
        return C4_U8_F32(pData, stFormat);
    case EDXGIFormat::DXGI_FORMAT_R8G8B8A8_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8B8A8_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16G16_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_D32_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R32_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R24G8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_D24_UNORM_S8_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16_FLOAT:
        break;
    case EDXGIFormat::DXGI_FORMAT_D16_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R16_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8_UINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8_SINT:
        break;
    case EDXGIFormat::DXGI_FORMAT_A8_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R1_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        break;
    case EDXGIFormat::DXGI_FORMAT_R8G8_B8G8_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_G8R8_G8B8_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC1_TYPELESS:
    case EDXGIFormat::DXGI_FORMAT_BC1_UNORM:
    case EDXGIFormat::DXGI_FORMAT_BC1_UNORM_SRGB:
        return C4_BC1ToF32(pData, stFormat);
        break;
    case EDXGIFormat::DXGI_FORMAT_BC2_TYPELESS:
    case EDXGIFormat::DXGI_FORMAT_BC2_UNORM:
    case EDXGIFormat::DXGI_FORMAT_BC2_UNORM_SRGB:
        return C4_BCXToF32(pData, stFormat);
        break;
    case EDXGIFormat::DXGI_FORMAT_BC3_TYPELESS:
    case EDXGIFormat::DXGI_FORMAT_BC3_UNORM:
    case EDXGIFormat::DXGI_FORMAT_BC3_UNORM_SRGB:
        return C4_BCXToF32(pData, stFormat);
    case EDXGIFormat::DXGI_FORMAT_BC4_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC4_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC4_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC5_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC5_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC5_SNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_B5G6R5_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_B5G5R5A1_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_B8G8R8A8_UNORM:
    case EDXGIFormat::DXGI_FORMAT_B8G8R8X8_UNORM:
        return C4_U8_F32(pData, stFormat);
        return BGRA_TToRGBA_T<float>(C4_U8_F32(pData, stFormat), stFormat);
        break;
    case EDXGIFormat::DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_B8G8R8A8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        break;
    case EDXGIFormat::DXGI_FORMAT_B8G8R8X8_TYPELESS:
        break;
    case EDXGIFormat::DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        break;
    case EDXGIFormat::DXGI_FORMAT_BC6H_TYPELESS:
    case EDXGIFormat::DXGI_FORMAT_BC6H_UF16:
    case EDXGIFormat::DXGI_FORMAT_BC6H_SF16:
        return C4_BCXToF32(pData, stFormat);
        break;
    case EDXGIFormat::DXGI_FORMAT_BC7_TYPELESS:
    case EDXGIFormat::DXGI_FORMAT_BC7_UNORM:
    case EDXGIFormat::DXGI_FORMAT_BC7_UNORM_SRGB:
        return C4_BCXToF32(pData, stFormat);
        break;
    case EDXGIFormat::DXGI_FORMAT_AYUV:
        break;
    case EDXGIFormat::DXGI_FORMAT_Y410:
        break;
    case EDXGIFormat::DXGI_FORMAT_Y416:
        break;
    case EDXGIFormat::DXGI_FORMAT_NV12:
        break;
    case EDXGIFormat::DXGI_FORMAT_P010:
        break;
    case EDXGIFormat::DXGI_FORMAT_P016:
        break;
    case EDXGIFormat::DXGI_FORMAT_420_OPAQUE:
        break;
    case EDXGIFormat::DXGI_FORMAT_YUY2:
        break;
    case EDXGIFormat::DXGI_FORMAT_Y210:
        break;
    case EDXGIFormat::DXGI_FORMAT_Y216:
        break;
    case EDXGIFormat::DXGI_FORMAT_NV11:
        break;
    case EDXGIFormat::DXGI_FORMAT_AI44:
        break;
    case EDXGIFormat::DXGI_FORMAT_IA44:
        break;
    case EDXGIFormat::DXGI_FORMAT_P8:
        break;
    case EDXGIFormat::DXGI_FORMAT_A8P8:
        break;
    case EDXGIFormat::DXGI_FORMAT_B4G4R4A4_UNORM:
        break;
    case EDXGIFormat::DXGI_FORMAT_P208:
        break;
    case EDXGIFormat::DXGI_FORMAT_V208:
        break;
    case EDXGIFormat::DXGI_FORMAT_V408:
        break;
    case EDXGIFormat::DXGI_FORMAT_FORCE_UINT:
        break;
    default:
        break;
	}

    return std::vector<float>();// C4_AnyToF32(pData, stFormat);
}

void SerialiseImage(std::vector<float>& pData, FTextureInfo& stFormat, std::string&& strFormat)
{
    if (pData.size() == 0)
    {
        return;
    }

    for(uint32_t i = 0; i < stFormat.uCount; ++i)
    {
        // Write the format to disk
        std::ofstream fileWrite(strFormat + "." + std::to_string(i) + ".cif", std::ios::binary | std::ios::ate);

        fileWrite.write(
            reinterpret_cast<char*>(&stFormat.uWidth),
            sizeof(uint32_t)
        );

        fileWrite.write(
            reinterpret_cast<char*>(&stFormat.uHeight),
            sizeof(uint32_t)
        );

        fileWrite.write(
            reinterpret_cast<char*>(&stFormat.uDepth),
            sizeof(uint32_t)
        );

        // Pointer manipulation
        // Images are RGBA_F32 in this buffer...
        auto basePtr = reinterpret_cast<char*>(pData.data());
        auto offset = sizeof(float) * MinOne(stFormat.uWidth) * MinOne(stFormat.uHeight) * MinOne(stFormat.uDepth) * 4;

        if (offset * i > pData.size()) return;


        fileWrite.write(
            &basePtr[i * offset],
            offset
        );

        // Close
        fileWrite.close();
    }
}
