#include "Npc_AI.h"



Npc_AI::Npc_AI(int d_style):T_AI(d_style)
{
}


Npc_AI::~Npc_AI()
{
}

void Npc_AI::CheckOverlay( Npc* npc, vector<Npc*> npc_set)
{
	vector<Npc*>::iterator np;

	RECT testRec;
	GetHitRect(npc, 1, testRec);// 获取当前Sprite周围的矩形

	int r_dir = 0;
	if (dir_style == 8)
	{
		r_dir = rand() % 5;
	}
	else
	{
		r_dir = rand() % 3;
	}

	RECT lprcDst;
	for (np = npc_set.begin(); np != npc_set.end(); np++)
	{
		if (*np == npc) continue;

		RECT pRect = { (*np)->GetX(), (*np)->GetY(),
			(*np)->GetX() + (*np)->GetRatioSize().cx,
			(*np)->GetY() + (*np)->GetRatioSize().cy };

		if ((IntersectRect(&lprcDst, &pRect, &testRec)) == TRUE)
		{
			npc->SetDir(EvadeDir[npc->GetDir()][r_dir]);
		}
	}
}
