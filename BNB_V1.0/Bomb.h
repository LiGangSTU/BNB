#pragma once
#include ".\GameEngine\T_Sprite.h"
class Bomb :
	public T_Sprite
{
private:
	// 加入炮弹专属的属性
public:
	Bomb(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Bomb();
};

