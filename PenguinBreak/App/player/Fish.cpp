#include "Fish.h"

FishClass::FishClass()
{
}

FishClass::~FishClass()
{
}

void FishClass::Init()
{
	m_fishNum = {};
}

void FishClass::Update(bool &m_changeBreakFlag,int &m_remainLives)
{
	if (m_changeBreakFlag == true)
	{
		m_fishFlag = true;
		m_changeBreakFlag = false;
	}
	if (m_fishFlag == true)
	{
		m_fishNum += c_fishPlas;
		m_fishFlag = false;
		//100ŒÂW‚Ü‚Á‚½‚çŽc‹@‚P‚Â‘‚¦‚é
		if (m_fishNum >= c_fishMax)
		{
			m_fishNum -= c_fishMax;
			m_remainLives++;
		}
	}
}
