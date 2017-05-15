//	カメラクラス
#pragma once
#include <SimpleMath.h>

class Camera
{
public:
	Camera(float width, float hight);
	~Camera();

	virtual void Update();

	//	ビュー行列のゲッター
	const DirectX::SimpleMath::Matrix& GetViewMatrix();
	//	プロジェクション行列のゲッター
	const DirectX::SimpleMath::Matrix& GetProjMatrix();
	//	EyePosのゲッター
	const DirectX::SimpleMath::Vector3& GetEyePos();
	//	RefPosのゲッター
	const DirectX::SimpleMath::Vector3& GetRefPos();

	//	各種変数取得関数
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);
	void SetFovY(float fovY);
	void SetAspect(float aspect);
	void SetNearClip(float nearClip);
	void SetFarClip(float farClip);

protected:
	//	ビュー行列
	DirectX::SimpleMath::Matrix m_viemat;
	//	視点
	DirectX::SimpleMath::Vector3 m_eyepos;
	//	参照
	DirectX::SimpleMath::Vector3 m_refpos;
	//	上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;


	//	プロジェクション行列
	DirectX::SimpleMath::Matrix m_projmat;
	//	垂直方向ベクトル
	float m_fovY;
	//	アスペクト比
	float m_aspect;
	//	ニアクリップ
	float m_nearClip;
	//	ファークリップ
	float m_farClip;
};

