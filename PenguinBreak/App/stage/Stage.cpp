#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
#include<string>

using namespace std;
Stage::Stage()
{}

Stage::~Stage()
{}

void Stage::Init()
{
	m_blockBox.Init();
	m_floorOBJ = Shape::CreateOBJ("ice", false, "OBJ/");
	m_floorGraph = Texture::Get()->LoadTexture(L"Resources/floor.png");

	MainInit(0);

	m_goalFish.Init();
	//動く床を初期化
	m_moveFloor.Init();
	//反転床を初期化
	m_floorPitfall.Init();
	//魚を初期化
	m_fishBox.Init();
	//電気の罠を初期化
	m_elect.Init();
	//危険魚を初期化
	m_dangerFish.Init();
	//落下地点
	m_dropPoint.Init();

	m_figurineOBJ.Init();

	m_boxStaring.Init();

	m_boxSE = Audio::SoundLoadWave("Resources/sound/SE/boxBreak.wav");
	m_goalSE = Audio::SoundLoadWave("Resources/sound/SE/goal.wav");
	m_jumpSE = Audio::SoundLoadWave("Resources/sound/SE/jump.wav");
	m_bombSE = Audio::SoundLoadWave("Resources/sound/SE/bomb.wav");

	m_water = Shape::CreateRect(500.0f, 500.0f);
	m_waterGraph = Texture::Get()->LoadTexture(L"Resources/cube/WaterTexture.jpg");
}

void Stage::MainInit(int stageNum)
{
	m_blockMax = 0;
	m_blockNum = 0;
	//床
	LoadStage(stageNum);
	m_goalFlag = false;
	m_goalSEFlag = false;
	//魚を消す
	m_fishBox.Delete();
}

void Stage::Update(const Vec3& pPos)
{
	Vec3 PPos = pPos;

	m_dropPoint.ActiveNo();
	m_boxStaring.Update();
	for (auto& s : stageData)
	{
		if (s->fileName.compare("WALL") == 0 || s->fileName.compare("STLON") == 0 || s->fileName.compare("DEADTREE") == 0 || s->fileName.compare("BARRIERWALL") == 0
			|| s->fileName.compare("SIGNBOARD1") == 0 || s->fileName.compare("SIGNBOARD2") == 0 || CheckBoxJudge(s) == true)
		{
			m_blockBox.PlayerHit(s);
			m_blockBox.PlayerSpinHit(s);
			if (!(s->fileName.compare("WALL") == 0 || s->fileName.compare("DEADTREE") == 0 || s->fileName.compare("BARRIERWALL") == 0))
			{
				m_dropPoint.Update(PPos, s->position,
					s->rotation, s->scale);
			}
		}
		else if (s->fileName.compare("GOAL") == 0)
		{
			if (Collision::CheckBox2Box(s->box, Player::Get()->GetBox()))
			{
				//ゴール
				m_goalFlag = true;
				if (m_goalSEFlag == false)
				{
					Audio::Get()->SoundSEPlayWave(m_goalSE);
				}
				m_goalSEFlag = true;
			}
			m_goalFish.Update();
		}
	}
	//壊れる箱の処理
	BreakBoxs();
	for (auto& s : stageData)
	{
		if (s->fileName.compare("FLOORNORMAL") == 0)
		{
			m_dropPoint.Update(PPos, s->position,
				s->rotation, s->scale);
			if (Player::Get()->GetIsFishDie() == false)
			{
				//プレイヤー
				PushCollision::Player2Floor(s->position,
					s->rotation, s->scale);
			}
		}
		else if (s->fileName.compare("FLOORMOVE") == 0 || s->fileName.compare("FLOORMOVE2") == 0)
		{
			if (Player::Get()->GetIsFishDie() == false)
			{
				//プレイヤー
				PushCollision::Player2Floor(s->position,
					s->rotation, s->scale, s->actionType);
				m_dropPoint.Update(PPos, s->position,
					s->rotation, s->scale);

			}
			m_moveFloor.Update(s);
		}
	}

	//	case ELECTRICITY:
	//		m_elect.Update(s);
	//		break;
	//	case FISHATTACK:
	//		if (Collision::CheckBox2Box(s->box, Player::Get()->GetBox()))
	//		{
	//			Player::Get()->DieType(EATDIE);
	//			Player::Get()->FishDie(s->position, m_dangerFish.GetFishAngle());
	//		}
	//		m_dangerFish.Update(s);
	//		break;
	//	case FLOOR11:
	//	case FLOOR169:
	//		if (Player::Get()->GetIsFishDie() == false)
	//		{
	//			//プレイヤー
	//			PushCollision::Player2Floor(s->position,
	//				s->rotation, s->scale);
	//		}
	//		break;
	//	case FLOORPITFALL_A:
	//	case FLOORPITFALL_B:
	//		if (Player::Get()->GetIsFishDie() == false)
	//		{
	//			if (s->actionType == 0)
	//			{
	//				PushCollision::Player2Floor(s->position,
	//					s->rotation, s->scale);
	//				m_dropPoint.Update(PPos, s->position,
	//					s->rotation, s->scale);
	//			}
	//		}
	//		m_floorPitfall.Update(s);
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//箱の更新
	m_blockBox.Update();

	m_elect.AllUpdate();

	m_dangerFish.AllUpdate();
	//魚の更新
	m_fishBox.Update(pPos);
}

