#include "ShadowMap.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float> shadow : register(t1);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
	return float4(1,1,1, 1);
}