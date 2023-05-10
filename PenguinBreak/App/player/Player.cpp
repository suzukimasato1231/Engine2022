#include"Player.h"
#include"Shape.h"
#include"Input.h"
#include"Collision.h"
#include "Safe_delete.h"
Player::Player()
{}

Player::~Player()
{}

void Player::Init()
{
	m_oldPosition = m_position;
	m_pBox.maxPosition = XMVectorSet(m_position.x + m_pScale.x / 2, m_position.y + m_pScale.y / 2, m_position.z + m_pScale.z / 2, 1);
	m_pBox.minPosition = XMVectorSet(m_position.x - m_pScale.x / 2, m_position.y - m_pScale.y / 2, m_position.z - m_pScale.z / 2, 1);
	m_staging.Init();
	m_walkSE = Audio::SoundLoadWave("Resources/sound/SE/walk.wav");
	m_fallSE = Audio::SoundLoadWave("Resources/sound/SE/fall.wav");
	m_electSE = Audio::SoundLoadWave("Resources/sound/SE/elect.wav");
	m_pFbx.Load();

}

void Player::Update()
{
	if (m_gameoverFlag == true) { return; }

	m_oldPosition = m_position;
	m_oldGroundFlag = m_groundFlag;
	m_vec = {};
	//���̊Ԋu�̍X�V
	AudioUpdate();
	//�ړ�
	Move();
	//�W�����v
	Jump();
	//�X�s���U��
	SpinAttack();

	m_staging.Update();

	m_position += m_vec;
	m_pBox.maxPosition = XMVectorSet(m_position.x + m_pScale.x / 2, m_position.y + m_pScale.y / 2, m_position.z + m_pScale.z / 2, 1);
	m_pBox.minPosition = XMVectorSet(m_position.x - m_pScale.x / 2, m_position.y - m_pScale.y / 2, m_position.z - m_pScale.z / 2, 1);
	//������
	FallDie();
	
	fishClass.Update(m_changeBreakFlag,m_remainLives);

	RedFishDie();

	m_pFbx.Update(m_oldPosition, m_angle);

	AnimationUpdate();
}

void Player::Draw(bool shadowFlag)
{
	m_staging.Draw3D();
	if (m_starStaging == false || m_moveFlag == false)
	{
		m_pFbx.Draw(shadowFlag);
	}
}

void Player::DrawParticle()
{
	m_staging.Draw();
}

void Player::SetPosition(const Vec3& position)
{
	m_position = position;
	m_pBox.maxPosition = XMVectorSet(position.x + m_pScale.x / 2, position.y + m_pScale.y / 2, position.z + m_pScale.z / 2, 1);
	m_pBox.minPosition = XMVectorSet(position.x - m_pScale.x / 2, position.y - m_pScale.y / 2, position.z - m_pScale.z / 2, 1);
}


void Player::Reset()
{
	m_position = c_firstPosition;	//���W
	m_oldPosition = m_position;
	m_remainLives = c_remainLivesMax;
	fishClass.Init();
	m_gameoverFlag = false;
	m_dieType = static_cast<int>(DieType::DIENULL);
	m_clearFlag = false;
	m_angle = c_firstAngle;	//�p�x
	m_decLifeTime = {};
	m_isFishDie = false;
	m_pFbx.Reset();
	if (m_moveFlag == true)
	{
		m_starStaging = true;
		m_startTime = {};
	}
	else
	{
		m_starStaging = false;
	}
}

void Player::GoalStaging(int fbxType)
{
	m_angle.y = 180.0f;
	m_pFbx.PlayFBX(fbxType);
}

void Player::StopAnimation()
{
	m_pFbx.StopAnimation();
}

