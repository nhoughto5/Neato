#pragma once


#ifdef NEATO_PLATFORM_WINDOWS
extern Neato::Application* Neato::CreateApplication();
int main(int argc, char** argv) {

    auto app = Neato::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif //NEATO_PLATFORM_WINDOWS