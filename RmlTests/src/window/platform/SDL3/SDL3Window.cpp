#include "SDL3Window.hpp"
#include <cstdlib>
#ifdef WIN32
#include <windows.h>
#endif

#include "Application.hpp"
#include <cassert>
#include "SDL3SystemInterface.hpp"

uint32_t RmlTests::SDL3Window::s_SDLInstances = 0;
std::unordered_map<std::string, SDL_Cursor*> RmlTests::SDL3Window::s_ValidCursors;

void RmlTests::SDL3Window::InitSDL()
{
    if (s_SDLInstances == 0)
    {
        bool code = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
        assert(code);
        InitCursorMap();
    }
    s_SDLInstances++;
}

void RmlTests::SDL3Window::ShutdownSDL()
{
    if (s_SDLInstances <= 1)
    {
        ShutdownCursorMap();
        SDL_Quit();
    }
    s_SDLInstances--;
}

void RmlTests::SDL3Window::InitCursorMap()
{
    s_ValidCursors =
    {
        {"arrow", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT)},
        {"move", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_MOVE)},
        {"pointer", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER)},
        {"resize", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NWSE_RESIZE)},
        {"cross", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR)},
        {"text", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT)},
        {"unavailable", SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NOT_ALLOWED)}
    };
}

void RmlTests::SDL3Window::ShutdownCursorMap()
{
    for (auto& pair : s_ValidCursors) {
        SDL_DestroyCursor(pair.second); // free the cursor
        pair.second = nullptr; // cannot do this because cursors is const
    }
}

RmlTests::SDL3Window::SDL3Window(uint32_t width, uint32_t height, std::string title) : 
    RmlTests::Window(width, height, title)
{
    InitSDL();
    m_Window = SDL_CreateWindow(
        m_WindowTitle.c_str(),
        m_Width,
        m_Height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN
    );
    
    SDL_ShowWindow(m_Window);
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

std::any RmlTests::SDL3Window::GetWindowPointer()
{
    return m_Window;
}

void RmlTests::SDL3Window::ModifyCursor(const std::string& cursorName)
{
    SDL_Cursor* cursor = nullptr;

    auto it = s_ValidCursors.find(cursorName);
    if (it != s_ValidCursors.end())
        cursor = it->second;

    if (cursor)
        SDL_SetCursor(cursor);
}

void RmlTests::SDL3Window::EventLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        auto app = Application::GetInstance();
        auto rmlContext = app->GetRmlContext();
        InputEventHandler(rmlContext, m_Window, event);
        if (event.type == SDL_EVENT_QUIT)
            app->ProcessQuit();
        if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            int w, h;
            SDL_GetWindowSizeInPixels(m_Window, &w, &h);
            m_Width = w;
            m_Height = h;
            app->ProcessResize(m_Width, m_Height);
        }   
    }
}
