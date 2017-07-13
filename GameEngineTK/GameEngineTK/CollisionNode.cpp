#include "pch.h"
#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

bool CollisionNode::m_DebugVisible;

//	======================
//	CollosionNodeのメンバ関数
//	======================
SphereNode::SphereNode()
{
	//	デフォルト半径１M
	m_LocalRadius = 1.0f;
}


void CollisionNode::SetParent(Obj3D * parent)
{
	m_obj.SetParent(parent);

}


//	======================
//	SphereNodeのメンバ関数
//	======================
void SphereNode::Initialize()
{
	//	デバック表示用モデルを読み込む
	m_obj.LoadModel(L"Resouces/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_Trans);
	m_obj.SetScale(Vector3(m_LocalRadius));

	//	ワールド座標の更新
	m_obj.Update();

	{//	ワールド座標での当たり判定球を計算
		//	計算済みのワールド行列を取得
		const Matrix& worldm = m_obj.GetWorld();
	
		//	モデル座標系での中心点
		Vector3 center(0, 0, 0);
		
		//	モデル座標系での右端(球の表面の座標)
		Vector3 right(1, 0, 0);

		//	ワールド座標に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//	当たりスフィアに結果を代入
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);

	}

}

void SphereNode::Draw()
{
	m_obj.Draw();
}

