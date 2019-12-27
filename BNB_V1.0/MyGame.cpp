#include "MyGame.h"

MyGame::MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth,
	int iHeight) :T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight)
{
	wnd_width = iWidth;
	wnd_height = iHeight;
}

void MyGame::LoadPlayer()
{
	GAMELAYER gameLayer;
	SPRITEINFO spInfo;
	// ������ҽ�ɫ
	player = new Player(L".\\res\\blockorange.png", 80, 80);
	spInfo.Active = false;
	spInfo.Dead = false;
	spInfo.Dir = DIR_UP;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.5f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 10;
	spInfo.Alpha = 255;

	spInfo.X = t_scene.getSceneX();
	spInfo.Y = t_scene.getSceneY();

	spInfo.Visible = true;
	player->Initiate(spInfo);
	player->SetSequence(Player::FRAME_UP, 20);
	player->SetLayerTypeID(LAYER_PLY);
	gameLayer.layer = player;
	gameLayer.type_id = LAYER_PLY;
	// ������ǰ��ռ���t_scene��˳��ȷ����z_order
	gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);
}

void MyGame::LoadNPC(int NPC_NUM)
{
	for (int i = 0; i<NPC_NUM; i++)
	{
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
		//��ȡ�������(NPC��ɫ�ڵ�ͼ���Ľ�����)
		int sdr = rand() % 4;
		int d = rand() % 2;
		switch (sdr)
		{
		case 0://���Ͻ�
			if (d == 0)  spInfo.Dir = DIR_RIGHT;
			if (d == 1)  spInfo.Dir = DIR_DOWN;
			spInfo.X = t_scene.getSceneX();
			spInfo.Y = t_scene.getSceneY();
			break;
		case 1://���Ͻ�
			if (d == 0)  spInfo.Dir = DIR_LEFT;
			if (d == 1)  spInfo.Dir = DIR_DOWN;
			spInfo.X = t_scene.getSceneX() + scn_width - sp_width;
			spInfo.Y = t_scene.getSceneY();
			break;
		case 2://���½�
			if (d == 0)  spInfo.Dir = DIR_RIGHT;
			if (d == 1)  spInfo.Dir = DIR_UP;
			spInfo.X = t_scene.getSceneX();
			spInfo.Y = t_scene.getSceneY() + scn_height - sp_height;
			break;
		case 3://���½�
			if (d == 0)  spInfo.Dir = DIR_LEFT;
			if (d == 1)  spInfo.Dir = DIR_UP;
			spInfo.X = t_scene.getSceneX() + scn_width - sp_width;
			spInfo.Y = t_scene.getSceneY() + scn_height - sp_height;
			break;
		}

		//��NPC�б��������µ���Ŀ
		npc_set.push_back(new Npc(L".\\res\\blockgreen.png", 80, 80));

		//��ʼ�������ӵ���Ŀ
		Npc *npc = npc_set.back();
		npc->Initiate(spInfo);
		switch (spInfo.Dir)
		{
		case DIR_LEFT:
			npc->SetSequence(Npc::FRAME_LEFT, 20);
			break;
		case DIR_RIGHT:
			npc->SetSequence(Npc::FRAME_RIGHT, 20);
			break;
		case DIR_UP:
			npc->SetSequence(Npc::FRAME_UP, 20);
			break;
		case DIR_DOWN:
			npc->SetSequence(Npc::FRAME_DOWN, 20);
			break;
		}
		npc->SetLayerTypeID(LAYER_NPC);

		gameLayer.layer = npc;
		gameLayer.type_id = LAYER_NPC;
		gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
		gameLayer.layer->setZorder(gameLayer.z_order);
		t_scene.Append(gameLayer);
		npc = NULL;
	}
	
}


void MyGame::LoadMap()
{
	t_scene.LoadTxtMap(".\\map\\newMap.txt");
	scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
	scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
	// ��ͼ��ʼλ���Ե�ͼ��Ϊ����
	int scn_x = (wnd_width - scn_width) / 2;
	int scn_y = (wnd_height - scn_height) / 2;
	// ��ͼ��ʼ����λ���м�
	t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
	// �����е�ͼͼ�㶨λ����Ļ����
	SCENE_LAYERS::iterator p;
	for (p = t_scene.getSceneLayers()->begin(); p != t_scene.getSceneLayers()->end(); p++)
	{
		if (p->layer->ClassName() == "T_Map")
		{
			p->layer->SetPosition(scn_x, scn_y);
		}
	}
}



void MyGame::GameInit()
{
	LoadMap();
	LoadPlayer();
	// ʹ��Ĭ��ֵ10
	LoadNPC();
	// ��������
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	// ����wave�ļ���ʧ���򷵻�
	backmusic_buffer.LoadWave(ds, L".\\sound\\backmusic.wav");
	robot_buffer.LoadWave(ds, L".\\sound\\robot.wav");
	mousedown_buffer.LoadWave(ds, L".\\sound\\mousedown.wav");
	mousemove_buffer.LoadWave(ds, L".\\sound\\mouseover.wav");
	GameState = GAME_START;
	backmusic_buffer.Play(true);	// ѭ�����ű�������
}

void MyGame::GameLogic()
{
	GameKeyAction();
	// ���������ĽǶȳ�����������
	player->updatePos(player->GetDir(),&t_scene);
	player->updateAnimation();
	//npc.UpdateAnimation();	// ���¶���
	//player.UpdateAnimation();
	vector<Npc*>::iterator np;
	for (np = npc_set.begin();np != npc_set.end();np++)
	{
		(*np)->updatePos(player, &t_scene, npc_set);
		(*np)->updateAnimation();
	}
}

void MyGame::GameEnd()
{
}

void MyGame::GamePaint(HDC hdc)
{
	/*map.Draw(hdc,0,0);*/
	t_scene.Draw(hdc,0,0);
}

void MyGame::GameKeyAction(int ActionType)
{
	if (ActionType == KEY_SYS_NONE)
	{
		if (CheckKey(VK_LEFT)&&!CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(true);
			player->SetSequence(Player::FRAME_LEFT, 20);
			player->SetDir(DIR_LEFT);
			robot_buffer.Restore();
			robot_buffer.Play(false);
		}
		if (CheckKey(VK_UP) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player->SetActive(true);
			player->SetSequence(Player::FRAME_UP, 20);
			player->SetDir(DIR_UP);
			robot_buffer.Restore();
			robot_buffer.Play(false);
		}
		if (CheckKey(VK_DOWN) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player->SetActive(true);
			player->SetSequence(Player::FRAME_DOWN, 20);
			player->SetDir(DIR_DOWN);
			robot_buffer.Restore();
			robot_buffer.Play(false);
		}
		if (CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(true);
			player->SetSequence(Player::FRAME_RIGHT, 20);
			player->SetDir(DIR_RIGHT);
			robot_buffer.Restore();
			robot_buffer.Play(false);
		}// û�а������,��ôӦ��ͣ��
		if (!CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(false);
		}
	}
	
	
}

void MyGame::GameMouseAction(int x, int y, int ActionType)
{
}

MyGame::~MyGame()
{
	/*delete player.player;
	player.player = NULL;*/
}
