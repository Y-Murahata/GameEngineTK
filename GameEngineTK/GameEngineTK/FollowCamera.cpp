#include "pch.h"
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERADISTANCE = 6.0f;


//	�R���X�g���N�^
FollowCamera::FollowCamera(float width, float hight)
	:Camera(width,hight)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
}


FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	//	�J�����̈ʒu���W�����@��肷������ɂ��炷
	refpos = m_targetPos + Vector3(0, 1.0f, 0);
	//	�J��������Q�ƒn�_�܂ł̍����i�O��������悤�ɏ������炷�j
	Vector3 cameraV(0, 0, CAMERADISTANCE);
	//	���@�̌��ɉ�荞�ނ��߂̉�]�s��
	Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	//	�����s�����]
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	eyepos = refpos + cameraV;

	//	�S���R�̃A���S���Y��
	eyepos = GetEyePos() + (eyepos - GetEyePos())*0.1;
	refpos = GetRefPos() + (refpos - GetRefPos())*0.1;

	//	�J�����̎Q�Ɠ_�����@�ɂ���
	SetEyePos(eyepos);
	SetRefPos(refpos);

	//	���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(const float targetAnge)
{
	m_targetAngle = targetAnge;
}
