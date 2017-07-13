#include "pch.h"
#include "Camera.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

//	コンストラクタ
Camera::Camera(float width,float hight)
{
	//	ビュー行列の生成
	m_eyepos = Vector3(0, 0.1f, 7.0f);	//	視点
	m_refpos = Vector3(0, 0, 0);	//	参照点
	m_upvec = Vector3(0, 1.0f, 0);	//	上方向ベクトル
	m_viemat = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//	射影行列の生成
	m_fovY = XMConvertToRadians(60.0f);	//	視野角
	m_aspect = (float)width / hight;	//	アス比
	m_nearClip = 0.1f;					//	ニアクリップ
	m_farClip = 1000.0f;				//	ファークリップ
	m_projmat = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}


Camera::~Camera()
{
}

void Camera::Update()
{
	//	ビュー行列の作成
	m_viemat = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//射影行列の作成
	m_projmat = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

//	ビュー行列を取得
const DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{
	return m_viemat;
}
//	射影行列を取得
const DirectX::SimpleMath::Matrix& Camera::GetProjMatrix()
{
	return m_projmat;
}

//	EyePosのゲッター
const DirectX::SimpleMath::Vector3 & Camera::GetEyePos()
{
	return m_eyepos;
}

//	RefPosのゲッター
const DirectX::SimpleMath::Vector3 & Camera::GetRefPos()
{
	return m_refpos;
}


//	視点をセット
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}
//	参照点をセット
void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}
//	上方向ベクトルをセット
void Camera::SetUpVec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}
//	垂直方向視野角をセット
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}
//	アスペクト比をセット
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}
//	ニアクリップをセット
void Camera::SetNearClip(float nearClip)
{
	m_nearClip = nearClip;
}
//	ファークリップをセット
void Camera::SetFarClip(float farClip)
{
	m_farClip = farClip;
}
