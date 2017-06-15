// -- �w�b�_�t�@�C���̓ǂݍ��� -----------
#include "pch.h"
#include "Player.h"

// -- ���O��Ԃ̎w�� ---------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;

// -- �����o�֐��̒�` -------------------
// ----------------------------
// �R���X�g���N�^
// ��������
// ----------------------------
Player::Player()
{
	Initialize();

	//	���˃t���O�̏�����
	m_FireFlag = false;
}

// ----------------------------
// �f�X�g���N�^
// ----------------------------
Player::~Player()
{
}

// ----------------------------
// ����������
// ��������
// �߂�l����
// ----------------------------
void Player::Initialize()
{
	//	���@�p�[�c�̓ǂݍ���
	{
		m_obj.resize(PLAYER_PARTS_NUM);	//	�p�[�c���Ƀ��T�C�Y
		m_obj[PLAYER_PARTS_BODY].LoadModel(L"Resouces/Body.cmo");
		m_obj[PLAYER_PARTS_SHOULDER_R].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[PLAYER_PARTS_SHOULDER_L].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[PLAYER_PARTS_ARM_R].LoadModel(L"Resouces/Arm.cmo");
		m_obj[PLAYER_PARTS_ARM_L].LoadModel(L"Resouces/Arm.cmo");
		m_obj[PLAYER_PARTS_HAND_R].LoadModel(L"Resouces/Hand.cmo");
		m_obj[PLAYER_PARTS_HAND_L].LoadModel(L"Resouces/Hand.cmo");
		m_obj[PLAYER_PARTS_WEPON1].LoadModel(L"Resouces/Wepon1.cmo");
		m_obj[PLAYER_PARTS_WEPON2].LoadModel(L"Resouces/Wepon.cmo");
		m_obj[PLAYER_PARTS_HIP].LoadModel(L"Resouces/Hip.cmo");
		m_obj[PLAYER_PARTS_THIGH_R].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[PLAYER_PARTS_THIGH_L].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[PLAYER_PARTS_SHIN_R].LoadModel(L"Resouces/Shin.cmo");
		m_obj[PLAYER_PARTS_SHIN_L].LoadModel(L"Resouces/Shin.cmo");
		m_obj[PLAYER_PARTS_LEG_R].LoadModel(L"Resouces/Leg.cmo");
		m_obj[PLAYER_PARTS_LEG_L].LoadModel(L"Resouces/Leg.cmo");
	}

	//	�p�[�c�̐e�q�֌W���Z�b�g�i�{�f�B�����	�j
	{
		m_obj[PLAYER_PARTS_SHOULDER_R].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_SHOULDER_L].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_ARM_R].SetParent(&m_obj[PLAYER_PARTS_SHOULDER_R]);
		m_obj[PLAYER_PARTS_ARM_L].SetParent(&m_obj[PLAYER_PARTS_SHOULDER_L]);
		m_obj[PLAYER_PARTS_HAND_R].SetParent(&m_obj[PLAYER_PARTS_ARM_R]);
		m_obj[PLAYER_PARTS_HAND_L].SetParent(&m_obj[PLAYER_PARTS_ARM_L]);
		m_obj[PLAYER_PARTS_WEPON1].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_WEPON2].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_HIP].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_THIGH_R].SetParent(&m_obj[PLAYER_PARTS_HIP]);
		m_obj[PLAYER_PARTS_THIGH_L].SetParent(&m_obj[PLAYER_PARTS_HIP]);
		m_obj[PLAYER_PARTS_SHIN_R].SetParent(&m_obj[PLAYER_PARTS_THIGH_R]);
		m_obj[PLAYER_PARTS_SHIN_L].SetParent(&m_obj[PLAYER_PARTS_THIGH_L]);
		m_obj[PLAYER_PARTS_LEG_R].SetParent(&m_obj[PLAYER_PARTS_SHIN_R]);
		m_obj[PLAYER_PARTS_LEG_L].SetParent(&m_obj[PLAYER_PARTS_SHIN_L]);
	}
	//	�e����̃I�t�Z�b�g�i���W�̂��炵���j���Z�b�g
	{
		m_obj[PLAYER_PARTS_BODY].SetTranslation(Vector3(0, 2.0f, 0));
		m_obj[PLAYER_PARTS_SHOULDER_R].SetTranslation(Vector3(0.3f, 0, 0));
		m_obj[PLAYER_PARTS_SHOULDER_L].SetTranslation(Vector3(-0.3f, 0, 0));
		m_obj[PLAYER_PARTS_ARM_R].SetTranslation(Vector3(0.3f, 0, -0.6));
		m_obj[PLAYER_PARTS_ARM_L].SetTranslation(Vector3(0.3f, 0, 0.6));
		m_obj[PLAYER_PARTS_WEPON1].SetTranslation(Vector3(-0.3, 0, 0.5));
		m_obj[PLAYER_PARTS_WEPON2].SetTranslation(Vector3(0.5, 0, 0.5));
		m_obj[PLAYER_PARTS_HIP].SetTranslation(Vector3(0, -0.35f, 0));
		m_obj[PLAYER_PARTS_THIGH_R].SetTranslation(Vector3(0.35, -0.0f, 0.2));
		m_obj[PLAYER_PARTS_THIGH_L].SetTranslation(Vector3(-0.35, -0.0f, 0.2));
		m_obj[PLAYER_PARTS_SHIN_R].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[PLAYER_PARTS_SHIN_L].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[PLAYER_PARTS_LEG_R].SetTranslation(Vector3(0, -0.5, 0));
		m_obj[PLAYER_PARTS_LEG_L].SetTranslation(Vector3(0, -0.5, 0));
	}
	//	�X�P�[����ύX
	{
		m_obj[PLAYER_PARTS_BODY].SetScale(Vector3(1.5, 1.5, 1.5));
		m_obj[PLAYER_PARTS_HIP].SetScale(Vector3(1.0, 1.0, 1.0));
		m_obj[PLAYER_PARTS_WEPON1].SetScale(Vector3(2.0, 2.0, 2.0));
		m_obj[PLAYER_PARTS_WEPON2].SetScale(Vector3(0.5, 0.5, 0.5));
		m_obj[PLAYER_PARTS_SHOULDER_R].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[PLAYER_PARTS_SHOULDER_L].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[PLAYER_PARTS_LEG_R].SetScale(Vector3(1.5, 0.7, 1));
		m_obj[PLAYER_PARTS_LEG_L].SetScale(Vector3(1.5, 0.7, 1));
	}

	//	�p�x��ύX
	{
		m_obj[PLAYER_PARTS_SHOULDER_L].SetRotation(Vector3(0, 180, 0));
		m_obj[PLAYER_PARTS_ARM_R].SetRotation(Vector3(-90, 0, 0));
		m_obj[PLAYER_PARTS_ARM_L].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_HAND_L].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_WEPON1].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_WEPON2].SetRotation(Vector3(45, 0, 0));
		m_obj[PLAYER_PARTS_THIGH_R].SetRotation(Vector3(70, 0, 0));
		m_obj[PLAYER_PARTS_THIGH_L].SetRotation(Vector3(70, 0, 0));
		m_obj[PLAYER_PARTS_SHIN_R].SetRotation(Vector3(-110, 0, 0));
		m_obj[PLAYER_PARTS_SHIN_L].SetRotation(Vector3(-110, 0, 0));
		m_obj[PLAYER_PARTS_LEG_R].SetRotation(Vector3(40, 0, 0));
		m_obj[PLAYER_PARTS_LEG_L].SetRotation(Vector3(40, 0, 0));
	}

}

