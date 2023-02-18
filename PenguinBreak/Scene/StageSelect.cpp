#include "StageSelect.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"DebugText.h"
#include"../App/player/Player.h"
#include"Object.h"
#include"../App/stage/Stage.h"
StageSelect::StageSelect()
{}
StageSelect::~StageSelect()
{
}
void StageSelect::Initialize()
{
	selectOBJ = Shape::CreateOBJ("cube");
	boxBreakOBJ = Shape::CreateRect(30.0f, 30.0f);

	selectGraph[0] = Texture::Get()->LoadTexture(L"Resources/select/select1.png");
	selectGraph[1] = Texture::Get()->LoadTexture(L"Resources/select/select2.png");
	selectGraph[2] = Texture::Get()->LoadTexture(L"Resources/select/select3.png");

	boxFramGraph = Texture::Get()->LoadTexture(L"Resources/select/selectFram.png");
	boxBreakGraph = Texture::Get()->LoadTexture(L"Resources/UI/UIBox.png");
	// ���C�g�O���[�v�N���X�쐬
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, -1));
	boxSE = Audio::SoundLoadWave("Resources/sound/SE/boxBreak.wav");


	numberGraph[0] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber1.png");
	numberGraph[1] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber2.png");
	numberGraph[2] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber3.png");
	numberGraph[3] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber4.png");
	numberGraph[4] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber5.png");
	numberGraph[5] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber6.png");
	numberGraph[6] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber7.png");
	numberGraph[7] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber8.png");
	numberGraph[8] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber9.png");
	numberGraph[9] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber10.png");
	numberGraph[10] = Texture::Get()->LoadTexture(L"Resources/UI/UISlash.png");
}

void StageSelect::Init()
{
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	Player::Get()->ChangeMoveFlag(false);
	Player::Get()->Reset();
	Player::Get()->GetClearFlag(false);
	for (size_t i = 0; i < stageNumMax; i++)
	{
		selectPos[i] = Vec3(50.0f + 50 * i, 30.0f, 150.0f);
		selectBox[i].maxPosition = XMVectorSet(selectPos[i].x + selectScale / 2, selectPos[i].y + selectScale / 2, selectPos[i].z + selectScale / 2, 1);
		selectBox[i].minPosition = XMVectorSet(selectPos[i].x - selectScale / 2, selectPos[i].y - selectScale / 2, selectPos[i].z - selectScale / 2, 1);
	}
	selectFlag = false;
	Stage::Get()->LoadStage(0);
	Player::Get()->SetPosition(Vec3(20.0f, 10.0f, 150.0f));

	//���o������
	for (int i = 0; i < stageNumMax; i++)
	{
		productionFlag[i] = false;
	}
	productionTime = 0;
}


void StageSelect::Update()
{
	//�X�e�[�W�I��
	Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3(0.0f, 15.0f, -130.0f));

	for (int i = 0; i < stageNumMax; i++)
	{
		if (Collision::CheckBox2Box(Player::Get()->GetBox(), selectBox[i]))
		{
			if (selectPos[i].y - selectScale / 2 > Player::Get()->GetOldPosition().y + Player::Get()->GetPSize().y / 2 && productionTime == 0)
			{
				stageNum = i + 1;
				productionFlag[i] = true;
				productionTime = productionTimeMax;
				Player::Get()->JumpPoweZero();
				Audio::Get()->SoundSEPlayWave(boxSE);
			}
			else
			{
				Player::Get()->SetPosition(Vec3(Player::Get()->GetOldPosition().x, Player::Get()->GetPosition().y, Player::Get()->GetPosition().z));
			}
		}
	}

	if (productionFlag[0] == true || productionFlag[1] == true || productionFlag[2] == true)
	{
		Player::Get()->DieType(1);
		Player::Get()->JumpPoweZero();
	}

	Player::Get()->Update();

	Stage::Get()->Update(Player::Get()->GetPosition());
	//���C�g�X�V
	lightGroup->Update();

	//������ɏオ�鉉�o
	for (int i = 0; i < stageNumMax; i++)
	{
		if (productionFlag[i] == true && productionTime > 0)
		{
			productionTime--;

			if (productionTime > productionTimeMax - 10)
			{
				selectPos[i].y += 1.0f;
			}
			else if (productionTime > productionTimeMax - 20)
			{
				selectPos[i].y -= 1.0f;
			}

			if (productionTime <= 0)
			{
				selectFlag = true;
			}
		}
	}


	//�ő唠�̐�
	for (int i = 0; i < 3; i++)
	{
		breakNumMax[i] = breakBoxMax[i] % 10;
		breakNumTenMax[i] = breakBoxMax[i] / 10;


		breakNum[i] = breakBox[i] % 10;
		breakNumTen[i] = breakBox[i] / 10;
	}
}

void StageSelect::Draw()
{
	//�w�i�`��
	Player::Get()->Draw(true);
	Stage::Get()->Draw(Player::Get()->GetPosition(), true);
	for (size_t i = 0; i < stageNumMax; i++)
	{
		Object::NoShadowDraw(boxBreakOBJ, flamePSR[i], Vec3(50.0f + 50 * i, 50.0f, 150.0f),
			Vec3(1.3f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), boxFramGraph);
		Object::NoShadowDraw(boxBreakOBJ, boxBreakPSR[i], Vec3(40.0f + 50 * i, 50.0f, 149.5f),
			Vec3(0.4f, 0.4f, 0.4f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), boxBreakGraph);
		//�����\�̌�
		Object::NoShadowDraw(boxBreakOBJ, boxBreakPSR[i], Vec3(48.0f + 50 * i, 57.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), numberGraph[breakNumTen[i]]);
		//������̌�
		Object::NoShadowDraw(boxBreakOBJ, boxBreakPSR[i], Vec3(56.0f + 50 * i, 57.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), numberGraph[breakNum[i]]);
		//�ő吔���\�̌�
		Object::NoShadowDraw(boxBreakOBJ, boxBreakPSR[i], Vec3(53.0f + 50 * i, 42.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), numberGraph[breakNumTenMax[i]]);
		//�ő吔����̌�
		Object::NoShadowDraw(boxBreakOBJ, boxBreakPSR[i], Vec3(60.0f + 50 * i, 42.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), numberGraph[breakNumMax[i]]);

		Object::NoShadowDraw(boxBreakOBJ, boxBreakPSR[i], Vec3(54.0f + 50 * i, 50.0f, 149.0f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), numberGraph[10]);

		Object::Draw(selectOBJ, selectPsr[i], selectPos[i],
			Vec3(selectScale, selectScale, selectScale), Vec3(), Vec2(), selectGraph[i], true);
	}
}

void StageSelect::DrawShadow()
{
	Player::Get()->Draw();
	Stage::Get()->Draw(Player::Get()->GetPosition());
}

void StageSelect::SetBreakBoxNum(int breakBox_)
{
	if (breakBox_ > breakBox[stageNum - 1])
	{
		this->breakBox[stageNum - 1] = breakBox_;
	}

}
