#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
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
	blockBox.Init();
	floorOBJ = Shape::CreateOBJ("ice", false, "OBJ/");
	floorGraph = Texture::Get()->LoadTexture(L"Resources/floor.png");

	MainInit(0);

	goalFish.Init();
	//動く床を初期化
	moveFloor.Init();
	//反転床を初期化
	floorPitfall.Init();
	//魚を初期化
	fishBox.Init();
	//電気の罠を初期化
	elect.Init();
	//危険魚を初期化
	dangerFish.Init();
	//落下地点
	dropPoint.Init();

	figurineOBJ.Init();

	boxStaring.Init();

	boxSE = Audio::SoundLoadWave("Resources/sound/SE/boxBreak.wav");
	goalSE = Audio::SoundLoadWave("Resources/sound/SE/goal.wav");
	jumpSE = Audio::SoundLoadWave("Resources/sound/SE/jump.wav");
	bombSE = Audio::SoundLoadWave("Resources/sound/SE/bomb.wav");

	water = Shape::CreateRect(500.0f, 500.0f);
	waterGraph = Texture::Get()->LoadTexture(L"Resources/cube/WaterTexture.jpg");
}

void Stage::MainInit(int stageNum)
{
	blockMax = 0;
	blockNum = 0;
	//床
	LoadStage(stageNum);
	goalFlag = false;
	goalSEFlag = false;
	//魚を消す
	fishBox.Delete();
}

void Stage::Update(const Vec3& pPos)
{
	Vec3 PPos = pPos;
	//判定する箇所だけ行うため
	int Z = static_cast<int>(PPos.z / (-mapSize));
	int X = static_cast<int>(PPos.x / mapSize);

	dropPoint.ChangeFlag();

	boxStaring.Update();

	for (int i = 0; i < stageObj.size(); i++)
	{
		switch (stageObj[i]->type)
		{
		case Wall:
		case BarrierWall:
		case DEADTREE:
		case STLON:
		case BOX:
		case BOXJUMP:
		case BOXHARD:
		case BOXBOMB:
			blockBox.PlayerHit(stageObj[i], X, Z);
			blockBox.PlayerSpinHit(stageObj[i], X, Z);
			if (stageObj[i]->type != Wall || stageObj[i]->type != DEADTREE || stageObj[i]->type != BarrierWall)
			{
				dropPoint.Update(PPos, stageObj[i]->position,
					stageObj[i]->angle, stageObj[i]->scale);
			}
			break;
		case Goal:
			if ((X - 1 <= stageObj[i]->map.x && stageObj[i]->map.x <= X + 1)
				&& ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
			{
				if (Collision::CheckBox2Box(stageObj[i]->box, Player::Get()->GetBox()))
				{
					//ゴール
					goalFlag = true;
					if (goalSEFlag == false)
					{
						Audio::Get()->SoundSEPlayWave(goalSE);
					}
					goalSEFlag = true;
				}
			}
			goalFish.Update();
			break;
		case ELECTRICITY:
			elect.Update(stageObj[i], Z);
			break;
		case FISHATTACK:
			if ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1)
			{
				if (Collision::CheckBox2Box(stageObj[i]->box, Player::Get()->GetBox()))
				{
					Player::Get()->DieType(EATDIE);
					Player::Get()->FishDie(stageObj[i]->actionPos, dangerFish.GetFishAngle());
				}
			}
			dangerFish.Update(stageObj[i]);
			break;
		default:
			break;
		}
	}
	//壊れる箱の処理
	BreakBoxs();

	//箱の更新
	blockBox.Update();

	elect.AllUpdate();

	dangerFish.AllUpdate();
	//床
	for (int i = 0; i < floor.size(); i++)
	{
		switch (floor[i]->type)
		{
		case FloorNormal:
			dropPoint.Update(PPos, floor[i]->position,
				floor[i]->angle, floor[i]->scale);
		case Floor11:
		case Floor169:
			if ((X - 1 <= floor[i]->map.x && floor[i]->map.x <= X + 1)
				&& ((MAP_HEIGHT - 1 + Z) - 100 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 100)
				&& Player::Get()->GetIsFishDie() == false)
			{
				//プレイヤー
				PushCollision::Player2Floor(floor[i]->position,
					floor[i]->angle, floor[i]->scale);
			}
			break;
		case FloorMove:
			if ((X - 3 <= floor[i]->map.x && floor[i]->map.x <= X + 3)
				&& ((MAP_HEIGHT - 1 + Z) - 4 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4)
				&& Player::Get()->GetIsFishDie() == false)
			{
				//プレイヤー
				PushCollision::Player2Floor(floor[i]->position,
					floor[i]->angle, floor[i]->scale, floor[i]->moveFlag);
				dropPoint.Update(PPos, floor[i]->position,
					floor[i]->angle, floor[i]->scale);

			}
			moveFloor.Update(floor[i]);
			break;
		case FloorPitfall_A:
		case FloorPitfall_B:
			if (((MAP_HEIGHT - 1 + Z) - drawNumY <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4)
				&& Player::Get()->GetIsFishDie() == false)
			{
				if (floor[i]->moveFlag == 0)
				{
					PushCollision::Player2Floor(floor[i]->position,
						floor[i]->angle, floor[i]->scale);
					dropPoint.Update(PPos, floor[i]->position,
						floor[i]->angle, floor[i]->scale);
				}
			}
			floorPitfall.Update(floor[i]);
			break;
		default:
			break;
		}
	}
	//魚の更新
	fishBox.Update(pPos);
}

