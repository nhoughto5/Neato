#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Neato {
    class NEATO_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in client
    Application* CreateApplication();
}


