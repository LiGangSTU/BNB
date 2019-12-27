#pragma once
#include ".\GameEngine\T_Sprite.h"
class Explosion :
	public T_Sprite
{
public:
	Explosion(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Explosion();
};

