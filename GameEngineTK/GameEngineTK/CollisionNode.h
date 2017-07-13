//
//	当たり判定のノード
//
#pragma once

#include "Collision.h"
#include "Obj3D.h"

class CollisionNode
{
protected:
	//	デバック表示ON
	static bool m_DebugVisible;

public:
	static bool GetDebugVisible() { return m_DebugVisible; }
	static bool SetDebugVisible(bool flag) { m_DebugVisible = flag; }

public:
	virtual void Initialize() = 0;	//	初期化
	virtual void Update() = 0;		//	更新
	virtual void Draw() = 0;		//	描画

	void SetParent(Obj3D* parent);
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; };

protected:
	//	デバック表示用オブジェクト
	Obj3D m_obj;

	//	親からのオフセット
	DirectX::SimpleMath::Vector3 m_Trans;

};

class SphereNode : public CollisionNode , public Sphere
{
public:
	SphereNode();

	void Initialize();	//	初期化
	void Update();		//	更新
	void Draw();		//	描画

	void SetLoacalRadius(float radius) { m_LocalRadius = radius; };
protected:
	//	ローカル半径
	float m_LocalRadius;

};

