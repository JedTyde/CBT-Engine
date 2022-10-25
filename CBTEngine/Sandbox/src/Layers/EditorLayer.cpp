#include "EditorLayer.h"

#include "../vendor/imgui/imgui.h"
#include <stdio.h>

#include "CBT/Application.h"
#include "CBT/Events/Event.h"

EditorLayer::EditorLayer() : Layer("Editor Layer")
{

}

EditorLayer::~EditorLayer()
{

}

void EditorLayer::OnAttach()
{
	m_About = std::make_shared<AboutPanel>();


	/*m_Configuration = std::make_shared<ConfigurationPanel>();

	m_Panels.push_back(m_Configuration);*/
}

void EditorLayer::OnDetach()
{
	m_Panels.clear();
}

void EditorLayer::OnUpdate()
{
	//if (m_Configuration->active)
	//	m_Configuration->Update();
	//if (m_Assets->active)
	//	m_Assets->Update();
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


}

void EditorLayer::DockSpace()
{

}

bool EditorLayer::OnKeyPressed(CBT::KeyPressedEvent& k)
{
	return false;
}