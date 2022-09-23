#include "Application.h"
#include "Events/Event.h"

namespace CBT {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			CBT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CBT_TRACE(e);
		}
		while (true);
	}
}