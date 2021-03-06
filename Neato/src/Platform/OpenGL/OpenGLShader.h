#pragma once
#include "glm/glm.hpp"
#include "Neato/Renderer/Shader.h"

// TODO: Remove! 
typedef unsigned int GLenum;

namespace Neato {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
        virtual const std::string& GetName() const override { return m_Name; };
		
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string ReadFile(const std::string& filePath);
		uint32_t mRendererID;
        std::string m_Name;
	};
}

