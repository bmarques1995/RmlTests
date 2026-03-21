#pragma once

#include <RmlUi/Core/RenderInterface.h>
#include "D3D11Context.hpp"

namespace RmlTests
{	
	class D3D11RenderInterface : public Rml::RenderInterface
	{
	public:
		D3D11RenderInterface(D3D11RenderControllers* startupData);
		~D3D11RenderInterface();

		Rml::CompiledGeometryHandle CompileGeometry(Rml::Span<const Rml::Vertex> vertices, Rml::Span<const int> indices) override;
		void RenderGeometry(Rml::CompiledGeometryHandle geometry, Rml::Vector2f translation, Rml::TextureHandle texture) override;
		void ReleaseGeometry(Rml::CompiledGeometryHandle geometry) override;
		Rml::TextureHandle LoadTexture(Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
		Rml::TextureHandle GenerateTexture(Rml::Span<const byte> source, Rml::Vector2i source_dimensions) override;
		void ReleaseTexture(Rml::TextureHandle texture) override;
		void EnableScissorRegion(bool enable) override;
		void SetScissorRegion(Rml::Rectanglei region) override;

	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
	};
}