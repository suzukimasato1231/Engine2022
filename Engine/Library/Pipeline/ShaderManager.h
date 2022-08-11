#pragma once
#include <d3dcompiler.h>
#include <d3dx12.h>

using namespace Microsoft::WRL;
class Shader
{
public:
	ComPtr<ID3DBlob> vsBlob = nullptr; //���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> gsBlob = nullptr; //�W�I���g���V�F�[�_�[
	ComPtr<ID3DBlob> psBlob = nullptr; //�s�N�Z���V�F�[�_�I�u�W�F�N�g
};

ComPtr<ID3DBlob> LoadShader(LPCWSTR VshaderName = L"", LPCSTR Vtarget = "", LPCSTR entryPoint = "main");

class ShaderManager
{
public:
	//2D
	static Shader spriteShader;
	static Shader postNormalShader;
	static Shader postTestShader;
	static Shader ShadowMapShader;
	//3D
	static Shader objShader;
	static Shader toonObjShader;
	static Shader normalMapShader;
	static Shader particleShader;

	static void LoadShaders();
};