#include "MyGame.h"

MyGame::MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth,
	int iHeight) :T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight)
{
	wnd_width = iWidth;
	wnd_height = iHeight;
}

void MyGame::GameInit()
{
	// 加载地图
	map.LoadMap();
	// 加载玩家以及NPC
	player.LoadPlayer();
	for (int i = 0; i < 3; i++)
	{
		npc.LoadNpc(i);
	}
}

void MyGame::GameLogic()
{
	GameKeyAction();
	npc.UpdateNpcPos();		// 移动NPC
	if (player.player->IsActive())
	{
		player.UpdateplayerPos(player.player->GetDir());
	}
	npc.UpdateAnimation();	// 更新动画
	player.UpdateAnimation();
}

void MyGame::GameEnd()
{
}

void MyGame::GamePaint(HDC hdc)
{
	map.Draw(hdc,0,0);
}

void MyGame::GameKeyAction(int ActionType)
{
	if (ActionType == KEY_SYS_NONE)
	{
		if (CheckKey(VK_LEFT)&&!CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player.player->SetActive(true);
			player.player->SetSequence(player.FRAME_LEFT, 20);
			player.player->SetDir(DIR_LEFT);
		}
		if (CheckKey(VK_UP) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player.player->SetActive(true);
			player.player->SetSequence(player.FRAME_UP, 20);
			player.player ->SetDir(DIR_UP);
		}
		if (CheckKey(VK_DOWN) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player.player->SetActive(true);
			player.player->SetSequence(player.FRAME_DOWN, 20);
			player.player->SetDir(DIR_DOWN);
		}
		if (CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player.player->SetActive(true);
			player.player->SetSequence(player.FRAME_RIGHT, 20);
			player.player->SetDir(DIR_RIGHT);
		}// 没有按方向键,那么应该停下
		if (!CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player.player->SetActive(false);
		}
	}
	
	
}

void MyGame::GameMouseAction(int x, int y, int ActionType)
{
}

MyGame::~MyGame()
{
	delete player.player;
	player.player = NULL;
}
