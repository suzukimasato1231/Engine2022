#include "Object.h"
#include <DirectXTex.h>
#include<string>
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

ID3D12Device* Object::dev = nullptr;
ID3D12GraphicsCommandList* Object::cmdList = nullptr;
LightGroup* Object::lightGroup = nullptr;
Pipeline::PipelineSet Object::objPipelineSet;		//OBJ読み込み
size_t Object::objNum = 0;
size_t Object::OBJNum = 0;


std::vector<Object::OBJBuffer*> Object::OBJbuffer;
Object::~Object()
{
	//OBJデータ削除
	for (int i = (int)OBJbuffer.size() - 1; i >= 0; i--)
	{
		delete OBJbuffer[i];
		OBJbuffer.erase(OBJbuffer.begin() + i);
	}
}

void  Object::Init(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList)
{
	Object::dev = dev;

	Object::cmdList = cmdList;

	//パイプライン生成
	objPipelineSet = Pipeline::OBJCreateGraphicsPipeline(Object::dev, ShaderManager::objShader);
}

Object* Object::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Object* object = new Object();
	if (object == nullptr) {
		return nullptr;
	}

	// 初期化
	return object;
}



void Object::MatWord(ObjectData& polygon, Vec3 position, Vec3 scale, Vec3 rotation, Vec4 color)
{
	HRESULT result;
	if (polygon.psc.position.x != position.x || polygon.psc.position.y != position.y || polygon.psc.position.z != position.z
		|| polygon.psc.scale.x != scale.x || polygon.psc.scale.y != scale.y || polygon.psc.scale.z != scale.z
		|| polygon.psc.color.x != color.x || polygon.psc.color.y != color.y || polygon.psc.color.z != color.z || polygon.psc.color.w != color.w)
	{
		//ワールド変換：//スケーリング//回転行列XMMATRIX//平行移動行列
		XMMATRIX matScale, matRot, matTrains;
		//ワールド変換
		matScale = XMMatrixScaling(scale.x, scale.y, scale.z);//大きさ
		matTrains = XMMatrixTranslation(position.x, position.y, position.z);//平行移動行列を再計算
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));//Z軸まわりに４５度回転
		matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));//X軸まわりに４５度回転
		matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));//Y軸まわりに４５度回転

		polygon.matWorld = XMMatrixIdentity();//ワールド行列は毎フレームリセット
		polygon.matWorld *= matScale;//ワールド行列にスケーリングを反映
		polygon.matWorld *= matRot;//ワールド行列に回転を反映
		polygon.matWorld *= matTrains;//ワールド行列に変更移動を反映

		polygon.psc.position = position;
		polygon.psc.scale = scale;
		polygon.psc.color = color;
	}


	const XMMATRIX& matViewProjection = Camera::Get()->GetMatView() * Camera::Get()->GetProjection();
	const Vec3& cameraPos = Camera::Get()->GetEye();
	//GPU上のバッファに対応した仮想メモリを取得
	ConstBufferDataB0* constMap = nullptr;
	result = Object::OBJbuffer[OBJNum]->constBuffB0->Map(0, nullptr, (void**)&constMap);
	//行列の合成   ワールド変換行列 ＊ ビュー変換行列 ＊ 射影変換行列
	constMap->viewproj = matViewProjection;
	if (polygon.parent == nullptr)
	{
		constMap->world = polygon.matWorld;
	}
	else
	{
		constMap->world = polygon.matWorld * polygon.parent->matWorld;
	}
	constMap->cameraPos = cameraPos;
	constMap->color = color;
	constMap->lightproj = lightGroup->GetLightMatProjection();
	Object::OBJbuffer[OBJNum]->constBuffB0->Unmap(0, nullptr);


	//定数バッファへデータ転送
	ConstBufferDataB1* constMap1 = nullptr;
	result = Object::OBJbuffer[OBJNum]->constBuffB1->Map(0, nullptr, (void**)&constMap1);
	constMap1->ambient = polygon.material.ambient;
	constMap1->diffuse = polygon.material.diffuse;
	constMap1->specular = polygon.material.specular;
	constMap1->alpha = polygon.material.alpha;
	Object::OBJbuffer[OBJNum]->constBuffB1->Unmap(0, nullptr);
}

void Object::PreDraw()
{
	objNum = 0;
	OBJNum = 0;
}

void Object::OBJConstantBuffer()
{
	HRESULT result;
	Object::OBJbuffer.push_back(new Object::OBJBuffer);
	// 定数バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::OBJbuffer[Object::OBJbuffer.size() - 1]->constBuffB0));

	// 定数バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::OBJbuffer[Object::OBJbuffer.size() - 1]->constBuffB1));
}


void Object::Draw(ObjectData& polygon, Vec3 position, Vec3 scale, Vec3 rotation, Vec4 color, int graph, bool shadowFlag)
{
	//プリミティブ形状の設定コマンド（三角形リスト）
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//デスクリプタヒープをセット
	ID3D12DescriptorHeap* ppHeaps[] = { Texture::Get()->GetDescHeap() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	if (OBJNum >= Object::OBJbuffer.size())
	{
		//定数バッファ
		OBJConstantBuffer();
	}
	//更新
	MatWord(polygon, position, scale, rotation, color);
	if (objPipelineSet.pipelinestate == nullptr || objPipelineSet.rootsignature == nullptr)
	{
		assert(0);
	}
	cmdList->SetPipelineState(objPipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(objPipelineSet.rootsignature.Get());

	//頂点バッファの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &polygon.vbView);

	////インデックスバッファビューのセットコマンド
	cmdList->IASetIndexBuffer(&polygon.ibView);

	//ヒープの先頭にあるCBVをルートパラメータ０番に設定
	cmdList->SetGraphicsRootConstantBufferView(0, Object::OBJbuffer[OBJNum]->constBuffB0->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, Object::OBJbuffer[OBJNum]->constBuffB1->GetGPUVirtualAddress());
	if (graph > 0)
	{
		//ヒープの２番目にあるSRVをルートパラメータ１番に設定
		cmdList->SetGraphicsRootDescriptorTable(2, Texture::Get()->GetGPUSRV(graph));
	}
	else if (polygon.OBJTexture == 0)
	{
		//ヒープの２番目にあるSRVをルートパラメータ１番に設定
		cmdList->SetGraphicsRootDescriptorTable(2, Texture::Get()->GetGPUSRV(graph));
	}
	else
	{
		//ヒープの２番目にあるSRVをルートパラメータ１番に設定
		cmdList->SetGraphicsRootDescriptorTable(2, Texture::Get()->GetGPUSRV(polygon.OBJTexture));
	}
	//ライトの描画
	lightGroup->Draw(cmdList, 3);
	//影を描画するか
	if (shadowFlag == true)
	{//シャドウマップを設定
		cmdList->SetGraphicsRootDescriptorTable(4, Texture::Get()->GetGPUSRV(Texture::Get()->GetShadowTexture()));
	}

	//描画コマンド          //頂点数				//インスタンス数	//開始頂点番号		//インスタンスごとの加算番号
	cmdList->DrawIndexedInstanced((UINT)polygon.indices.size(), 1, 0, 0, 0);
	OBJNum++;
}
