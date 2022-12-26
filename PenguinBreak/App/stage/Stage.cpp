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
	floorOBJ = Shape::CreateOBJ("ice",false,"OBJ/");
	floorGraph = Texture::Get()->LoadTexture(L"Resources/floor.png");
	wallOBJ = Shape::CreateOBJ("iceWall", false, "OBJ/");

	blackGround = Shape::CreateSquare(1.0f, 0.5f, 1.0f);
	blackGraph = Texture::Get()->LoadTexture(L"Resources/black.png");

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

	boxStaring.Init();
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

	dropPoint.ChangeFlag();

	boxStaring.Update();

	for (int i = 0; i < stageObj.size(); i++)
	{
		switch (stageObj[i]->type)
		{
		case Wall:
		case BOX:
		case BOXJUMP:
		case BOXHARD:
			blockBox.PlayerHit(stageObj[i], X, Z);
			if (stageObj[i]->type != Wall)
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

	if (blockBox.GetIs_Hit() == true && Player::Get()->GetIsFishDie() == false)
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
					BOX == stageObj[i]->type)
				{
					Player::Get()->GetBlockStepOnFlag();
					Player::Get()->ChangeBreakFlag();
					boxStaring.BreakBoxFlag(stageObj[i]->position);
					fishBox.Create(stageObj[i]->position);
					delete stageObj[i];
					stageObj.erase(stageObj.begin() + i);
					blockNum++;
					break;
				}//ジャンプ台
				else if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
					BOXJUMP == stageObj[i]->type)
				{
					Player::Get()->GetJumpBox();
					Player::Get()->GetBlockStepOnFlag();
				}
			}
		}
		else if (breakFlag == 2)
		{
			if (stageObj[breakNum]->type == BOX)
			{
				Player::Get()->JumpPoweZero();
				Player::Get()->ChangeBreakFlag();
				for (int i = 0; i < stageObj.size(); i++)
				{
					if (breakNum == -1) { break; }
					if (blockBox.GetObj_Data(breakNum).position == stageObj[i]->position &&
						BOX == stageObj[i]->type)
					{
						boxStaring.BreakBoxFlag(stageObj[i]->position);
						fishBox.Create(stageObj[i]->position);
						delete stageObj[i];
						stageObj.erase(stageObj.begin() + i);
						blockNum++;
					}
				}
			}
		}
	}
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
			if ((X - drawNumX <= floor[i]->map.x && floor[i]->map.x <= X + drawNumX)
				&& ((MAP_HEIGHT - 1 + Z) - drawNumY <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4)
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

void Stage::Draw(Vec3 pPos, bool shadowFlag)
{
	Vec3 PPos = Player::Get()->GetPosition();
	//判定する箇所だけ行うため
	int X = static_cast<int>(PPos.x / mapSize);
	int Z = static_cast<int>(PPos.z / (-mapSize));
	size_t floorSize = floor.size();
	//床の描画
	for (int i = 0; i < floorSize; i++)
	{
		if ((X - drawNumX <= floor[i]->map.x && floor[i]->map.x <= X + drawNumX)
			&& ((MAP_HEIGHT - 1 + Z) - 50 <= floor[i]->map.y && floor[i]->map.y <= (MAP_HEIGHT - 1 + Z) + 4))
		{
			switch (floor[i]->type)
			{
			case FloorNormal:
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 15.0f, floor[i]->position.z),
					Vec3(25.0f, 30.0f, 25.0f * (floor[i]->size + 1)),
					floor[i]->angle, Vec2(), 0, shadowFlag);
				break;
			case Floor169:
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 12.0f, floor[i]->position.z + 9.5f),
					Vec3(25.0f, 30.0f, 32.1f * 2),
					floor[i]->angle, Vec2(), floorGraph, shadowFlag);
				break;
			case Floor11:
				Object::Draw(floorOBJ, floor[i]->psr, Vec3(floor[i]->position.x, floor[i]->position.y - 12.0f, floor[i]->position.z - 9.5f),
					Vec3(25.0f, 30.0f, 32.1f),
					floor[i]->angle, Vec2(), floorGraph, shadowFlag);
				break;
			case FloorMove:
				moveFloor.Draw(floor[i], shadowFlag);
				break;
			case FloorPitfall_A:
			case FloorPitfall_B:
				floorPitfall.Draw(floor[i], shadowFlag);
				break;
			default:
				break;
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
					Vec3(12.0f, 12.0f, 12.0f), stageObj[i]->angle, Vec2(), 0, shadowFlag);
				break;
			case  Goal:
				goalFish.Draw(stageObj[i], shadowFlag);
				break;
			case BOX:
			case BOXJUMP:
			case BOXHARD:
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
	Object::NoShadowDraw(blackGround, blackPsr[0], Vec3(pPos.x, -50.0f, pPos.z + 1000.0f),
		Vec3(10000.0f, 1.0f, 100000.0f), Vec3(), Vec2(), blackGraph);

	//左右の床の描画
	Object::Draw(floorOBJ, blackPsr[1], Vec3(-280.0f, 5.0f, 1200.0f),
		Vec3(550.0f, 15.0f, 5500.0f),
		Vec3(), Vec2(), 0, shadowFlag);
	Object::Draw(floorOBJ, blackPsr[2], Vec3(500.0f, 5.0f, 1200.0f),
		Vec3(550.0f, 15.0f, 5500.0f),
		Vec3(), Vec2(), 0, shadowFlag);

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
				}
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)), FloorNormal, num_ - 1);
			}
			break;
			case Floor169:
				SetFloor(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f + 0.0f, (MAP_HEIGHT - 1 - y) * mapSize + 12.3f),
					Vec3(mapSize, 1.0f, 32.01f * 2), Vec3(141.61f, 0.0f, 0.0f), Vec2(static_cast<float>(x), static_cast<float>(y)), Floor169);
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
			case FloorMove2:
				SetMoveFloor2(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapPos[y][x]) * 20.0f, (MAP_HEIGHT - 1 - y) * mapSize),
					Vec3(25.0f, 1.0f, 25.0f), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
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
					goalFish.GetGoalScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BOX:
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BOXDOUBLE:
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				SetBreakBox(Vec3(static_cast<float>(x) * mapSize, (static_cast<float>(MapOBJPos[y][x]) + 1.0f) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BOXJUMP:
				SetJumpBox(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case BOXHARD:
				SetBreakHard(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case ELECTRICITY:
				SetElectricity(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
				break;
			case FISHATTACK:
				SetFishAttack(Vec3(static_cast<float>(x) * mapSize, static_cast<float>(MapOBJPos[y][x]) * 20.0f + blockBox.GetBoxScale().y / 2, (MAP_HEIGHT - 1 - y) * mapSize),
					blockBox.GetBoxScale(), Vec3(), Vec2(static_cast<float>(x), static_cast<float>(y)));
			default:
				break;
			}
		}
	}
}

void Stage::SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type, int size)
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

void Stage::SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, BOX);
	blockMax++;
}

void Stage::SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, BOXJUMP);
}

void Stage::SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
{
	stageObj.push_back(new StageOBJ);
	size_t num = stageObj.size() - 1;
	*stageObj[num] = BlockBox::SetBox(position, scale, angle, map, BOXHARD);
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
	floor.push_back(new Floor);
	size_t NUM = floor.size() - 1;
	floor[NUM]->map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	floor[NUM]->position = position;
	floor[NUM]->scale = scale;
	floor[NUM]->angle = angle;
	floor[NUM]->type = FloorMove;
}

void Stage::SetMoveFloor2(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map)
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

void Stage::SetPitfallFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int time)
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
	*stageObj[num] = DangerFish::SetDangerFish(position, scale, angle, map, FISHATTACK);
}