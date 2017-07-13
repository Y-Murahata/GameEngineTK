#include "pch.h"
#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//	�ÓI�����o�ϐ��̎���
//	�f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device> Obj3D::m_d3dDevice;
//	�f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3D::m_d3dContext;
//	�J����
Camera* Obj3D::m_Camera;
//	�ėp�`��ݒ�
std::unique_ptr<DirectX::CommonStates> Obj3D::m_states;
//	�G�t�F�N�g�t�@�N�g���[
std::unique_ptr<DirectX::EffectFactory>	Obj3D::m_factory;


//	�ÓI�����o�ϐ��̏�����
void Obj3D::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,static Camera* camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;
		
	m_states = std::make_unique<DirectX::CommonStates>(m_d3dDevice.Get());

	m_factory = std::make_unique<DirectX::EffectFactory>(m_d3dDevice.Get());
	(*m_factory).SetDirectory(L"Resouces");

}

//	�R���X�g���N�^
Obj3D::Obj3D()
{
	//	�X�P�[����1�{�ɐݒ�
	m_scale = Vector3(1, 1, 1);

	//	�e�I�u�W�F�N�g�|�C���^
	m_parent = nullptr;

	//	�f�t�H���g�ł̓N�H�[�^�j�I���͎g�p���Ȃ�
	m_UseQuaternion = false;
}

void Obj3D::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

//	�A�b�v�f�[�g
void Obj3D::Update()
{
	//	�s��̌v�Z=========================================================
	//	�X�P�[�����O�s��
	Matrix scalemat = Matrix::CreateScale(m_scale);

	Matrix rotmat;
	//	��]�s��
	if (m_UseQuaternion)
	{
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		//	�I�C���[�p�ŉ�]���v�Z ZXY
		Matrix rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(m_rotation.z));
		Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(m_rotation.x));
		Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(m_rotation.y));
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	//	���s�ړ��s��
	Matrix transmat = Matrix::CreateTranslation(m_translation);
	//	���[���h���X�V
	m_world = scalemat * rotmat * transmat;

	//	�e������ΐe�̍s���������
	if (m_parent)
	{
		m_world *= m_parent->m_world;
	}

}

//	�`��
void Obj3D::Draw()
{
	//	�J���������������Ă��Ȃ������痎�Ƃ�
	assert(m_Camera);

	//	���f���������Ă�����
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjMatrix());
	}

}

//	�s��X�V
void Obj3D::Calc()
{
	Matrix scalem;
	Matrix rotm;
	Matrix transm;

	scalem = Matrix::CreateScale(m_scale);

	if (m_UseQuaternion)
	{
		rotm = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		rotm = Matrix::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z);
	}

	transm = Matrix::CreateTranslation(m_translation);

	// ���[���h�s���SRT�̏��ɍ���
	m_world = Matrix::Identity;
	m_world *= scalem;
	m_world *= rotm;
	m_world *= transm;

	// �e�s�񂪂����
	if (m_parent)
	{
		// �e�s����|����
		m_world = m_world * m_parent->GetWorld();
	}
}
