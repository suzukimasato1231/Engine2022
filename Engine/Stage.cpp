#include "Stage.h"
#include"Shape.h"
#include <LoadCSV.h>
#include"PushCollision.h"
Stage::Stage()
{}

Stage::~Stage()
{
}

void Stage::Init()
{
	floorOBJ[0] = Shape::CreateSquare(mapSize, 1.0f, mapSize);
	floorOBJ[1] = Shape::CreateSquare(mapSize, 1.0f, 28.28f);
	floorOBJ[2] = Shape::CreateSquare(mapSize, 1.0f, 28.28f);
	floorGraph = Texture::Instance()->LoadTexture(L"Resources/ground.png");

	wallOBJ = Shape::CreateSquare(wallScale.x, wallScale.y, wallScale.z);
	wallGraph = Texture::Instance()->LoadTexture(L"Resources/map/block.png");
	//ÉSÅ[Éãê›íË
	goalOBJ = Shape::CreateSquare(goalScale.x, goalScale.y, goalScale.z);
	breakBoxOBJ = Shape::CreateSquare(breakBoxScale.x, breakBoxScale.y, breakBoxScale.z);
	breakBoxGraph = Texture::Instance()->LoadTexture(L"Resources/woodenBox.png");

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
				goalPos = Vec3(static_cast<float>(x) * 50 - 100, static_cast<float>(mapOBJPos[y][x]) * 10, (MAP_HEIGHT - 1 - y) * mapSize);
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
}

void Stage::Update()
{
	Vec3 PPos = Player::Instance()->GetPosition();
	//îªíËÇ∑ÇÈâ”èäÇæÇØçsÇ§ÇΩÇﬂ
	int Z = static_cast<int>(PPos.z / (-mapSize));
	int X = static_cast<int>((PPos.x + 100.0f) / mapSize);
	for (int y = (MAP_HEIGHT - 1 + Z) - 1; y < (MAP_HEIGHT - 1 + Z) + 1; y++)
	{
		for (int x = X - 1; x < X + 2; x++)
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
				PushCollision::Player2Floor(Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(0.0f, 0.0f, 0.0f), Vec3(mapSize, 1.0f, mapSize));
				break;
			case Floor169:
				PushCollision::Player2Floor(Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapPos[y][x]) * 10 - 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(158.20f, 0.0f, 0.0f), Vec3(mapSize, 1.0f, 26.92f));
				break;
			case Floor11:
				PushCollision::Player2Floor(Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapPos[y][x]) * 10 - 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(21.80f, 0.0f, 0.0f), Vec3(mapSize, 1.0f, 26.92f));
				break;
			default:
				break;
			}

			switch (mapOBJ[y][x])
			{
			case NoneOBJ:
				break;
			case Wall:
				PushCollision::PlayerBox(Vec3(static_cast<float>(x) * mapSize - 100, static_cast<float>(mapOBJPos[y][x]) * 10.0f + wallScale.y / 2 - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					wallScale, mapOBJ[(y - 1) % MAP_HEIGHT][x], mapOBJ[(y + 1) % MAP_HEIGHT][x]);
				break;
			case Goal:
				goalFlag = PushCollision::PlayerGoal(goalBox);
				break;
			case BreakBox:
			{
				int breakNum = 0;
				int breakFlag = PushCollision::PlayerBox(Vec3(static_cast<float>(x) * mapSize - 100, static_cast<float>(mapOBJPos[y][x]) * 10.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					breakBoxScale, mapOBJ[(y - 1) % MAP_HEIGHT][x], mapOBJ[(y + 1) % MAP_HEIGHT][x]);
				if (breakFlag == 1)
				{
					mapOBJ[y][x] = 0;
					Player::Instance()->GetBlockStepOnFlag();
				}
				else if(breakFlag == 2)
				{
					mapOBJ[y][x] = 0;
				}
			}
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
	int Z = static_cast<int>(PPos.z / (-mapSize));

	for (int y = (MAP_HEIGHT - 1 + Z) - 40; y < (MAP_HEIGHT - 1 + Z) + 5; y++)
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
					Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
				break;
			case Floor169:
				Object::Draw(floorOBJ[1],
					Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f - 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(158.20f, 0.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
				break;
			case Floor11:
				Object::Draw(floorOBJ[2],
					Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapPos[y][x]) * 10.0f - 5.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(21.80f, 0.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), floorGraph);
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
					Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapOBJPos[y][x]) * 10.0f + wallScale.y / 2 - 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), wallGraph);
				break;
			case Goal:
				Object::Draw(goalOBJ,
					Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapOBJPos[y][x]) * 10.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			case BreakBox:
				Object::Draw(breakBoxOBJ,
					Vec3(static_cast<float>(x) * mapSize - 100.0f, static_cast<float>(mapOBJPos[y][x]) * 10.0f + breakBoxScale.y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), breakBoxGraph);
				break;
			default:
				break;
			}
		}
	}
}



