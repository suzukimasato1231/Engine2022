#include "ShadowMap.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float> shadow : register(t1);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
	//ライトから見た深度バッファの作成用
	float depth = (input.svpos.z / input.svpos.w + 1.0f) * 0.5;
	// テクスチャマッピング
	//float4 texcolor = shadow.Sample(smp, input.uv);
	return float4(depth,depth,depth, 1);
}