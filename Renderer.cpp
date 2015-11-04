#include "pch.h"
#include "Renderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

Renderer::Renderer() {}

void Renderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();
}

void Renderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();

	//arrowTexture	// Create the transition screen
	//	ID3D11ShaderResourceView* m_backgroundTexture = nullptr;
	//CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/nightsky.dds", nullptr, &m_backgroundTexture, MAXSIZE_T);
	//float scaleX = m_movementBounds.Width / 1024;
	//float scaleY = m_movementBounds.Height / 1138;
	//scale = scaleX > scaleY ? scaleX : scaleY;
	//background = new Sprite(m_backgroundTexture, XMFLOAT2(1024, 1138),	// Magic numbers for now...
	//	XMFLOAT2(0, 0), &m_movementBounds, scale, 6);

	//vectorBoard = new VectorBoard();
}

void Renderer::Update(float timeTotal, float timeDelta)
{

}

void Renderer::Render()
{
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
	m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(),
		midnightBlue
		);
}