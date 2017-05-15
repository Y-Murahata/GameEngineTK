#include "pch.h"
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	静的メンバ変数の初期化
const float FollowCamera::CAMERADISTANCE = 5.0f;


//	コンストラクタ
FollowCamera::FollowCamera(float width, float hight)
	:Camera(width,hight)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
}


FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	//	カメラの位置座標を自機よりすこし上にずらす
	refpos = m_targetPos + Vector3(0, 2, 0);
	//	カメラから参照地点までの差分（前方を見るように少しずらす）
	Vector3 cameraV(0, 0, CAMERADISTANCE);
	//	自機の後ろに回り込むための回転行列
	Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	//	差分行列を回転
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	eyepos = refpos + cameraV;

	//	ゴム紐のアルゴリズム
	eyepos = GetEyePos() + (eyepos - GetEyePos())*0.05;
	refpos = GetRefPos() + (refpos - GetRefPos())*0.05;

	//	カメラの参照点を自機にする
	SetEyePos(eyepos);
	SetRefPos(refpos);

	//	基底クラスの更新
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(const float targetAnge)
{
	m_targetAngle = targetAnge;
}
