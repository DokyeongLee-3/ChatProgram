#pragma once

#include "../IMGUI/IMGUIWindow.h"


class CClientWindow :
    public CIMGUIWindow
{

public:
    CClientWindow();
    ~CClientWindow();

private:
    char m_ID[100];

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void SetID(const char* ID)
    {
        strcpy_s(m_ID, sizeof(m_ID), ID);
    }

    char* GetID()
    {
        return m_ID;
    }

public:
    void SendClientToServ(char* Chat);
    void StackChatLog(char* Chat);
};

