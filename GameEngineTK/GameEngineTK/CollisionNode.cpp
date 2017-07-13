#include "pch.h"
#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

bool CollisionNode::m_DebugVisible;

//	======================
//	CollosionNode�̃����o�֐�
//	======================
SphereNode::SphereNode()
{
	//	�f�t�H���g���a�PM
	m_LocalRadius = 1.0f;
}


void CollisionNode::SetParent(Obj3D * parent)
{
	m_obj.SetParent(parent);

}


//	======================
//	SphereNode�̃����o�֐�
//	======================
void SphereNode::Initialize()
{
	//	�f�o�b�N�\���p���f����ǂݍ���
	m_obj.LoadModel(L"Resouces/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_Trans);
	m_obj.SetScale(Vector3(m_LocalRadius));

	//	���[���h���W�̍X�V
	m_obj.Update();

	{//	���[���h���W�ł̓����蔻�苅���v�Z
		//	�v�Z�ς݂̃��[���h�s����擾
		const Matrix& worldm = m_obj.GetWorld();
	
		//	���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		
		//	���f�����W�n�ł̉E�[(���̕\�ʂ̍��W)
		Vector3 right(1, 0, 0);

		//	���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//	������X�t�B�A�Ɍ��ʂ���
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);

	}

}

void SphereNode::Draw()
{
	m_obj.Draw();
}

