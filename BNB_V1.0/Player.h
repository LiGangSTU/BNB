#pragma once
#include ".\GameEngine\T_Sprite.h"
#include "GameEngine/T_Scene.h"
#include "GameEngine/T_Config.h"
class Player :
	public T_Sprite
{
private:
	// 加入一些本游戏中玩家特有的内容
	
public:
	// 玩家帧
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];
	Player(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Player();
	
	// 改变玩家位置
	void updatePos(int dir, T_Scene *t_scene);
	// 更新动画
	void updateAnimation();
};

