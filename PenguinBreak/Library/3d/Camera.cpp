#include "Camera.h"
using namespace DirectX;

Camera::Camera()
{
	matView = XMMatrixIdentity();
	//射影変換
	matProjection = XMMatrixIdentity();
}

Camera::~Camera()
{
}

Camera* Camera::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Camera* view = new Camera();
	if (view == nullptr) {
		return nullptr;
	}

	// 初期化
	return view;
}

void Camera::Initilize(Vec3 eye, Vec3 target, Vec3 up)
{
	//射影変換用
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		1.0f, 100.0f
	);
	this->eye = eye, this->target = target, this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::SetCamera(Vec3 eye, Vec3 target, Vec3 up)
{
	this->eye = eye, this->target = target, this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	//射影変換用
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		1.0f, 1500.0f
	);
	matViewProjection = matView * matProjection;
}

void Camera::FollowCamera(Vec3 position, Vec3 d, float angleX, float angleY)
{
	target = position;//注視点座標

   //カメラ追従
	if (angleX != followX || angleY != followY || !(d == followD))
	{
		followX = angleX, followY = angleY, followD = d;
		//1
		Vec3 V0 = d;
		//2
		XMMATRIX followRotM = XMMatrixIdentity();
		followRotM *= XMMatrixRotationY(XMConvertToRadians(angleX));//Y軸
		followRotM *= XMMatrixRotationX(XMConvertToRadians(angleY));//X軸

		//3
		XMVECTOR v3 = { V0.x,V0.y,V0.z };
		XMVECTOR v = XMVector3TransformNormal(v3, followRotM);

		//4
		followF3 = { v.m128_f32[0],v.m128_f32[1],v.m128_f32[2] };
	}
	eye.x = target.x + followF3.x, eye.y = target.y + followF3.y, eye.z = target.z + followF3.z;

	//5
	//ビュー変換行列
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	matViewProjection = matView * matProjection;
}

XMMATRIX Camera::GetMatView()
{
	return matView;
}

XMMATRIX Camera::GetProjection()
{
	return matProjection;
}

XMMATRIX Camera::GetMatViewProjection()
{
	return matViewProjection;
}

Vec3 Camera::GetEye()
{
	return eye;
}
Vec3 Camera::GetTarget()
{
	return target;
}

Vec3 Camera::GetUp()
{
	return up;
}
