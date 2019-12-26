#include "Npc.h"
// 重新定义动画帧
int Npc::FRAME_DOWN[20] = { 0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4 };
int Npc::FRAME_LEFT[20] = { 5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9 };
int Npc::FRAME_RIGHT[20] = { 10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14 };
int Npc::FRAME_UP[20] = { 15,15,15,15,16,16,16,16,17,17,17,17,18,18,18,18,19,19,19,19 };



void Npc::LoadNpc(int num)
{
	int scn_width, scn_height;
	scn_width = map.getSceneLayers()->back().layer->GetWidth();
	scn_height = map.getSceneLayers()->back().layer->GetHeight();
	GAMELAYER gameLayer;
	SPRITEINFO spInfo;

	spInfo.Active = true;
	spInfo.Dead = false;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.5f;
	spInfo.Speed = 2;
	spInfo.Alpha = 230;
	spInfo.Visible = true;
	spInfo.Level = 0;
	spInfo.Score = 0;

	int sp_width = 40;
	int sp_height = 40;
	//抽取随机方向(NPC角色在地图的四角生成)
	int sdr = num;
	int d = rand() % 2;
	switch (sdr)
	{
	case 0://左上角
		if (d == 0)  spInfo.Dir = DIR_RIGHT;
		if (d == 1)  spInfo.Dir = DIR_DOWN;
		spInfo.X = map.getSceneX();
		spInfo.Y = map.getSceneY();
		break;
	case 1://右上角
		if (d == 0)  spInfo.Dir = DIR_LEFT;
		if (d == 1)  spInfo.Dir = DIR_DOWN;
		spInfo.X = map.getSceneX() + scn_width - sp_width;
		spInfo.Y = map.getSceneY();
		break;
	case 2://左下角
		if (d == 0)  spInfo.Dir = DIR_RIGHT;
		if (d == 1)  spInfo.Dir = DIR_UP;
		spInfo.X = map.getSceneX();
		spInfo.Y = map.getSceneY() + scn_height - sp_height;
		break;
	case 3://右下角
		if (d == 0)  spInfo.Dir = DIR_LEFT;
		if (d == 1)  spInfo.Dir = DIR_UP;
		spInfo.X = map.getSceneX() + scn_width - sp_width;
		spInfo.Y = map.getSceneY() + scn_height - sp_height;
		break;
	}

	//在NPC列表中增加新的项目
	npc_set.push_back(new T_Sprite(L".\\res\\spritesheet.png", 42, 56));

	//初始化刚增加的项目
	T_Sprite *sp = npc_set.back();
	sp->Initiate(spInfo);
	switch (spInfo.Dir)
	{
	case DIR_LEFT:
		sp->SetSequence(FRAME_LEFT, 20);
		break;
	case DIR_RIGHT:
		sp->SetSequence(FRAME_RIGHT, 20);
		break;
	case DIR_UP:
		sp->SetSequence(FRAME_UP, 20);
		break;
	case DIR_DOWN:
		sp->SetSequence(FRAME_DOWN, 20);
		break;
	}
	sp->SetLayerTypeID(LAYER_NPC);

	gameLayer.layer = sp;
	gameLayer.type_id = LAYER_NPC;
	gameLayer.z_order = map.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	map.Append(gameLayer);
	sp = NULL;
}

void Npc::UpdateNpcPos()
{
	if (npc_set.size() == 0)
	{
		return;
	}
	T_AI* spAi = new T_AI(4);
	// 遍历所有npc
	for (vSpriteSet::iterator i = npc_set.begin(); i != npc_set.end(); i++)
	{
		if ((*i)->IsActive() && (*i)->IsVisible())
		{
			spAi->Evade((*i), player.player);	// 躲避玩家角色
			spAi->CheckOverlay((*i), npc_set);	// 防止互相重叠
			int npc_dir = (*i)->GetDir();
			switch (npc_dir)
			{
			case DIR_LEFT:
				(*i)->SetSequence(FRAME_LEFT, 20);
				break;
			case DIR_RIGHT:
				(*i)->SetSequence(FRAME_RIGHT, 20);
				break;
			case DIR_UP:
				(*i)->SetSequence(FRAME_UP, 20);
				break;
			case DIR_DOWN:
				(*i)->SetSequence(FRAME_DOWN, 20);
				break;
			}
			spAi->Wander((*i), npc_dir, (*i)->GetSpeed(), map.getBarrier());
		}
	}
	delete spAi;
}

void Npc::UpdateAnimation()
{
	vSpriteSet::iterator i;
	if (npc_set.size() > 0)
	{
		for (i = npc_set.begin(); i != npc_set.end(); i++)
		{
			(*i)->LoopFrame();
		}
	}
}
Npc::Npc()
{

}

Npc::~Npc()
{
}
