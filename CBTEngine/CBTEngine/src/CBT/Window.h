#pragma once

#include "CBTpch.h"

#include "CBT/Core.h"
#include "CBT/Events/Event.h"

namespace CBT {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "CBT Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};
		//Interface representing a desktop system based Window
	
	class CBT_API Window 
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}
			
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;		
		virtual bool GetFullScreen() const = 0;
		virtual bool GetResizable() const = 0;
		
		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetFullScreen(bool enabled) = 0;
		virtual void SetResizable(bool enabled) = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
		};
						
}