// ----------------------------
// �X�V����
// ��������
// �߂�l����
// ----------------------------
void Player::Update()
{
	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();
	// ���͏�Ԃ̍X�V����
	dxtk.UpdateInputState();
	// �L-�{�[�h�̏��
	Keyboard::State keyboardState = dxtk.m_keyboard->GetState();

	//	�L�[�{�[�h�̍X�V
	keyTrackerState.Update(dxtk.m_keyboard->GetState());

	//	���@�p�[�c�̃M�~�b�N=========================
	{
		//	�r�𓮂���
		{
			Vector3 ArmRod_R;
			Vector3 ArmRod_L;

			ArmRod_R = m_obj[PLAYER_PARTS_SHOULDER_R].GetRotation();
			ArmRod_L = m_obj[PLAYER_PARTS_SHOULDER_L].GetRotation();

			if (keyboardState.Up)
			{
				m_obj[PLAYER_PARTS_SHOULDER_R].SetRotation(ArmRod_R += Vector3(10, 0, 0));
				m_obj[PLAYER_PARTS_SHOULDER_L].SetRotation(ArmRod_L += Vector3(-10, 0, 0));

			}
			if (keyboardState.Down)
			{
				m_obj[PLAYER_PARTS_SHOULDER_R].SetRotation(ArmRod_R += Vector3(-10, 0, 0));
				m_obj[PLAYER_PARTS_SHOULDER_L].SetRotation(ArmRod_L += Vector3(10, 0, 0));
			}
		}

		//	�L���m���𓮂���
		if (CannonFlag == true)
		{
			CannonDoingFlag = false;

			Vector3 pos;
			pos = m_obj[PLAYER_PARTS_WEPON1].GetTranslation();

			Vector3 rotation;
			rotation = m_obj[PLAYER_PARTS_WEPON1].GetRotation();

			if (pos.y <= 0.3)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetTranslation(pos += Vector3(0, 0.01, 0));
				CannonDoingFlag = true;

			}
			if (rotation.x != 0)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetRotation(rotation += Vector3(-1, 0, 0));
				CannonDoingFlag = true;
			}
		}
		else if (CannonFlag == false)
		{
			CannonDoingFlag = false;

			Vector3 pos;
			pos = m_obj[PLAYER_PARTS_WEPON1].GetTranslation();

			Vector3 rotation;
			rotation = m_obj[PLAYER_PARTS_WEPON1].GetRotation();

			if (pos.y > 0)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetTranslation(pos += Vector3(0, -0.01, 0));
				CannonDoingFlag = true;
			}
			if (rotation.x <= 90)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetRotation(rotation += Vector3(3, 0, 0));
				CannonDoingFlag = true;
			}
		}

		//	����΂�
		{
			//	Vector3 pos_R;
			//	Vector3 pos_L;
			//	pos_R = m_obj[PLAYER_PARTS_HAND_R].GetTranslation();
			//	pos_L = m_obj[PLAYER_PARTS_HAND_L].GetTranslation();

			//	if (HandFlag == true)
			//	{
			//		m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos_R += Vector3(0, 0.1, 0));
			//		m_obj[PLAYER_PARTS_HAND_L].SetTranslation(pos_L += Vector3(0, 0.1, 0));

			//		if (pos_R.y > 10) { HandFlag = false; }
			//	}
			//	else
			//	{
			//		if (pos_R.y > 0)
			//		{
			//			//m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos_R += Vector3(0, -0.1, 0));
			//			//m_obj[PLAYER_PARTS_HAND_L].SetTranslation(pos_L += Vector3(0, -0.1, 0));
			//		}

			//	}

		}
	}

	if (keyboardState.D)
	{
		//m_tankRot -= 5.0f;
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		m_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle - 5.0f, 0));
	}
	if (keyboardState.A)
	{
		//m_tankRot += 5.0f;
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		m_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle + 5.0f, 0));
	}
	if (keyboardState.W)
	{
		//	�ړ��x�N�g���iW���W�O�i�j
		Vector3 moveV(0, 0, -0.1f);
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(angle));
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	���@�̍��W���ړ�
		Vector3 pos = m_obj[PLAYER_PARTS_BODY].GetTranslation();
		m_obj[PLAYER_PARTS_BODY].SetTranslation(pos + moveV);
	}
	if (keyboardState.S)
	{
		//	�ړ��x�N�g���iW���W�O�i�j
		Vector3 moveV(0, 0, 0.1f);
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		//	�ړ��x�N�g�������@�̊p�x�ɍ��킹�ĉ�]����(�X�P�[�����������Ȃ��v�Z)		
		Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(angle));
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	���@�̍��W���ړ�
		Vector3 pos = m_obj[PLAYER_PARTS_BODY].GetTranslation();
		m_obj[PLAYER_PARTS_BODY].SetTranslation(pos + moveV);
	}
	if (keyboardState.Z)
	{
		if (HandFlag == false)
		{
			HandFlag = !HandFlag;
		}
	}
	if (keyboardState.X)
	{
		if (CannonDoingFlag == false)
		{
			//	�t���O�̐؂�ւ�
			CannonFlag = !CannonFlag;

		}
	}

	////	�X�y�[�X�������ꂽ��
	//if (keyboardState.Space && m_FireFlag == false)
	//{
	//	FireBullet();
	//	m_FireFlag = true;
	//}
	////	�e�ۂ�O�i�����鏈��
	//	//	���@�̍��W���ړ�
	//	Vector3 pos = m_obj[PLAYER_PARTS_HAND_R].GetTranslation();
	//	m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos + m_BulletVel[0]);

	//	//	�X�y�[�X�L�[�������ꂽ�猳�̈ʒu�ɖ߂�
	//	if (m_FireFlag == true)
	//	{
	//		////	�e��ݒ�
	//		//m_obj[PLAYER_PARTS_HAND_R].SetParent(&m_obj[PLAYER_PARTS_ARM_R]);
	//		////	�p�x��ύX
	//		//m_obj[PLAYER_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
	//		////	���[�J�����W���Z�b�g
	//		//m_obj[PLAYER_PARTS_HAND_R].SetTranslation(Vector3(0,0,0));
	//		//	�t���O��܂�	
	//		//m_FireFlag = false;
	//	}
	//}

	//keyTrackerState

	//	�X�y�[�X�������ꂽ��
	if (keyTrackerState.IsKeyPressed(Keyboard::Keys::Space))
	{
		//	�X�y�[�X�L�[�������ꂽ�猳�̈ʒu�ɖ߂�
		if (m_FireFlag == true)
		{
			//	�e��ݒ�
			m_obj[PLAYER_PARTS_HAND_R].SetParent(&m_obj[PLAYER_PARTS_ARM_R]);
			//	�p�x��ύX
			m_obj[PLAYER_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
			//	���[�J�����W���Z�b�g
			m_obj[PLAYER_PARTS_HAND_R].SetTranslation(Vector3(0, 0, 0));
			//	�傫�������ɖ߂�
			m_obj[PLAYER_PARTS_HAND_R].SetScale(Vector3(1, 1, 1));
			//	�t���O��܂�	
			m_FireFlag = false;
		}
		else
		{
			FireBullet();
			m_FireFlag = true;
		}
	}
	if (m_FireFlag == true)
	{
		//	�e�ۂ�O�i�����鏈��
		//	���@�̍��W���ړ�
		Vector3 pos = m_obj[PLAYER_PARTS_HAND_R].GetTranslation();
		m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos + m_BulletVel[0]);
	}


	// 3D���f���̍X�V����
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Update(); }


}

