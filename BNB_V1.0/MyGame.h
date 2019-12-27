#pragma once
#include ".\\GameEngine\T_Engine.h"

#include "Npc.h"
#include  "Npc_AI.h"
#include "Player.h"
#include "GameEngine/T_Scene.h"
#include "Explosion.h"
#include "Bomb.h"
#include "GameMenu.h"
#include "GameEngine/T_Audio.h"

typedef  vector<T_Sprite*> vSpriteSet;

class MyGame :
	public T_Engine
{
private:
	int wnd_width;
	int wnd_height;	// ���ڿ��
	int NPC_NUM = 10;	//npc����
	
public:
	MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon = NULL, WORD SmIcon = NULL, int iWidth = 800,
		int iHeight = 800);
	~MyGame();

	//Npc* npc;
	Player* player;
	vector<Bomb*> Player_bomb_set;// ����ڵ�����
	vector<Npc*> npc_set;	// NPC��ɫ����
	vector<Bomb*> Npc_bomb_set;	// Npc�ڵ�����
	
	// ��������
	AudioDX ds;
	AudioDXBuffer backmusic_buffer;	// ��������
	AudioDXBuffer robot_buffer;		// ��������
	AudioDXBuffer mousedown_buffer;	// �������Ч
	AudioDXBuffer mousemove_buffer;	// ��껬����Ч
	AudioDXBuffer blast_buffer;		// ��ը��Ч
	// ������
	T_Scene t_scene;
	// �������
	int scn_width;
	int scn_height;
	// �˵���
	GameMenu game_menu;
	//++++++++++++++++++++++++
	// �������
	void LoadPlayer();
	// ����NPC
	void LoadNPC(int NPC_NUM = 10);
	// �����ͼ
	void LoadMap();
	void GameInit() override;
	void GameLogic() override;
	void GameEnd() override;
	void GamePaint(HDC hdc) override;
	void GameKeyAction(int ActionType = KEY_SYS_NONE) override;
	void GameMouseAction(int x, int y, int ActionType) override;
};

