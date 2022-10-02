#pragma once

#include "../IMGUI/IMGUIWindow.h"


class CClientWindow :
    public CIMGUIWindow
{

public:
    CClientWindow();
    ~CClientWindow();


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void SendClientToServ(char* Chat);
    void StackChatLog(char* Chat);
};