void Stage::Draw(const Vec3& pPos, bool shadowFlag)
{
	Vec3 PPos = pPos;

	for (auto& s : stageData)
	{
		if (s->fileName.compare("WALL") == 0 || s->fileName.compare("STLON") == 0
			|| s->fileName.compare("DEADTREE") == 0 || s->fileName.compare("BARRIERWALL") == 0
			|| s->fileName.compare("ICEARCH") == 0 || s->fileName.compare("SIGNBOARD1") == 0 || s->fileName.compare("SIGNBOARD2") == 0)
		{
			m_figurineOBJ.Draw(s, shadowFlag);
		}
		else if (CheckBoxJudge(s) == true)
		{
			m_blockBox.Draw(s, shadowFlag);
		}
		else if (s->fileName.compare("FLOORNORMAL") == 0)
		{
			Object::Draw(m_floorOBJ, s->psr, Vec3(s->position.x, s->position.y, s->position.z),
				s->scale, s->rotation, Vec2(), 0, shadowFlag);
		}
		else if (s->fileName.compare("GOAL") == 0)
		{
			m_goalFish.Draw(s, shadowFlag);
		}
		else if (s->fileName.compare("FLOORMOVE") == 0 || s->fileName.compare("FLOORMOVE2") == 0)
		{
			m_moveFloor.Draw(s, shadowFlag);
		}

	}

	//switch (s->type)
	//{
	//case FLOOR169:
	//	Object::Draw(m_floorOBJ, s->psr, Vec3(s->position.x, s->position.y - 12.0f, s->position.z + 9.5f),
	//		Vec3(25.0f, 30.0f, 32.1f * 2),
	//		s->rotation, Vec2(), m_floorGraph, shadowFlag);
	//case FLOOR11:
	//	Object::Draw(m_floorOBJ, s->psr, Vec3(s->position.x, s->position.y - 12.0f, s->position.z - 9.5f),
	//		Vec3(25.0f, 30.0f, 32.1f),
	//		s->rotation, Vec2(), m_floorGraph, shadowFlag);
	//case FLOORPITFALL_A:
	//case FLOORPITFALL_B:
	//	m_floorPitfall.Draw(s, shadowFlag);
	//case ELECTRICITY:
	//	m_elect.Draw(s, shadowFlag);
	//case FISHATTACK:
	//	m_dangerFish.Draw(s, shadowFlag);


	DrawWater();

	//箱壊した時に出る魚
	m_fishBox.Draw();

	m_dropPoint.Draw(Player::Get()->GetPosition());

	m_boxStaring.Draw3D();
}

