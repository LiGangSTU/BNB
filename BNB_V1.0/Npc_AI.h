#pragma once
#include ".\GameEngine\T_AI.h"
#include "Npc.h"
class Npc_AI :
	public T_AI
{
public:
	Npc_AI(int d_style);
	~Npc_AI();
	// ���NPC���еķ��ص�����
	void CheckOverlay(Npc* npc, vector<Npc*> npc_set);
};

