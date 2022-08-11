#pragma once
#include"Singleton.h"
#include"Sprite.h"
class UI :public Singleton<UI>
{
private:
	friend Singleton<UI>;
public:
	UI();
	~UI();

	void Init();

	void Update();

	void Draw();

private:
	SpriteData boxGraph;


};

