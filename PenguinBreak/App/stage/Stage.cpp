#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
#include<string>

using namespace std;
Stage::Stage()
{}

Stage::~Stage()
{
	for (int i = (int)floor.size() - 1; i >= 0; i--)
	{
		delete floor[i];
		floor.erase(floor.begin() + i);
	}
	for (int i = (int)stageObj.size() - 1; i >= 0; i--)
	{
		delete stageObj[i];
		stageObj.erase(stageObj.begin() + i);
	}
}

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
	//判定する箇所だけ行うため
	int Z = static_cast<int>(PPos.z / (-c_mapSize));
	int X = static_cast<int>(PPos.x / c_mapSize);

	m_dropPoint.ChangeFlag();

	m_boxStaring.Update();

	for (auto& s : stageObj)
	{
		switch (s->type)
		{
		case WALL:
		case BARRIERWALL:
		case DEADTREE:
		case STLON:
		case BOX:
		case BOXJUMP:
		case BOXHARD:
		case BOXBOMB:
			m_blockBox.PlayerHit(s, X, Z);
			m_blockBox.PlayerSpinHit(s, X, Z);
			if (!(s->type == WALL || s->type == DEADTREE || s->type == BARRIERWALL))
			{
				m_dropPoint.Update(PPos, s->position,
					s->angle, s->scale);
			}
			break;
		case GOAL:
			if ((X - 1 <= s->map.x && s->map.x <= X + 1)
				&& ((MAP_HEIGHT - 1 + Z) - 1 <= s->map.y && s->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
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
			}
			m_goalFish.Update();
			break;
		case ELECTRICITY:
			m_elect.Update(s, Z);
			break;
		case FISHATTACK:
			if ((MAP_HEIGHT - 1 + Z) - 1 <= s->map.y && s->map.y <= (MAP_HEIGHT - 1 + Z) + 1)
			{
				if (Collision::CheckBox2Box(s->box, Player::Get()->GetBox()))
				{
					Player::Get()->DieType(EATDIE);
					Player::Get()->FishDie(s->actionPos, m_dangerFish.GetFishAngle());
				}
			}
			m_dangerFish.Update(s);
			break;
		default:
			break;
		}
	}
	//壊れる箱の処理
	BreakBoxs();

	//箱の更新
	m_blockBox.Update();

	m_elect.AllUpdate();

	m_dangerFish.AllUpdate();
	//床
	for (auto f : floor)
	{
		switch (f->type)
		{
		case FLOORNORMAL:
			m_dropPoint.Update(PPos, f->position,
				f->angle, f->scale);
		case FLOOR11:
		case FLOOR169:
			if ((X - 1 <= f->map.x && f->map.x <= X + 1)
				&& ((MAP_HEIGHT - 1 + Z) - 100 <= f->map.y && f->map.y <= (MAP_HEIGHT - 1 + Z) + 100)
				&& Player::Get()->GetIsFishDie() == false)
			{
				//プレイヤー
				PushCollision::Player2Floor(f->position,
					f->angle, f->scale);
			}
			break;
		case FLOORMOVE:
			if ((X - 3 <= f->map.x && f->map.x <= X + 3)
				&& ((MAP_HEIGHT - 1 + Z) - 4 <= f->map.y && f->map.y <= (MAP_HEIGHT - 1 + Z) + 4)
				&& Player::Get()->GetIsFishDie() == false)
			{
				//プレイヤー
				PushCollision::Player2Floor(f->position,
					f->angle, f->scale, f->moveFlag);
				m_dropPoint.Update(PPos, f->position,
					f->angle, f->scale);

			}
			m_moveFloor.Update(f);
			break;
		case FLOORPITFALL_A:
		case FLOORPITFALL_B:
			if (((MAP_HEIGHT - 1 + Z) - c_drawNumY <= f->map.y && f->map.y <= (MAP_HEIGHT - 1 + Z) + 4)
				&& Player::Get()->GetIsFishDie() == false)
			{
				if (f->moveFlag == 0)
				{
					PushCollision::Player2Floor(f->position,
						f->angle, f->scale);
					m_dropPoint.Update(PPos, f->position,
						f->angle, f->scale);
				}
			}
			m_floorPitfall.Update(f);
			break;
		default:
			break;
		}
	}
	//魚の更新
	m_fishBox.Update(pPos);
}

