#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include"Vec.h"
#include"Singleton.h"
extern const int window_width;
extern const int window_height;
/// <summary>
/// カメラクラス
/// </summary>
class Camera :public Singleton<Camera>
{
	using XMMATRIX = DirectX::XMMATRIX;
private:
	friend Singleton<Camera>;
	//ビュー変換行列
	XMMATRIX matView;
	//射影変換
	XMMATRIX matProjection;

	XMMATRIX matViewProjection;

	Vec3 eye = {}, target = {}, up = {};

	//カメラ追従
	bool followDirty = false;
	float followX = 0.0f;
	float followY = 0.0f;
	Vec3 followD = {};
	Vec3 followF3 = {};
public:
	Camera();

	~Camera();

	/// <summary>
	/// カメラ生成
	/// </summary>
	/// <returns></returns>
	static Camera *Create();

	//カメラ初期化/カメラ位置eye/カメラターゲットtarget /カメラの向きup
	void Initilize(const Vec3 &eye, const Vec3 &target, const Vec3 &up);
	//カメラ位置セット/カメラ位置eye/カメラターゲットtarget /カメラの向きup
	void SetCamera(const Vec3 &eye, const Vec3 &target, const Vec3 &up);

	/// <summary>
	/// カメラが追従する
	/// </summary>
	/// <param name="position">追従するオブジェクトの座標</param>
	/// <param name="d">オブジェクトとカメラの距離</param>
	/// <param name="angleX">カメラの向きX</param>
	/// <param name="angleY">カメラの向きY</param>
	/// <returns></returns>
	void FollowCamera(const Vec3 &position, const Vec3 &d, float angleX = 0, float angleY = 0);

	//matViewを獲得
	XMMATRIX GetMatView();
	//projectionを獲得
	XMMATRIX GetProjection();

	XMMATRIX GetMatViewProjection();

	Vec3 GetEye();

	Vec3 GetTarget();

	Vec3 GetUp();
};