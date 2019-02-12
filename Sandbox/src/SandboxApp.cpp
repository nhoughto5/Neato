#include <Neato.h>
#include <stdio.h>

class ExampleLayer : public Neato::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//NEATO_INFO("ExampleLayer::Update");
	}

	void OnEvent(Neato::Event& event) override
	{
		NEATO_TRACE("{0}", event);
	}
};


class Sandbox : public Neato::Application {
public:
    Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Neato::ImGuiLayer());
    }

    ~Sandbox() {

    }
};

Neato::Application* Neato::CreateApplication()
{
    return new Sandbox();
}