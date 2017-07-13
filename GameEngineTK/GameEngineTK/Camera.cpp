#include "pch.h"
#include "Camera.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�R���X�g���N�^
Camera::Camera(float width,float hight)
{
	//	�r���[�s��̐���
	m_eyepos = Vector3(0, 0.1f, 7.0f);	//	���_
	m_refpos = Vector3(0, 0, 0);	//	�Q�Ɠ_
	m_upvec = Vector3(0, 1.0f, 0);	//	������x�N�g��
	m_viemat = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	�ˉe�s��̐���
	m_fovY = XMConvertToRadians(60.0f);	//	����p
	m_aspect = (float)width / hight;	//	�A�X��
	m_nearClip = 0.1f;					//	�j�A�N���b�v
	m_farClip = 1000.0f;				//	�t�@�[�N���b�v
	m_projmat = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}


Camera::~Camera()
{
}

void Camera::Update()
{
	//	�r���[�s��̍쐬
	m_viemat = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//�ˉe�s��̍쐬
	m_projmat = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

//	�r���[�s����擾
const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{
	return m_viemat;
}
//	�ˉe�s����擾
const DirectX::SimpleMath::Matrix& Camera::GetProjMatrix()
{
	return m_projmat;
}

//	EyePos�̃Q�b�^�[
const DirectX::SimpleMath::Vector3 & Camera::GetEyePos()
{
	return m_eyepos;
}

//	RefPos�̃Q�b�^�[
const DirectX::SimpleMath::Vector3 & Camera::GetRefPos()
{
	return m_refpos;
}


//	���_���Z�b�g
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}
//	�Q�Ɠ_���Z�b�g
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}
//	������x�N�g�����Z�b�g
void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}
//	������������p���Z�b�g
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}
//	�A�X�y�N�g����Z�b�g
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}
//	�j�A�N���b�v���Z�b�g
void Camera::SetNearClip(float nearClip)
{
	m_nearClip = nearClip;
}
//	�t�@�[�N���b�v���Z�b�g
void Camera::SetFarClip(float farClip)
{
	m_farClip = farClip;
}
