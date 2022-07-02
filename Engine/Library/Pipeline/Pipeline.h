#pragma once
#include<d3dcompiler.h>
#include<DirectXTex.h>
#include<d3dx12.h>
#include<wrl.h>
#include"ShaderManager.h"
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class Pipeline :public ShaderManager
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
	static PipelineSet  SpriteCreateGraphicsPipeline(ID3D12Device* dev,Shader shader);
	//OBJ読み込み
	static PipelineSet  OBJCreateGraphicsPipeline(ID3D12Device* dev, Shader shader);

	//パーティクル
	//四角形
	static PipelineSet ParticleCreateGraphicsPipeline(ID3D12Device* dev, Shader shader);

	//ポストエフェクト
	//通常
	static PipelineSet PostNormalCreateGraphicsPipeline(ID3D12Device* dev, Shader shader);
};