#include "Stage.h"
#include"Shape.h"
#include"PushCollision.h"
#include<string>

using namespace std;
Stage::Stage()
{}

Stage::~Stage()
{
	stageData.clear();
}

void Stage::Init()
{
	m_blockBox.Init();
	m_floorOBJ = Shape::CreateOBJ("ice", false, "OBJ/");
	m_floorGraph = Texture::Get()->LoadTexture(L"Resources/floor.png");

	MainInit(0);

	m_goalFish.Init();
	//��������������
	m_moveFloor.Init();
	//���]����������
	m_floorPitfall.Init();
	//����������
	m_fishBox.Init();
	//�d�C��㩂�������
	m_elect.Init();
	//�댯����������
	m_dangerFish.Init();

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
	//��
	LoadStage(stageNum);
	m_goalFlag = false;
	m_goalSEFlag = false;
	//��������
	m_fishBox.Delete();
}

void Stage::Update(const Vec3& pPos)
{
	m_boxStaring.Update();
	for (auto& s : stageData)
	{
		if (CheckFigurineJudge(s) || CheckBoxJudge(s) == true)
		{
			m_blockBox.PlayerHit(s);
			m_blockBox.PlayerSpinHit(s);
		}
		else if (s->fileName.compare("GOAL") == 0)
		{
			if (Collision::CheckBox2Box(s->box, Player::Get()->GetBox()))
			{
				//�S�[��
				m_goalFlag = true;
				if (m_goalSEFlag == false)
				{
					Audio::Get()->SoundSEPlayWave(m_goalSE);
				}
				m_goalSEFlag = true;
			}
			m_goalFish.Update();
		}
		else if (s->fileName.compare("ELECTRICITY") == 0)
		{
			m_elect.Update(s);
		}
		else if (s->fileName.compare("FISHATTACK") == 0)
		{
			if (Collision::CheckBox2Box(s->box, Player::Get()->GetBox()))
			{
				Player::Get()->DieType(static_cast<int>(DieType::EATDIE));
				Player::Get()->FishDie(s->actionPos, m_dangerFish.GetFishAngle());
			}
			m_dangerFish.Update(s);
		}
	}
	//���锠�̏���
	BreakBoxs();
	for (auto& s : stageData)
	{
		if (s->fileName.compare("FLOORNORMAL") == 0)
		{
			FloorHitDropPoint(s, pPos);
		}
		else if (s->fileName.compare("FLOORMOVE") == 0 || s->fileName.compare("FLOORMOVE2") == 0)
		{
			if (Player::Get()->GetIsFishDie() == false)
			{
				//�v���C���[
				PushCollision::Player2Floor(s->position,
					s->rotation, s->scale, s->actionType);
			}
			m_moveFloor.Update(s);
		}
		else if (s->fileName.compare("FLOORPITFALL_A") == 0 || s->fileName.compare("FLOORPITFALL_B") == 0)
		{
			if (s->actionType == 0)
			{
				FloorHitDropPoint(s, pPos);
			}
			m_floorPitfall.Update(s);
		}
	}

	//���̍X�V
	m_blockBox.Update();

	m_elect.AllUpdate();

	m_dangerFish.AllUpdate();
	//���̍X�V
	m_fishBox.Update(pPos);
}

