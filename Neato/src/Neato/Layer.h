#pragma once
#include "Neato/Core.h"
#include "Neato/Events/Event.h"
#include "Neato/Core/TimeStep.h"
//#include "imgui.h"
namespace Neato {
	class NEATO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(TimeStep ts);
		virtual void OnEvent(Event& event);
		virtual void OnImGuiRender();
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}