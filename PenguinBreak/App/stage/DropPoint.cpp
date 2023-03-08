#include "DropPoint.h"
#include"Collision.h"
#include"Shape.h"
#include"../player/Player.h"
#include"Texture.h"
DropPoint::DropPoint()
{
}


DropPoint::~DropPoint()
{
}


void DropPoint::Init()
{
	m_dropPointOBJ = Shape::CreateSquare(10.0f, 0.05f, 10.0f);
	m_dropPointGraph = Texture::Get()->LoadTexture(L"Resources/UI/dropPoint.png");
}

void DropPoint::Update(const Vec3 &pPos, const Vec3 &pos, const Vec3 &angle, const Vec3 &scale)
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
		m_groundDistance = pos.y + scale.y / 2;
		m_isPointFlag = true;
	}
}


void DropPoint::Draw(const Vec3 &pPos)
{
	if (Player::Get()->GetGroundFlag() == false && m_isPointFlag == true)
	{
		Object::NoShadowDraw(m_dropPointOBJ, m_dropPointPSR,
			Vec3(pPos.x, m_groundDistance, pPos.z),
			Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec2(), m_dropPointGraph);
	}
}
