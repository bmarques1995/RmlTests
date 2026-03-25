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
	auto* p_geometry_handle = new d3d11_geometry_data{};

	D3D11_BUFFER_DESC vboDesc = {};

	vboDesc.Usage = D3D11_USAGE_DEFAULT; // matches GL_STATIC_DRAW
	vboDesc.ByteWidth = sizeof(Rml::Vertex) * vertices.size();
	vboDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vboDesc.CPUAccessFlags = 0; // no CPU access
	vboDesc.MiscFlags = 0;
	vboDesc.StructureByteStride = sizeof(Rml::Vertex); // optional but good practice

	D3D11_SUBRESOURCE_DATA vboData = {};
	vboData.pSysMem = vertices.data();
	vboData.SysMemPitch = 0;
	vboData.SysMemSlicePitch = 0;

	m_Device->CreateBuffer(&vboDesc, &vboData, p_geometry_handle->VBO.GetAddressOf());

	D3D11_BUFFER_DESC iboDesc = {};

	iboDesc.Usage = D3D11_USAGE_DEFAULT;
	iboDesc.ByteWidth = sizeof(int) * indices.size();
	iboDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iboDesc.CPUAccessFlags = 0;
	iboDesc.MiscFlags = 0;
	iboDesc.StructureByteStride = sizeof(int);

	D3D11_SUBRESOURCE_DATA iboData = {};

	iboData.pSysMem = indices.data();
	iboData.SysMemPitch = 0;
	iboData.SysMemSlicePitch = 0;

	m_Device->CreateBuffer(&iboDesc, &iboData, p_geometry_handle->IBO.GetAddressOf());

	/*Can be modified*/
	p_geometry_handle->ShaderIndex = 0;
	p_geometry_handle->NumberOfIndices = indices.size();

	return Rml::CompiledGeometryHandle(p_geometry_handle);
}

void RmlTests::D3D11RenderInterface::RenderGeometry(Rml::CompiledGeometryHandle geometryHandle, Rml::Vector2f translation, Rml::TextureHandle texture)
{
	/*

	Gfx::CompiledGeometryData* geometry = (Gfx::CompiledGeometryData*)handle;

	if (texture == TexturePostprocess)
	{
		// Do nothing.
	}
	else if (texture)
	{
		UseProgram(ProgramId::Texture);
		SubmitTransformUniform(translation);
		if (texture != TextureEnableWithoutBinding)
			glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
	}
	else
	{
		UseProgram(ProgramId::Color);
		glBindTexture(GL_TEXTURE_2D, 0);
		SubmitTransformUniform(translation);
	}

	glBindVertexArray(geometry->vao);
	glDrawElements(GL_TRIANGLES, geometry->draw_count, GL_UNSIGNED_INT, (const GLvoid*)0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	Gfx::CheckGLError("RenderCompiledGeometry");

	*/
	
	/*
	d3d11_geometry_data* geometry = reinterpret_cast<d3d11_geometry_data*>(geometryHandle);
	m_DeviceContext->IASetVertexBuffers();
	m_DeviceContext->IASetIndexBuffer(geometry->IBO.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_DeviceContext->DrawIndexedInstanced(geometry->NumberOfIndices, 1, 0, 0, 0);
	*/
}

void RmlTests::D3D11RenderInterface::ReleaseGeometry(Rml::CompiledGeometryHandle geometryHandle)
{
	d3d11_geometry_data* geometry = reinterpret_cast<d3d11_geometry_data*>(geometryHandle);
	geometry->IBO->Release();
	geometry->VBO->Release();
	delete geometry;
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

Rml::CompiledShaderHandle RmlTests::D3D11RenderInterface::CompileShader(const Rml::String& name, const Rml::Dictionary& parameters)
{
	return Rml::CompiledShaderHandle();
}

void RmlTests::D3D11RenderInterface::RenderShader(Rml::CompiledShaderHandle shader, Rml::CompiledGeometryHandle geometry, Rml::Vector2f translation, Rml::TextureHandle texture)
{
}

void RmlTests::D3D11RenderInterface::ReleaseShader(Rml::CompiledShaderHandle shader)
{
}
