#pragma once
#include ".\\GameEngine\T_Engine.h"

#include "Npc.h"
#include  "Npc_AI.h"
#include "Player.h"
#include "GameEngine/T_Scene.h"
#include "Explosion.h"
#include "Bomb.h"
#include "GameMenu.h"
#include "GameEngine/T_Audio.h"

typedef  vector<T_Sprite*> vSpriteSet;

class MyGame :
	public T_Engine
{
private:
	int wnd_width;
	int wnd_height;	// 窗口宽高
	int NPC_NUM = 10;	//npc数量
	
public:
	MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon = NULL, WORD SmIcon = NULL, int iWidth = 800,
		int iHeight = 800);
	~MyGame();

	//Npc* npc;
	Player* player;
	vector<Bomb*> Player_bomb_set;// 玩家炮弹集合
	vector<Npc*> npc_set;	// NPC角色集合
	vector<Bomb*> Npc_bomb_set;	// Npc炮弹集合
	
	// 处理声音
	AudioDX ds;
	AudioDXBuffer backmusic_buffer;	// 背景音乐
	AudioDXBuffer robot_buffer;		// 行走音乐
	AudioDXBuffer mousedown_buffer;	// 鼠标点击音效
	AudioDXBuffer mousemove_buffer;	// 鼠标滑动音效
	AudioDXBuffer blast_buffer;		// 爆炸音效
	// 场景类
	T_Scene t_scene;
	// 场景宽高
	int scn_width;
	int scn_height;
	// 菜单类
	GameMenu game_menu;
	//++++++++++++++++++++++++
	// 加载玩家
	void LoadPlayer();
	// 加载NPC
	void LoadNPC(int NPC_NUM = 10);
	// 载入地图
	void LoadMap();
	void GameInit() override;
	void GameLogic() override;
	void GameEnd() override;
	void GamePaint(HDC hdc) override;
	void GameKeyAction(int ActionType = KEY_SYS_NONE) override;
	void GameMouseAction(int x, int y, int ActionType) override;
};

