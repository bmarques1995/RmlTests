#include "GraphicsContext.hpp"

#include "D3D11/D3D11Context.hpp"
#include "D3D11/D3D11RenderInterface.hpp"

RmlTests::GraphicsContext* RmlTests::GraphicsContext::Create(GRAPHICS_API api, std::any window, uint32_t width, uint32_t height)
{
    switch (api)
    {
        case GRAPHICS_API::D3D11: return new D3D11Context(std::any_cast<HWND>(window), width, height);
        default: return nullptr;
    }
}

Rml::RenderInterface* RmlTests::GraphicsContext::CreateRMLRenderInterface(GRAPHICS_API api, std::any startupData)
{
    switch (api)
    {
        case GRAPHICS_API::D3D11:
        {
            D3D11RenderControllers controllers = std::any_cast<D3D11RenderControllers>(startupData);
            return new D3D11RenderInterface(&controllers); 
        }
        default: return nullptr;
    }
}
