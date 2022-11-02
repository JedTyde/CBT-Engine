#include "CBTpch.h"
#include "WindowsWindow.h"

#include "CBT/Log.h"

#include <CBT/Events/ApplicationEvent.h>
#include <CBT/Events/KeyEvent.h>
#include <CBT/Events/MouseEvent.h>

#include <GLFW/glfw3.h>
#include "../../CBTEngine/vendor/GLAD/include/glad/glad.h"

namespace CBT {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		//CBT_CORE_ERROR no ta definido hehe
		//CBT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;


		CBT_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			CBT_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		CBT_CORE_TRACE("Creating window...");
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CBT_CORE_ASSERT(status, "Failed to initialize GLAD!")
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//CBT_CORE_INFO("Using Glad {0}", glad_glGetString(GLAD_GL_VERSION_1_0));
		CBT_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		CBT_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		CBT_CORE_INFO("OpenGL version supported {0}", glGetString(GL_VERSION));
		CBT_CORE_INFO("GLSL: {0}\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);				
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
			
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	};

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::SetFullScreen(bool enabled)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		m_OldData.Refresh = mode->refreshRate;
		m_Data.Refresh = mode->refreshRate;

		if (enabled)
			glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		else
			glfwSetWindowMonitor(m_Window, nullptr, (m_Data.Width / 2) - (m_OldData.Width / 2), (m_Data.Height / 2) - (m_OldData.Height / 2),
				m_OldData.Width, m_OldData.Height, m_OldData.Refresh);
		CBT_CORE_INFO("Window fullscreen changed {0}, {1}, {2}", m_OldData.Width, m_OldData.Height, m_OldData.Refresh);
		m_Fullscreen = enabled;
	}

	void WindowsWindow::SetResizable(bool enabled)
	{
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, enabled);
		m_Resizable = enabled;
	}

}