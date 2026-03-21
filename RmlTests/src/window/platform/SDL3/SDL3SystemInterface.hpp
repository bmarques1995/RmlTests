#pragma once

#include <RmlUi/Core/SystemInterface.h>
#include <SDL3/SDL.h>
#include <unordered_map>
#include "Window.hpp"
#include <RmlUi/Core/Input.h>

namespace RmlTests
{
	class SDL3SystemInterface : public Rml::SystemInterface
	{
	public:
		
		SDL3SystemInterface(std::shared_ptr<Window> window);
		~SDL3SystemInterface();

		virtual double GetElapsedTime() override;
		virtual void SetMouseCursor(const Rml::String& cursor_name) override;

		virtual void SetClipboardText(const Rml::String& text) override;
		virtual void GetClipboardText(Rml::String& text) override;

		virtual void ActivateKeyboard(Rml::Vector2f caret_position, float line_height) override;
		virtual void DeactivateKeyboard() override;
	private:
		
		std::shared_ptr<Window> m_Window;
	};

	int GetKeyModifierState();
	bool InputEventHandler(Rml::Context* context, SDL_Window* window, SDL_Event& ev);
	Rml::Input::KeyIdentifier ConvertKey(int sdlkey);
	int ConvertMouseButton(int button);
	int GetKeyModifierState();
	Rml::TouchList TouchEventToTouchList(SDL_Event& ev, Rml::Context* context, SDL_FingerID finger_id);
}