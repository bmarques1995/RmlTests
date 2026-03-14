#include "Application.hpp"

#ifdef WIN32
#include <windows.h>
#endif

RmlTests::Application* RmlTests::Application::s_Instance = nullptr;

RmlTests::Application::Application() :
    m_API(RmlTests::GRAPHICS_API::D3D11),
    m_Running(true)
{
    if (s_Instance != nullptr)
    {
        return;
    }
    EnableSingleton(this);


    m_Window.reset(RmlTests::Window::Create(1280, 720, "SDL3 + D3D11"));
    m_Context.reset(RmlTests::GraphicsContext::Create(m_API, std::any_cast<HWND>(m_Window->GetNativePointer()), m_Window->GetWidth(), m_Window->GetHeight()));
    m_Context->SetClearColor(.0f, .5f, .25f, 1.0f);
}

RmlTests::Application::~Application()
{
    m_Context.reset();
    m_Window.reset();
}

void RmlTests::Application::Run()
{
	while (m_Running)
	{
        m_Window->Update();
        m_Context->ReceiveCommands();
        m_Context->DispatchCommands();
        m_Context->Present();
	}
}

void RmlTests::Application::ProcessQuit()
{
	m_Running = false;
}

void RmlTests::Application::ProcessResize(uint32_t width, uint32_t height)
{
    m_Context->OnResize(width, height);
}

RmlTests::Application* RmlTests::Application::GetInstance()
{
    return s_Instance;
}

void RmlTests::Application::EnableSingleton(Application* app)
{
    if(s_Instance == nullptr)
        s_Instance = app;
}
