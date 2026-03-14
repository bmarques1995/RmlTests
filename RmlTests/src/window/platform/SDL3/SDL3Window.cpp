#include "SDL3Window.hpp"
#include <cstdlib>
#ifdef WIN32
#include <windows.h>
#endif

#include "Application.hpp"

uint32_t RmlTests::SDL3Window::s_SDLInstances = 0;

void RmlTests::SDL3Window::InitSDL()
{
    if(s_SDLInstances == 0)
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD ) < 0) {
            printf("SDL Init failed: %s\n", SDL_GetError());
            exit(65);
        }
    s_SDLInstances++;
}

void RmlTests::SDL3Window::ShutdownSDL()
{
    if (s_SDLInstances <= 1)
        SDL_Quit();
    s_SDLInstances--;
}

RmlTests::SDL3Window::SDL3Window(uint32_t width, uint32_t height, std::string title) : 
    RmlTests::Window()
{
    InitSDL();
    m_Window = SDL_CreateWindow(
        m_WindowTitle.c_str(),
        m_Width,
        m_Height,
        SDL_WINDOW_RESIZABLE
    );
}

RmlTests::SDL3Window::~SDL3Window()
{
    SDL_DestroyWindow(m_Window);
    ShutdownSDL();
}

void RmlTests::SDL3Window::Update()
{
    EventLoop();
}

std::any RmlTests::SDL3Window::GetNativePointer()
{
#ifdef WIN32
    SDL_PropertiesID props = SDL_GetWindowProperties(m_Window);
    HWND hwnd = (HWND)SDL_GetPointerProperty(
        props,
        SDL_PROP_WINDOW_WIN32_HWND_POINTER,
        NULL
    );
    return hwnd;
#else
    return nullptr;
#endif
}

void RmlTests::SDL3Window::EventLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        auto app = Application::GetInstance();
        if (event.type == SDL_EVENT_QUIT)
            app->ProcessQuit();
        if (event.type == SDL_EVENT_WINDOW_RESIZED && event.window.windowID == SDL_GetWindowID(m_Window))
        {
            m_Width = event.window.data1;
            m_Height = event.window.data2;
            app->ProcessResize(event.window.data1, event.window.data2);
        }   
    }
}
