#pragma once
#include ".\\GameEngine\T_Engine.h"
#include "GameMap.h"
#include "BNB_Player.h"
#include "Npc.h"


class MyGame :
	public T_Engine
{
private:
	int wnd_width;
	int wnd_height;	// ´°¿Ú¿í¸ß
	
public:
	MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon = NULL, WORD SmIcon = NULL, int iWidth = 800,
		int iHeight = 600);
	~MyGame();

	Npc npc;
	BNB_Player player;
	GameMap map;
	void GameInit() override;
	void GameLogic() override;
	void GameEnd() override;
	void GamePaint(HDC hdc) override;
	void GameKeyAction(int ActionType = KEY_SYS_NONE) override;
	void GameMouseAction(int x, int y, int ActionType) override;
};

