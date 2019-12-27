#include "Npc.h"
#include  "Npc_AI.h"

int Npc::FRAME_LEFT[20] = { 0,0,1,1,1,1,2,2,2,2,0,0,1,1,1,1,2,2,2,2 };
int Npc::FRAME_RIGHT[20] = { 3,3,4,4,4,4,5,5,5,5,3,3,4,4,4,4,5,5,5,5 };
int Npc::FRAME_UP[20] = { 6,6,7,7,7,7,8,8,8,8,6,6,7,7,7,7,8,8,8,8 };
int Npc::FRAME_DOWN[20] = { 9,9,10,10,10,10,11,11,11,11,9,9,10,10,10,10,11,11,11,11 };
Npc::Npc(wstring imgPath, int frameWidth , int frameHeight ):T_Sprite(imgPath, frameWidth,frameHeight)
{
}


Npc::~Npc()
{
}

void Npc::updatePos(T_Sprite* player, T_Scene* t_scene, vector<Npc*> npc_set)
{
	// 不需要每次都遍历其余NPC，在外部控制循环就好了
	Npc_AI* spAi = new Npc_AI(4);
	if (this->IsActive() && this->IsVisible())
		{
			spAi->Evade(this, player);	// 躲避玩家角色
			spAi->CheckOverlay(this, npc_set);	// 防止互相重叠
			int npc_dir = this->GetDir();
			switch (npc_dir)
			{
			case DIR_LEFT:
				this->SetSequence(FRAME_LEFT, 20);
				break;
			case DIR_RIGHT:
				this->SetSequence(FRAME_RIGHT, 20);
				break;
			case DIR_UP:
				this->SetSequence(FRAME_UP, 20);
				break;
			case DIR_DOWN:
				this->SetSequence(FRAME_DOWN, 20);
				break;
			}
			spAi->Wander(this, npc_dir, this->GetSpeed(), t_scene->getBarrier());
		}
	delete spAi;
}

void Npc::updateAnimation()
{
	if (this->IsActive() && this->IsVisible())
	{
		this->LoopFrame();
	}
}
