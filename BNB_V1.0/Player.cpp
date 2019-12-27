#include "Player.h"


int Player::FRAME_LEFT[20] = { 0,0,1,1,1,1,2,2,2,2,0,0,1,1,1,1,2,2,2,2 };
int Player::FRAME_RIGHT[20] = { 3,3,4,4,4,4,5,5,5,5,3,3,4,4,4,4,5,5,5,5 };
int Player::FRAME_UP[20] = { 6,6,7,7,7,7,8,8,8,8,6,6,7,7,7,7,8,8,8,8 };
int Player::FRAME_DOWN[20] = { 9,9,10,10,10,10,11,11,11,11,9,9,10,10,10,10,11,11,11,11 };
Player::Player(wstring imgPath, int frameWidth, int frameHeight):T_Sprite(imgPath, frameWidth, frameHeight)
{
}


Player::~Player()
{
}

void Player::updatePos(int dir, T_Scene* t_scene)
{
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;
	if (this->IsActive() && this->IsVisible())
	{
		switch (dir)
		{
		case DIR_LEFT:
			SpeedX = -this->GetSpeed();
			SpeedY = 0;
			// ������һ���Ƿ�Խ���߽�
			nextStepX = this->GetX() - this->GetSpeed();
			if (nextStepX <= 0)
			{
				SpeedX = 0 - this->GetX();
			}
			break;
		case DIR_RIGHT:
			SpeedX = this->GetSpeed();
			SpeedY = 0;
			// ������һ���ƶ��Ƿ񳬹��߽�
			nextStepX = this->GetX() + this->GetRatioSize().cx + this->GetSpeed();
			if (nextStepX >= WIN_WIDTH)
			{
				SpeedX = WIN_WIDTH - this->GetRatioSize().cx - this->GetX();
			}
			break;
		case DIR_UP:
			SpeedY = -this->GetSpeed();
			SpeedX = 0;
			// ������һ���ƶ��Ƿ񳬹��߽�
			nextStepY = this->GetY() - this->GetSpeed();
			if (nextStepY <= 0)
			{
				SpeedY = 0 - this->GetY();
			}
			break;
		case DIR_DOWN:
			SpeedX = 0;
			SpeedY = this->GetSpeed();
			nextStepY = this->GetY() + this->GetRatioSize().cy + SpeedY;
			if (nextStepY >= WIN_HEIGHT)
			{
				SpeedY = WIN_HEIGHT - this->GetRatioSize().cy - this->GetY();
			}
			break;
		}
		int x = this->GetX();	// ����ƶ�ǰ������
		int y = this->GetY();
		// TODO �Լ�����Ϸ��Ҫ�����������ʵ��ģ����ײ�����ǲ�һ�����ز���ײ
		if (!this->CollideWith(t_scene->getBarrier()))
		{
			this->Move(SpeedX, SpeedY);
		}
		if (this->CollideWith(t_scene->getBarrier()))
		{
			this->SetPosition(x, y);	// ��ԭ�ƶ�ǰ��λ��
		}
		t_scene->ScrollScene(this);
	}
}

void Player::updateAnimation()
{
	if (this->IsActive() && this->IsVisible())
	{
		this->LoopFrame();
	}
}