void Stage::Draw(const Vec3& pPos, bool shadowFlag)
{
	Vec3 PPos = pPos;
	//判定する箇所だけ行うため
	int Z = static_cast<int>(PPos.z / (-mapSize));
	size_t floorSize = floor.size();
	static const int floorNormalMax = (MAP_HEIGHT - 1 + Z) - 100;
	static const int stageMin = (MAP_HEIGHT - 1 + Z) + 6;
	//床の描画
	for (size_t i = 0; i < floorSize; i++)
	{
		switch (floor[i]->type)
		{
		case FloorNormal:
			if (floorNormalMax <= floor[i]->map.y && floor[i]->map.y <= stageMin)
			{
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 20.0f, floor[i]->position.z),
					Vec3(25.0f, 40.0f, 25.0f * (floor[i]->size + 1)),
					floor[i]->angle, Vec2(), 0, shadowFlag);
			}
			break;
		case Floor169:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= floor[i]->map.y && floor[i]->map.y <= stageMin)
			{
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 12.0f, floor[i]->position.z + 9.5f),
					Vec3(25.0f, 30.0f, 32.1f * 2),
					floor[i]->angle, Vec2(), floorGraph, shadowFlag);
			}
			break;
		case Floor11:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= floor[i]->map.y && floor[i]->map.y <= stageMin)
			{
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 12.0f, floor[i]->position.z - 9.5f),
					Vec3(25.0f, 30.0f, 32.1f),
					floor[i]->angle, Vec2(), floorGraph, shadowFlag);
			}
			break;
		case FloorMove:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= floor[i]->map.y && floor[i]->map.y <= stageMin)
			{
				moveFloor.Draw(floor[i], shadowFlag);
			}
			break;
		case FloorPitfall_A:
		case FloorPitfall_B:
			if ((MAP_HEIGHT - 1 + Z) - 50 <= floor[i]->map.y && floor[i]->map.y <= stageMin)
			{
				floorPitfall.Draw(floor[i], shadowFlag);
			}
			break;
		default:
			break;
		}

	}
	size_t stageObjSize = stageObj.size();
	//オブジェクト描画
	for (int i = 0; i < stageObjSize; i++)
	{
		if ((MAP_HEIGHT - 1 + Z) - drawNumY <= stageObj[i]->map.y && stageObj[i]->map.y <= stageMin)
		{
			switch (stageObj[i]->type)
			{
			case Wall:
			case DEADTREE:
			case STLON:
			case ICEARCH:
				figurineOBJ.Draw(stageObj[i], shadowFlag);
				break;
			case  Goal:
				goalFish.Draw(stageObj[i], shadowFlag);
				break;
			case BOX:
			case BOXJUMP:
			case BOXHARD:
			case BOXBOMB:
				blockBox.Draw(stageObj[i], shadowFlag);
				break;
			case ELECTRICITY:
				elect.Draw(stageObj[i], shadowFlag);
				break;
			case FISHATTACK:
				dangerFish.Draw(stageObj[i], shadowFlag);
				break;
			default:
				break;
			}
		}
	}

	//左右の床の描画
	Object::Draw(floorOBJ, blackPsr[1], Vec3(-340.0f, 5.0f, pPos.z + 600.0f),
		Vec3(650.0f, 15.0f, 1500.0f),
		Vec3(), Vec2(), 0, shadowFlag);
	Object::Draw(floorOBJ, blackPsr[2], Vec3(560.0f, 5.0f, pPos.z + 600.0f),
		Vec3(650.0f, 15.0f, 1500.0f),
		Vec3(), Vec2(), 0, shadowFlag);

	DrawWater();

	//箱壊した時に出る魚
	fishBox.Draw();

	dropPoint.Draw(Player::Get()->GetPosition());

	boxStaring.Draw3D();
}

