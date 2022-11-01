#include "EditorLayer.h"

#include "../vendor/imgui/imgui.h"
#include <stdio.h>

#include "CBT/Application.h"
#include "CBT/Events/Event.h"
#include "Panels/ConfigPanel.h"
#include "Panels/HierarchyPanel.h"

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

	m_Panels.push_back(m_Configuration.get());
	m_Panels.push_back(m_Hierarchy.get());

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

}

bool EditorLayer::OnKeyPressed(CBT::KeyPressedEvent& k)
{
	return false;
}