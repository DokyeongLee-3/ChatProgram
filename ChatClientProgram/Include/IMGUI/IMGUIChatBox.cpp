
#include "IMGUIChatBox.h"
#include "imgui_internal.h"
#include "../Client/ClientWindow.h"

CIMGUIChatBox::CIMGUIChatBox()
{
}

CIMGUIChatBox::~CIMGUIChatBox()
{
}

bool CIMGUIChatBox::Init()
{
	return true;
}

void CIMGUIChatBox::Render()
{

    char* ID = ((CClientWindow*)m_Owner)->GetID();


    ImGui::TextUnformatted(ID);

    ImGui::Separator();

    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

    ImGui::BeginChild("ScrollingRegion", ImVec2(0.f, 350.f), false, ImGuiWindowFlags_HorizontalScrollbar);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    for (int i = 0; i < m_ChatBox.Items.Size; i++)
    {
        const char* item = m_ChatBox.Items[i];

        ImVec4 color;
        bool has_color = false;
        //if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
        //else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
        //if (has_color)
        //    ImGui::PushStyleColor(ImGuiCol_Text, color);

        ImGui::TextUnformatted(item);
        //if (has_color)
        //    ImGui::PopStyleColor();
    }

	//bool Open = false;
	//m_ChatBox.Draw("ClientChatBox", &Open);


    ImGui::PopStyleVar();
    ImGui::EndChild();
}
