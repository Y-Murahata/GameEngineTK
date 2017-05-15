//	�J�����N���X
#pragma once
#include <SimpleMath.h>

class Camera
{
public:
	Camera(float width, float hight);
	~Camera();

	virtual void Update();

	//	�r���[�s��̃Q�b�^�[
	const DirectX::SimpleMath::Matrix& GetViewMatrix();
	//	�v���W�F�N�V�����s��̃Q�b�^�[
	const DirectX::SimpleMath::Matrix& GetProjMatrix();
	//	EyePos�̃Q�b�^�[
	const DirectX::SimpleMath::Vector3& GetEyePos();
	//	RefPos�̃Q�b�^�[
	const DirectX::SimpleMath::Vector3& GetRefPos();

	//	�e��ϐ��擾�֐�
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);
	void SetFovY(float fovY);
	void SetAspect(float aspect);
	void SetNearClip(float nearClip);
	void SetFarClip(float farClip);

protected:
	//	�r���[�s��
	DirectX::SimpleMath::Matrix m_viemat;
	//	���_
	DirectX::SimpleMath::Vector3 m_eyepos;
	//	�Q��
	DirectX::SimpleMath::Vector3 m_refpos;
	//	������x�N�g��
	DirectX::SimpleMath::Vector3 m_upvec;


	//	�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projmat;
	//	���������x�N�g��
	float m_fovY;
	//	�A�X�y�N�g��
	float m_aspect;
	//	�j�A�N���b�v
	float m_nearClip;
	//	�t�@�[�N���b�v
	float m_farClip;
};

