//	
//	3D�I�u�W�F�N�g�̃N���X
//
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3D
{
public:
	//	�ÓI�����o�ϐ��̏�����
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		static Camera* camera);
private:
	//	static�����o�ϐ�
	//	�f�o�C�X
	static	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//	�f�o�C�X�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//	�J����
	static Camera* m_Camera;
	//	�ėp�`��ݒ�
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//	�G�t�F�N�g�t�@�N�g���[
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	

public:
	//	�R���X�g���N��
	Obj3D();
	//	���f�������[�h
	void LoadModel(const wchar_t* fileName);
	//�@�X�V
	void	Update();

	//	�`��
	void	Draw();

	//	Setter
	//	�X�P�[�����O
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	���s�ړ�(XYZ)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotation) { m_rotationQ = rotation;  m_UseQuaternion = true; }
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation;  m_UseQuaternion = false; }

	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation;}
	//	�e��3D�I�u�W�F�N�g�̃|�C���^
	void SetParent(Obj3D* parent) { m_parent = parent; }
	//	Getter
	//	�X�P�[�����O
	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }
	//	��]�p(XYZ)
	DirectX::SimpleMath::Vector3 GetRotation() { return m_rotation; }
	//	���s�ړ�(XYZ)
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_translation; }
	//	���[���h�s��
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }
	//	�e��3D�I�u�W�F�N�g�̃|�C���^
	Obj3D* GetParent() { return m_parent; }

private:
	//	�����o�ϐ��i�v���C�x�[�g�j
	//	3D���f��
	std::unique_ptr<DirectX::Model> m_model;
	//	�X�P�[�����O
	DirectX::SimpleMath::Vector3 m_scale;
	//	��]�p(XYZ �I�C���[�p)
	DirectX::SimpleMath::Vector3 m_rotation;
	//	��]�p(�N�H�[�^�j�I��)
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//	���s�ړ�(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	//	�e��3D�I�u�W�F�N�g�̃|�C���^
	Obj3D* m_parent;
	//	�N�H�[�^�j�I���g�p�t���O
	bool m_UseQuaternion;

};

