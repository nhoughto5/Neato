#pragma once
#include "Neato/Layer.h"
#include "Neato/Core.h"
namespace Neato {
	class NEATO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void Begin();
		void End();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	private:

		float m_Time = 0.0f;
	};
}