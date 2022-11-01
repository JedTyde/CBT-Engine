#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include <CBT/Events/ApplicationEvent.h>
#include "ImGui/ImGuiLayer.h"
#include "../Render3D.h"


namespace CBT {

	struct SysInfo
	{
		SysInfo() = default;

		char glfwVer[32];
		uint32_t cache;
		uint32_t numCores;
		float ram;
		const unsigned char* gpu;
		const unsigned char* gpuBrand;
		float gpuVRAM;
		float gpuVRAMUsage;
		float gpuVRAMAV;
		float gpuVRAMReserve;
	};

	class CBT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		inline ImGuiContext* GetImGuiContext() { return m_ImGuiLayer->GetContext(); }

		inline SysInfo& GetSystemInfo() { return m_SysInfo; }

		void GetUrl(const char* url);
		void Quit();
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		
		SysInfo m_SysInfo;
		
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		Render3D* m_Render3d;

	private:
		static Application* s_Instance;
	};

	//Define in client
	Application* CreateApplication();
}