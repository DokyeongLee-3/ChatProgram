#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <Windows.h>
#include <functional>
#include <algorithm>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d2d1.h>

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

#define	FONT_PATH		"Font"
#define	ROOT_PATH		"Root"

struct Resolution
{
	unsigned int	Width;
	unsigned int	Height;
};



#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define	DECLARE_SINGLE(Type)	\
private:\
	static Type*	m_Inst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_Inst)\
			m_Inst = new Type;\
		return m_Inst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_Inst);\
	}\
private:\
	Type();\
	~Type();

#define	DEFINITION_SINGLE(Type)	Type* Type::m_Inst = nullptr;