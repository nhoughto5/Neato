#include "NeatoPCH.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Neato/Renderer/Renderer.h"

namespace Neato {
    Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filePath);
		}
		return nullptr;
	}

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		return nullptr;
	}

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& s) {
        NEATO_CORE_ASSERT(!Exists(name), "Shader already exists");
        m_Shaders[name] = s;
    }

    void ShaderLibrary::Add(const Ref<Shader>& s) {
        auto& name = s->GetName();
        Add(name, s);
    }

    Neato::Ref<Neato::Shader> ShaderLibrary::Load(const std::string& filePath) {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Neato::Ref<Neato::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath) {
        auto shader = Shader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Neato::Ref<Neato::Shader> ShaderLibrary::Get(const std::string& name) {
        NEATO_CORE_ASSERT(Exists(name), "Shader not found");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}

