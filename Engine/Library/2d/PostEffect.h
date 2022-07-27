#pragma once
#include "Sprite.h"
#include"Singleton.h"
#include"Sprite.h"
#include"Texture.h"
class PostEffect : public Singleton<PostEffect>
{
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	friend Singleton<PostEffect>;
public:

	//画面クリアカラー
	static const float clearColor[4];
	static ID3D12Device* dev;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ID3D12Device* dev);

	//パイプライン生成
	void CreatePipeline(ID3D12Device* dev);

	/// <summary>
	/// 描画コマンドの発行
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	void UpdatePost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY);

	void DrawPost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY);
	//パイプライン切り替え
	void SetPipeline(int num);

private:
	
	//テクスチャバッファ
	ComPtr<ID3D12Resource>texbuff;
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//深度バッファ
	ComPtr<ID3D12Resource>depthBuff;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap>descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap>descHeapDSV;

	//GPUリソースの生成1
	ComPtr<ID3D12Resource> constBuff;

	SpriteData sprite;

	//パイプラインセット
	Pipeline::PipelineSet pipelineSet;
};

