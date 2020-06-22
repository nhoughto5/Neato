#pragma once
#include "glm/glm.hpp"

namespace Neato {
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera();

        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3& const getPosition();
        const float const getRotation();
        void SetPosition(const glm::vec3& position);
        void SetRotation(float rot);

        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionViewMatrix() const;
    private:
        void RecalculateViewMatrix();

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionViewMatrix;

        glm::vec3 m_Position;
        float m_Rotation = 0.0f;
    };
}


