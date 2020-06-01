#pragma once
// For use by applications

#include "Neato/Application.h"
#include <stdio.h>
#include "Neato/Input.h"
#include "Neato/Log.h"
#include "Neato/Layer.h"
#include "Neato/MouseButtonCodes.h"
#include "Neato/KeyCodes.h"
#include "Neato/ImGui/ImGuiLayer.h"
#include "Neato/Events/KeyEvent.h"
#include "Neato/Core/TimeStep.h"

// ===== Renderer ==== //
#include "Neato/Renderer/Renderer.h"
#include "Neato/Renderer/RenderCommand.h"
#include "Neato/Renderer/Buffer.h"
#include "Neato/Renderer/Shader.h"
#include "Neato/Renderer/Texture.h"
#include "Neato/Renderer/VertexArray.h"
#include "Neato/Renderer/OrthographicCamera.h"

// ===== Entry Point ==== //
#include "Neato/EntryPoint.h"