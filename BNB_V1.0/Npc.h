#pragma once
#include ".\\GameEngine\T_Sprite.h"
#include ".\\GameEngine\T_AI.h"
#include "GameMap.h"
#include "BNB_Player.h"
typedef  vector<T_Sprite*> vSpriteSet;
class Npc 
{
public:
	// 重新定义四个方向的动画帧
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];

	static const int NPC_NUM = 3;	// NPC总数

	vSpriteSet npc_set;	// NPC角色集合
	GameMap map;
	BNB_Player player;
	void LoadNpc(int num);
	void UpdateNpcPos();
	// 更新动画
	void UpdateAnimation();
	
	Npc();
	~Npc();
};

