#pragma once
#include<vector>
#include<string>
#include<d3dx12.h>
#include"Pipeline.h"
#include"Camera.h"
#include<unordered_map>
#include"LightGroup.h"
#include"Vec.h"
#include"Singleton.h"
#include"Texture.h"
#pragma comment(lib,"d3d12.lib")

////頂点データ構造体
struct Vertex
{
	Vec3 pos;//xyz座標
	Vec3 normal;//法線ベクトル
	Vec2 uv;//uv座標
};

//マテリアル
struct Material
{
	std::string name;			//マテリアル名
	Vec3 ambient;			//アンビエント影響度
	Vec3 diffuse;			//ディフューズ影響度
	Vec3 specular;			//スペキュラー影響度
	float alpha;				//アルファ
	std::string textureFilename;//テクスチャファイル名
	//コンストラクタ
	Material()
	{
		ambient = { 1.0f,1.0f,1.0f };
		diffuse = { 0.0f,0.0f,0.0f };
		specular = { 0.0f,0.0f,0.0f };
		alpha = 1.0f;
	}
};
/// <summary>
/// 位置、大きさ、色情報
/// </summary>
struct PSC
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec4 color = {};
};

//オブジェクトデータ構造体
struct ObjectData
{
	//頂点データ
	std::vector<Vertex*> vertices;
	//インデックスデータ
	std::vector<unsigned short*> indices;
	//頂点バッファの生成
	ComPtr<ID3D12Resource> vertBuff = nullptr;
	//インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff = nullptr;
	//頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//オブジェ読み込み用
	int OBJTexture = 0;
	//頂点法線スムージング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>>smoothData;
	//ワールド変換
	XMMATRIX matWorld;
	//親クラス
	ObjectData* parent = nullptr;
	//マテリアル
	Material material;
	//位置、大きさ、色情報
	PSC psc;
};

class Object :public Singleton<Object>
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	friend Singleton<Object>;
public:
	static ID3D12Device* dev;					//デバイス
	static ID3D12GraphicsCommandList* cmdList;	//コマンドリスト
public://構造体

	struct ConstBuffer
	{
		//GPUリソースの生成
		ComPtr<ID3D12Resource>constBuff = nullptr;
	};

	//OBJデータ関連
	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;//ビュープロジェクション行列
		XMMATRIX world;//ワールド座標
		Vec3 cameraPos;//カメラ座標(ワールド座標)
		Vec4 color;
		XMMATRIX lightproj;//ビュープロジェクション行列
	};
	struct ConstBufferDataB1
	{
		Vec3 ambient;	//アンビエント係数
		float pad1;			//パディング
		Vec3 diffuse;	//ディフューズ係数
		float pad2;			//パディング
		Vec3 specular;	//スペキュラー係数
		float alpha;		//アルファ
	};

	//OBJ定数バッファ
	struct OBJBuffer
	{
		ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
		ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ
	};
public://パイプライン設定
	static Pipeline::PipelineSet objPipelineSet;		//OBJ読み込み
public://変数	
	//OBJデータ
	static std::vector<OBJBuffer*> OBJbuffer;
public:
	Object() {};
	~Object();
	//初期化
	static void Init(ID3D12Device* dev, ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object* Create();

	static void SetLight(LightGroup* light) { Object::lightGroup = light; }

	static void SetPipeline(Pipeline::PipelineSet piepline) { Object::objPipelineSet = piepline; }
public:
	//ライトクラス
	static LightGroup* lightGroup;
public://オブジェクト関連
	//オブジェクト描画前
	static void PreDraw();
	//定数バッファ設定
	static void OBJConstantBuffer();
	/// <summary>
	/// オブジェクトのデータ更新
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="matRot">回転</param>
	/// <param name="color">色</param>
	static void MatWord(ObjectData& polygon, Vec3 position, Vec3 scale, Vec3 matRot, Vec4 color);
	/// <summary>
	/// OBJ描画
	/// </summary>
	/// <param name="polygon">オブジェクトデータ</param>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="matRot">回転</param>
	/// <param name="color">色</param>
	static	void Draw(ObjectData& polygon, Vec3 position, Vec3 scale, Vec3 matRot, Vec4 color = { 1,1,1,1 }, int graph = 0, bool shadowFlag = false);
public:
	static size_t OBJNum;//OBJ読み込みの数
	static size_t objNum;//オブジェクトの数
};