#pragma once

#include <CBT/Layer.h>

#include "Panels/Panels.h"
#include "Panels/AboutPanel.h"
#include "CBT/Events/KeyEvent.h"
#include "CBT/Events/Event.h"


class EditorLayer : public CBT::Layer
{
public:
	EditorLayer();
	~EditorLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnEvent(CBT::Event& ev) override;

private:
	void MainMenuBar();
	void DockSpace();

	bool OnKeyPressed(CBT::KeyPressedEvent& k);
	std::vector<Panels*> m_Panels;
	std::unique_ptr<Panels>	m_Configuration;
	std::unique_ptr<Panels>	m_Assets;

	bool m_ShowConsole = false;
	bool m_ShowDemo = false;

	std::shared_ptr<Panels>			m_About = nullptr;
};

