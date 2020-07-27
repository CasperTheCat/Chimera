#pragma once
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <d3d11_4.h>
#include <memory>

class DXRenderer 
{
	//std::vector<uint8_t> pVertexBuffers;
 //   HMENU     m_hMenu;
 //   RECT      m_rc;
 //   HWND      m_hWnd;
 //   HINSTANCE m_hInstance;
 //   std::wstring m_windowClassName;
private:

    ////-----------------------------------------------------------------------------
    //// Direct3D device
    ////-----------------------------------------------------------------------------
    //Microsoft::WRL::ComPtr<ID3D11Device>        m_pd3dDevice;
    //Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dDeviceContext; // immediate context
    //Microsoft::WRL::ComPtr<IDXGISwapChain>      m_pDXGISwapChain;


    ////-----------------------------------------------------------------------------
    //// DXGI swap chain device resources
    ////-----------------------------------------------------------------------------
    //Microsoft::WRL::ComPtr < ID3D11Texture2D>        m_pBackBuffer;
    //Microsoft::WRL::ComPtr < ID3D11RenderTargetView> m_pRenderTarget;


    ////-----------------------------------------------------------------------------
    //// Direct3D device resources for the depth stencil
    ////-----------------------------------------------------------------------------
    //Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_pDepthStencil;
    //Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;


    ////-----------------------------------------------------------------------------
    //// Direct3D device metadata and device resource metadata
    ////-----------------------------------------------------------------------------
    //D3D_FEATURE_LEVEL       m_featureLevel;
    //D3D11_TEXTURE2D_DESC    m_bbDesc;
    //D3D11_VIEWPORT          m_viewport;

public:
	DXRenderer();
	~DXRenderer();


	void SetVertexShader(std::vector<uint8_t> &&pBytecode);
	void AddVertexBuffer(std::vector<uint8_t>& pBuffer);
	void AddConstVertexBuffer(std::vector<uint8_t>& pBuffer);
	void AddSRVBuffer(std::vector<uint8_t>& pBuffer);

};