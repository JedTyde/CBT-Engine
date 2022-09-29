#pragma once

#include "CBT/Layer.h"

namespace CBT
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);

	private:

	};
}