void Stage::DrawParicle()
{
	elect.DrawParicle();
	//パーティクル
	boxStaring.Draw();
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
	char* FilepathFloor = "";
	char* FilepathFloorPos = "";
	char* FilepathOBJ = "";
	char* FilepathOBJPos = "";
	switch (stageNum)
	{
	case 0:
		//Floor
		FilepathFloor = (char*)"Resources/map/selectFloor.csv";
		FilepathFloorPos = (char*)"Resources/map/selectTitlePos.csv";
		//OBJ
		FilepathOBJ = (char*)"Resources/map/selectObj.csv";
		FilepathOBJPos = (char*)"Resources/map/selectObjPos.csv";
		break;
	case 1:
		//Floor
		FilepathFloor = (char*)"Resources/map/Floor_Title1.csv";
		FilepathFloorPos = (char*)"Resources/map/Floor_TitlePos1.csv";
		//OBJ
		FilepathOBJ = (char*)"Resources/map/OBJTitle1.csv";
		FilepathOBJPos = (char*)"Resources/map/Obj_TitlePos1.csv";
		break;
	case 2:
		//Floor
		FilepathFloor = (char*)"Resources/map/Floor_Title2.csv";
		FilepathFloorPos = (char*)"Resources/map/Floor_TitlePos2.csv";
		//OBJ
		FilepathOBJ = (char*)"Resources/map/OBJTitle2.csv";
		FilepathOBJPos = (char*)"Resources/map/Obj_TitlePos2.csv";
		break;
	case 3:
		//Floor
		FilepathFloor = (char*)"Resources/map/Floor_Title3.csv";
		FilepathFloorPos = (char*)"Resources/map/Floor_TitlePos3.csv";
		//OBJ
		FilepathOBJ = (char*)"Resources/map/OBJTitle3.csv";
		FilepathOBJPos = (char*)"Resources/map/Obj_TitlePos3.csv";
		break;
	case 4:
		//Floor
		FilepathFloor = (char*)"Resources/map/Floor_Title4.csv";
		FilepathFloorPos = (char*)"Resources/map/Floor_TitlePos4.csv";
		//OBJ
		FilepathOBJ = (char*)"Resources/map/OBJTitle4.csv";
		FilepathOBJPos = (char*)"Resources/map/Obj_TitlePos4.csv";
		break;
	default:
		break;
	}
	////ブロック
	int	Map[MAP_HEIGHT][MAP_WIDTH] = {};		//マップチップ
	int MapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int MapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//壁などのOBJ
	int MapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//壁などのOBJの座標
	LoadCSV(Map, FilepathFloor);
	LoadCSV(MapPos, FilepathFloorPos);

	LoadCSV(MapOBJ, FilepathOBJ);
	LoadCSV(MapOBJPos, FilepathOBJPos);

	for (size_t y = 0; y < MAP_HEIGHT; y++)
	{
		for (size_t x = 0; x < MAP_WIDTH; x++)
		{
			Vec2 map = { static_cast<float>(x), static_cast<float>(y) };
			//OBJ
			switch (Map[y][x])
			{
			case NoneFloor:
				break;
			case FloorNormal:
			{
				int num_ = 1;

				while (Map[y + num_][x] == FloorNormal)
				{
					Map[y + num_][x] = 0;
					num_++;
					if (y + num_ >= MAP_HEIGHT)
					{
						break;
					}
				}
				SetFloor(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, FloorNormal, num_ - 1);
			}
			break;
			case Floor169:
				SetFloor(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f + 0.0f, (MAP_HEIGHT - 1 - y) * mapSize + 12.3f),
					Vec3(mapSize, 1.0f, 32.01f * 2), Vec3(141.61f, 0.0f, 0.0f), map, Floor169);
				break;
			case Floor11:
				SetFloor(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(mapSize, 1.0f, 32.01f), Vec3(38.39f, 0.0f, 0.0f), map, Floor11);
				break;
			case FloorMove:
				SetMoveFloor(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map);
				break;
			case FloorPitfall_A:
				SetPitfallFloor(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, 70);
				break;
			case FloorPitfall_B:
				SetPitfallFloor(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map, 140);
				break;
			case FloorMove2:
				SetMoveFloor2(Vec3(map.x * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), map);
				break;
			default:
				break;
			}
			switch (MapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
			case BarrierWall:
				SetWallBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + wallScale.y / 2 - 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					wallScale, Vec3(), map, MapOBJ[y][x]);
				break;
			case Goal:
				SetGoal(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20 + 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					goalFish.GetGoalScale(), Vec3(), map);
				break;
			case BOX:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOX);
				break;
			case BOXDOUBLE:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOX);
				SetBox(Vec3(static_cast<float>(x) * mapSize, (static_cast<float>(MapOBJPos[y][x]) + 1.0f) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOX);
				break;
			case BOXJUMP:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOXJUMP);
				break;
			case BOXHARD:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOXHARD);
				break;
			case BOXBOMB:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOXBOMB);
				break;
			case BOX_BOMB:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOX);
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x] + 1.0f) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOXBOMB);
				break;
			case BOMB_BOX:
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOXBOMB);
				SetBox(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x] + 1.0f) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map, BOX);
				break;
			case ELECTRICITY:
				SetElectricity(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map);
				break;
			case FISHATTACK:
				SetFishAttack(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), map);
				break;
			case DEADTREE:
			case STLON:
			case ICEARCH:
				SetFigrineOBJ(Vec3(map.x * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					wallScale, Vec3(), map, MapOBJ[y][x]);
				break;
			default:
				break;
			}
		}
	}
}

