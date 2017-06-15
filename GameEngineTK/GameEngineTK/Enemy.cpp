// -- �w�b�_�t�@�C���̓ǂݍ��� -----------
#include "pch.h"
#include "Enemy.h"

// -- ���O��Ԃ̎w�� ---------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;

// -- �����o�֐��̒�` -------------------
// ----------------------------
// �R���X�g���N�^
// ��������
// ----------------------------
Enemy::Enemy()
{
	Initialize();
}

// ----------------------------
// �f�X�g���N�^
// ----------------------------
Enemy::~Enemy()
{
}

// ----------------------------
// ����������
// ��������
// �߂�l����
// ----------------------------
void Enemy::Initialize()
{
	//	���@�p�[�c�̓ǂݍ���
	{
		m_obj.resize(ENEMY_PARTS_NUM);	//	�p�[�c���Ƀ��T�C�Y
		m_obj[ENEMY_PARTS_BODY].LoadModel(L"Resouces/Body.cmo");
		m_obj[ENEMY_PARTS_SHOULDER_R].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[ENEMY_PARTS_SHOULDER_L].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[ENEMY_PARTS_ARM_R].LoadModel(L"Resouces/Arm.cmo");
		m_obj[ENEMY_PARTS_ARM_L].LoadModel(L"Resouces/Arm.cmo");
		m_obj[ENEMY_PARTS_HAND_R].LoadModel(L"Resouces/Hand.cmo");
		m_obj[ENEMY_PARTS_HAND_L].LoadModel(L"Resouces/Hand.cmo");
		m_obj[ENEMY_PARTS_WEPON1].LoadModel(L"Resouces/Wepon1.cmo");
		m_obj[ENEMY_PARTS_WEPON2].LoadModel(L"Resouces/Wepon.cmo");
		m_obj[ENEMY_PARTS_HIP].LoadModel(L"Resouces/Hip.cmo");
		m_obj[ENEMY_PARTS_THIGH_R].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[ENEMY_PARTS_THIGH_L].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[ENEMY_PARTS_SHIN_R].LoadModel(L"Resouces/Shin.cmo");
		m_obj[ENEMY_PARTS_SHIN_L].LoadModel(L"Resouces/Shin.cmo");
		m_obj[ENEMY_PARTS_LEG_R].LoadModel(L"Resouces/Leg.cmo");
		m_obj[ENEMY_PARTS_LEG_L].LoadModel(L"Resouces/Leg.cmo");
	}

	//	�p�[�c�̐e�q�֌W���Z�b�g�i�{�f�B�����	�j
	{
		m_obj[ENEMY_PARTS_SHOULDER_R].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_SHOULDER_L].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_ARM_R].SetParent(&m_obj[ENEMY_PARTS_SHOULDER_R]);
		m_obj[ENEMY_PARTS_ARM_L].SetParent(&m_obj[ENEMY_PARTS_SHOULDER_L]);
		m_obj[ENEMY_PARTS_HAND_R].SetParent(&m_obj[ENEMY_PARTS_ARM_R]);
		m_obj[ENEMY_PARTS_HAND_L].SetParent(&m_obj[ENEMY_PARTS_ARM_L]);
		m_obj[ENEMY_PARTS_WEPON1].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_WEPON2].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_HIP].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_THIGH_R].SetParent(&m_obj[ENEMY_PARTS_HIP]);
		m_obj[ENEMY_PARTS_THIGH_L].SetParent(&m_obj[ENEMY_PARTS_HIP]);
		m_obj[ENEMY_PARTS_SHIN_R].SetParent(&m_obj[ENEMY_PARTS_THIGH_R]);
		m_obj[ENEMY_PARTS_SHIN_L].SetParent(&m_obj[ENEMY_PARTS_THIGH_L]);
		m_obj[ENEMY_PARTS_LEG_R].SetParent(&m_obj[ENEMY_PARTS_SHIN_R]);
		m_obj[ENEMY_PARTS_LEG_L].SetParent(&m_obj[ENEMY_PARTS_SHIN_L]);
	}
	//	�e����̃I�t�Z�b�g�i���W�̂��炵���j���Z�b�g
	{
		m_obj[ENEMY_PARTS_BODY].SetTranslation(Vector3(0, 3.0f, 0));
		m_obj[ENEMY_PARTS_SHOULDER_R].SetTranslation(Vector3(0.3f, 0, 0));
		m_obj[ENEMY_PARTS_SHOULDER_L].SetTranslation(Vector3(-0.3f, 0, 0));
		m_obj[ENEMY_PARTS_ARM_R].SetTranslation(Vector3(0.3f, 0, -0.6));
		m_obj[ENEMY_PARTS_ARM_L].SetTranslation(Vector3(0.3f, 0, 0.6));
		m_obj[ENEMY_PARTS_WEPON1].SetTranslation(Vector3(-0.3, 0, 0.5));
		m_obj[ENEMY_PARTS_WEPON2].SetTranslation(Vector3(0.5, 0, 0.5));
		m_obj[ENEMY_PARTS_HIP].SetTranslation(Vector3(0, -0.35f, 0));
		m_obj[ENEMY_PARTS_THIGH_R].SetTranslation(Vector3(0.35, -0.0f, 0.2));
		m_obj[ENEMY_PARTS_THIGH_L].SetTranslation(Vector3(-0.35, -0.0f, 0.2));
		m_obj[ENEMY_PARTS_SHIN_R].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[ENEMY_PARTS_SHIN_L].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[ENEMY_PARTS_LEG_R].SetTranslation(Vector3(0, -0.5, 0));
		m_obj[ENEMY_PARTS_LEG_L].SetTranslation(Vector3(0, -0.5, 0));
	}
	//	�X�P�[����ύX
	{
		m_obj[ENEMY_PARTS_BODY].SetScale(Vector3(1.5, 1.5, 1.5));
		m_obj[ENEMY_PARTS_HIP].SetScale(Vector3(1.0, 1.0, 1.0));
		m_obj[ENEMY_PARTS_WEPON1].SetScale(Vector3(2.0, 2.0, 2.0));
		m_obj[ENEMY_PARTS_WEPON2].SetScale(Vector3(0.5, 0.5, 0.5));
		m_obj[ENEMY_PARTS_SHOULDER_R].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[ENEMY_PARTS_SHOULDER_L].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[ENEMY_PARTS_LEG_R].SetScale(Vector3(1.5, 0.7, 1));
		m_obj[ENEMY_PARTS_LEG_L].SetScale(Vector3(1.5, 0.7, 1));
	}

	//	�p�x��ύX
	{
		m_obj[ENEMY_PARTS_SHOULDER_L].SetRotation(Vector3(0, 180, 0));
		m_obj[ENEMY_PARTS_ARM_R].SetRotation(Vector3(-90, 0, 0));
		m_obj[ENEMY_PARTS_ARM_L].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_HAND_L].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_WEPON1].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_WEPON2].SetRotation(Vector3(45, 0, 0));
		m_obj[ENEMY_PARTS_THIGH_R].SetRotation(Vector3(70, 0, 0));
		m_obj[ENEMY_PARTS_THIGH_L].SetRotation(Vector3(70, 0, 0));
		m_obj[ENEMY_PARTS_SHIN_R].SetRotation(Vector3(-110, 0, 0));
		m_obj[ENEMY_PARTS_SHIN_L].SetRotation(Vector3(-110, 0, 0));
		m_obj[ENEMY_PARTS_LEG_R].SetRotation(Vector3(40, 0, 0));
		m_obj[ENEMY_PARTS_LEG_L].SetRotation(Vector3(40, 0, 0));
	}

	//	�����z�u
	Vector3 pos;
	pos.x = rand()%10;
	pos.y = 2;
	pos.z = rand()%10;

	this->SetPosition(pos);


	m_Timer = 0;
	
	m_DistAngle = 0;
}