void Stage::Draw(const Vec3& pPos, bool shadowFlag)
{
	Vec3 PPos = pPos;
	//判定する箇所だけ行うため
	int Z = static_cast<int>(PPos.z / (-c_mapSize));
	static const int floorNormalMax = (MAP_HEIGHT - 1 + Z) - 100;
	static const int stageMin = (MAP_HEIGHT - 1 + Z) + 6;
	//床の描画
	for (auto f : floor)
	{
		switch (f->type)
		{
		case FLOORNORMAL:
			if (floorNormalMax <= f->map.y && f->map.y <= stageMin)
			{
				Object::Draw(m_floorOBJ, f->psr, Vec3(f->position.x, f->position.y - 20.0f, f->position.z),
					Vec3(25.0f, 40.0f, 25.0f * (f->size + 1)),
					f->angle, Vec2(), 0, shadowFlag);
			}
			break;
		case FLOOR169:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= f->map.y && f->map.y <= stageMin)
			{
				Object::Draw(m_floorOBJ, f->psr, Vec3(f->position.x, f->position.y - 12.0f, f->position.z + 9.5f),
					Vec3(25.0f, 30.0f, 32.1f * 2),
					f->angle, Vec2(), m_floorGraph, shadowFlag);
			}
			break;
		case FLOOR11:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= f->map.y && f->map.y <= stageMin)
			{
				Object::Draw(m_floorOBJ, f->psr, Vec3(f->position.x, f->position.y - 12.0f, f->position.z - 9.5f),
					Vec3(25.0f, 30.0f, 32.1f),
					f->angle, Vec2(), m_floorGraph, shadowFlag);
			}
			break;
		case FLOORMOVE:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= f->map.y && f->map.y <= stageMin)
			{
				m_moveFloor.Draw(f, shadowFlag);
			}
			break;
		case FLOORPITFALL_A:
		case FLOORPITFALL_B:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= f->map.y && f->map.y <= stageMin)
			{
				m_floorPitfall.Draw(f, shadowFlag);
			}
			break;
		default:
			break;
		}

	}
	//オブジェクト描画
	for (auto s : stageObj)
	{
		if ((MAP_HEIGHT - 1 + Z) - c_drawNumY <= s->map.y && s->map.y <= stageMin)
		{
			switch (s->type)
			{
			case WALL:
			case DEADTREE:
			case STLON:
			case ICEARCH:
			case SIGNBOARD1:
			case SIGNBOARD2:
				m_figurineOBJ.Draw(s, shadowFlag);
				break;
			case  GOAL:
				m_goalFish.Draw(s, shadowFlag);
				break;
			case BOX:
			case BOXJUMP:
			case BOXHARD:
			case BOXBOMB:
				m_blockBox.Draw(s, shadowFlag);
				break;
			case ELECTRICITY:
				m_elect.Draw(s, shadowFlag);
				break;
			case FISHATTACK:
				m_dangerFish.Draw(s, shadowFlag);
				break;
			default:
				break;
			}
		}
	}

	//左右の床の描画
	Object::Draw(m_floorOBJ, m_blackPsr[1], Vec3(-340.0f, 5.0f, pPos.z + 600.0f),
		Vec3(650.0f, 15.0f, 1500.0f),
		Vec3(), Vec2(), 0, shadowFlag);
	Object::Draw(m_floorOBJ, m_blackPsr[2], Vec3(560.0f, 5.0f, pPos.z + 600.0f),
		Vec3(650.0f, 15.0f, 1500.0f),
		Vec3(), Vec2(), 0, shadowFlag);

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
	for (int i = (int)floor.size() - 1; i >= 0; i--)
	{
		delete floor[i];
		floor.erase(floor.begin() + i);
	}
	for (int i = (int)stageObj.size() - 1; i >= 0; i--)
	{
		delete stageObj[i];
		stageObj.erase(stageObj.begin() + i);
	}
	const string basePath = "Resources/map/";
	string FilepathFloor = "";
	string FilepathFloorPos = "";
	string FilepathOBJ = "";
	string FilepathOBJPos = "";
	switch (stageNum)
	{
	case 0:
		//Floor
		FilepathFloor = "selectFloor.csv";
		FilepathFloorPos = "Resources/map/selectTitlePos.csv";
		//OBJ
		FilepathOBJ = "selectObj.csv";
		FilepathOBJPos = "selectObjPos.csv";
		break;
	case 1:
		//Floor
		FilepathFloor = "Floor_Title1.csv";
		FilepathFloorPos = "Floor_TitlePos1.csv";
		//OBJ
		FilepathOBJ = "OBJTitle1.csv";
		FilepathOBJPos = "Obj_TitlePos1.csv";
		break;
	case 2:
		//Floor
		FilepathFloor = "Floor_Title2.csv";
		FilepathFloorPos = "Floor_TitlePos2.csv";
		//OBJ
		FilepathOBJ = "OBJTitle2.csv";
		FilepathOBJPos = "Obj_TitlePos2.csv";
		break;
	case 3:
		//Floor
		FilepathFloor = "Floor_Title3.csv";
		FilepathFloorPos = "Floor_TitlePos3.csv";
		//OBJ
		FilepathOBJ = "OBJTitle3.csv";
		FilepathOBJPos = "Obj_TitlePos3.csv";
		break;
	default:
		break;
	}

	////ブロック
	int	Map[MAP_HEIGHT][MAP_WIDTH] = {};		//マップチップ
	int MapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int MapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//壁などのOBJ
	int MapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//壁などのOBJの座標
	LoadCSV(Map, basePath + FilepathFloor);
	LoadCSV(MapPos, basePath + FilepathFloorPos);

	LoadCSV(MapOBJ, basePath + FilepathOBJ);
	LoadCSV(MapOBJPos, basePath + FilepathOBJPos);

	for (size_t y = 0; y < MAP_HEIGHT; y++)
	{
		for (size_t x = 0; x < MAP_WIDTH; x++)
		{
			Vec2 map = { static_cast<float>(x), static_cast<float>(y) };
			//OBJ
			switch (Map[y][x])
			{
			case NONEFLOOR:
				break;
			case FLOORNORMAL:
			{
				int num_ = 1;
				while (Map[y + num_][x] == FLOORNORMAL)
				{
					Map[y + num_][x] = 0;
					num_++;
					if (y + num_ >= MAP_HEIGHT)
					{
						break;
					}
				}
				SetFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, FLOORNORMAL, num_ - 1);
			}
			break;
			case FLOOR169:
				SetFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f + 0.0f, (MAP_HEIGHT - 1 - y) * c_mapSize + 12.3f),
					Vec3(c_mapSize, 1.0f, 32.01f * 2), Vec3(141.61f, 0.0f, 0.0f), map, FLOOR169);
				break;
			case FLOOR11:
				SetFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f - 10.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					Vec3(c_mapSize, 1.0f, 32.01f), Vec3(38.39f, 0.0f, 0.0f), map, FLOOR11);
				break;
			case FLOORMOVE:
				SetMoveFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, FLOORMOVE);
				break;
			case FLOORPITFALL_A:
				SetPitfallFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, 70);
				break;
			case FLOORPITFALL_B:
				SetPitfallFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, 140);
				break;
			case FLOORMOVE2:
				SetMoveFloor(Vec3(map.x * c_mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, FLOORMOVE2);
				break;
			default:
				break;
			}
			switch (MapOBJ[y][x])
			{
			case NONEOBJ:
				break;
			case WALL:
			case BARRIERWALL:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_wallScale.y / 2 - 20.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_wallScale, Vec3(), map, MapOBJ[y][x]);
				break;
			case GOAL:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20 + 5.0f, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_goalFish.GetGoalScale(), Vec3(), map, GOAL);
				break;
			case BOX:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOX);
				break;
			case BOXDOUBLE:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOX);
				SetObject(Vec3(static_cast<float>(x) * c_mapSize, (static_cast<float>(MapOBJPos[y][x]) + 1.0f) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOX);
				break;
			case BOXJUMP:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOXJUMP);
				break;
			case BOXHARD:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOXHARD);
				break;
			case BOXBOMB:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOXBOMB);
				break;
			case BOX_BOMB:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOX);
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x] + 1.0f) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOXBOMB);
				break;
			case BOMB_BOX:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOXBOMB);
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x] + 1.0f) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map, BOX);
				break;
			case ELECTRICITY:
				SetElectricity(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map);
				break;
			case FISHATTACK:
				SetFishAttack(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_blockBox.GetBoxScale(), Vec3(), map);
				break;
			case DEADTREE:
			case STLON:
			case ICEARCH:
			case SIGNBOARD1:
			case SIGNBOARD2:
				SetObject(Vec3(map.x * c_mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + m_blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * c_mapSize),
					m_wallScale, Vec3(), map, MapOBJ[y][x]);
				break;
			default:
				break;
			}
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
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (m_blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOX == stageObj[i]->type)
				{
					Player::Get()->ActivateBlockStepOn();
					Player::Get()->ActivateChangeBreak();
					m_boxStaring.BreakBoxFlag(stageObj[i]->position);
					m_fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
					break;
				}//ジャンプ台
				else if (m_blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXJUMP == stageObj[i]->type)
				{
					Player::Get()->ActivateJumpBox();
					Player::Get()->ActivateBlockStepOn();
					Audio::Get()->SoundSEPlayWave(m_jumpSE);
				}//爆発箱
				else if (m_blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXBOMB == stageObj[i]->type)
				{
					Player::Get()->DieType(BOMBDIE);
					m_boxStaring.BombBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					Audio::Get()->SoundSEPlayWave(m_bombSE);
				}
			}
		}
		else if (breakFlag == 2)
		{
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (m_blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOX == stageObj[i]->type)
				{
					Player::Get()->JumpPoweZero();
					Player::Get()->ActivateChangeBreak();
					m_boxStaring.BreakBoxFlag(stageObj[i]->position);
					m_fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
				}
				else if (m_blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXBOMB == stageObj[i]->type)
				{
					Player::Get()->DieType(BOMBDIE);
					m_boxStaring.BombBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					Audio::Get()->SoundSEPlayWave(m_bombSE);
				}
			}
		}
	}
	//スピンで壊れる箱の処理
	if (m_blockBox.GetIs_Spin() == true)
	{
		for (int i = 0; i < stageObj.size(); i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (m_blockBox.GetObj_Spin(j).position == stageObj[i]->position &&
					BOX == stageObj[i]->type)
				{
					m_boxStaring.BreakBoxFlag(stageObj[i]->position);
					m_fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
				}
				else if (m_blockBox.GetObj_Spin(j).position == stageObj[i]->position &&
					BOXBOMB == stageObj[i]->type)
				{
					//爆発オン
					Player::Get()->DieType(BOMBDIE);
					//爆発演出
					m_boxStaring.BombBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					Audio::Get()->SoundSEPlayWave(m_bombSE);
				}
			}
		}
	}
}

