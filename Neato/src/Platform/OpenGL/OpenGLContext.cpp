#include "NeatoPCH.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neato {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		NEATO_CORE_ASSERT(windowHandle, "Window handle is null");
	}


	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NEATO_CORE_ASSERT(status, "Failed to init Glad");

		NEATO_CORE_INFO("OpenGL Info");
		NEATO_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		NEATO_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		NEATO_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