void Stage::DrawParicle()
{
	m_elect.DrawParicle();
	//パーティクル
	m_boxStaring.Draw();
}

void Stage::LoadStage(int stageNum)
{

	stageData.clear();

	string FilepathFloor = "";

	switch (stageNum)
	{
	case 0:
		FilepathFloor = "select";
		break;
	case 1:
		FilepathFloor = "stage01";
		break;
	case 2:
		FilepathFloor = "stage02";
		break;
	case 3:
		FilepathFloor = "stage03";
		break;
	default:
		break;
	}

	levelData = LoadJson::Load(FilepathFloor);
	for (auto& loadData : levelData->objects)
	{
		switch (loadData.type)
		{
		case MESHTYPE:
		{
			StageData* objectData = new StageData();
			objectData->position = loadData.translation;
			objectData->rotation = loadData.rotation;
			objectData->scale = loadData.scaling;
			objectData->fileName = loadData.fileName;
			if (objectData->fileName.compare("WALL") == 0 || objectData->fileName.compare("STLON") == 0
				|| objectData->fileName.compare("DEADTREE") == 0 || objectData->fileName.compare("BARRIERWALL") == 0
				|| objectData->fileName.compare("ICEARCH") == 0 || objectData->fileName.compare("SIGNBOARD1") == 0 || objectData->fileName.compare("SIGNBOARD2") == 0)
			{
				objectData->rotation.z -= 90.0f;
				objectData->box.maxPosition =
					XMVectorSet(objectData->position.x + m_wallScale.x / 2, objectData->position.y + m_wallScale.y / 2, objectData->position.z + m_wallScale.z / 2, 1);
				objectData->box.minPosition =
					XMVectorSet(objectData->position.x - m_wallScale.x / 2, objectData->position.y - m_wallScale.y / 2, objectData->position.z - m_wallScale.z / 2, 1);
			}
			else if (CheckBoxJudge(objectData) == true)
			{
				objectData->rotation.z -= 90.0f;
				objectData->box.maxPosition =
					XMVectorSet(objectData->position.x + boxScale / 2, objectData->position.y + boxScale / 2, objectData->position.z + boxScale / 2, 1);
				objectData->box.minPosition =
					XMVectorSet(objectData->position.x - boxScale / 2, objectData->position.y - boxScale / 2, objectData->position.z - boxScale / 2, 1);
			}
			else if (objectData->fileName.compare("GOAL") == 0)
			{
				objectData->rotation.z -= 90.0f;
				objectData->box.maxPosition =
					XMVectorSet(objectData->position.x + m_goalFish.GetGoalScale().x / 2, objectData->position.y + m_goalFish.GetGoalScale().y / 2, objectData->position.z + m_goalFish.GetGoalScale().z / 2, 1);
				objectData->box.minPosition =
					XMVectorSet(objectData->position.x - m_goalFish.GetGoalScale().x / 2, objectData->position.y - m_goalFish.GetGoalScale().y / 2, objectData->position.z - m_goalFish.GetGoalScale().z / 2, 1);
			}
			else if (objectData->fileName.compare("FLOORMOVE") == 0)
			{
				objectData->actionType = MOVEFRONT;
			}
			else if (objectData->fileName.compare("FLOORMOVE2") == 0)
			{
				objectData->actionType = MOVEBACK;
			}
			stageData.push_back(objectData);
		}
		break;
		default:
			break;
		}
	}
}

void Stage::DrawWater()
{
	m_waterUV.y += 0.001f;
	if (m_waterUV.y >= 1.0f)
	{
		m_waterUV.y = 0.0f;
	}
	for (size_t i = 0; i < 6; i++)
	{
		Object::NoShadowDraw(m_water, PSR(),
			Vec3(50.0f, -70.0f, 500.0f * i), Vec3(1.0f, 1.0f, 1.0f),
			Vec3(90.0f, 0.0f, 0.0f), m_waterUV, m_waterGraph);
	}
}

