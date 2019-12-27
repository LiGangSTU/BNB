#pragma once
#include ".\GameEngine\T_Sprite.h"
#include "GameEngine/T_Scene.h"
#include "GameEngine/T_Config.h"
class Player :
	public T_Sprite
{
private:
	// ����һЩ����Ϸ��������е�����
	
public:
	// ���֡
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];
	Player(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Player();
	
	// �ı����λ��
	void updatePos(int dir, T_Scene *t_scene);
	// ���¶���
	void updateAnimation();
};

