#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
#include"../Particle/Particle.h"
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
	for (int i = (int)moveFloorData.size() - 1; i >= 0; i--)
	{
		delete moveFloorData[i];
		moveFloorData.erase(moveFloorData.begin() + i);
	}
	for (int i = (int)floorPitfallData.size() - 1; i >= 0; i--)
	{
		delete floorPitfallData[i];
		floorPitfallData.erase(floorPitfallData.begin() + i);
	}
}

void Stage::Init()
{
	blockBox.Init();
	floorOBJ = Shape::CreateOBJ("ice");//Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	floorGraph = Texture::Get()->LoadTexture(L"Resources/ice/ice.png");

	wallOBJ = Shape::CreateOBJ("iceWall");
	//ゴール設定
	goalOBJ = Shape::CreateOBJ("goal");

	moveFloorOBJ = Shape::CreateOBJ("moveFloor");
	floorPitfallOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);

	blackGround = Shape::CreateSquare(1.0f, 0.5f, 1.0f);
	blackGraph = Texture::Get()->LoadTexture(L"Resources/black.png");

	MainInit(0);

	//魚を初期化
	fishBox.Init();
	//電気の罠
	elect.Init();
	//危険魚
	dangerFish.Init();
}

void Stage::MainInit(int stageNum)
{
	blockMax = 0;
	blockNum = 0;
	//床
	LoadStage(stageNum);
	goalFlag = false;
	//魚を消す
	fishBox.Delete();
}

