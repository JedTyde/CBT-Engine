#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace CBT {

	class CBTE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Define in client
	Application* CreateApplication();
}