#pragma once
#include<Singleton.h>

class TimeAttack :public Singleton<TimeAttack>
{
private:
	friend Singleton<TimeAttack>;
public:
	TimeAttack();
	~TimeAttack();

	void Init();

	void Reset();

	void Update();

	void Draw();
private:
	const float timeframe = 60.0f;

	const float timeCount = 1.0f;

	float time = 0.0f;
};

