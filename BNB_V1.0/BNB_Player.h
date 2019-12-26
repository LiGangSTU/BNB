#pragma once
#include ".\\GameEngine\T_Sprite.h"
#include "GameMap.h"
class BNB_Player 
{
public:
	// 重新定义四个方向的动画帧
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];

	static const int NPC_NUM = 3;	// NPC总数

	T_Sprite *player;
	GameMap map;
	void LoadPlayer();
	void UpdateplayerPos(int dir);
	// 更新动画
	void UpdateAnimation();
	BNB_Player();
	~BNB_Player();
};

