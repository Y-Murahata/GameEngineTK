//----------------------------------------
// �v���C���[�𐧌䂷��N���X
//----------------------------------------
#pragma once
// -- �w�b�_�t�@�C���̓ǂݍ��� -----------
#include "Singleton.h"
#include "DXTKResouces.h"
#include "Obj3D.h"
#include "pch.h"
#include <SimpleMath.h>
#include <d3d11_1.h>
#include <Keyboard.h>
#include <vector>

// -- �N���X�̐錾 -----------------------
class Player
{
	// ���@�p�[�c
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_SHOULDER_R,
		PLAYER_PARTS_SHOULDER_L,
		PLAYER_PARTS_ARM_R,
		PLAYER_PARTS_ARM_L,
		PLAYER_PARTS_HAND_R,
		PLAYER_PARTS_HAND_L,
		PLAYER_PARTS_WEPON1,
		PLAYER_PARTS_WEPON2,
		PLAYER_PARTS_HIP,
		PLAYER_PARTS_THIGH_R,
		PLAYER_PARTS_THIGH_L,
		PLAYER_PARTS_SHIN_R,
		PLAYER_PARTS_SHIN_L,
		PLAYER_PARTS_LEG_R,
		PLAYER_PARTS_LEG_L,

		PLAYER_PARTS_NUM
	};
	//	�e��t���O
	bool CannonFlag = false;
	bool CannonDoingFlag = false;
	bool HandFlag = false;

	//	�e�ۂ̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 m_BulletVel[2];

protected:
	// �f�[�^�����o ///////////
	// �p�[�c
	std::vector<Obj3D> m_obj;

	// ���@�̍��W
	DirectX::SimpleMath::Vector3 m_position;
	// ���@�̊p�x
	DirectX::SimpleMath::Vector3 m_angle;
public:
	// �����o�֐� /////////////
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �p�x���擾
	DirectX::SimpleMath::Vector3 GetAngle() { return m_obj[PLAYER_PARTS_BODY].GetRotation(); };
	// ���W���擾
	inline  DirectX::SimpleMath::Vector3 GetPosition()  { return m_obj[PLAYER_PARTS_BODY].GetTranslation(); };
	// ���[���h�s����擾
	 DirectX::SimpleMath::Matrix GetWorldMat() { return m_obj[PLAYER_PARTS_BODY].GetWorld(); };
	// ���W��ݒ�
	 void SetPosition(DirectX::SimpleMath::Vector3& trans) { m_obj[PLAYER_PARTS_BODY].SetTranslation(trans); };

	 //	�e�ۂ𔭎�
	 void FireBullet();
	 //	�e�ۂ��đ��U
	 void ResetBullet();

	 //	�L�[�{�[�h�g���b�J�[
	 DirectX::Keyboard::KeyboardStateTracker keyTrackerState;


	 //	���˃t���O
	 bool m_FireFlag;
};