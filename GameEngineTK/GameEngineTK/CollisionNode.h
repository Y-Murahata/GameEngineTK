//
//	�����蔻��̃m�[�h
//
#pragma once

#include "Collision.h"
#include "Obj3D.h"

class CollisionNode
{
protected:
	//	�f�o�b�N�\��ON
	static bool m_DebugVisible;

public:
	static bool GetDebugVisible() { return m_DebugVisible; }
	static bool SetDebugVisible(bool flag) { m_DebugVisible = flag; }

public:
	virtual void Initialize() = 0;	//	������
	virtual void Update() = 0;		//	�X�V
	virtual void Draw() = 0;		//	�`��

	void SetParent(Obj3D* parent);
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; };

protected:
	//	�f�o�b�N�\���p�I�u�W�F�N�g
	Obj3D m_obj;

	//	�e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_Trans;

};

class SphereNode : public CollisionNode , public Sphere
{
public:
	SphereNode();

	void Initialize();	//	������
	void Update();		//	�X�V
	void Draw();		//	�`��

	void SetLoacalRadius(float radius) { m_LocalRadius = radius; };
protected:
	//	���[�J�����a
	float m_LocalRadius;

};