void Player::MoveController(const Vec3& speed)
{
	const int audioCoolTime = 15;//����炷�܂ł̎���
	if (m_groundFlag == true && m_audioTime % audioCoolTime == 0)
	{
		Audio::Get()->SoundSEPlayWave(m_walkSE);
	}
	float rad = Input::Get()->GetLeftAngle();
	m_vec.x = speed.x * sinf(-rad);
	if (m_moveFlag == true)
	{
		m_vec.z = speed.z * cosf(rad);;
	}
	m_angle.y = XMConvertToDegrees(atan2(sinf(-rad), cosf(rad)));
	if (m_walkTime < 0)
	{
		m_staging.CreateWalk(m_position, m_vec);
		m_walkTime = c_walkTimeMax;
	}
	m_walkTime--;
}


void Player::SpinAttack()
{
	m_spinFlag = false;
	if (((Input::Get()->KeybordPush(DIK_F) || Input::Get()->ControllerDown(ButtonX))
		&& m_starStaging == false && m_dieType == static_cast<int>(DieType::DIENULL) && m_clearFlag == false && m_spinCoolTime <= 0))
	{
		m_pFbx.PlayFBX(FbxSpin);
		m_spinCoolTime = c_spinCoolTimeMax;
		m_spinAttack.maxPosition = XMVectorSet(m_oldPosition.x + c_spinScale, m_oldPosition.y + 1, m_oldPosition.z + c_spinScale, 1);
		m_spinAttack.minPosition = XMVectorSet(m_oldPosition.x - c_spinScale, m_oldPosition.y - 0, m_oldPosition.z - c_spinScale, 1);
		m_spinFlag = true;
	}

	if (m_spinCoolTime >= c_spinCoolTimeMax - 10)
	{
		m_spinAttack.maxPosition = XMVectorSet(m_oldPosition.x + c_spinScale, m_oldPosition.y + 1, m_oldPosition.z + c_spinScale, 1);
		m_spinAttack.minPosition = XMVectorSet(m_oldPosition.x - c_spinScale, m_oldPosition.y - 0, m_oldPosition.z - c_spinScale, 1);
		m_spinFlag = true;
	}

	if (m_spinCoolTime >= 0)
	{
		m_spinCoolTime--;
	}

}

void Player::AnimationUpdate()
{
	//�J�n���̃A�j���[�V����
	if (m_starStaging == false || m_moveFlag == false) { return; }
	if (m_startTime >= c_startTimeMax - 40)
	{
		m_staging.CreateStart(m_position);
	}
	m_startTime++;
	if (m_startTime >= c_startTimeMax)
	{
		m_starStaging = false;
		m_startTime = 0;
	}
}

void Player::AudioUpdate()
{
	m_audioTime++;
	const int audioTimeMax = 201;//���Ԃ����Z�b�g����ő�l
	if (m_audioTime >= audioTimeMax)
	{
		m_audioTime = 0;
	}
}

bool Player::OutofFallDown(const Vec3& pos)const
{
	if (pos.y < c_fallPos && m_dieType == static_cast<int>(DieType::DIENULL))
	{
		return true;
	}
	return false;
}


//�ړ�
void Player::Move()
{
	if (m_dieType != static_cast<int>(DieType::DIENULL) || m_clearFlag == true || m_gameoverFlag == true || m_starStaging == true) { return; }
	//�L�[�{�[�h�ړ�
	if (Input::Get()->KeybordInputArrow() == true)
	{
		if (m_moveFlag == true)//�ړ����QD���RD��
		{
			if (Input::Get()->KeybordPush(DIK_UP))
			{
				m_vec.z += c_speed.z;
			}
			if (Input::Get()->KeybordPush(DIK_DOWN))
			{
				m_vec.z -= c_speed.z;
			}
		}
		//�ړ�
		if (Input::Get()->KeybordPush(DIK_RIGHT))
		{
			m_vec.x += c_speed.x;
		}
		if (Input::Get()->KeybordPush(DIK_LEFT))
		{
			m_vec.x -= c_speed.x;
		}
	}
	//�R���g���[���[�ړ�
	if (Input::Get()->ConLeftInput())
	{
		MoveController(c_speed);
		m_pFbx.PlayFBX(FbxWalk);
	}
	else if (Input::Get()->ConLeftInputS())
	{
		MoveController(c_walkSpeed);
		m_pFbx.PlayFBX(FbxWalking);
	}
	else
	{
		m_pFbx.PlayFBX(FbxNone);
	}
}