// ----------------------------
// �`�揈��
// ��������
// �߂�l����
// ----------------------------
void Player::Draw()
{
	// 3D���f���̕`�揈��
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Draw(); }
}


//	�e�𔭎˂���
void Player::FireBullet()
{
	//	���˂������p�[�c�̃��[���h���W���擾
	Matrix worldm = m_obj[PLAYER_PARTS_HAND_R].GetWorld();

	//	���[���h���W����e�v�f�𒊏o
	Vector3 scale;			//	���[���h�X�P�[�����O
	Quaternion rotation;	//	���[���h��]
	Vector3 translation;	//	���[���h���W

	if (worldm.Decompose(scale, rotation, translation))
	{
		//	���˃p�[�c��e���番�����ēƗ�
		m_obj[PLAYER_PARTS_HAND_R].SetScale(scale);
		m_obj[PLAYER_PARTS_HAND_R].SetRotationQ(rotation);
		m_obj[PLAYER_PARTS_HAND_R].SetTranslation(translation);
		m_obj[PLAYER_PARTS_HAND_R].SetParent(nullptr);
	}

	//	�e�ۂ̑��x��ݒ�
	m_BulletVel[0] = Vector3(0, 0, -0.1f);
	m_BulletVel[0] = Vector3::Transform(m_BulletVel[0], rotation);

}

void Player::ResetBullet()
{

}
