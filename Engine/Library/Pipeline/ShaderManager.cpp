#include "ShaderManager.h"

ComPtr<ID3DBlob> LoadShader(LPCWSTR VshaderName, LPCSTR Vtarget)
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> Blob;
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	if (VshaderName != L"")
	{
		// 頂点シェーダの読み込みとコンパイル
		result = D3DCompileFromFile(VshaderName,
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", Vtarget, D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0, &Blob, &errorBlob);
		if (FAILED(result)) {
			std::string errstr;
			errstr.resize(errorBlob->GetBufferSize());

			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				errstr.begin());
			errstr += "\n";
			OutputDebugStringA(errstr.c_str());
			exit(1);
		}
	}
	return Blob;
}


Shader ShaderManager::spriteShader;
Shader ShaderManager::objShader;
Shader ShaderManager::toonObjShader;
Shader ShaderManager::particleShader;
Shader ShaderManager::postNormalShader;
Shader ShaderManager::postTestShader;

void ShaderManager::LoadShaders()
{	
	spriteShader.vsBlob = LoadShader(L"Resources/shaders/SpriteVS.hlsl", "vs_5_0");
	spriteShader.psBlob = LoadShader(L"Resources/shaders/SpritePS.hlsl", "ps_5_0");

	objShader.vsBlob = LoadShader(L"Resources/shaders/OBJVertexShader.hlsl", "vs_5_0");
	objShader.psBlob = LoadShader(L"Resources/shaders/OBJPixelShader.hlsl", "ps_5_0");

	toonObjShader.vsBlob = LoadShader(L"Resources/shaders/OBJToonVS.hlsl", "vs_5_0");
	toonObjShader.psBlob = LoadShader(L"Resources/shaders/OBJToonPS.hlsl", "ps_5_0");

	particleShader.vsBlob = LoadShader(L"Resources/shaders/ParticleVS.hlsl", "vs_5_0");
	particleShader.psBlob = LoadShader(L"Resources/shaders/ParticlePS.hlsl", "ps_5_0");
	particleShader.gsBlob = LoadShader(L"Resources/shaders/ParticleGS.hlsl", "gs_5_0");

	postNormalShader.vsBlob = LoadShader(L"Resources/shaders/PostEffect/PostEffectNormalVS.hlsl", "vs_5_0");
	postNormalShader.psBlob = LoadShader(L"Resources/shaders/PostEffect/PostEffectNormalPS.hlsl", "ps_5_0");

	postTestShader.vsBlob = LoadShader(L"Resources/shaders/PostEffect/PostEffectTestVS.hlsl", "vs_5_0");
	postTestShader.psBlob = LoadShader(L"Resources/shaders/PostEffect/PostEffectTestPS.hlsl", "ps_5_0");
}