void Stage::SetFloor(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int type, int size)
{
	floor.push_back(new Floor);
	size_t Num = floor.size() - 1;
	floor[Num]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[Num]->position = position;
	floor[Num]->position.z -= size * scale.z / 2;
	floor[Num]->scale = scale;
	floor[Num]->scale.z += scale.z * size;
	floor[Num]->angle = angle;
	floor[Num]->type = type;
	floor[Num]->size = size;
}

void Stage::SetObject(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int type)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	stageObj[num]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	stageObj[num]->position = position;
	stageObj[num]->scale = scale;
	stageObj[num]->angle = angle;
	stageObj[num]->box.maxPosition = XMVectorSet(
		position.x + scale.x / 2,
		position.y + scale.y / 2,
		position.z + scale.z / 2, 1);
	stageObj[num]->box.minPosition = XMVectorSet(
		position.x - scale.x / 2,
		position.y - scale.y / 2,
		position.z - scale.z / 2, 1);
	stageObj[num]->type = type;
	if (type == BOX) { m_blockMax++; }
}

void Stage::SetMoveFloor(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, const int type)
{
	floor.push_back(new Floor);
	size_t NUM = floor.size() - 1;
	floor[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[NUM]->position = position;
	floor[NUM]->scale = scale;
	floor[NUM]->angle = angle;
	floor[NUM]->type = FLOORMOVE;
	if (type == FLOORMOVE2) { floor[NUM]->moveFlag = 1; }
}

void Stage::SetPitfallFloor(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int time)
{
	floor.push_back(new Floor);
	size_t NUM = floor.size() - 1;
	floor[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[NUM]->position = position;
	floor[NUM]->scale = scale;
	floor[NUM]->angle = angle;
	floor[NUM]->time = time;
	floor[NUM]->type = FLOORPITFALL_A;
}

void Stage::SetElectricity(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = Electricity::SetElect(position, scale, angle, map, ELECTRICITY);
}

void Stage::SetFishAttack(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = DangerFish::SetDangerFish(position, scale, angle, map, FISHATTACK);
}