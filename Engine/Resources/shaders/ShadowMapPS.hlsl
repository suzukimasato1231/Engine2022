#include "ShadowMap.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> shadow : register(t1);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
	//���C�g���猩���[�x�o�b�t�@�̍쐬�p
	return float4(0.5,0.5,0.5,1.0);
}