void Stage::Draw(bool shadowFlag)
{
	for (auto& s : stageData)
	{
		if (CheckFigurineJudge(s))
		{
			m_figurineOBJ.Draw(s, shadowFlag);
		}
		else if (CheckBoxJudge(s) == true)
		{
			m_blockBox.Draw(s, shadowFlag);
		}
		else if (s->fileName.compare("FLOORNORMAL") == 0)
		{
			Object::Draw(m_floorOBJ, s->psr, s->position,
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
		else if (s->fileName.compare("FLOORPITFALL_A") == 0 || s->fileName.compare("FLOORPITFALL_B") == 0)
		{
			m_floorPitfall.Draw(s, shadowFlag);
		}
		else if (s->fileName.compare("ELECTRICITY") == 0)
		{
			m_elect.Draw(s, shadowFlag);
		}
		else if (s->fileName.compare("FISHATTACK") == 0)
		{
			m_dangerFish.Draw(s, shadowFlag);
		}
	}
	DrawWater();

	//���󂵂����ɏo�鋛
	m_fishBox.Draw();

	m_boxStaring.Draw3D();
}

void Stage::DrawParicle()
{
	m_elect.DrawParicle();
	//�p�[�e�B�N��
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
			if (CheckFigurineJudge(objectData))
			{
				SetStageBox(objectData, m_wallScale);
			}
			else if (CheckBoxJudge(objectData))
			{
				SetStageBox(objectData, boxScale);
				if (objectData->fileName.compare("BOX") == 0) { m_blockMax++; }
			}
			else if (objectData->fileName.compare("GOAL") == 0)
			{
				SetStageBox(objectData, m_goalFish.GetGoalScale());
			}
			else if (objectData->fileName.compare("FLOORMOVE") == 0)
			{
				objectData->actionType = static_cast<int>(MoveType::MOVEFRONT);
			}
			else if (objectData->fileName.compare("FLOORMOVE2") == 0)
			{
				objectData->actionType = static_cast<int>(MoveType::MOVEBACK);
			}
			else if (objectData->fileName.compare("FLOORPITFALL_A") == 0)
			{
				objectData->actionType = PITFALLOPEN;
			}
			else if (objectData->fileName.compare("FLOORPITFALL_B") == 0)
			{
				objectData->actionType = PITFALLCLOSE;
			}
			else if (objectData->fileName.compare("ELECTRICITY") == 0)
			{
				const Vec3 BasicScale = { 90.0f * objectData->scale.z ,40.0f,20.0f };	//��{�̑傫��
				Vec3 basicPos = objectData->position;
				basicPos.x -= objectData->scale.z * 5.5f;
				objectData->rotation.y -= 90.0f;
				objectData->rotation.z -= 90.0f;
				objectData->box.maxPosition =
					XMVectorSet(basicPos.x + BasicScale.x / 2, basicPos.y + BasicScale.y / 2, basicPos.z + BasicScale.z / 2, 1);
				objectData->box.minPosition =
					XMVectorSet(basicPos.x - BasicScale.x / 2, basicPos.y - BasicScale.y / 2, basicPos.z - BasicScale.z / 2, 1);
			}
			else if (objectData->fileName.compare("FISHATTACK") == 0)
			{
				const Vec3 BasicScale = { 25.0f ,25.0f,25.0f };//��{�̑傫��
				objectData->actionPos = objectData->position;
				SetStageBox(objectData, BasicScale);
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
	const Vec3 angle = { 90.0f,0.0f,0.0f };
	const Vec3 scale = { 1.0f,1.0f,1.0f };
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			Object::NoShadowDraw(m_water, m_blackPsr[i][j],
				Vec3(50.0f + 500.0f * j, -70.0f, 500.0f * i), scale,
				angle, m_waterUV, m_waterGraph);
		}
	}
}

void Stage::BreakBoxs()
{
	//���ނ��@���ĉ��锠�̏���
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
					stageData.erase(stageData.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
					break;
				}//�W�����v��
				else if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOXJUMP") == 0)
				{
					Player::Get()->ActivateJumpBox();
					Player::Get()->ActivateBlockStepOn();
					Audio::Get()->SoundSEPlayWave(m_jumpSE);
				}//������
				else if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOXBOMB") == 0)
				{
					Player::Get()->DieType(static_cast<int>(DieType::BOMBDIE));
					m_boxStaring.BombBoxFlag(stageData[i]->position);
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
					stageData.erase(stageData.begin() + i);
					m_blockNum++;
					Audio::Get()->SoundSEPlayWave(m_boxSE);
				}
				else if (m_blockBox.GetObj_Data(breakNum).position == stageData[i]->position &&
					stageData[i]->fileName.compare("BOXBOMB") == 0)
				{
					Player::Get()->DieType(static_cast<int>(DieType::BOMBDIE));
					m_boxStaring.BombBoxFlag(stageData[i]->position);
					stageData.erase(stageData.begin() + i);
					Audio::Get()->SoundSEPlayWave(m_bombSE);
				}
			}
		}
	}
	//�X�s���ŉ��锠�̏���
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
						stageData.erase(stageData.begin() + i);
						m_blockNum++;
						Audio::Get()->SoundSEPlayWave(m_boxSE);
					}
					else if (m_blockBox.GetObj_Spin(j).position == stageData[i]->position &&
						stageData[i]->fileName.compare("BOXBOMB") == 0)
					{
						//�����I��
						Player::Get()->DieType(static_cast<int>(DieType::BOMBDIE));
						//�������o
						m_boxStaring.BombBoxFlag(stageData[i]->position);
						stageData.erase(stageData.begin() + i);
						Audio::Get()->SoundSEPlayWave(m_bombSE);
					}
				}
			}
		}
	}
}

bool Stage::CheckBoxJudge(const StageData* stageData)
{
	if (stageData == nullptr) { assert(0); }
	if (stageData->fileName.compare("BOX") == 0 || stageData->fileName.compare("BOXJUMP") == 0 || stageData->fileName.compare("BOXHARD") == 0 || stageData->fileName.compare("BOXBOMB") == 0)
	{
		return true;
	}
	return false;
}

bool Stage::CheckFigurineJudge(const StageData* stageData)
{
	if (stageData == nullptr) { assert(0); }
	if (stageData->fileName.compare("WALL") == 0 || stageData->fileName.compare("STLON") == 0
		|| stageData->fileName.compare("DEADTREE") == 0 || stageData->fileName.compare("BARRIERWALL") == 0
		|| stageData->fileName.compare("ICEARCH") == 0 || stageData->fileName.compare("SIGNBOARD1") == 0
		|| stageData->fileName.compare("SIGNBOARD2") == 0)
	{
		return true;
	}
	return false;
}

void Stage::SetStageBox(StageData* stageData, const Vec3& scale)
{
	stageData->rotation.z -= 90.0f;
	stageData->box.maxPosition =
		XMVectorSet(stageData->position.x + scale.x / 2, stageData->position.y + scale.y / 2, stageData->position.z + scale.z / 2, 1);
	stageData->box.minPosition =
		XMVectorSet(stageData->position.x - scale.x / 2, stageData->position.y - scale.y / 2, stageData->position.z - scale.z / 2, 1);
}

void Stage::FloorHitDropPoint(const StageData* s, const Vec3& PPos)
{
	if (s == nullptr) { assert(0); }
	
	if (Player::Get()->GetIsFishDie() == true) { return; }

	//�v���C���[
	PushCollision::Player2Floor(s->position,
		s->rotation, s->scale);

}
