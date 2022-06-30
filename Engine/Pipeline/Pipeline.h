#pragma once
#include<d3dcompiler.h>
#include<DirectXTex.h>
#include<d3dx12.h>
#include<wrl.h>
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class Pipeline
{
public:
	//構造体
	struct PipelineSet
	{
		//パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState>pipelinestate;
		//ルートシグネチャ
		ComPtr <ID3D12RootSignature>rootsignature;
	};
	//スプライト
	static PipelineSet  SpriteCreateGraphicsPipeline(ID3D12Device *dev);
	//OBJ読み込み
	static PipelineSet  OBJCreateGraphicsPipeline(ID3D12Device *dev);
	//パーティクル

	//四角形
	static PipelineSet ParticleCreateGraphicsPipeline(ID3D12Device *dev);

	//ポストエフェクト

	//ぼかし
	static PipelineSet PostTestCreateGraphicsPipeline(ID3D12Device* dev);
	//通常
	static PipelineSet PostNormalCreateGraphicsPipeline(ID3D12Device* dev);
};