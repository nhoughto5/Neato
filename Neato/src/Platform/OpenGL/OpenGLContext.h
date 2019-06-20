#pragma once
#include "Neato/Renderer/GraphicsContext.h"
struct GLFWwindow;
namespace Neato {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:

		GLFWwindow* m_WindowHandle;
	};
}
