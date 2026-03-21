#pragma once

#include <any>
#include <cstdint>
#include <string>
#include <RmlUi/Core/SystemInterface.h>

namespace RmlTests
{
	class Window
	{
	public:
		Window();
		Window(uint32_t width, uint32_t height, std::string title);

		virtual ~Window();

		virtual void Update() = 0;
		//For Example HWND 
		virtual std::any GetNativePointer() = 0;
		//For Example SDL_Window* 
		virtual std::any GetWindowPointer() = 0;
		virtual void ModifyCursor(const std::string& cursorName) = 0;

		static Window* Create();
		static Window* Create(uint32_t width, uint32_t height, std::string title);

		static Rml::SystemInterface* CreateRMLSystemInterface(std::shared_ptr<Window> window);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

	protected:
		std::string m_WindowTitle;
		uint32_t m_Width;
		uint32_t m_Height;
	};
}
