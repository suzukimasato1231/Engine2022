#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
#include"Particle.h"
Stage::Stage()
{}

Stage::~Stage()
{
	for (int i = (int)floor.size() - 1; i >= 0; i--)
	{
		delete floor[i];
		floor.erase(floor.begin() + i);
	}
	for (int i = (int)breakBoxData.size() - 1; i >= 0; i--)
	{
		delete breakBoxData[i];
		breakBoxData.erase(breakBoxData.begin() + i);
	}
	for (int i = (int)wallData.size() - 1; i >= 0; i--)
	{
		delete wallData[i];
		wallData.erase(wallData.begin() + i);
	}
	for (int i = (int)goalData.size() - 1; i >= 0; i--)
	{
		delete goalData[i];
		goalData.erase(goalData.begin() + i);
	}
	for (int i = (int)moveFloorData.size() - 1; i >= 0; i--)
	{
		delete moveFloorData[i];
		moveFloorData.erase(moveFloorData.begin() + i);
	}
}

void Stage::Init()
{
	floorOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	floorGraph = Texture::Get()->LoadTexture(L"Resources/ground.png");

	wallOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	wallGraph = Texture::Get()->LoadTexture(L"Resources/map/block.png");
	//ÉSÅ[Éãê›íË
	goalOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);

	breakBoxOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	breakBoxGraph = Texture::Get()->LoadTexture(L"Resources/woodenBox.png");

	moveFloorOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
	moveGraph = Texture::Get()->LoadTexture(L"Resources/map/block.png");
	MainInit(0);
}

void Stage::MainInit(int stageNum)
{
	stageBlockNum = 0;
	blockNum = 0;
	//è∞
	LoadStage();
	goalFlag = false;
}

