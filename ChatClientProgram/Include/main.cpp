

#include "resource.h"
#include "Engine/Engine.h"

#define BUFFSIZE 200
#define NAMESIZE 20

char message[BUFFSIZE];

void echooff(FILE* f)
{
#ifdef _WIN32
	if (f == stdin)
	{
		HANDLE h;
		DWORD mode;

		h = GetStdHandle(STD_INPUT_HANDLE);
		if (GetConsoleMode(h, &mode))
		{
			mode &= ~ENABLE_ECHO_INPUT;
			SetConsoleMode(h, mode);
		}
	}
#elif defined HAVE_TERMIOS_H
	struct termios ts;

	tcgetattr(fileno(f), &ts);
	ts.c_lflag &= ~ECHO;
	tcsetattr(fileno(f), TCSANOW, &ts);
#else
	(void)f;
#endif
}

//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	//char ID[100];
//	//strcpy(ID, argv[1]);
//
//	CEngine::GetInst()->Init(hInstance, TEXT("ChatProgram"), 1280, 720, IDI_ICON1);
//
//	CEngine::GetInst()->Run();
//
//	CEngine::GetInst()->DestroyInst();
//
//	return 0;
//}

int main(int argc, char* argv[])
{
	char ID[100];

	printf("Enter Your Name : ");
	scanf_s("%s", ID, sizeof(ID));

	HINSTANCE hInstance = GetModuleHandle(NULL);
	
	CEngine::GetInst()->Init(hInstance, TEXT("ChatProgram"), 1280, 720, IDI_ICON1, ID);

	CEngine::GetInst()->Run();

	return 0;
}