void Stage::Update(Vec3 pPos)
{
	Vec3 PPos = Player::Get()->GetPosition();
	//判定する箇所だけ行うため
	int Z = static_cast<int>(PPos.z / (-mapSize));
	int X = static_cast<int>(PPos.x / mapSize);

	for (int i = 0; i < stageObj.size(); i++)
	{
		switch (stageObj[i]->type)
		{
		case Wall:
		case BreakBox:
		case BreakJUMP:
		case BreakHARD:
			blockBox.PlayerHit(stageObj[i], X, Z);
			break;
		case Goal:
			if ((X - 1 <= stageObj[i]->map.x && stageObj[i]->map.x <= X + 1)
				&& ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
			{
				if (Collision::CheckBox2Box(stageObj[i]->box, Player::Get()->GetBox()))
				{
					//ゴール
					goalFlag = true;
				}
			}
			break;
		case ELECTRICITY:
			if ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1 && elect.GetElectFlag())
			{
				if (Collision::CheckBox2Box(stageObj[i]->box, Player::Get()->GetBox()))
				{
					Player::Get()->DieType(ELECTDIE);
				}
			}
			break;
		case FISHATTACK:
			if ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1 && elect.GetElectFlag())
			{
				if (Collision::CheckBox2Box(stageObj[i]->box, Player::Get()->GetBox()))
				{
					Player::Get()->DieType(EATDIE);
				}
			}
			break;
		default:
			break;
		}
	}

	if (blockBox.GetIs_Hit() == true)
	{
		int breakNum = -1;
		int breakFlag = PushCollision::PlayerBreakBox(blockBox.GetObj_Data(), breakNum);
		//ブロックが壊れる
		if (breakFlag == 1 && Player::Get()->GetOldGroundFlag() == false)
		{
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BreakBox == stageObj[i]->type)
				{
					Player::Get()->GetBlockStepOnFlag();
					Player::Get()->ChangeBreakFlag();
					Particle::Get()->BreakBoxFlag(stageObj[i]->position);
					fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
					break;
				}//ジャンプ台
				else if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BreakJUMP == stageObj[i]->type)
				{
					Player::Get()->GetJumpBox();
					Player::Get()->GetBlockStepOnFlag();
				}
			}
		}
		else if (breakFlag == 2 && stageObj[breakNum]->type == BreakBox)
		{
			Player::Get()->JumpPoweZero();
			Player::Get()->ChangeBreakFlag();
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BreakBox == stageObj[i]->type)
				{
					Particle::Get()->BreakBoxFlag(stageObj[i]->position);
					fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
				}
			}
		}
	}
	//箱の更新
	blockBox.Update();
	elect.Update();
	dangerFish.Update();

	//床
	for (int i = 0; i < floor.size(); i++)
	{
		if ((X - 1 <= floor[i]->map.x && floor[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			//プレイヤー
			PushCollision::Player2Floor(floor[i]->position,
				floor[i]->angle, floor[i]->scale);
		}
	}
	//動く床
	for (int i = 0; i < moveFloorData.size(); i++)
	{
		MoveFloorUpdate(i);
		if ((X - 3 <= moveFloorData[i]->map.x && moveFloorData[i]->map.x <= X + 3)
			&& ((MAP_HEIGHT - 1 + Z) - 3 <= moveFloorData[i]->map.y && moveFloorData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 3))
		{
			PushCollision::Player2Floor(moveFloorData[i]->position,
				moveFloorData[i]->angle, moveFloorData[i]->scale, moveFloorData[i]->moveFlag);
		}
	}

	for (int i = 0; i < floorPitfallData.size(); i++)
	{
		PitfallUpdate(i);
		if ((X - drawNumX <= floorPitfallData[i]->map.x && floorPitfallData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= floorPitfallData[i]->map.y && floorPitfallData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			if (floorPitfallData[i]->moveFlag == 0)
			{
				PushCollision::Player2Floor(floorPitfallData[i]->position,
					floorPitfallData[i]->angle, floorPitfallData[i]->scale);
			}
		}
	}
	//魚の更新
	fishBox.Update(pPos);
}

void Stage::Draw(Vec3 pPos, bool shadowFlag)
{
	Vec3 PPos = Player::Get()->GetPosition();
	//判定する箇所だけ行うため
	int X = static_cast<int>(PPos.x / mapSize);
	int Z = static_cast<int>(PPos.z / (-mapSize));
	//床の描画
	for (int i = 0; i < floor.size(); i++)
	{
		if ((X - drawNumX <= floor[i]->map.x && floor[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			switch (floor[i]->type)
			{
			case FloorNormal:
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 15.0f, floor[i]->position.z),
					Vec3(12.5f, 15.0f, 12.5f),
					floor[i]->angle, Vec4(), 0, shadowFlag);
				break;
			case Floor169:
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 16.0f, floor[i]->position.z),
					Vec3(15.0f, 15.0f, 23.0f),
					floor[i]->angle, Vec4(), 0, shadowFlag);
				break;
			case Floor11:
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 16.0f, floor[i]->position.z),
					Vec3(15.0f, 15.0f, 23.0f),
					floor[i]->angle, Vec4(), 0, shadowFlag);
				break;
			default:
				break;
			}
		}
	}
	//動く床
	for (int i = 0; i < moveFloorData.size(); i++)
	{
		if ((X - drawNumX <= moveFloorData[i]->map.x && moveFloorData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= moveFloorData[i]->map.y && moveFloorData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(moveFloorOBJ, moveFloorData[i]->psr, Vec3(moveFloorData[i]->position.x, moveFloorData[i]->position.y - 15.0f, moveFloorData[i]->position.z),
				Vec3(14.0f, 14.0f, 14.0f), moveFloorData[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);
		}
	}
	//落とし穴
	for (int i = 0; i < floorPitfallData.size(); i++)
	{
		if ((X - drawNumX <= floorPitfallData[i]->map.x && floorPitfallData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= floorPitfallData[i]->map.y && floorPitfallData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{//開いている
			if (floorPitfallData[i]->moveFlag == 0)
			{
				Object::Draw(floorPitfallOBJ, floorPitfallData[i]->psr, floorPitfallData[i]->position, floorPitfallData[i]->scale,
					floorPitfallData[i]->drawAngle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), pitfallGraph, shadowFlag);
			}//閉じている
			else if (floorPitfallData[i]->moveFlag == 1)
			{
				Object::Draw(floorPitfallOBJ, floorPitfallData[i]->psr, floorPitfallData[i]->position, floorPitfallData[i]->scale,
					floorPitfallData[i]->drawAngle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), pitfallGraph, shadowFlag);
			}
		}
	}

	//オブジェクト描画
	for (int i = 0; i < stageObj.size(); i++)
	{
		if ((X - drawNumX <= stageObj[i]->map.x && stageObj[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			switch (stageObj[i]->type)
			{
			case Wall:
				Object::Draw(wallOBJ, stageObj[i]->psr, Vec3(stageObj[i]->position.x, stageObj[i]->position.y - 30.0f, stageObj[i]->position.z),
					Vec3(12.0f, 12.0f, 12.0f), stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);
				break;
			case  Goal:
				Object::Draw(goalOBJ, stageObj[i]->psr, stageObj[i]->position, Vec3(5.0f, 5.0f, 5.0f),
					stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);
				break;
			case BreakBox:
			case BreakJUMP:
			case BreakHARD:
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
	//闇
	Object::Draw(blackGround, blackPsr[0], Vec3(pPos.x, -50.0f, pPos.z + 1000.0f),
		Vec3(10000.0f, 1.0f, 100000.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), blackGraph);

	//左右の床の描画
	Object::Draw(floorOBJ, blackPsr[1], Vec3(-560.0f, 5.0f, 1200.0f),
		Vec3(550.0f, 15.0f, 5500.0f),
		Vec3(), Vec4(), 0, shadowFlag);
	Object::Draw(floorOBJ, blackPsr[2], Vec3(800.0f, 5.0f, 1200.0f),
		Vec3(550.0f, 15.0f, 5500.0f),
		Vec3(), Vec4(), 0, shadowFlag);

	//箱壊した時に出る魚
	fishBox.Draw();
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
	for (int i = (int)moveFloorData.size() - 1; i >= 0; i--)
	{
		delete moveFloorData[i];
		moveFloorData.erase(moveFloorData.begin() + i);
	}
	for (int i = (int)floorPitfallData.size() - 1; i >= 0; i--)
	{
		delete floorPitfallData[i];
		floorPitfallData.erase(floorPitfallData.begin() + i);
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
			//OBJ
			switch (Map[y][x])
			{
			case NoneFloor:
				break;
			case FloorNormal:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)), FloorNormal);
				break;
			case Floor169:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(mapSize, 1.0f, 32.01f), Vec3(141.61f, 0.0f, 0.0f), Vec2(static_cast<float>(x), static_cast<float>(y)), Floor169);
				break;
			case Floor11:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(mapSize, 1.0f, 32.01f), Vec3(38.39f, 0.0f, 0.0f), Vec2(static_cast<float>(x), static_cast<float>(y)), Floor11);
				break;
			case FloorMove:
				SetMoveFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case FloorPitfall_A:
				SetPitfallFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)), 50);
				break;
			case FloorPitfall_B:
				SetPitfallFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)), 100);
				break;
			default:
				break;
			}
			switch (MapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
				SetWallBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + wallScale.y / 2 - 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					wallScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case Goal:
				SetGoal(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20 + 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					goalScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakBox:
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakBox2:
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, (static_cast<float>(MapOBJPos[y][x]) + 1.0f) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakJUMP:
				SetJumpBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakHARD:
				SetBreakHard(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case ELECTRICITY:
				SetElectricity(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case FISHATTACK:
				SetFishAttack(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
			default:
				break;
			}
		}
	}
}

void Stage::SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type)
{
	floor.push_back(new Floor);
	size_t floorNum = floor.size() - 1;
	floor[floorNum]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[floorNum]->position = position;
	floor[floorNum]->scale = scale;
	floor[floorNum]->angle = angle;
	floor[floorNum]->type = type;
}

