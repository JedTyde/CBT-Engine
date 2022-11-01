#pragma once

#include "CBT/Window.h"



struct GLFWwindow;

namespace CBT {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override  { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline bool GetFullScreen() const override { return m_Fullscreen; }
		inline bool GetResizable() const override { return m_Resizable; }

		//Window attributes
		inline void SetEventCallback (const EventCallbackFn& callback) override {m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual void SetFullScreen(bool enabled) override;
		virtual void SetResizable(bool enabled) override;

		inline void* GetNativeWindow() const override { return m_Window; }


	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			uint32_t Refresh = 0;

			EventCallbackFn EventCallback;
		};

		bool m_Fullscreen = false;
		bool m_Resizable = false;

		WindowData m_Data;
		WindowData m_OldData;
	};
}
