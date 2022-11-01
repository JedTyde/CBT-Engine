#include "CBTpch.h"
#include "Application.h"

#include "CBT/Log.h"

#include "Events/ApplicationEvent.h"

#include "../../CBTEngine/vendor/GLAD/include/glad/glad.h"
#include "../Render3D.h"
#include "../Shader.h"

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049
#define GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX 0x904B

namespace CBT {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CBT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		int min, major, rev;
		SetHardwareInfo();

		m_Render3d = new Render3D();
		m_Render3d->Init();

	};

	Application::~Application()
	{	
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::SetHardwareInfo()
	{
		SYSTEM_INFO info;
		::GetSystemInfo(&info);

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		GLint total_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &total_mem_kb);
		GLint cur_avail_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &cur_avail_mem_kb);
		GLint cur_reserv_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &cur_reserv_mem_kb);

		m_SysInfo.numCores = info.dwNumberOfProcessors;
		m_SysInfo.ram = (float)(memInfo.ullTotalPhys >> 20);
		m_SysInfo.gpu = (const unsigned char*)glGetString(GL_VENDOR);
		m_SysInfo.gpuBrand = glGetString(GL_RENDERER);
		m_SysInfo.gpuVRAM = (float)(total_mem_kb >> 10);
		m_SysInfo.gpuVRAMAV = (float)(cur_avail_mem_kb >> 10);
		m_SysInfo.gpuVRAMUsage = (float)((total_mem_kb - cur_avail_mem_kb) >> 10);
		m_SysInfo.gpuVRAMReserve = (float)(cur_reserv_mem_kb >> 10);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//CBT_CORE_TRACKER("{0}", e); //coretracker no fonsiona :(
	}

	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(0.4, 0.4, 0.4, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Render3d->DrawTriangle();
			m_Render3d->DrawModel();
			m_ImGuiLayer->Begin();


			{
				m_ImGuiLayer->OnUpdate();
				//TODO: Optick On ImGuiRender call
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();
			m_Window->OnUpdate();
			m_Render3d->Update();
		}
	}

	void Application::GetUrl(const char* url)
	{
		ShellExecuteA(0, "open", url, NULL, NULL, SW_SHOWNORMAL);
	}

	void Application::Quit()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}