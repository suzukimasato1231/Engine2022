#include "ShadowMap.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float> shadow : register(t1);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp1 : register(s1);

float4 main(VSOutput input) : SV_TARGET
{
	//���C�g���猩���[�x�o�b�t�@�̍쐬�p
	float depth = (input.svpos.z / input.svpos.w + 1.0f) * 0.5;
	// �e�N�X�`���}�b�s���O
	//float4 texcolor = shadow.Sample(smp, input.uv);
	return float4(depth,depth,depth, 1);
}