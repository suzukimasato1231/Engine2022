#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"Player.h"
#include"PushCollision.h"
Stage::Stage()
{}

Stage::~Stage()
{
}

void Stage::Init()
{

	floorOBJ[0] = Shape::CreateSquare(50.0f, 1.0f, 50.0f);
	floorOBJ[1] = Shape::CreateSquare(50.0f, 1.0f, 50.99f);
	floorOBJ[2] = Shape::CreateSquare(50.0f, 1.0f, 50.99f);
	floorGraph = Texture::Instance()->LoadTexture(L"Resources/ground.png");

	wallOBJ = Shape::CreateSquare(50.0f, 50.0f, 50.0f);
	wallGraph = Texture::Instance()->LoadTexture(L"Resources/map/block.png");

	//ÉSÅ[Éãê›íË
	goalOBJ = Shape::CreateSquare(goalScale.x,goalScale.y,goalScale.z);

	char* Filepath = "";
	char* FilepathOBJ = "";

	//è∞
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
			switch (mapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
				break;
			case Goal:
				goalPos = Vec3(static_cast<float>(x) * 50 - 100, static_cast<float>(mapOBJPos[y][x]) * 10, (MAP_HEIGHT - 1 - y) * 50.0f);
				goalBox = {};
				goalBox.maxPosition = XMVectorSet(goalPos.x + goalScale.x / 2, goalPos.y + goalScale.y / 2, goalPos.z + goalScale.z / 2, 1);
				goalBox.minPosition = XMVectorSet(goalPos.x - goalScale.x / 2, goalPos.y - goalScale.y / 2, goalPos.z - goalScale.z / 2, 1);
				break;
			default:
				break;
			}
		}
	}
}

void Stage::MainInit(int stageNum)
{
}

void Stage::Update()
{
	Vec3 PPos = Player::Instance()->GetPosition();
	//îªíËÇ∑ÇÈâ”èäÇæÇØçsÇ§ÇΩÇﬂ
	int Z = static_cast<int>(PPos.z / (-mapSize.y));
	for (int y = (MAP_HEIGHT - 1 + Z) - 30; y < (MAP_HEIGHT - 1 + Z) + 5; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (y < 0 || x < 0 || y >= MAP_HEIGHT || x >= MAP_WIDTH)
			{
				continue;
			}

			switch (map[y][x])
			{
			case NoneFloor:
				break;
			case FloorNormal:
				PushCollision::Player2Floor(Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(0.0f, 0.0f, 0.0f), Vec3(50.0f, 1.0f, 50.0f));
				break;
			case Floor169:
				PushCollision::Player2Floor(Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapPos[y][x]) * 10 - 5.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(169.3099f, 0.0f, 0.0f), Vec3(50.0f, 1.0f, 50.99f));
				break;
			case Floor11:
				PushCollision::Player2Floor(Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapPos[y][x]) * 10 - 5.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(11.3099f, 0.0f, 0.0f), Vec3(50.0f, 1.0f, 50.99f));
				break;
			default:
				break;
			}

			switch (mapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
				PushCollision::PlayerBox(Vec3(static_cast<float>(x) * 50.0f - 100, static_cast<float>(mapOBJPos[y][x]) * 10.0f + wallScale.y / 3, (MAP_HEIGHT - 1 - y) * 50.0f),
					wallScale);
				break;
			case Goal:
				goalFlag = PushCollision::PlayerGoal(goalBox);
				break;
			default:
				break;
			}
		}
	}
}

void Stage::Draw()
{
	Vec3 PPos = Player::Instance()->GetPosition();
	//îªíËÇ∑ÇÈâ”èäÇæÇØçsÇ§ÇΩÇﬂ
	int Z = static_cast<int>(PPos.z / (-mapSize.y));
	for (int y = (MAP_HEIGHT - 1 + Z) - 30; y < (MAP_HEIGHT - 1 + Z) + 5; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (y < 0 || x < 0 || y >= MAP_HEIGHT || x >= MAP_WIDTH)
			{
				continue;
			}
			switch (map[y][x])
			{
			case NoneFloor:
				break;
			case FloorNormal:
				Object::Draw(floorOBJ[0],
					Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
				break;
			case Floor169:
				Object::Draw(floorOBJ[1],
					Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f - 5.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(169.3099f, 0.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
				break;
			case Floor11:
				Object::Draw(floorOBJ[2],
					Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f - 5.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(11.3099f, 0.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
				break;
			default:
				break;
			}

			switch (mapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
				Object::Draw(wallOBJ,
					Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapOBJPos[y][x]) * 10.0f + wallScale.y / 3, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), wallGraph);
				break;
			case Goal:
				Object::Draw(goalOBJ,
					Vec3(static_cast<float>(x) * 50.0f - 100.0f, static_cast<float>(mapOBJPos[y][x]) * 10.0f, (MAP_HEIGHT - 1 - y) * 50.0f),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			default:
				break;
			}
		}
	}
}



