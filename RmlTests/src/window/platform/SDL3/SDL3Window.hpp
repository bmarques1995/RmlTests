#pragma once

#include "Window.hpp"
#include <SDL3/SDL.h>
#include <unordered_map>

namespace RmlTests
{
	class SDL3Window final : public Window
	{
	public:	
		SDL3Window(uint32_t width, uint32_t height, std::string title);
		~SDL3Window();

		void Update() override;
		std::any GetNativePointer() override;
		std::any GetWindowPointer() override;
		void ModifyCursor(const std::string& cursorName) override;

	private:
		void EventLoop();

		static void InitSDL();
		static void ShutdownSDL();

		static void InitCursorMap();
		static void ShutdownCursorMap();
		
		static uint32_t s_SDLInstances;
		static std::unordered_map<std::string, SDL_Cursor*> s_ValidCursors;
		SDL_Window* m_Window;
	};
}
