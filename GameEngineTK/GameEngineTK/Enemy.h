//----------------------------------------
// �G�𐧌䂷��N���X
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
class Enemy
{
	// ���@�p�[�c
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_HEAD,
		ENEMY_PARTS_BODY,
		ENEMY_PARTS_SHOULDER_R,
		ENEMY_PARTS_SHOULDER_L,
		ENEMY_PARTS_ARM_R,
		ENEMY_PARTS_ARM_L,
		ENEMY_PARTS_HAND_R,
		ENEMY_PARTS_HAND_L,
		ENEMY_PARTS_WEPON1,
		ENEMY_PARTS_WEPON2,
		ENEMY_PARTS_HIP,
		ENEMY_PARTS_THIGH_R,
		ENEMY_PARTS_THIGH_L,
		ENEMY_PARTS_SHIN_R,
		ENEMY_PARTS_SHIN_L,
		ENEMY_PARTS_LEG_R,
		ENEMY_PARTS_LEG_L,

		ENEMY_PARTS_NUM
	};
	//	�e��t���O
	bool CannonFlag = false;
	bool CannonDoingFlag = false;
	bool HandFlag = false;

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
	Enemy();
	// �f�X�g���N�^
	~Enemy();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �p�x���擾
	DirectX::SimpleMath::Vector3 GetAngle() { return m_obj[ENEMY_PARTS_BODY].GetRotation(); };
	// ���W���擾
	inline  DirectX::SimpleMath::Vector3 GetPosition()  { return m_obj[ENEMY_PARTS_BODY].GetTranslation(); };
	// ���[���h�s����擾
	 DirectX::SimpleMath::Matrix GetWorldMat() { return m_obj[ENEMY_PARTS_BODY].GetWorld(); };
	// ���W��ݒ�
	 void SetPosition(DirectX::SimpleMath::Vector3& trans) { m_obj[ENEMY_PARTS_BODY].SetTranslation(trans); };

	 //	�^�C�}�[
	 int m_Timer;
	 //	�ڕW�̊p�x
	 float m_DistAngle;
};