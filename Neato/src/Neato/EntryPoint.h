#pragma once
#ifdef NEATO_PLATFORM_WINDOWS
extern Neato::Application* Neato::CreateApplication();
int main(int argc, char** argv) {
    Neato::Log::Init();
    NEATO_CORE_ERROR("Initialized Log");
    int a = 6;
    NEATO_TRACE("Initialized var={0}", 6);
    auto app = Neato::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif //NEATO_PLATFORM_WINDOWS