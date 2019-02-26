#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Neato/Events/ApplicationEvent.h"
#include "Neato/LayerStack.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"

namespace Neato {
    class NEATO_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}