void Stage::BreakBoxs()
{
	//踏むか叩いて壊れる箱の処理
	if (m_blockBox.GetIs_Hit() == true && Player::Get()->GetIsFishDie() == false)
	{
		int breakNum = -1;
		int breakFlag = PushCollision::PlayerBreakBox(m_blockBox.GetObj_Data(), breakNum);
		if (breakFlag == 1 && Player::Get()->GetOldGroundFlag() == false)
		{
			for (int i = 0; i < stageData.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOX") == 0)
				{
					Player::Get()->ActivateBlockStepOn();
					Player::Get()->ActivateChangeBreak();
					m_boxStaring.BreakBoxFlag(stageData[i]->position);
					m_fishBox.Create(stageData[i]->position);
					delete stageData[i];
					stageData.erase(stageData.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
					break;
				}//ジャンプ台
				else if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOXJUMP") == 0)
				{
					Player::Get()->ActivateJumpBox();
					Player::Get()->ActivateBlockStepOn();
					Audio::Get()->SoundSEPlayWave(m_jumpSE);
				}//爆発箱
				else if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOXBOMB") == 0)
				{
					Player::Get()->DieType(BOMBDIE);
					m_boxStaring.BombBoxFlag(stageData[i]->position);
					delete stageData[i];
					stageData.erase(stageData.begin() + i);
					Audio::Get()->SoundSEPlayWave(m_bombSE);
				}
			}
		}
		else if (breakFlag == 2)
		{
			for (int i = 0; i < stageData.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOX") == 0)
				{
					Player::Get()->JumpPoweZero();
					Player::Get()->ActivateChangeBreak();
					m_boxStaring.BreakBoxFlag(stageData[i]->position);
					m_fishBox.Create(stageData[i]->position);
					delete stageData[i];
					stageData.erase(stageData.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
				}
				else if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOXBOMB") == 0)
				{
					Player::Get()->DieType(BOMBDIE);
					m_boxStaring.BombBoxFlag(stageData[i]->position);
					delete stageData[i];
					stageData.erase(stageData.begin() + i);
					Audio::Get()->SoundSEPlayWave(m_bombSE);
				}
			}
		}
	}
	//スピンで壊れる箱の処理
	if (m_blockBox.GetIs_Spin() == true)
	{
		for (int i = 0; i < stageData.size(); i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (stageData.size() != i)
				{
					if (m_blockBox.GetObj_Spin(j).position == stageData[i]->position &&
						stageData[i]->fileName.compare("BOX") == 0)
					{
						m_boxStaring.BreakBoxFlag(stageData[i]->position);
						m_fishBox.Create(stageData[i]->position);
						delete stageData[i];
						stageData.erase(stageData.begin() + i);
						m_blockNum++;
						Audio::Get()->SoundSEPlayWave(m_boxSE);
					}
					else if (m_blockBox.GetObj_Spin(j).position == stageData[i]->position &&
						stageData[i]->fileName.compare("BOXBOMB") == 0)
					{
						//爆発オン
						Player::Get()->DieType(BOMBDIE);
						//爆発演出
						m_boxStaring.BombBoxFlag(stageData[i]->position);
						delete stageData[i];
						stageData.erase(stageData.begin() + i);
						Audio::Get()->SoundSEPlayWave(m_bombSE);
					}
				}
			}
		}
	}
}

bool Stage::CheckBoxJudge(StageData* stageData)
{
	if (stageData == nullptr) { assert(0); }
	if (stageData->fileName.compare("BOX") == 0 ||stageData->fileName.compare("BOXJUMP") == 0 ||
		stageData->fileName.compare("BOXHARD") == 0 ||stageData->fileName.compare("BOXBOMB") == 0)
	{
		return true;
	}
	return false;
}
