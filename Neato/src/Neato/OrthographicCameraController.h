#pragma once
#include "Neato/Renderer/OrthographicCamera.h"
#include "Neato/Core/TimeStep.h"
#include "Neato/Events/ApplicationEvent.h"
#include "Neato/Events/MouseEvent.h"

namespace Neato {
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false); // aspectRatio * 2 units

        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
        float GetZoomLevel() { return m_ZoomLevel; }
    private:

        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;

        bool m_Rotation;

        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraSpeed = 5.0f, m_CameraRotation = 0.0f, m_CameraRotationSpeed = 180.0f;

        OrthographicCamera m_Camera;
    };
}


