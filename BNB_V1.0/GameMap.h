#pragma once
#include ".\\GameEngine\T_Scene.h"
class GameMap:public T_Scene
{
public:
	int wnd_width;
	int wnd_height;	// ���ڿ��
	// ���ڳ�����
	T_Scene t_scene;	// ��Ϸ����
	int scn_width, scn_height;	// ��Ϸ���ڿ��
						// ������Ϸ��ͼ����
	void LoadMap();
	GameMap();
	~GameMap();
};

