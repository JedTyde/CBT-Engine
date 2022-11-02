#include "EditorLayer.h"

#include "../vendor/imgui/imgui.h"
#include <stdio.h>

#include "CBT/Application.h"
#include "CBT/Events/Event.h"
#include "Panels/ConfigPanel.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/InspectorPanel.h"

EditorLayer::EditorLayer() : Layer("Editor Layer")
{

}

EditorLayer::~EditorLayer()
{

}

void EditorLayer::OnAttach()
{
	m_About = std::make_unique<AboutPanel>();
	m_Configuration = std::make_unique<ConfigPanel>();
	m_Hierarchy= std::make_unique<HierarchyPanel>();
	m_Inspector= std::make_unique<InspectorPanel>();

	m_Panels.push_back(m_Configuration.get());
	m_Panels.push_back(m_Hierarchy.get());
	m_Panels.push_back(m_Inspector.get());

}

void EditorLayer::OnDetach()
{
	m_Panels.clear();
}

void EditorLayer::OnUpdate()
{
	for (auto& p : m_Panels)
		p->Update();
}

void EditorLayer::OnImGuiRender()
{
	ImGuiContext* ctx = CBT::Application::Get().GetImGuiContext();
	ImGui::SetCurrentContext(ctx);
	MainMenuBar();
	DockSpace();
	for (auto& p : m_Panels)
	{
		if (p->active)
			p->Draw();
	}
	if (m_About->active)
		m_About->Draw();
	if (m_ShowDemo)
		ImGui::ShowDemoWindow(&m_ShowDemo);


}

void EditorLayer::OnEvent(CBT::Event& ev)
{

}

void EditorLayer::MainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("General"))
		{
			ImGui::MenuItem("Load");
				
			if (ImGui::MenuItem("Close"))
				CBT::Application::Get().Quit();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			int i = 1;
			for (auto& p : m_Panels)
			{
				if (ImGui::MenuItem(p->GetName(), "", p->active))
					p->SwitchActive();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("GuiDemo", "", m_ShowDemo))
			{
				m_ShowDemo != m_ShowDemo;
			}

			if (ImGui::MenuItem("Download Latest"))
				CBT::Application::Get().GetUrl("https://github.com/JedTyde/CBT-Engine/releases"); 

			if (ImGui::MenuItem("Got an issue?"))
				CBT::Application::Get().GetUrl("https://github.com/JedTyde/CBT-Engine/issues");

			if (ImGui::MenuItem("About", "", m_About->active))
				m_About->SwitchActive();
			ImGui::End();
		}
		
		ImGui::EndMainMenuBar();
	}

}

void EditorLayer::DockSpace()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	static bool show = false;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &show, window_flags);

	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);
	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}

bool EditorLayer::OnKeyPressed(CBT::KeyPressedEvent& k)
{
	return false;
}