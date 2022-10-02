
#include "IMGUIChatBox.h"
#include "imgui_internal.h"

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
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoDocking);

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

	/*bool Open = false;
	m_ChatBox.Draw("ClientChatBox", &Open);*/

    ImGui::EndChild();
}
