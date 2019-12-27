#pragma once
#include ".\GameEngine\T_AI.h"
#include "Npc.h"
class Npc_AI :
	public T_AI
{
public:
	Npc_AI(int d_style);
	~Npc_AI();
	// 针对NPC进行的防重叠函数
	void CheckOverlay(Npc* npc, vector<Npc*> npc_set);
};