void Player::Jump()
{
	//�W�����v
	if (((Input::Get()->KeybordPush(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA))
		&& m_groundFlag == true && m_starStaging == false && m_dieType == static_cast<int>(DieType::DIENULL) && m_clearFlag == false) || m_blockStepOnFlag)
	{
		if (m_jumpBoxFlag)
		{
			m_jumpPower = c_jumpBoxPowerMax;
			m_jumpBoxFlag = false;
		}
		else
		{
			m_jumpPower = c_jumpPowerMax;
		}
		m_blockStepOnFlag = false;

		m_pFbx.PlayFBX(FbxJump);
	}

	//�d�͉��Z
	m_vec.y -= m_gravity;
	if (m_jumpPower > 0)
	{
		m_vec.y += m_jumpPower;
		m_jumpPower -= m_jumpPowerDelay;
	}
	m_groundFlag = false;
}

void Player::FallDie()
{
	if (OutofFallDown(m_position))
	{
		const int dieTime = 30;	//���񂾂Ƃ��̉��o����
		m_dieNowTime = dieTime;
		m_staging.CreateFallDown(m_position);
		Audio::Get()->SoundSEPlayWave(m_fallSE);
		m_dieType = static_cast<int>(DieType::DIENOW);
	}
	else if (m_dieType == static_cast<int>(DieType::ELECTDIE))
	{
		const int dieTime = 200;				//���񂾂Ƃ��̉��o����
		m_dieNowTime = dieTime;
		m_staging.CreateElect(m_position);
		m_dieType = static_cast<int>(DieType::DIENOW);
		Audio::Get()->SoundSEPlayWave(m_electSE);
		m_pFbx.PlayFBX(FbxElectDie);
	}
	else if (m_dieType == static_cast<int>(DieType::EATDIE))
	{
		const int dieTime = 100;		//���񂾂Ƃ��̉��o����
		m_dieNowTime = dieTime;
		m_dieType = static_cast<int>(DieType::DIENOW);
		m_isFishDie = true;
	}
	else if (m_dieType == static_cast<int>(DieType::BOMBDIE))
	{
		const int dieTime = 50;			//���񂾂Ƃ��̉��o����
		m_dieNowTime = dieTime;
		m_dieType = static_cast<int>(DieType::DIENOW);
		m_pFbx.PlayFBX(FBXMAX);
	}


	if (m_dieType != static_cast<int>(DieType::DIENOW)) { return; }

	if (m_dieNowTime > 0)
	{
		m_dieNowTime--;
		//�Ó]�J�n
		if (m_dieNowTime == 1)
		{
			m_decLifeTime = 50;
		}
	}
	else
	{
		if (m_remainLives > 0)
		{
			m_decLifeTime--;
			if (m_decLifeTime <= 0)
			{
				SetPosition(c_firstPosition);
				m_angle = c_firstAngle;	//�p�x
				m_oldPosition = m_position;
				m_remainLives--;
				m_isFishDie = false;
				m_dieType = static_cast<int>(DieType::DIENULL);
				m_starStaging = true;
			}
		}
		else if (m_remainLives == 0)
		{
			m_gameoverFlag = true;
			m_dieType = static_cast<int>(DieType::DIENULL);
		}
	}

}

void Player::RedFishDie()
{
	if (m_isFishDie == false) { return; }
	m_position = m_fishDiePos;
	m_oldPosition = m_position;
	m_angle.x = m_fishDieAngle.x;
	if (m_position.y < c_fallPos && m_dieType == static_cast<int>(DieType::DIENOW))
	{
		m_isFishDie = false;
	}
}