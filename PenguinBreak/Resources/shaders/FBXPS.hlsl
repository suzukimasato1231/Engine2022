#include "FBX.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

struct PSOutput
{
	float4 target0 :SV_TARGET0;
	float4 target1 :SV_TARGET1;
};

PSOutput main(VSOutput input)
{
	PSOutput output;
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	//// Lambert反射
	//float3 light = normalize(float3(1, -1, 1)); // 右下奥　向きのライト
	//float diffuse = saturate(dot(-light, input.normal));
	//float brightness = diffuse + 0.3f;
	//float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);

	// 光沢度
	const float shininess = 4.0f;
	// 頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.svpos.xyz);

	// 環境反射光
	float3 ambient = 0.5;

	// シェーディングによる色
	float4 shadecolor = float4(ambientColor * 0.5, 1.0);

	//平行光源
	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLights[i].active) {
			// ライトに向かうベクトルと法線の内積
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			// 反射光ベクトル
			float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
			// 拡散反射光
			float3 diffuse = dotlightnormal * 0.3;
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * 0.3;

			// 全て加算する
			shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
		}
	}

	// 陰影とテクスチャの色を合成
	output.target0 = shadecolor * texcolor;
	output.target1 = float4(1 - (shadecolor * texcolor).rgb, 1);

	return output;
}