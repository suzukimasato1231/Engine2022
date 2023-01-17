#pragma once
#include "Model.h"
#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<DirectXMath.h>
#include<string>
#include"FbxLoader.h"
#include"LightGroup.h"
/// <summary>
/// FBXオブジェクトクラス
/// </summary>
class FBXObject3d
{
protected://エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public://静的メンバ関数
	static void SetDevice(ID3D12Device *device) { FBXObject3d::device = device; }
	static void SetLight(LightGroup* lightGroup) { FBXObject3d::lightGroup = lightGroup; }
	static void SetCmdList(ID3D12GraphicsCommandList *cmdList) { FBXObject3d::cmdList = cmdList; }
private://静的メンバ変数
	//デバイス
	static ID3D12Device *device;
	//ライトクラス
	static LightGroup* lightGroup;

	static ID3D12GraphicsCommandList *cmdList;
public://定数
	//ボーンの最大数
	static const int MAX_BONES = 32;
public://サブクラス

		//定数バッファ用データ構造体(座標変換行列用)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//ビュープロジェクション行列
		XMMATRIX world;		//ワールド行列
		Vec3 cameraPos;	//カメラ座標(ワールド座標)
	};



	//定数バッファ用データ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update(bool shadowFlag);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model"></param>
	void SetModel(Model *model) { this->model = model; }

	/// <summary>
	/// アニメーション開始
	/// </summary>
	/// <param name="Loop">ループ再生させるかどうか</param>
	void PlayAnimation(bool Loop);
	/// <summary>
	/// アニメーションの停止
	/// </summary>
	void StopAnimation();

	void SetPosition(Vec3 pos) { FBXObject3d::position = pos; }
	void SetScale(Vec3 scale) { FBXObject3d::scale = scale; }
	void SetRotation(Vec3 rotation) { FBXObject3d::rotation = rotation; }
protected://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuffTransform;
	//定数バッファ
	ComPtr<ID3D12Resource>constBufferSkin;

	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature>rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState>pipelinestate;

	//ローカルスケール
	Vec3 scale = { 0.025f,0.025f,0.025f };//ペンギン
	//X,Y,Z軸回りのローカル回転角
	Vec3 rotation = { 0.0f,180.0f,0.0f };
	//ローカル座標
	Vec3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	Model *model = nullptr;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;
	//アニメーションをループさせるかどうか
	bool isLoop = false;
};
