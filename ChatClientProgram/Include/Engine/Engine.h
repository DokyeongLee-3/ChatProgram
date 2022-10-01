#pragma once

#include "../GameInfo.h"
#include "../Timer.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_RS;
	static bool	m_Loop;
	class CTimer* m_Timer;
	bool		m_Start;
	float		m_ClearColor[4];

public:
	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

	void Exit()
	{
		DestroyWindow(m_hWnd);
	}

	float GetFPS()	const
	{
		return m_Timer->GetFPS();
	}

	float GetDeltaTime()	const
	{
		return m_Timer->GetDeltaTime();
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Name, unsigned int Width,
		unsigned int Height, int IconID, char* ID,
		bool WindowMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, unsigned int Width,
		unsigned int Height, char* ID, bool WindowMode = true);
	int Run();
	void Logic();

private:
	bool Update(float DeltaTime);
	bool Render(float DeltaTime);

private:
	ATOM Register(const TCHAR* Name, int IconID);
	BOOL Create(const TCHAR* Name);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	DECLARE_SINGLE(CEngine)
};

