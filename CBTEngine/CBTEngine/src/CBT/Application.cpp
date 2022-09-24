#include "CBTpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "CBT/Log.h"

namespace CBT {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	};

	Application::~Application()
	{	
	}

	void Application::Run()
	{
		/*WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			CBT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CBT_TRACE(e);
		}*/

		while (m_Running);
		{
			m_Window->OnUpdate();
		}
	}
}