void Stage::Update()
{
	Vec3 PPos = Player::Get()->GetPosition();
	//îªíËÇ∑ÇÈâ”èäÇæÇØçsÇ§ÇΩÇﬂ
	int Z = static_cast<int>(PPos.z / (-mapSize));
	int X = static_cast<int>(PPos.x / mapSize);

	bool isHit2 = false;
	int boxCount = 0;
	BreakBoxData boxData[4] = {};
	//î†
	for (int i = 0; i < breakBoxData.size(); i++)
	{
		if ((X - 1 <= breakBoxData[i]->map.x && breakBoxData[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= breakBoxData[i]->map.y && breakBoxData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			if (Collision::CheckBox2Box(breakBoxData[i]->box, Player::Get()->GetBox()))
			{
				boxData[boxCount] = *breakBoxData[i];
				boxCount++;
				isHit2 = true;
			}
		}
	}
	if (isHit2 == true)
	{
		int breakNum = -1;
		int breakFlag = PushCollision::PlayerBreakBox(boxData,breakNum);
		//ÉuÉçÉbÉNÇ™âÛÇÍÇÈ
		if (breakFlag == 1 && Player::Get()->GetOldGroundFlag() == false)
		{
			Player::Get()->GetBlockStepOnFlag();
			for (int i = 0; i < breakBoxData.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (boxData[breakNum].position.x == breakBoxData[i]->position.x &&
					boxData[breakNum].position.y == breakBoxData[i]->position.y &&
					boxData[breakNum].position.z == breakBoxData[i]->position.z)
				{
					Particle::Get()->BreakBoxFlag(breakBoxData[i]->position);
					delete breakBoxData[i];
					breakBoxData.erase(breakBoxData.begin() + i);
					blockNum++;
					break;
				}
			}
		}
		else if (breakFlag == 2)
		{
			Player::Get()->JumpPoweZero();
			for (int i = 0; i < breakBoxData.size(); i++)
			{
				if (breakNum == -1) { break; }
				if (boxData[breakNum].position.x == breakBoxData[i]->position.x &&
					boxData[breakNum].position.y == breakBoxData[i]->position.y &&
					boxData[breakNum].position.z == breakBoxData[i]->position.z)
				{
					Particle::Get()->BreakBoxFlag(breakBoxData[i]->position);
					delete breakBoxData[i];
					breakBoxData.erase(breakBoxData.begin() + i);
					blockNum++;
				}
			}
		}
	}


	//ï«
	int wallCount = 0;
	WallData memoryData[4] = {};
	bool isHit = false;
	for (int i = 0; i < wallData.size(); i++)
	{
		if ((X - 1 <= wallData[i]->map.x && wallData[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= wallData[i]->map.y && wallData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			if (Collision::CheckBox2Box(wallData[i]->box, Player::Get()->GetBox()))
			{
				memoryData[wallCount] = *wallData[i];
				wallCount++;
				isHit = true;
			}
		}
	}
	if (isHit == true)
	{
		PushCollision::PlayerBox2(memoryData);
	}


	//è∞
	for (int i = 0; i < floor.size(); i++)
	{
		if ((X - 1 <= floor[i]->map.x && floor[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			PushCollision::Player2Floor(floor[i]->position,
				floor[i]->angle, floor[i]->scale);
		}
	}

	//ÉSÅ[Éã
	for (int i = 0; i < goalData.size(); i++)
	{
		if ((X - 1 <= goalData[i]->map.x && goalData[i]->map.x <= X + 1)
			&& ((MAP_HEIGHT - 1 + Z) - 1 <= goalData[i]->map.y && goalData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
		{
			goalFlag = PushCollision::PlayerGoal(goalData[i]->box);
		}
	}
	//ìÆÇ≠è∞
	for (int i = 0; i < moveFloorData.size(); i++)
	{
		if ((X - 10 <= moveFloorData[i]->map.x && moveFloorData[i]->map.x <= X + 10)
			&& ((MAP_HEIGHT - 1 + Z) - 10 <= moveFloorData[i]->map.y && moveFloorData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 10))
		{
			MoveFloorUpdate(i);
			PushCollision::Player2Floor(moveFloorData[i]->position,
				moveFloorData[i]->angle, moveFloorData[i]->scale, moveFloorData[i]->moveFlag);
		}
	}
}

void Stage::Draw()
{
	Vec3 PPos = Player::Get()->GetPosition();
	//îªíËÇ∑ÇÈâ”èäÇæÇØçsÇ§ÇΩÇﬂ
	int X = static_cast<int>(PPos.x / mapSize);
	int Z = static_cast<int>(PPos.z / (-mapSize));
	//è∞ÇÃï`âÊ
	for (int i = 0; i < floor.size(); i++)
	{
		if ((X - drawNumX <= floor[i]->map.x && floor[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - 55 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(floorOBJ, floor[i]->position, floor[i]->scale,
				floor[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
		}
	}
	//î†ÇÃï`âÊ
	for (int i = 0; i < breakBoxData.size(); i++)
	{
		if ((X - drawNumX <= breakBoxData[i]->map.x && breakBoxData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - 55 <= breakBoxData[i]->map.y && breakBoxData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(breakBoxOBJ, breakBoxData[i]->position, breakBoxData[i]->scale,
				breakBoxData[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), breakBoxGraph);
		}
	}
	//ï«
	for (int i = 0; i < wallData.size(); i++)
	{
		if ((X - drawNumX <= wallData[i]->map.x && wallData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - 55 <= wallData[i]->map.y && wallData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(wallOBJ, wallData[i]->position, wallData[i]->scale,
				wallData[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), wallGraph);
		}
	}
	//ÉSÅ[Éã
	for (int i = 0; i < goalData.size(); i++)
	{
		if ((X - drawNumX <= goalData[i]->map.x && goalData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - 55 <= goalData[i]->map.y && goalData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(goalOBJ, goalData[i]->position, goalData[i]->scale,
				goalData[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	//ìÆÇ≠è∞
	for (int i = 0; i < moveFloorData.size(); i++)
	{
		if ((X - drawNumX <= moveFloorData[i]->map.x && moveFloorData[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - 55 <= moveFloorData[i]->map.y && moveFloorData[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			Object::Draw(moveFloorOBJ, moveFloorData[i]->position, moveFloorData[i]->scale,
				moveFloorData[i]->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), moveGraph);
		}
	}
}

void Stage::LoadStage()
{
	for (int i = (int)floor.size() - 1; i >= 0; i--)
	{
		delete floor[i];
		floor.erase(floor.begin() + i);
	}
	for (int i = (int)breakBoxData.size() - 1; i >= 0; i--)
	{
		delete breakBoxData[i];
		breakBoxData.erase(breakBoxData.begin() + i);
	}
	for (int i = (int)wallData.size() - 1; i >= 0; i--)
	{
		delete wallData[i];
		wallData.erase(wallData.begin() + i);
	}
	for (int i = (int)goalData.size() - 1; i >= 0; i--)
	{
		delete goalData[i];
		goalData.erase(goalData.begin() + i);
	}
	for (int i = (int)moveFloorData.size() - 1; i >= 0; i--)
	{
		delete moveFloorData[i];
		moveFloorData.erase(moveFloorData.begin() + i);
	}
	char* Filepath = "";
	char* FilepathOBJ = "";
	Filepath = (char*)"Resources/map/Floor_Title1.csv";
	FilepathOBJ = (char*)"Resources/map/Floor_TitlePos1.csv";

	LoadCSV(map, Filepath);
	LoadCSV(mapPos, FilepathOBJ);
	//OBJ
	Filepath = (char*)"Resources/map/OBJTitle1.csv";
	FilepathOBJ = (char*)"Resources/map/Obj_TitlePos1.csv";
	LoadCSV(mapOBJ, Filepath);
	LoadCSV(mapOBJPos, FilepathOBJ);

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
				SetGoal(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(mapOBJPos[y][x]) * 20 + goalScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
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
	breakBoxData.push_back(new BreakBoxData);
	size_t boxNum = breakBoxData.size() - 1;
	breakBoxData[boxNum]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	breakBoxData[boxNum]->position = position;
	breakBoxData[boxNum]->scale = scale;
	breakBoxData[boxNum]->angle = angle;
	breakBoxData[boxNum]->box.maxPosition = XMVectorSet(
		position.x + scale.x / 2,
		position.y + scale.y / 2,
		position.z + scale.z / 2, 1);
	breakBoxData[boxNum]->box.minPosition = XMVectorSet(
		position.x - scale.x / 2,
		position.y - scale.y / 2,
		position.z - scale.z / 2, 1);
	stageBlockNum++;
}

void Stage::SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	wallData.push_back(new WallData);
	size_t boxNum = wallData.size() - 1;
	wallData[boxNum]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	wallData[boxNum]->position = position;
	wallData[boxNum]->scale = scale;
	wallData[boxNum]->angle = angle;
	wallData[boxNum]->box.maxPosition = XMVectorSet(
		position.x + scale.x / 2,
		position.y + scale.y / 2,
		position.z + scale.z / 2, 1);
	wallData[boxNum]->box.minPosition = XMVectorSet(
		position.x - scale.x / 2,
		position.y - scale.y / 2,
		position.z - scale.z / 2, 1);
}

void Stage::SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	goalData.push_back(new GoalData);
	size_t boxNum = goalData.size() - 1;
	goalData[boxNum]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	goalData[boxNum]->position = position;
	goalData[boxNum]->scale = scale;
	goalData[boxNum]->angle = angle;
	goalData[boxNum]->box.maxPosition = XMVectorSet(position.x + scale.x / 2, position.y + scale.y / 2, position.z + scale.z / 2, 1);
	goalData[boxNum]->box.minPosition = XMVectorSet(position.x - scale.x / 2, position.y - scale.y / 2, position.z - scale.z / 2, 1);
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



