#pragma once

#include "Panels.h"
#include "../EditorLayer.h"

#include "List.h"
#include "CBT/Application.h"

class ConfigPanel : public Panels
{
public:
	ConfigPanel();
	virtual ~ConfigPanel();

	void Draw() override;

	void Update() override;
private:
	CBT::List<float> m_FPSLog;
	CBT::List<float> m_MSLog;
	CBT::List<float> m_MemLog;
	CBT::List<float> m_AllocLog;
	CBT::List<float> m_ByteLog;

	bool m_Fullscreen = false;
	bool m_Resizable = false;
	bool m_VSync = false;

	CBT::SysInfo info;
};
