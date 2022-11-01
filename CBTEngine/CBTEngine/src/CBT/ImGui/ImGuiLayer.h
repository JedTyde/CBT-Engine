#pragma once

#include "CBT/Layer.h"

#include "CBT/Events/ApplicationEvent.h"
#include "CBT/Events/KeyEvent.h"
#include "CBT/Events/MouseEvent.h"
#include "../../CBTEngine/vendor/imgui/imgui.h"
#include "ImGuiLog.h"

namespace CBT
{
	class CBT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void Begin();
		void End();

		void OnAttach();
		void OnDettach();
		void OnUpdate();
		void OnEvent(Event& event);
		inline ImGuiContext* GetContext() { return m_Context; }

		inline void CoreLogTrace(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::TRACE, log); }
		inline void CoreLogInfo(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::INFO, log); }
		inline void CoreLogWarn(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::WARN, log); }
		inline void CoreLogError(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::ERR, log); }
		inline void CoreLogCritical(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::CRITICAL, log); }

		inline ImGuiLog& GetLog() { return m_Log; }

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		ImGuiLog m_Log;

		float m_Time = 0.0f;
		ImGuiContext* m_Context;
	};
}