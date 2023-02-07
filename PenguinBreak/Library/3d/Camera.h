#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include"Vec.h"
#include"Singleton.h"
extern const int window_width;
extern const int window_height;
/// <summary>
/// �J�����N���X
/// </summary>
class Camera :public Singleton<Camera>
{
	using XMMATRIX = DirectX::XMMATRIX;
private:
	friend Singleton<Camera>;
	//�r���[�ϊ��s��
	XMMATRIX matView;
	//�ˉe�ϊ�
	XMMATRIX matProjection;

	XMMATRIX matViewProjection;

	Vec3 eye = {}, target = {}, up = {};

	//�J�����Ǐ]
	bool followDirty = false;
	float followX = 0.0f;
	float followY = 0.0f;
	Vec3 followD = {};
	Vec3 followF3 = {};
public:
	Camera();

	~Camera();

	/// <summary>
	/// �J��������
	/// </summary>
	/// <returns></returns>
	static Camera *Create();

	//�J����������/�J�����ʒueye/�J�����^�[�Q�b�gtarget /�J�����̌���up
	void Initilize(const Vec3 &eye, const Vec3 &target, const Vec3 &up);
	//�J�����ʒu�Z�b�g/�J�����ʒueye/�J�����^�[�Q�b�gtarget /�J�����̌���up
	void SetCamera(const Vec3 &eye, const Vec3 &target, const Vec3 &up);

	/// <summary>
	/// �J�������Ǐ]����
	/// </summary>
	/// <param name="position">�Ǐ]����I�u�W�F�N�g�̍��W</param>
	/// <param name="d">�I�u�W�F�N�g�ƃJ�����̋���</param>
	/// <param name="angleX">�J�����̌���X</param>
	/// <param name="angleY">�J�����̌���Y</param>
	/// <returns></returns>
	void FollowCamera(const Vec3 &position, const Vec3 &d, float angleX = 0, float angleY = 0);

	//matView���l��
	XMMATRIX GetMatView();
	//projection���l��
	XMMATRIX GetProjection();

	XMMATRIX GetMatViewProjection();

	Vec3 GetEye();

	Vec3 GetTarget();

	Vec3 GetUp();
};