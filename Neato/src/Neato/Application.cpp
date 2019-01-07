#include "Application.h"
#include "Log.h"
#include "Neato/Events/ApplicationEvent.h"

namespace Neato {
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run() {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            NEATO_CORE_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput))
        {
            NEATO_CORE_TRACE(e);
        }
        while (true);
    }
}

