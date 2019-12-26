#include "BNB_Player.h"

int BNB_Player::FRAME_DOWN[20] = { 0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4 };
int BNB_Player::FRAME_LEFT[20] = { 5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9 };
int BNB_Player::FRAME_RIGHT[20] = { 10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14 };
int BNB_Player::FRAME_UP[20] = { 15,15,15,15,16,16,16,16,17,17,17,17,18,18,18,18,19,19,19,19 };


void BNB_Player::LoadPlayer()
{
	GAMELAYER gameLayer;
	SPRITEINFO spInfo;
	// 加载玩家角色
	player = new T_Sprite(L".\\res\\spritesheet.png", 42, 56);
	spInfo.Active = false;
	spInfo.Dead = false;
	spInfo.Dir = DIR_UP;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.5f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 10;
	spInfo.Alpha = 255;
	spInfo.X = map.getSceneX();
	spInfo.Y = map.getSceneY();
	spInfo.Visible = true;
	player->Initiate(spInfo);
	player->SetSequence(FRAME_UP, 20);
	player->SetLayerTypeID(LAYER_PLY);
	gameLayer.layer = player;
	gameLayer.type_id = LAYER_PLY;
	// 这里就是按照加入t_scene的顺序确定的z_order
	gameLayer.z_order = map.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	map.Append(gameLayer);
}

void BNB_Player::UpdateplayerPos(int dir)
{
	if (player == NULL)
	{
		return;
	}
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;
	if (player->IsActive() && player->IsVisible())
	{
		switch (dir)
		{
		case DIR_LEFT:
			SpeedX = -player->GetSpeed();
			SpeedY = 0;
			// 计算下一步是否越过边界
			nextStepX = player->GetX() - player->GetSpeed();
			if (nextStepX <= 0)
			{
				SpeedX = 0 - player->GetX();
			}
			break;
		case DIR_RIGHT:
			SpeedX = player->GetSpeed();
			SpeedY = 0;
			// 计算下一步移动是否超过边界
			nextStepX = player->GetX() + player->GetRatioSize().cx + player->GetSpeed();
			int wnd_width, wnd_height;
			wnd_width = map.getSceneLayers()->back().layer->GetWidth();
			wnd_height = map.getSceneLayers()->back().layer->GetHeight();
			if (nextStepX >= wnd_width)
			{
				SpeedX = wnd_width - player->GetRatioSize().cx - player->GetX();
			}
			break;
		case DIR_UP:
			SpeedY = -player->GetSpeed();
			SpeedX = 0;
			// 计算下一步移动是否超过边界
			nextStepY = player->GetY() - player->GetSpeed();
			if (nextStepY <= 0)
			{
				SpeedY = 0 - player->GetY();
			}
			break;
		case DIR_DOWN:
			SpeedX = 0;
			SpeedY = player->GetSpeed();
			nextStepY = player->GetY() + player->GetRatioSize().cy + SpeedY;
			if (nextStepY >= wnd_height)
			{
				SpeedY = wnd_height - player->GetRatioSize().cy - player->GetY();
			}
			break;
		}
		int x = player->GetX();	// 获得移动前的坐标
		int y = player->GetY();
		// TODO 自己的游戏需要重载这个函数实现模糊碰撞，就是差一点像素不碰撞
		if (!player->CollideWith(map.getBarrier()))
		{
			player->Move(SpeedX, SpeedY);
		}
		if (player->CollideWith(map.getBarrier()))
		{
			player->SetPosition(x, y);	// 还原移动前的位置
		}
		map.ScrollScene(player);
	}
}

void BNB_Player::UpdateAnimation()
{
	if (player != NULL)
	{
		if (player->IsActive() && player->IsVisible())
		{
			player->LoopFrame();
		}
	}
}

BNB_Player::BNB_Player()
{

}

BNB_Player::~BNB_Player()
{
}
