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
}

void EditorLayer::OnDetach()
{
	m_Panels.clear();
}

void EditorLayer::OnUpdate()
{
	if (m_Configuration->active)
		m_Configuration->Update();
	if (m_Assets->active)
		m_Assets->Update();
}

void EditorLayer::OnImGuiRender()
{



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