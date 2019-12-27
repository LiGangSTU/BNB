#include "BNB_Player.h"

int BNB_Player::FRAME_DOWN[20] = { 0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4 };
int BNB_Player::FRAME_LEFT[20] = { 5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9 };
int BNB_Player::FRAME_RIGHT[20] = { 10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14 };
int BNB_Player::FRAME_UP[20] = { 15,15,15,15,16,16,16,16,17,17,17,17,18,18,18,18,19,19,19,19 };


void BNB_Player::LoadPlayer()
{
	GAMELAYER gameLayer;
	SPRITEINFO spInfo;
	// ������ҽ�ɫ
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
	// ������ǰ��ռ���t_scene��˳��ȷ����z_order
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
			// ������һ���Ƿ�Խ���߽�
			nextStepX = player->GetX() - player->GetSpeed();
			if (nextStepX <= 0)
			{
				SpeedX = 0 - player->GetX();
			}
			break;
		case DIR_RIGHT:
			SpeedX = player->GetSpeed();
			SpeedY = 0;
			// ������һ���ƶ��Ƿ񳬹��߽�
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
			// ������һ���ƶ��Ƿ񳬹��߽�
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
		int x = player->GetX();	// ����ƶ�ǰ������
		int y = player->GetY();
		// TODO �Լ�����Ϸ��Ҫ�����������ʵ��ģ����ײ�����ǲ�һ�����ز���ײ
		if (!player->CollideWith(map.getBarrier()))
		{
			player->Move(SpeedX, SpeedY);
		}
		if (player->CollideWith(map.getBarrier()))
		{
			player->SetPosition(x, y);	// ��ԭ�ƶ�ǰ��λ��
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
