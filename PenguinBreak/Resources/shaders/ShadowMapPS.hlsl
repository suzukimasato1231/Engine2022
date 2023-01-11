#include "ShadowMap.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float> shadow : register(t1);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
	return float4(1,1,1, 1);
}