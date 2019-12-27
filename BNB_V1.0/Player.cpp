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
			// 计算下一步是否越过边界
			nextStepX = this->GetX() - this->GetSpeed();
			if (nextStepX <= 0)
			{
				SpeedX = 0 - this->GetX();
			}
			break;
		case DIR_RIGHT:
			SpeedX = this->GetSpeed();
			SpeedY = 0;
			// 计算下一步移动是否超过边界
			nextStepX = this->GetX() + this->GetRatioSize().cx + this->GetSpeed();
			if (nextStepX >= WIN_WIDTH)
			{
				SpeedX = WIN_WIDTH - this->GetRatioSize().cx - this->GetX();
			}
			break;
		case DIR_UP:
			SpeedY = -this->GetSpeed();
			SpeedX = 0;
			// 计算下一步移动是否超过边界
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
		int x = this->GetX();	// 获得移动前的坐标
		int y = this->GetY();
		// TODO 自己的游戏需要重载这个函数实现模糊碰撞，就是差一点像素不碰撞
		if (!this->CollideWith(t_scene->getBarrier()))
		{
			this->Move(SpeedX, SpeedY);
		}
		if (this->CollideWith(t_scene->getBarrier()))
		{
			this->SetPosition(x, y);	// 还原移动前的位置
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
