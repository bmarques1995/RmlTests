#pragma once

#include "Window.hpp"
#include <SDL3/SDL.h>

namespace RmlTests
{
	class SDL3Window final : public Window
	{
	public:
	
		static void InitSDL();
		static void ShutdownSDL();
		
		SDL3Window(uint32_t width, uint32_t height, std::string title);
		~SDL3Window();

		virtual void Update() override;
		virtual std::any GetNativePointer() override;

	private:
		void EventLoop();
		
		static uint32_t s_SDLInstances;
		SDL_Window* m_Window;
	};
}
