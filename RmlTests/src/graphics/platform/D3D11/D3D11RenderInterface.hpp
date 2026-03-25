#pragma once

#include <RmlUi/Core/RenderInterface.h>
#include "D3D11Context.hpp"

namespace RmlTests
{	
	struct d3d11_geometry_data
	{
		ComPtr<ID3D11Buffer> VBO;
		ComPtr<ID3D11Buffer> IBO;
		uint32_t ShaderIndex;
		uint32_t NumberOfIndices;
	};

	struct d3d11_shader_info
	{
		ComPtr<ID3DBlob> VSBlob;
		ComPtr<ID3D11VertexShader> VSO;
		ComPtr<ID3DBlob> PSBlob;
		ComPtr<ID3D11PixelShader> PSO;
		ComPtr<ID3D11InputLayout> IL;
		uint32_t Stride;
	};

	class D3D11RenderInterface : public Rml::RenderInterface
	{
	public:
		D3D11RenderInterface(D3D11RenderControllers* startupData);
		~D3D11RenderInterface();

		void CompileBaseShaders();

		Rml::CompiledGeometryHandle CompileGeometry(Rml::Span<const Rml::Vertex> vertices, Rml::Span<const int> indices) override;
		void RenderGeometry(Rml::CompiledGeometryHandle geometryHandle, Rml::Vector2f translation, Rml::TextureHandle texture) override;
		void ReleaseGeometry(Rml::CompiledGeometryHandle geometryHandle) override;
		Rml::TextureHandle LoadTexture(Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
		Rml::TextureHandle GenerateTexture(Rml::Span<const byte> source, Rml::Vector2i source_dimensions) override;
		void ReleaseTexture(Rml::TextureHandle texture) override;
		void EnableScissorRegion(bool enable) override;
		void SetScissorRegion(Rml::Rectanglei region) override;

		// Called by RmlUi when it wants to compile a new shader.
		Rml::CompiledShaderHandle CompileShader(const Rml::String& name, const Rml::Dictionary& parameters) override;

		// Called by RmlUi when it wants to render geometry using the given shader.
		void RenderShader(Rml::CompiledShaderHandle shader,
			Rml::CompiledGeometryHandle geometry,
			Rml::Vector2f translation,
			Rml::TextureHandle texture) override;

		// Called by RmlUi when it no longer needs a previously compiled shader.
		void ReleaseShader(Rml::CompiledShaderHandle shader) override;

	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
	};
}