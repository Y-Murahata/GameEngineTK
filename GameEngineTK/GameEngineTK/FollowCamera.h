//
//	���@�ɒǏ]����J�����N���X
//
#pragma once

#include"Camera.h"

class FollowCamera :public Camera
{
public:
	//	�R���X�g���N�^
	FollowCamera(float width, float hight);
	~FollowCamera();

	//	���t���[���X�V(�J�����N���X�̃A�b�v�f�[�g���㏑��)
	void Update()override;

	//	�J�����Ǝ��@�Ƃ̋���
	static const float CAMERADISTANCE;

	//	�Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);

	//	�Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetAngle(const float targetAnge);

protected:
	//	�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_targetPos;

	//	�Ǐ]�Ώۂ̌X��
	float m_targetAngle;
};

