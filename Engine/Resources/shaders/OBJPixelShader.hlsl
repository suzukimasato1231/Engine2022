#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp0 : register(s0);      // 0番スロットに設定されたサンプラー
Texture2D<float4> shadow : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp0, input.uv);

	// 光沢度
	const float shininess = 4.0f;
	// 頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	// 環境反射光
	float3 ambient = m_ambient;

	// シェーディングによる色
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);

	////平行光源
 //  for (int i = 0; i < DIRLIGHT_NUM; i++) {
	//   if (dirLights[i].active) {
	//	   // ライトに向かうベクトルと法線の内積
	//	   float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
	//	   // 反射光ベクトル
	//	   float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
	//	   // 拡散反射光
	//	   float3 diffuse = dotlightnormal * m_diffuse;
	//	   // 鏡面反射光
	//	   float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//	   // 全て加算する
	//	   shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
	//   }
 //  }

   float w = 1.0f / input.posInLVP.z;
	float2 shadowmap = float2(0,0);
	//ライトからみたシーンの位置
	shadowmap.x = (1.0f + input.posInLVP.x * w) * 0.5f;
	shadowmap.y = (1.0f - input.posInLVP.y * w) * 0.5f;

	/*float2 shadowmap = input.posInLVP.xy / input.posInLVP.w;
	shadowmap *= float2(0.5f, -0.5f);
	shadowmap += 0.5f;*/

   float z = (shadow.Sample(smp0,shadowmap)).z;

   //深度を比較
   if (z < input.posInLVP.z - 0.005)
   {
	   shadecolor.rgb = shadecolor.rgb * 0.5f;//暗くする
   }

   // シェーディングによる色で描画
	return shadecolor * texcolor;

}


