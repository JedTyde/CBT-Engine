#pragma once

#include "../vendor/imgui/imgui.h"

struct ImGuiLog
{
    enum LogLevel {
        TRACE,
        INFO,
        WARN,
        ERR,
        CRITICAL,
        LAST
    };

    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    ImVector<LogLevel>  LogLevels;
    bool                AutoScroll;  // Keep scrolling if already at the bottom.

    ImVec4 LevelColors[LogLevel::LAST];
    int infoCount;
    int warnCount;
    int errorCount;

    ImGuiLog()
    {
        AutoScroll = true;
        Clear();

        LevelColors[LogLevel::TRACE] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        LevelColors[LogLevel::INFO] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::WARN] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::ERR] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::CRITICAL] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);


    }

    void    Clear()
    {
        Buf.clear();
        LogLevels.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);

        infoCount = warnCount = errorCount = 0;
    }

    void    AddLog(LogLevel level, const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n') {
                LineOffsets.push_back(old_size + 1);
                LogLevels.push_back(level);
            }
        if (level == LogLevel::INFO || level == LogLevel::TRACE) infoCount++;
        if (level == LogLevel::WARN) warnCount++;
        if (level == LogLevel::ERR || level == LogLevel::CRITICAL) errorCount++;
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            Clear();
        if (copy)
            ImGui::LogToClipboard();

        if (Buf.size() > 0) {

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();
            if (Filter.IsActive())
            {
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end)) {
                        ImGui::PushStyleColor(ImGuiCol_Text, LevelColors[LogLevels[line_no]]);
                        ImGui::TextUnformatted(line_start, line_end);
                        ImGui::PopStyleColor();
                    }
                }
            }
            else
            {
                ImGuiListClipper clipper;
                clipper.Begin(LineOffsets.Size - 1);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        ImGui::PushStyleColor(ImGuiCol_Text, LevelColors[LogLevels[line_no]]);
                        ImGui::TextUnformatted(line_start, line_end);
                        ImGui::PopStyleColor();
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }
};