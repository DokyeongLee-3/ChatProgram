
#include "IMGUIManager.h"
#include "IMGUIWindow.h"
#include "../PathManager.h"

DEFINITION_SINGLE(CIMGUIManager)

CIMGUIManager::CIMGUIManager()	:
	m_Context(nullptr)
{
}

CIMGUIManager::~CIMGUIManager()
{
	auto	iter = m_mapWindow.begin();
	auto	iterEnd = m_mapWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void CIMGUIManager::SetStagingTree(CIMGUITree* Tree)
{
	m_StagingTree = Tree;
}

CIMGUITree* CIMGUIManager::GetStagingTree() const
{
	return m_StagingTree;
}

bool CIMGUIManager::Init()
{
	char pszOldWindowTitle[1024];
	GetConsoleTitleA(pszOldWindowTitle, 1024);
	m_hWnd = FindWindowA(NULL, pszOldWindowTitle);

	m_Context = ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	// BackEnd Setup
	ImGui_ImplWin32_Init(m_hWnd);

	AddFont("Default", "NotoSansKR-Regular.otf", 15.f, true);
	AddFont("DefaultBlack", "NotoSansKR-Black.otf", 15.f, true);
	AddFont("DefaultBold", "NotoSansKR-Bold.otf", 15.f, true);

	m_CurrentFont = FindFont("DefaultBold");

	return true;
}

void CIMGUIManager::Update(float DeltaTime)
{
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	//ImGui::PushFont(m_CurrentFont);

	auto	iter = m_mapWindow.begin();
	auto	iterEnd = m_mapWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->IsOpen() == false)
			continue;
		iter->second->Update(DeltaTime);
	}

	//ImGui::PopFont();

	// Window���� �׷��� �������� ���� ȭ�鿡 �׷����°��� �ƴ϶�
	// IMGUI ������ ���ۿ� �׷����� �ȴ�.
	// �� ���۸� ���������� �ѹ� �׷����� ������� ó���� �ȴ�.
	ImGui::Render();
}

void CIMGUIManager::Render()
{
	if (m_mapWindow.empty())
		return;

	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

CIMGUIWindow* CIMGUIManager::FindIMGUIWindow(const std::string& Name)
{
	auto	iter = m_mapWindow.find(Name);

	if (iter == m_mapWindow.end())
		return nullptr;

	return iter->second;
}

bool CIMGUIManager::AddFont(const std::string& Name, const char* FileName, float Size, bool Korea, int OverH, int OverV,
	float Spacing, const std::string& PathName)
{
	ImFont* Font = FindFont(Name);

	if (Font)
		return false;

	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	return AddFontFullPath(Name, FullPath, Size, Korea, OverH, OverV, Spacing);
}

bool CIMGUIManager::AddFontFullPath(const std::string& Name, const char* FullPath, float Size, bool Korea, int OverH,
	int OverV, float Spacing)
{
	ImFont* Font = FindFont(Name);

	if (Font)
		return false;

	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig	config;

	config.OversampleH = OverH;
	config.OversampleV = OverV;
	config.GlyphExtraSpacing.x = Spacing;
	config.PixelSnapH = 1;

	if (!Korea)
		Font = io.Fonts->AddFontFromFileTTF(FullPath, Size, &config, io.Fonts->GetGlyphRangesDefault());

	else
		Font = io.Fonts->AddFontFromFileTTF(FullPath, Size, &config, io.Fonts->GetGlyphRangesKorean());

	m_mapFont.insert(std::make_pair(Name, Font));

	return true;
}

void CIMGUIManager::SetCurrentFont(const std::string& Name)
{
	ImFont* Font = FindFont(Name);

	if (!Font)
		return;

	m_CurrentFont = Font;
}

ImFont* CIMGUIManager::FindFont(const std::string& Name)
{
	auto	iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
		return nullptr;

	return iter->second;
}

void CIMGUIManager::SetCurrentFont()
{
	ImGui::PushFont(m_CurrentFont);
}

void CIMGUIManager::ResetCurrentFont()
{
	ImGui::PopFont();
}
