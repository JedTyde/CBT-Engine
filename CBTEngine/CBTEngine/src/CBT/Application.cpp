#include "CBTpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "CBT/Log.h"

namespace CBT {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	};

	Application::~Application()
	{	
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//CBT_CORE_TRACKER("{0}", e); //coretracker no fonsiona :(
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
			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}