// ----------------------------
// �X�V����
// ��������
// �߂�l����
// ----------------------------
void Enemy::Update()
{
	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;

		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	//if (keyboardState.D)
	//{
	//	//m_tankRot -= 5.0f;
	//	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	//	m_obj[ENEMY_PARTS_BODY].SetRotation(Vector3(0, angle - 5.0f, 0));
	//}
	//if (keyboardState.A)
	//{
	//	//m_tankRot += 5.0f;
	//	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	//	m_obj[ENEMY_PARTS_BODY].SetRotation(Vector3(0, angle + 5.0f, 0));
	//}

	{
		//	�p�x�̕ύX
		Vector3 rotv = m_obj[ENEMY_PARTS_BODY].GetRotation();

		float angle = m_DistAngle - rotv.y;

		//�@180�x�𒴂��Ă���ꍇ�A�t���̂ق����߂�
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}
		//	���
		rotv.y += angle * 0.05;

		

		m_obj[ENEMY_PARTS_BODY].SetRotation(rotv);
	}

	//	�����Ă�������Ɉړ�����
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	//	���@�̍��W���ړ�
	Vector3 pos = m_obj[ENEMY_PARTS_BODY].GetTranslation();
	m_obj[ENEMY_PARTS_BODY].SetTranslation(pos + moveV);

	//if (keyboardState.S)
	//{
	//	//	�ړ��x�N�g���iW���W�O�i�j
	//	Vector3 moveV(0, 0, 0.1f);
	//	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	//	//	�ړ��x�N�g�������@�̊p�x�ɍ��킹�ĉ�]����(�X�P�[�����������Ȃ��v�Z)		
	//	Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(angle));
	//	moveV = Vector3::TransformNormal(moveV, rotmat);

	//	//	���@�̍��W���ړ�
	//	Vector3 pos = m_obj[ENEMY_PARTS_BODY].GetTranslation();
	//	m_obj[ENEMY_PARTS_BODY].SetTranslation(pos + moveV);
	//}

	// 3D���f���̍X�V����
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Update(); }
}

// ----------------------------
// �`�揈��
// ��������
// �߂�l����
// ----------------------------
void Enemy::Draw()
{
	// 3D���f���̕`�揈��
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Draw(); }
}