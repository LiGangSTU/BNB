
#include "MyGame.h"

// WinMainº¯Êý
//
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance, 
				   PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"GdiTest";
	MyGame* mygame = new MyGame(h_instance,WIN_CLASS,WinTitle,
									NULL, NULL, 800, 800);
	T_Engine::pEngine = mygame;
	mygame->SetFrame(20);
	mygame->StartEngine();

	return TRUE;
}
