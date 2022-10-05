#include "Fish.h"
#include"Shape.h"
Fish::Fish()
{
}

Fish::~Fish()
{
}

void Fish::Create(int stageNum)
{
	
}

void Fish::Init()
{
	fishOBJ = Shape::CreateOBJ("fish", true);
}

void Fish::Update()
{
}

void Fish::Draw()
{
	//Object::Draw(fishOBJ, );
}
