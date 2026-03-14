#include "Window.hpp"
#include "SDL3/SDL3Window.hpp"

RmlTests::Window::Window()
{
    m_Width = 1280;
    m_Height = 720;
    m_WindowTitle = "Generic title";
}

RmlTests::Window::Window(uint32_t width, uint32_t height, std::string title) :
    m_Width(width), m_Height(height), m_WindowTitle(title)
{
}

RmlTests::Window::~Window()
{
}

RmlTests::Window* RmlTests::Window::Create()
{
    return new SDL3Window(1280, 720, "Sample Window");
}

RmlTests::Window* RmlTests::Window::Create(uint32_t width, uint32_t height, std::string title)
{
    return new SDL3Window(width, height, title);
}

uint32_t RmlTests::Window::GetWidth() const
{
    return m_Width;
}

uint32_t RmlTests::Window::GetHeight() const
{
    return m_Height;
}
