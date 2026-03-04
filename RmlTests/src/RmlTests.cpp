// RmlTests.cpp: define o ponto de entrada para o aplicativo.
//

#include "RmlTests.hpp"
#include <SDL3/SDL.h>
#include <glad/gl.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return -1;
    }

    // Request OpenGL 4.5 Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *m_Window = SDL_CreateWindow(
        "SDL3 + glad2",
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!m_Window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(m_Window);
    if (!gl_context) {
        printf("GL context creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return -1;
    }

    // ---- glad2 loading ----
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        printf("Failed to initialize glad2\n");
        SDL_GL_DestroyContext(gl_context);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return -1;
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        glViewport(0, 0, 800, 600);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(m_Window);
        SDL_GL_SetSwapInterval(1);
    }

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();

    return 0;
}
