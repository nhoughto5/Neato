#pragma once
#include "Neato/Layer.h"
#include "Neato/Events/MouseEvent.h"
#include "Neato/Events/KeyEvent.h"
#include "Neato/Events/ApplicationEvent.h"
namespace Neato {
	class NEATO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		static void SetClipboardText(void* user_data, const char* text);
		static const char* GetClipboardText(void* user_data);
		float m_Time = 0.0f;
	};
}