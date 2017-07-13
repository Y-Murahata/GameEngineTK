//----------------------------------------
// �v���C���[�𐧌䂷��N���X
//----------------------------------------
#pragma once
// -- �w�b�_�t�@�C���̓ǂݍ��� -----------
#include "Singleton.h"
#include "DXTKResouces.h"
#include "Obj3D.h"
#include "CollisionNode.h"
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
	///
	///	�萔
	///
	//	�d�͉����x<m/frame^2>
	const float GRAVITY_ACC = 0.03f;
	//	�W�����v����<m/frame>
	const float JUMP_SPEED_FIRST = 0.5f;
	//	�������x����<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;

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
	//	�f�o�b�O�`��
	void DebugDraw();
	// �p�x���擾
	DirectX::SimpleMath::Vector3 GetAngle() { return m_obj[PLAYER_PARTS_BODY].GetRotation(); };
	// ���W���擾
	inline  DirectX::SimpleMath::Vector3 GetPosition()  { return m_obj[PLAYER_PARTS_BODY].GetTranslation(); };
	// ���[���h�s����擾
	 DirectX::SimpleMath::Matrix GetWorldMat() { return m_obj[PLAYER_PARTS_BODY].GetWorld(); };
	 // �����蔻��̃X�t�B�A���擾
	 const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; };
	 const DirectX::SimpleMath::Vector3& GetVelosity() { return m_Velocity; }
	// ���W��ݒ�
	 void SetPosition(DirectX::SimpleMath::Vector3& trans) { m_obj[PLAYER_PARTS_BODY].SetTranslation(trans); };
	 //	�����蔻��X�t�B�A���擾����
	 const SphereNode& GetCollisionNodeBody() { return m_CollisionSphereBody; };
	 //	�e�ۂ𔭎�
	 void FireBullet();
	 //	�e�ۂ��đ��U
	 void ResetBullet();
	 //	�s��X�V
	 void Calc();

	 void StartJump();

	 void StartFall();

	 void StopJump();

	 //	�L�[�{�[�h�g���b�J�[
	 DirectX::Keyboard::KeyboardStateTracker keyTrackerState;

	 //	���˃t���O
	 bool m_FireFlag;

	 //	�e�ۗp�̓����蔻��
	 SphereNode m_CollisionNodeBullet;

	 //	�����蔻��p�X�t�B�A
	 SphereNode m_CollisionSphereBody;

	 //	���x
	 DirectX::SimpleMath::Vector3 m_Velocity;
	 
	 //	�W�����v��(������)�t���O
	 bool m_isJump;
};