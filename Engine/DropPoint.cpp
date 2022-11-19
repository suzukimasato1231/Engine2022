#include "DropPoint.h"
#include"Collision.h"
#include"Shape.h"
#include"../Engine/App/player/Player.h"
#include"Texture.h"
DropPoint::DropPoint()
{
}


DropPoint::~DropPoint()
{
}


void DropPoint::Init()
{
	dropPointOBJ = Shape::CreateSquare(10.0f, 0.05f, 10.0f);
	dropPointGraph = Texture::Get()->LoadTexture(L"Resources/dropPoint.png");
}

void DropPoint::Update(Vec3 pPos, Vec3 pos, Vec3 angle, Vec3 scale)
{
	//°OBB‚Ì“–‚½‚è”»’è‰Ÿ‚µ–ß‚µˆ—
	OBB diagonal;
	diagonal.Initilize(pos, angle, scale);
	//ƒvƒŒƒCƒ„[OBB
	OBB eOBB;
	Vec3 pSize = Player::Get()->GetPSize();
	eOBB.Initilize(pPos, Vec3{}, Vec3(pSize.x, pSize.y + 100.0f, pSize.z));
	if (OBBCollision::ColOBBs(eOBB, diagonal))
	{
		groundDistance = pos.y + scale.y / 2;
		isPointFlag = true;
	}
}


void DropPoint::Draw(Vec3 pPos)
{
	if (Player::Get()->GetGroundFlag() == false && isPointFlag == true)
	{
		Object::Draw(dropPointOBJ, dropPointPSR,
			Vec3(pPos.x, groundDistance, pPos.z),
			Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(), dropPointGraph, true);
	}
}
