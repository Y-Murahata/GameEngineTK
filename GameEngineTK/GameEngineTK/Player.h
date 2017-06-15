//----------------------------------------
// プレイヤーを制御するクラス
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
class Player
{
	// 自機パーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_HEAD,
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_SHOULDER_R,
		PLAYER_PARTS_SHOULDER_L,
		PLAYER_PARTS_ARM_R,
		PLAYER_PARTS_ARM_L,
		PLAYER_PARTS_HAND_R,
		PLAYER_PARTS_HAND_L,
		PLAYER_PARTS_WEPON1,
		PLAYER_PARTS_WEPON2,
		PLAYER_PARTS_HIP,
		PLAYER_PARTS_THIGH_R,
		PLAYER_PARTS_THIGH_L,
		PLAYER_PARTS_SHIN_R,
		PLAYER_PARTS_SHIN_L,
		PLAYER_PARTS_LEG_R,
		PLAYER_PARTS_LEG_L,

		PLAYER_PARTS_NUM
	};
	//	各種フラグ
	bool CannonFlag = false;
	bool CannonDoingFlag = false;
	bool HandFlag = false;

	//	弾丸の速度ベクトル
	DirectX::SimpleMath::Vector3 m_BulletVel[2];

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
	Player();
	// デストラクタ
	~Player();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 角度を取得
	DirectX::SimpleMath::Vector3 GetAngle() { return m_obj[PLAYER_PARTS_BODY].GetRotation(); };
	// 座標を取得
	inline  DirectX::SimpleMath::Vector3 GetPosition()  { return m_obj[PLAYER_PARTS_BODY].GetTranslation(); };
	// ワールド行列を取得
	 DirectX::SimpleMath::Matrix GetWorldMat() { return m_obj[PLAYER_PARTS_BODY].GetWorld(); };
	// 座標を設定
	 void SetPosition(DirectX::SimpleMath::Vector3& trans) { m_obj[PLAYER_PARTS_BODY].SetTranslation(trans); };

	 //	弾丸を発射
	 void FireBullet();
	 //	弾丸を再装填
	 void ResetBullet();

	 //	キーボードトラッカー
	 DirectX::Keyboard::KeyboardStateTracker keyTrackerState;


	 //	発射フラグ
	 bool m_FireFlag;
};