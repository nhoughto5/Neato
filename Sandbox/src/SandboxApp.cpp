#include <Neato.h>
#include <stdio.h>

class Sandbox : public Neato::Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

Neato::Application* Neato::CreateApplication()
{
    return new Sandbox();
}