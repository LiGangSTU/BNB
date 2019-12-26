#include "GameMap.h"



void GameMap::LoadMap()
{
	t_scene.LoadTxtMap(".\\map\\newMap.txt");
	scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
	scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
	// 视图初始位置以地图作为参照
	int scn_x = (wnd_width - scn_width) / 2;
	int scn_y = (wnd_height - scn_height) / 2;
	// 地图初始化定位到中间
	t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
	// 将所有地图图层定位到屏幕中央
	SCENE_LAYERS::iterator p;
	for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
	{
		if (p->layer->ClassName() == "T_Map")
		{
			p->layer->SetPosition(scn_x, scn_y);
		}
	}
}

GameMap::GameMap()
{
	wnd_width = 800;
	wnd_height = 800;
}


GameMap::~GameMap()
{
}
