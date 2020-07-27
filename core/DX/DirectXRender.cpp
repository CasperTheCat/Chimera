#include "DirectXRender.h"
#include <string>

DXRenderer::DXRenderer()
{
    //hr = D3D11CreateDeviceAndSwapChain(
    //    nullptr,
    //    D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
    //    nullptr,
    //    deviceFlags,
    //    levels,
    //    ARRAYSIZE(levels),
    //    D3D11_SDK_VERSION,
    //    &desc,
    //    swapChain.GetAddressOf(),
    //    device.GetAddressOf(),
    //    &m_featureLevel,
    //    context.GetAddressOf()
    //);
}

DXRenderer::~DXRenderer()
{
	
}

void DXRenderer::SetVertexShader(std::vector<uint8_t>&& pBytecode)
{
}
