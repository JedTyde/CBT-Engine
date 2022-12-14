#pragma once
#include "ConfigPanel.h"
#include "Panels.h"

#include "../../CBTEngine/vendor/imgui/imgui.h"

#include "Windows.h"
#include "psapi.h"

#include "AllocationMetrics.h"

ConfigPanel::ConfigPanel()
	: Panels("Configuration"), info()
{

}

ConfigPanel::~ConfigPanel()
{
}

void ConfigPanel::Draw()
{
	m_Resizable = CBT::Application::Get().GetWindow().GetResizable();
	m_Fullscreen = CBT::Application::Get().GetWindow().GetFullScreen();
	m_VSync = CBT::Application::Get().GetWindow().IsVSync();
	m_MSLog.push_back(1000.0f / ImGui::GetIO().Framerate);
	m_FPSLog.push_back(ImGui::GetIO().Framerate);
	m_AllocLog.push_back((float)CBT::AllocationMetrics::allocation_count);
	m_ByteLog.push_back((float)CBT::AllocationMetrics::bytes_allocated);

	ImGui::Begin(name, &active);
	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::Checkbox("Fullscreen", &m_Fullscreen))
			CBT::Application::Get().GetWindow().SetFullScreen(m_Fullscreen);
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &m_Resizable))
			CBT::Application::Get().GetWindow().SetResizable(m_Resizable);
		if (ImGui::Checkbox("VSync", &m_VSync))
			CBT::Application::Get().GetWindow().SetVSync(m_VSync);
	}
	char title[25];
	if (ImGui::CollapsingHeader("Info"))
	{
		sprintf_s(title, 25, "Framerate %.1f", m_FPSLog[m_FPSLog.size() - 1]);
		ImGui::PlotHistogram("##framerate", &m_FPSLog[0], (int)m_FPSLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));
		sprintf_s(title, 25, "Frametime %.1f", m_MSLog[m_MSLog.size() - 1]);
		ImGui::PlotHistogram("##frametime", &m_MSLog[0], (int)m_MSLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));
		sprintf_s(title, 25, "Mem used %.1f", m_MemLog[m_MemLog.size() - 1]);
		ImGui::PlotHistogram("##memory", &m_MemLog[0], (int)m_MemLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));
		sprintf_s(title, 25, "Current Allocations %.0f", m_AllocLog[m_AllocLog.size() - 1]);
		ImGui::PlotHistogram("##memory", &m_AllocLog[0], (int)m_AllocLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));
		sprintf_s(title, 25, "Bytes allocated %.0f", m_ByteLog[m_ByteLog.size() - 1]);
		ImGui::PlotHistogram("##memory", &m_ByteLog[0], (int)m_ByteLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));
	}
	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("GLFW version:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "3.4");
		ImGui::Separator();
		ImGui::Text("CPUs:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", info.numCores);
		ImGui::Text("System RAM:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.ram);
		ImGui::Separator();
		ImGui::Text("GPU:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", info.gpu);
		ImGui::Text("Brand:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", info.gpuBrand);
		ImGui::Text("Total VRAM:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.gpuVRAM);
		ImGui::Text("VRAM Usage:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), " %0.1fMb", info.gpuVRAMUsage);
		ImGui::Text("VRAM Available:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.gpuVRAMAV);
		ImGui::Text("VRAM Reserved:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.gpuVRAMReserve);
	}
	ImGui::End();
}

void ConfigPanel::Update()
{
	info = CBT::Application::Get().GetSystemInfo();
	if (m_MSLog.size() > 64)
		m_MSLog.erase(0);

	if (m_FPSLog.size() > 64)
		m_FPSLog.erase(0);

	if (m_MemLog.size() > 64)
		m_MemLog.erase(0);

	if (m_AllocLog.size() > 64)
		m_AllocLog.erase(0);

	if (m_ByteLog.size() > 64)
		m_ByteLog.erase(0);

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.WorkingSetSize >> 20;
	m_MemLog.push_back((float)virtualMemUsedByMe);
}