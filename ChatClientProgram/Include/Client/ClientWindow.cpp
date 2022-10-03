
#include "ClientWindow.h"
#include "../IMGUI/IMGUIListBox.h"
#include "../IMGUI/IMGUITextInput.h"
#include "../ClientManager.h"
#include "../IMGUI/IMGUISeperator.h"
#include "../IMGUI/IMGUIChatBox.h"

CClientWindow::CClientWindow()
{
}

CClientWindow::~CClientWindow()
{
}

bool CClientWindow::Init()
{
	CIMGUIWindow::Init();

	AddWidget<CIMGUISeperator>("Separator1");

	AddWidget<CIMGUIChatBox>("ChatBox");

	AddWidget<CIMGUISeperator>("Separator2");

	CIMGUITextInput* Input = AddWidget<CIMGUITextInput>("ChatInput", 400.f, 80.f);
	Input->SetSize(400.f, 150.f);
	Input->SetHideName(true);
	Input->AddFlag(ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue);
	Input->AddCallback<CClientWindow>(this, &CClientWindow::SendClientToServ);
	Input->AddCallback<CClientWindow>(this, &CClientWindow::StackChatLog);
	
	AddWidget<CIMGUISeperator>("Separator3");

	return true;
}

void CClientWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);



	//static ExampleAppConsole console;
	//bool open = false;
	//console.Draw("Example: Console", &open);

	//ImGui::ShowDemoWindow();
}

void CClientWindow::SendClientToServ(char* Chat)
{
	SOCKET socket = CClientManager::GetInst()->GetSocket();
	char* NewBuf = new char[1000];
	memset(NewBuf, 0, 1000);
	strcat_s(NewBuf, 1000, "[");
	strcat_s(NewBuf, 1000, m_ID);
	strcat_s(NewBuf, 1000, "] : ");
	strcat_s(NewBuf, 1000, Chat);
	send(socket, NewBuf, (int)(strlen(NewBuf) + 1), 0);
	Sleep(DWORD(0.4f));
}

void CClientWindow::StackChatLog(char* Chat)
{
	CIMGUIChatBox* Box = (CIMGUIChatBox*)FindWidget("ChatBox");

	if (Box)
	{
		char* AddMe = new char[1000];
		strcpy_s(AddMe, 1024, "[Me] : ");
		strcat(AddMe, Chat);


		Box->GetChatBoxConsole().AddLog(AddMe);
	}
}
