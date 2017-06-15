//----------------------------------------
// 敵を制御するクラス
//----------------------------------------
#pragma once
// -- ヘッダファイルの読み込み -----------
#include "Singleton.h"
#include "DXTKResouces.h"
#include "Obj3D.h"
#include "pch.h"
#include <SimpleMath.h>
#include <d3d11_1.h>
#include <Keyboard.h>
#include <vector>

// -- クラスの宣言 -----------------------
class Enemy
{
	// 自機パーツ
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_HEAD,
		ENEMY_PARTS_BODY,
		ENEMY_PARTS_SHOULDER_R,
		ENEMY_PARTS_SHOULDER_L,
		ENEMY_PARTS_ARM_R,
		ENEMY_PARTS_ARM_L,
		ENEMY_PARTS_HAND_R,
		ENEMY_PARTS_HAND_L,
		ENEMY_PARTS_WEPON1,
		ENEMY_PARTS_WEPON2,
		ENEMY_PARTS_HIP,
		ENEMY_PARTS_THIGH_R,
		ENEMY_PARTS_THIGH_L,
		ENEMY_PARTS_SHIN_R,
		ENEMY_PARTS_SHIN_L,
		ENEMY_PARTS_LEG_R,
		ENEMY_PARTS_LEG_L,

		ENEMY_PARTS_NUM
	};
	//	各種フラグ
	bool CannonFlag = false;
	bool CannonDoingFlag = false;
	bool HandFlag = false;

protected:
	// データメンバ ///////////
	// パーツ
	std::vector<Obj3D> m_obj;

	// 自機の座標
	DirectX::SimpleMath::Vector3 m_position;
	// 自機の角度
	DirectX::SimpleMath::Vector3 m_angle;
public:
	// メンバ関数 /////////////
	// コンストラクタ
	Enemy();
	// デストラクタ
	~Enemy();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 角度を取得
	DirectX::SimpleMath::Vector3 GetAngle() { return m_obj[ENEMY_PARTS_BODY].GetRotation(); };
	// 座標を取得
	inline  DirectX::SimpleMath::Vector3 GetPosition()  { return m_obj[ENEMY_PARTS_BODY].GetTranslation(); };
	// ワールド行列を取得
	 DirectX::SimpleMath::Matrix GetWorldMat() { return m_obj[ENEMY_PARTS_BODY].GetWorld(); };
	// 座標を設定
	 void SetPosition(DirectX::SimpleMath::Vector3& trans) { m_obj[ENEMY_PARTS_BODY].SetTranslation(trans); };

	 //	タイマー
	 int m_Timer;
	 //	目標の角度
	 float m_DistAngle;
};