#pragma once

#include <cstdint>
#include <any>

namespace RmlTests
{
    enum class GRAPHICS_API {
        D3D11
    };

    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void ReceiveCommands() = 0;
        virtual void DispatchCommands() = 0;
        virtual void Draw(uint32_t elements) = 0;
        virtual void Present() = 0;

        virtual void OnResize(uint32_t width, uint32_t height) = 0;

        static GraphicsContext* Create(GRAPHICS_API api, std::any window, uint32_t width, uint32_t height);
    };
}