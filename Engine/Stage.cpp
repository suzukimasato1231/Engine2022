#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
#include"Particle.h"
#include"EnemyManager.h"
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
}

void Stage::Init()
{
	floorOBJ = Shape::CreateOBJ("cube");
	floorGraph = Texture::Get()->LoadTexture(L"Resources/ground.png");

	wallOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	wallGraph = Texture::Get()->LoadTexture(L"Resources/map/block.png");
	//ゴール設定
	goalOBJ = Shape::CreateOBJ("goal");

	breakBoxOBJ = Shape::CreateOBJ("cube");
	normalBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	breakBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Hard.png");

	moveFloorOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	moveGraph = Texture::Get()->LoadTexture(L"Resources/map/block.png");
	MainInit(0);

	mask = Texture::Get()->LoadTexture(L"Resources/FirldMask.png");
	green = Texture::Get()->LoadTexture(L"Resources/Grass.jpg");
	grn = Texture::Get()->LoadTexture(L"Resources/Dirt.jpg");
}

void Stage::MainInit(int stageNum)
{
	stageBlockNum = 0;
	blockNum = 0;
	//床
	LoadStage(stageNum);
	goalFlag = false;
}

void Stage::Update()
{
	Vec3 PPos = Player::Get()->GetPosition();
	//判定する箇所だけ行うため
	int Z = static_cast<int>(PPos.z / (-mapSize));
	int X = static_cast<int>(PPos.x / mapSize);


	bool is_hit = false;
	int box_count = 0;
	StageOBJ obj_data[4] = {};
	//箱
	for (int i = 0; i < stageObj.size(); i++)
	{
		if ((X - 1 <= stageObj[i]->map.x && stageObj[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			if (Collision::CheckBox2Box(stageObj[i]->box, Player::Get()->GetBox()))
			{
				if (box_count >= 4)
				{
					break;
				}
				obj_data[box_count] = *stageObj[i];
				box_count++;
				is_hit = true;
				//ゴール
				if (stageObj[i]->type == Goal)
				{
					goalFlag = true;
				}
			}
		}
	}
	if (is_hit == true)
	{
		int breakNum = -1;
		int breakFlag = PushCollision::PlayerBreakBox(obj_data, breakNum);
		//ブロックが壊れる
		if (breakFlag == 1 && Player::Get()->GetOldGroundFlag() == false)
		{
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (obj_data[breakNum].position == stageObj[i]->position &&
					BreakBox == stageObj[i]->type)
				{
					Player::Get()->GetBlockStepOnFlag();
					Particle::Get()->BreakBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
					break;
				}//ジャンプ台
				else if (obj_data[breakNum].position == stageObj[i]->position &&
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
			for (int i = 0; i < stageObj.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (obj_data[breakNum].position == stageObj[i]->position &&
					BreakBox == stageObj[i]->type)
				{
					Particle::Get()->BreakBoxFlag(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
				}
			}
		}
	}

	//床
	for (int i = 0; i < floor.size(); i++)
	{
		if ((X - 1 <= floor[i]->map.x && floor[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			//プレイヤー
			PushCollision::Player2Floor(floor[i]->position,
				floor[i]->angle, floor[i]->scale);
			//敵
			Floor FloorIn = *floor[i];
			//enemy.FloorPush(FloorIn);
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
}

void Stage::Draw(bool shadowFlag)
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
			Object::DrawNormalMap(floorOBJ, Vec3(floor[i]->position.x, floor[i]->position.y, floor[i]->position.z),
				Vec3(floor[i]->scale.x, floor[i]->scale.y, floor[i]->scale.z),
				floor[i]->angle, mask, green, grn, shadowFlag);
		}
	}
	//動く床
	for (int i = 0; i < moveFloorData.size(); i++)
	{
		if ((X - drawNumX <= moveFloorData[i]->map.x && moveFloorData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= moveFloorData[i]->map.y && moveFloorData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(moveFloorOBJ, moveFloorData[i]->position, moveFloorData[i]->scale,
				moveFloorData[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), moveGraph, shadowFlag);
		}
	}
	//オブジェクト描画
	for (int i = 0; i < stageObj.size(); i++)
	{
		if ((X - drawNumX <= stageObj[i]->map.x && stageObj[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= stageObj[i]->map.y && stageObj[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			if (stageObj[i]->type == Wall)
			{
				Object::Draw(wallOBJ, stageObj[i]->position, stageObj[i]->scale,
					stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), wallGraph, shadowFlag);
			}
			else if (stageObj[i]->type == Goal)
			{
				Object::Draw(goalOBJ, stageObj[i]->position, Vec3(5.0f, 5.0f, 5.0f),
					stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);
			}
			else if (stageObj[i]->type == BreakBox)
			{
				Object::Draw(breakBoxOBJ, stageObj[i]->position, stageObj[i]->scale,
					stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), normalBoxGraph, shadowFlag);
			}
			else if (stageObj[i]->type == BreakJUMP)
			{
				Object::Draw(breakBoxOBJ, stageObj[i]->position, stageObj[i]->scale,
					stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), breakBoxGraph, shadowFlag);
			}
			else if (stageObj[i]->type == BreakHARD)
			{
				Object::Draw(breakBoxOBJ, stageObj[i]->position, stageObj[i]->scale,
					stageObj[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), breakBoxGraph, shadowFlag);
			}
		}
	}




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
	default:
		break;

	}
	LoadCSV(map, FilepathFloor);
	LoadCSV(mapPos, FilepathFloorPos);

	LoadCSV(mapOBJ, FilepathOBJ);
	LoadCSV(mapOBJPos, FilepathOBJPos);

	for (size_t y = 0; y < MAP_HEIGHT; y++)
	{
		for (size_t x = 0; x < MAP_WIDTH; x++)
		{
			//OBJ
			switch (map[y][x])
			{
			case NoneFloor:
				break;
			case FloorNormal:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case Floor169:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapPos[y][x]) * 20.0f - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(mapSize, 1.0f, 32.01f), Vec3(141.61f, 0.0f, 0.0f), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case Floor11:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapPos[y][x]) * 20.0f - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(mapSize, 1.0f, 32.01f), Vec3(38.39f, 0.0f, 0.0f), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case FloorMove:
				SetMoveFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			default:
				break;
			}
			switch (mapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
				SetWallBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20.0f + wallScale.y / 2 - 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					wallScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case Goal:
				SetGoal(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20 + 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					goalScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakBox:
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakBox2:
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, (static_cast<float>(mapOBJPos[y][x]) + 1.0f) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakJUMP:
				SetJumpBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BreakHARD:
				SetBreakHard(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			default:
				break;
			}
		}
	}
}

void Stage::SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	floor.push_back(new Floor);
	size_t floorNum = floor.size() - 1;
	floor[floorNum]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[floorNum]->position = position;
	floor[floorNum]->scale = scale;
	floor[floorNum]->angle = angle;
}

void Stage::SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
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
	stageObj[num]->type = BreakBox;
	stageBlockNum++;
}

void Stage::SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
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
	stageObj[num]->type = BreakJUMP;
	stageBlockNum++;
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

void Stage::SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
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
	stageObj[num]->type = BreakHARD;
	stageBlockNum++;
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
	size_t moveNum = moveFloorData.size() - 1;
	moveFloorData[moveNum]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	moveFloorData[moveNum]->position = position;
	moveFloorData[moveNum]->scale = scale;
	moveFloorData[moveNum]->angle = angle;
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



