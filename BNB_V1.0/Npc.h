#pragma once
#include ".\GameEngine\T_Sprite.h"
#include "GameEngine/T_Scene.h"

class Npc :
	public T_Sprite
{
public:
	// NPC帧
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];
	// 后期如果
	Npc(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Npc();
	// 改变NPC位置
	void updatePos(T_Sprite* player, T_Scene *t_scene,vector<Npc*> npc_set);
	// 更新动画
	void updateAnimation();
};

