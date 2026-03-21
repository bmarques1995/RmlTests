#include "D3D11RenderInterface.hpp"

RmlTests::D3D11RenderInterface::D3D11RenderInterface(D3D11RenderControllers* startupData) :
	m_Device(startupData->m_Device), m_DeviceContext(startupData->m_DeviceContext)
{
}

RmlTests::D3D11RenderInterface::~D3D11RenderInterface()
{
	m_Device = nullptr;
	m_DeviceContext = nullptr;
}

Rml::CompiledGeometryHandle RmlTests::D3D11RenderInterface::CompileGeometry(Rml::Span<const Rml::Vertex> vertices, Rml::Span<const int> indices)
{
	return Rml::CompiledGeometryHandle();
}

void RmlTests::D3D11RenderInterface::RenderGeometry(Rml::CompiledGeometryHandle geometry, Rml::Vector2f translation, Rml::TextureHandle texture)
{
}

void RmlTests::D3D11RenderInterface::ReleaseGeometry(Rml::CompiledGeometryHandle geometry)
{
}

Rml::TextureHandle RmlTests::D3D11RenderInterface::LoadTexture(Rml::Vector2i& texture_dimensions, const Rml::String& source)
{
	return Rml::TextureHandle();
}

Rml::TextureHandle RmlTests::D3D11RenderInterface::GenerateTexture(Rml::Span<const byte> source, Rml::Vector2i source_dimensions)
{
	return Rml::TextureHandle();
}

void RmlTests::D3D11RenderInterface::ReleaseTexture(Rml::TextureHandle texture)
{
}

void RmlTests::D3D11RenderInterface::EnableScissorRegion(bool enable)
{
}

void RmlTests::D3D11RenderInterface::SetScissorRegion(Rml::Rectanglei region)
{
}
