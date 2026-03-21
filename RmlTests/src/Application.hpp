#pragma once

#include <iostream>
#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include "GraphicsContext.hpp"
#include "Window.hpp"
#include <memory>

namespace RmlTests
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void ProcessQuit();
		void ProcessResize(uint32_t width, uint32_t height);
	
		static Application* GetInstance();
		Rml::Context* GetRmlContext();
	private:
		bool m_Running;

		static void EnableSingleton(Application* app);
		static Application* s_Instance;

		std::shared_ptr<Window> m_Window;
		Rml::Context* m_RmlContext;
		RmlTests::GRAPHICS_API m_API;
		//RmlTests::GRAPHICS_API m_API = RmlTests::GRAPHICS_API::D3D11;
		std::shared_ptr<RmlTests::GraphicsContext> m_Context;

		std::shared_ptr<Rml::RenderInterface> m_RMLRenderInterface;
		std::shared_ptr<Rml::SystemInterface> m_RMLSystemInterface;
	};
}
