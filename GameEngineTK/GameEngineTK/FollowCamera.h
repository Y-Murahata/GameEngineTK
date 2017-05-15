//
//	自機に追従するカメラクラス
//
#pragma once

#include"Camera.h"

class FollowCamera :public Camera
{
public:
	//	コンストラクタ
	FollowCamera(float width, float hight);
	~FollowCamera();

	//	毎フレーム更新(カメラクラスのアップデートを上書き)
	void Update()override;

	//	カメラと自機との距離
	static const float CAMERADISTANCE;

	//	追従対象の座標をセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos);

	//	追従対象の座標をセット
	void SetTargetAngle(const float targetAnge);

protected:
	//	追従対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;

	//	追従対象の傾き
	float m_targetAngle;
};

