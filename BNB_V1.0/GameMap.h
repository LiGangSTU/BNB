#pragma once
#include ".\\GameEngine\T_Scene.h"
class GameMap:public T_Scene
{
public:
	int wnd_width;
	int wnd_height;	// 窗口宽高
	// 关于场景类
	T_Scene t_scene;	// 游戏场景
	int scn_width, scn_height;	// 游戏窗口宽高
						// 加载游戏地图场景
	void LoadMap();
	GameMap();
	~GameMap();
};