void Stage::SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, BreakBox);
	blockMax++;
}

void Stage::SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, BreakJUMP);
}

void Stage::SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, BreakHARD);
}

void Stage::SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
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
	stageObj[num]->type = Wall;
}

void Stage::SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
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

void Stage::SetMoveFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	moveFloorData.push_back(new MoveFloorData);
	size_t NUM = moveFloorData.size() - 1;
	moveFloorData[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	moveFloorData[NUM]->position = position;
	moveFloorData[NUM]->scale = scale;
	moveFloorData[NUM]->angle = angle;
}

void Stage::SetPitfallFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int time)
{
	floorPitfallData.push_back(new FloorPitfallData);
	size_t NUM = floorPitfallData.size() - 1;
	floorPitfallData[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floorPitfallData[NUM]->position = position;
	floorPitfallData[NUM]->scale = scale;
	floorPitfallData[NUM]->angle = angle;
	floorPitfallData[NUM]->time = time;
}

void Stage::SetElectricity(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = Electricity::SetElect(position, scale, angle, map, ELECTRICITY);
}

void Stage::SetFishAttack(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = Electricity::SetElect(position, scale, angle, map, FISHATTACK);
}

void Stage::MoveFloorUpdate(int i)
{
	moveFloorData[i]->time++;
	if (moveFloorData[i]->moveFlag == 1)
	{
		moveFloorData[i]->position -= Vec3(0.0f, 0.0f, 0.5f);
		if (moveFloorData[i]->time >= 150)
		{
			moveFloorData[i]->moveFlag = 0;
			moveFloorData[i]->time = 0;
		}
	}
	else
	{
		moveFloorData[i]->position += Vec3(0.0f, 0.0f, 0.5f);
		if (moveFloorData[i]->time >= 150)
		{
			moveFloorData[i]->moveFlag = 1;
			moveFloorData[i]->time = 0;
		}
	}
}

void Stage::PitfallUpdate(int i)
{
	floorPitfallData[i]->time--;
	//開いている
	if (floorPitfallData[i]->moveFlag == 0)
	{
		if (floorPitfallData[i]->time <= 0)
		{
			floorPitfallData[i]->time = 50;
			floorPitfallData[i]->moveFlag = 1;
		}
		if (floorPitfallData[i]->time <= 5)
		{
			floorPitfallData[i]->drawAngle.z += 18;
		}
	}//閉じている
	else if (floorPitfallData[i]->moveFlag == 1)
	{
		if (floorPitfallData[i]->time <= 0)
		{
			floorPitfallData[i]->time = 50;
			floorPitfallData[i]->moveFlag = 0;
		}
		if (floorPitfallData[i]->time <= 5)
		{
			floorPitfallData[i]->drawAngle.z += 18;
		}
	}
}