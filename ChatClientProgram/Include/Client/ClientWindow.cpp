
#include "ClientWindow.h"
#include "../IMGUI/IMGUIListBox.h"

CClientWindow::CClientWindow()
{
}

CClientWindow::~CClientWindow()
{
}

bool CClientWindow::Init()
{
	CIMGUIWindow::Init();

	AddWidget<CIMGUIListBox>("Test");

	return true;
}

void CClientWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}