void Stage::DrawWater()
{
	waterUV.y += 0.001f;
	if (waterUV.y >= 1.0f)
	{
		waterUV.y = 0.0f;
	}
	for (size_t i = 0; i < 6; i++)
	{
		Object::NoShadowDraw(water, PSR(),
			Vec3(50.0f, -70.0f, 500.0f * i), Vec3(1.0f, 1.0f, 1.0f),
			Vec3(90.0f, 0.0f, 0.0f), waterUV, waterGraph);
	}
}

void Stage::BreakBoxs()
{
	//踏むか叩いて壊れる箱の処理
	if (blockBox.GetIs_Hit() == true && Player::Get()->GetIsFishDie() == false)
	{
		int breakNum = -1;
		int breakFlag = PushCollision::PlayerBreakBox(blockBox.GetObj_Data(), breakNum);
		if (breakFlag == 1 && Player::Get()->GetOldGroundFlag() == false)
		{
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOX == stageObj[i]->type)
				{
					Player::Get()->ActivateBlockStepOn();
					Player::Get()->ActivateChangeBreak();
					boxStaring.BreakBoxFlag(stageObj[i]->position);
					fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
					Audio::Get()->SoundSEPlayWave(boxSE);
					break;
				}//ジャンプ台
				else if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXJUMP == stageObj[i]->type)
				{
					Player::Get()->ActivateJumpBox();
					Player::Get()->ActivateBlockStepOn();
					Audio::Get()->SoundSEPlayWave(jumpSE);
				}//爆発箱
				else if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXBOMB == stageObj[i]->type)
				{
					Player::Get()->DieType(BOMBDIE);
					boxStaring.BombBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					Audio::Get()->SoundSEPlayWave(bombSE);
				}
			}
		}
		else if (breakFlag == 2)
		{
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOX == stageObj[i]->type)
				{
					Player::Get()->JumpPoweZero();
					Player::Get()->ActivateChangeBreak();
					boxStaring.BreakBoxFlag(stageObj[i]->position);
					fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
					Audio::Get()->SoundSEPlayWave(boxSE);
				}
				else if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXBOMB == stageObj[i]->type)
				{
					Player::Get()->DieType(BOMBDIE);
					boxStaring.BombBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					Audio::Get()->SoundSEPlayWave(bombSE);
				}
			}
		}
	}
	//スピンで壊れる箱の処理
	if (blockBox.GetIs_Spin() == true)
	{
		for (int i = 0; i < stageObj.size(); i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (blockBox.GetObj_Spin(j).position == stageObj[i]->position &&
					BOX == stageObj[i]->type)
				{
					boxStaring.BreakBoxFlag(stageObj[i]->position);
					fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
					Audio::Get()->SoundSEPlayWave(boxSE);
				}
				else if (blockBox.GetObj_Spin(j).position == stageObj[i]->position &&
					BOXBOMB == stageObj[i]->type)
				{
					//爆発オン
					Player::Get()->DieType(BOMBDIE);
					//爆発演出
					boxStaring.BombBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					Audio::Get()->SoundSEPlayWave(bombSE);
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

void Stage::SetBox(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int type)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, type);
	if (type == BOX) { blockMax++; }
}

void Stage::SetWallBox(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int type)
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
}

void Stage::SetGoal(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map)
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
	stageObj[num]->type = Goal;
}

void Stage::SetMoveFloor(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map)
{
	floor.push_back(new Floor);
	size_t NUM = floor.size() - 1;
	floor[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[NUM]->position = position;
	floor[NUM]->scale = scale;
	floor[NUM]->angle = angle;
	floor[NUM]->type = FloorMove;
}

void Stage::SetMoveFloor2(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map)
{
	floor.push_back(new Floor);
	size_t NUM = floor.size() - 1;
	floor[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[NUM]->position = position;
	floor[NUM]->scale = scale;
	floor[NUM]->angle = angle;
	floor[NUM]->type = FloorMove;
	floor[NUM]->moveFlag = 1;
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
	floor[NUM]->type = FloorPitfall_A;
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

void Stage::SetFigrineOBJ(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, int type)
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
}