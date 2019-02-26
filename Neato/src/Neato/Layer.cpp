#include "NeatoPCH.h"
#include "Layer.h"

namespace Neato {
	Neato::Layer::Layer(const std::string & name)
		: m_DebugName(name)
	{
	}

	Layer::~Layer()
	{

	}

	void Neato::Layer::OnAttach()
	{
	}

	void Neato::Layer::OnDetach()
	{
	}

	void Neato::Layer::OnUpdate()
	{
	}

	void Neato::Layer::OnEvent(Event& event)
	{
	}

	void Layer::OnImGuiRender()
	{
	}
}