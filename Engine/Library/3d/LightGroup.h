﻿#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CircleShadow.h"
extern const int window_width;
extern const int window_height;
/// <summary>
/// ライト
/// </summary>
class LightGroup
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: // 定数
	// 平行光源の数
	static const int DirLightNum = 1;
	// 点光源の数
	static const int PointLightNum = 1;
	// スポットライトの数
	static const int SpotLightNum = 1;
	// 丸影の数
	static const int CircleShadowNum = 1;

public: // サブクラス

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		// 環境光の色
		Vec3 ambientColor;
		float pad1;
		// 平行光源用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		// 点光源用
		PointLight::ConstBufferData pointLights[PointLightNum];
		// スポットライト用
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		// 丸影用
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static LightGroup* Create();

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// 標準のライト設定
	/// </summary>
	void DefaultLightSetting();

	/// <summary>
	/// 環境光のライト色をセット
	/// </summary>
	/// <param name="color">ライト色</param>
	void SetAmbientColor(const Vec3& color);

	/// <summary>
	/// 平行光源の有効フラグをセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="active">有効フラグ</param>
	void SetDirLightActive(int index, bool active);

	/// <summary>
	/// 平行光源のライト方向をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightdir">ライト方向</param>
	void SetDirLightDir(int index, const XMVECTOR& lightdir);

	/// <summary>
	/// 平行光源のライト色をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightcolor">ライト色</param>
	void SetDirLightColor(int index, const Vec3& lightcolor);

	/// <summary>
	/// 点光源の有効フラグをセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="active">有効フラグ</param>
	void SetPointLightActive(int index, bool active);

	/// <summary>
	/// 点光源のライト座標をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightpos">ライト座標</param>
	void SetPointLightPos(int index, const Vec3& lightpos);

	/// <summary>
	/// 点光源のライト色をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightcolor">ライト色</param>
	void SetPointLightColor(int index, const Vec3& lightcolor);

	/// <summary>
	/// 点光源のライト距離減衰係数をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightatten">ライト距離減衰係数</param>
	void SetPointLightAtten(int index, const Vec3& lightAtten);

	/// <summary>
	/// スポットライトの有効フラグをセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="active">有効フラグ</param>
	void SetSpotLightActive(int index, bool active);

	/// <summary>
	/// スポットライトのライト方向をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightdir">ライト方向</param>
	void SetSpotLightDir(int index, const XMVECTOR& lightdir);

	/// <summary>
	/// スポットライトのライト座標をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightpos">ライト座標</param>
	void SetSpotLightPos(int index, const Vec3& lightpos);

	/// <summary>
	/// スポットライトのライト色をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightcolor">ライト色</param>
	void SetSpotLightColor(int index, const Vec3& lightcolor);

	/// <summary>
	/// スポットライトのライト距離減衰係数をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightatten">ライト距離減衰係数</param>
	void SetSpotLightAtten(int index, const Vec3& lightAtten);

	/// <summary>
	/// スポットライトのライト減衰角度をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightFactorAngle">x:減衰開始角度 y:減衰終了角度</param>
	void SetSpotLightFactorAngle(int index, const Vec2& lightFactorAngle);

	/// <summary>
	/// 丸影の有効フラグをセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="active">有効フラグ</param>
	void SetCircleShadowActive(int index, bool active);

	/// <summary>
	/// 丸影のキャスター座標をセット
	/// </summary>
	/// <param name="index">番号</param>
	/// <param name="lightpos">キャスター座標</param>
	void SetCircleShadowCasterPos(int index, const Vec3& casterPos);

	/// <summary>
	/// 丸影の方向をセット
	/// </summary>
	/// <param name="index">番号</param>
	/// <param name="lightdir">方向</param>
	void SetCircleShadowDir(int index, const XMVECTOR& lightdir);

	/// <summary>
	/// 丸影のキャスターとライトの距離をセット
	/// </summary>
	/// <param name="index">番号</param>
	/// <param name="distanceCasterLight">キャスターとライトの距離</param>
	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight);

	/// <summary>
	/// 丸影の距離減衰係数をセット
	/// </summary>
	/// <param name="index">番号</param>
	/// <param name="lightatten">距離減衰係数</param>
	void SetCircleShadowAtten(int index, const Vec3& lightAtten);

	/// <summary>
	/// 丸影の減衰角度をセット
	/// </summary>
	/// <param name="index">番号</param>
	/// <param name="lightFactorAngle">x:減衰開始角度 y:減衰終了角度</param>
	void SetCircleShadowFactorAngle(int index, const Vec2& lightFactorAngle);
	/// <summary>
	/// 影の方向
	/// </summary>
	/// <param name="shadowDir"></param>
	void SetShadowDir(const Vec3 shadowDir);


	XMMATRIX GetLightMatProjection() { return lightMatViewProjection; }

private: // メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;

	// 環境光の色
	Vec3 ambientColor = { 1,1,1 };

	// 平行光源の配列
	DirectionalLight dirLights[DirLightNum];

	// 点光源の配列
	PointLight pointLights[PointLightNum];

	// スポットライトの配列
	SpotLight spotLights[SpotLightNum];

	// 丸影の配列
	CircleShadow circleShadows[CircleShadowNum];

	// ダーティフラグ
	bool dirty = false;

	//ビュー変換行列
	XMMATRIX matView;
	//射影変換
	XMMATRIX matProjection;

	XMMATRIX lightMatViewProjection;

	Vec3 shadowDir = { 1,1,0 };
};

