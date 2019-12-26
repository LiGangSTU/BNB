#pragma once
#include ".\\GameEngine\T_Sprite.h"
#include "GameMap.h"
class BNB_Player 
{
public:
	// ���¶����ĸ�����Ķ���֡
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];

	static const int NPC_NUM = 3;	// NPC����

	T_Sprite *player;
	GameMap map;
	void LoadPlayer();
	void UpdateplayerPos(int dir);
	// ���¶���
	void UpdateAnimation();
	BNB_Player();
	~BNB_Player();
};

