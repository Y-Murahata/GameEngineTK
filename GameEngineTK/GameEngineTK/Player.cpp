// -- ヘッダファイルの読み込み -----------
#include "pch.h"
#include "Player.h"

// -- 名前空間の指定 ---------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;

// -- メンバ関数の定義 -------------------
// ----------------------------
// コンストラクタ
// 引数無し
// ----------------------------
Player::Player()
{
	Initialize();

	//	発射フラグの初期化
	m_FireFlag = false;
}

// ----------------------------
// デストラクタ
// ----------------------------
Player::~Player()
{
}

// ----------------------------
// 初期化処理
// 引数無し
// 戻り値無し
// ----------------------------
void Player::Initialize()
{
	//	自機パーツの読み込み
	{
		m_obj.resize(PLAYER_PARTS_NUM);	//	パーツ分にリサイズ
		m_obj[PLAYER_PARTS_BODY].LoadModel(L"Resouces/Body.cmo");
		m_obj[PLAYER_PARTS_SHOULDER_R].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[PLAYER_PARTS_SHOULDER_L].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[PLAYER_PARTS_ARM_R].LoadModel(L"Resouces/Arm.cmo");
		m_obj[PLAYER_PARTS_ARM_L].LoadModel(L"Resouces/Arm.cmo");
		m_obj[PLAYER_PARTS_HAND_R].LoadModel(L"Resouces/Hand.cmo");
		m_obj[PLAYER_PARTS_HAND_L].LoadModel(L"Resouces/Hand.cmo");
		m_obj[PLAYER_PARTS_WEPON1].LoadModel(L"Resouces/Wepon1.cmo");
		m_obj[PLAYER_PARTS_WEPON2].LoadModel(L"Resouces/Wepon.cmo");
		m_obj[PLAYER_PARTS_HIP].LoadModel(L"Resouces/Hip.cmo");
		m_obj[PLAYER_PARTS_THIGH_R].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[PLAYER_PARTS_THIGH_L].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[PLAYER_PARTS_SHIN_R].LoadModel(L"Resouces/Shin.cmo");
		m_obj[PLAYER_PARTS_SHIN_L].LoadModel(L"Resouces/Shin.cmo");
		m_obj[PLAYER_PARTS_LEG_R].LoadModel(L"Resouces/Leg.cmo");
		m_obj[PLAYER_PARTS_LEG_L].LoadModel(L"Resouces/Leg.cmo");
	}

	//	パーツの親子関係をセット（ボディが基盤	）
	{
		m_obj[PLAYER_PARTS_SHOULDER_R].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_SHOULDER_L].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_ARM_R].SetParent(&m_obj[PLAYER_PARTS_SHOULDER_R]);
		m_obj[PLAYER_PARTS_ARM_L].SetParent(&m_obj[PLAYER_PARTS_SHOULDER_L]);
		m_obj[PLAYER_PARTS_HAND_R].SetParent(&m_obj[PLAYER_PARTS_ARM_R]);
		m_obj[PLAYER_PARTS_HAND_L].SetParent(&m_obj[PLAYER_PARTS_ARM_L]);
		m_obj[PLAYER_PARTS_WEPON1].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_WEPON2].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_HIP].SetParent(&m_obj[PLAYER_PARTS_BODY]);
		m_obj[PLAYER_PARTS_THIGH_R].SetParent(&m_obj[PLAYER_PARTS_HIP]);
		m_obj[PLAYER_PARTS_THIGH_L].SetParent(&m_obj[PLAYER_PARTS_HIP]);
		m_obj[PLAYER_PARTS_SHIN_R].SetParent(&m_obj[PLAYER_PARTS_THIGH_R]);
		m_obj[PLAYER_PARTS_SHIN_L].SetParent(&m_obj[PLAYER_PARTS_THIGH_L]);
		m_obj[PLAYER_PARTS_LEG_R].SetParent(&m_obj[PLAYER_PARTS_SHIN_R]);
		m_obj[PLAYER_PARTS_LEG_L].SetParent(&m_obj[PLAYER_PARTS_SHIN_L]);
	}
	//	親からのオフセット（座標のずらし分）をセット
	{
		m_obj[PLAYER_PARTS_BODY].SetTranslation(Vector3(0, 2.0f, 0));
		m_obj[PLAYER_PARTS_SHOULDER_R].SetTranslation(Vector3(0.3f, 0, 0));
		m_obj[PLAYER_PARTS_SHOULDER_L].SetTranslation(Vector3(-0.3f, 0, 0));
		m_obj[PLAYER_PARTS_ARM_R].SetTranslation(Vector3(0.3f, 0, -0.6));
		m_obj[PLAYER_PARTS_ARM_L].SetTranslation(Vector3(0.3f, 0, 0.6));
		m_obj[PLAYER_PARTS_WEPON1].SetTranslation(Vector3(-0.3, 0, 0.5));
		m_obj[PLAYER_PARTS_WEPON2].SetTranslation(Vector3(0.5, 0, 0.5));
		m_obj[PLAYER_PARTS_HIP].SetTranslation(Vector3(0, -0.35f, 0));
		m_obj[PLAYER_PARTS_THIGH_R].SetTranslation(Vector3(0.35, -0.0f, 0.2));
		m_obj[PLAYER_PARTS_THIGH_L].SetTranslation(Vector3(-0.35, -0.0f, 0.2));
		m_obj[PLAYER_PARTS_SHIN_R].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[PLAYER_PARTS_SHIN_L].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[PLAYER_PARTS_LEG_R].SetTranslation(Vector3(0, -0.5, 0));
		m_obj[PLAYER_PARTS_LEG_L].SetTranslation(Vector3(0, -0.5, 0));
	}
	//	スケールを変更
	{
		m_obj[PLAYER_PARTS_BODY].SetScale(Vector3(1.5, 1.5, 1.5));
		m_obj[PLAYER_PARTS_HIP].SetScale(Vector3(1.0, 1.0, 1.0));
		m_obj[PLAYER_PARTS_WEPON1].SetScale(Vector3(2.0, 2.0, 2.0));
		m_obj[PLAYER_PARTS_WEPON2].SetScale(Vector3(0.5, 0.5, 0.5));
		m_obj[PLAYER_PARTS_SHOULDER_R].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[PLAYER_PARTS_SHOULDER_L].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[PLAYER_PARTS_LEG_R].SetScale(Vector3(1.5, 0.7, 1));
		m_obj[PLAYER_PARTS_LEG_L].SetScale(Vector3(1.5, 0.7, 1));
	}

	//	角度を変更
	{
		m_obj[PLAYER_PARTS_SHOULDER_L].SetRotation(Vector3(0, 180, 0));
		m_obj[PLAYER_PARTS_ARM_R].SetRotation(Vector3(-90, 0, 0));
		m_obj[PLAYER_PARTS_ARM_L].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_HAND_L].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_WEPON1].SetRotation(Vector3(90, 0, 0));
		m_obj[PLAYER_PARTS_WEPON2].SetRotation(Vector3(45, 0, 0));
		m_obj[PLAYER_PARTS_THIGH_R].SetRotation(Vector3(70, 0, 0));
		m_obj[PLAYER_PARTS_THIGH_L].SetRotation(Vector3(70, 0, 0));
		m_obj[PLAYER_PARTS_SHIN_R].SetRotation(Vector3(-110, 0, 0));
		m_obj[PLAYER_PARTS_SHIN_L].SetRotation(Vector3(-110, 0, 0));
		m_obj[PLAYER_PARTS_LEG_R].SetRotation(Vector3(40, 0, 0));
		m_obj[PLAYER_PARTS_LEG_L].SetRotation(Vector3(40, 0, 0));
	}

}

// ----------------------------
// 更新処理
// 引数無し
// 戻り値無し
// ----------------------------
void Player::Update()
{
	// DXTKを管理するインスタンスを取得
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();
	// 入力状態の更新処理
	dxtk.UpdateInputState();
	// キ-ボードの状態
	Keyboard::State keyboardState = dxtk.m_keyboard->GetState();

	//	キーボードの更新
	keyTrackerState.Update(dxtk.m_keyboard->GetState());

	//	自機パーツのギミック=========================
	{
		//	腕を動かす
		{
			Vector3 ArmRod_R;
			Vector3 ArmRod_L;

			ArmRod_R = m_obj[PLAYER_PARTS_SHOULDER_R].GetRotation();
			ArmRod_L = m_obj[PLAYER_PARTS_SHOULDER_L].GetRotation();

			if (keyboardState.Up)
			{
				m_obj[PLAYER_PARTS_SHOULDER_R].SetRotation(ArmRod_R += Vector3(10, 0, 0));
				m_obj[PLAYER_PARTS_SHOULDER_L].SetRotation(ArmRod_L += Vector3(-10, 0, 0));

			}
			if (keyboardState.Down)
			{
				m_obj[PLAYER_PARTS_SHOULDER_R].SetRotation(ArmRod_R += Vector3(-10, 0, 0));
				m_obj[PLAYER_PARTS_SHOULDER_L].SetRotation(ArmRod_L += Vector3(10, 0, 0));
			}
		}

		//	キャノンを動かす
		if (CannonFlag == true)
		{
			CannonDoingFlag = false;

			Vector3 pos;
			pos = m_obj[PLAYER_PARTS_WEPON1].GetTranslation();

			Vector3 rotation;
			rotation = m_obj[PLAYER_PARTS_WEPON1].GetRotation();

			if (pos.y <= 0.3)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetTranslation(pos += Vector3(0, 0.01, 0));
				CannonDoingFlag = true;

			}
			if (rotation.x != 0)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetRotation(rotation += Vector3(-1, 0, 0));
				CannonDoingFlag = true;
			}
		}
		else if (CannonFlag == false)
		{
			CannonDoingFlag = false;

			Vector3 pos;
			pos = m_obj[PLAYER_PARTS_WEPON1].GetTranslation();

			Vector3 rotation;
			rotation = m_obj[PLAYER_PARTS_WEPON1].GetRotation();

			if (pos.y > 0)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetTranslation(pos += Vector3(0, -0.01, 0));
				CannonDoingFlag = true;
			}
			if (rotation.x <= 90)
			{
				m_obj[PLAYER_PARTS_WEPON1].SetRotation(rotation += Vector3(3, 0, 0));
				CannonDoingFlag = true;
			}
		}

		//	手を飛ばす
		{
			//	Vector3 pos_R;
			//	Vector3 pos_L;
			//	pos_R = m_obj[PLAYER_PARTS_HAND_R].GetTranslation();
			//	pos_L = m_obj[PLAYER_PARTS_HAND_L].GetTranslation();

			//	if (HandFlag == true)
			//	{
			//		m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos_R += Vector3(0, 0.1, 0));
			//		m_obj[PLAYER_PARTS_HAND_L].SetTranslation(pos_L += Vector3(0, 0.1, 0));

			//		if (pos_R.y > 10) { HandFlag = false; }
			//	}
			//	else
			//	{
			//		if (pos_R.y > 0)
			//		{
			//			//m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos_R += Vector3(0, -0.1, 0));
			//			//m_obj[PLAYER_PARTS_HAND_L].SetTranslation(pos_L += Vector3(0, -0.1, 0));
			//		}

			//	}

		}
	}

	if (keyboardState.D)
	{
		//m_tankRot -= 5.0f;
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		m_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle - 5.0f, 0));
	}
	if (keyboardState.A)
	{
		//m_tankRot += 5.0f;
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		m_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle + 5.0f, 0));
	}
	if (keyboardState.W)
	{
		//	移動ベクトル（W座標前進）
		Vector3 moveV(0, 0, -0.1f);
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(angle));
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	自機の座標を移動
		Vector3 pos = m_obj[PLAYER_PARTS_BODY].GetTranslation();
		m_obj[PLAYER_PARTS_BODY].SetTranslation(pos + moveV);
	}
	if (keyboardState.S)
	{
		//	移動ベクトル（W座標前進）
		Vector3 moveV(0, 0, 0.1f);
		float angle = m_obj[PLAYER_PARTS_BODY].GetRotation().y;
		//	移動ベクトルを自機の角度に合わせて回転する(スケールを加味しない計算)		
		Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(angle));
		moveV = Vector3::TransformNormal(moveV, rotmat);

		//	自機の座標を移動
		Vector3 pos = m_obj[PLAYER_PARTS_BODY].GetTranslation();
		m_obj[PLAYER_PARTS_BODY].SetTranslation(pos + moveV);
	}
	if (keyboardState.Z)
	{
		if (HandFlag == false)
		{
			HandFlag = !HandFlag;
		}
	}
	if (keyboardState.X)
	{
		if (CannonDoingFlag == false)
		{
			//	フラグの切り替え
			CannonFlag = !CannonFlag;

		}
	}

	////	スペースが押された時
	//if (keyboardState.Space && m_FireFlag == false)
	//{
	//	FireBullet();
	//	m_FireFlag = true;
	//}
	////	弾丸を前進させる処理
	//	//	自機の座標を移動
	//	Vector3 pos = m_obj[PLAYER_PARTS_HAND_R].GetTranslation();
	//	m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos + m_BulletVel[0]);

	//	//	スペースキーが押されたら元の位置に戻す
	//	if (m_FireFlag == true)
	//	{
	//		////	親を設定
	//		//m_obj[PLAYER_PARTS_HAND_R].SetParent(&m_obj[PLAYER_PARTS_ARM_R]);
	//		////	角度を変更
	//		//m_obj[PLAYER_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
	//		////	ローカル座標をセット
	//		//m_obj[PLAYER_PARTS_HAND_R].SetTranslation(Vector3(0,0,0));
	//		//	フラグを折る	
	//		//m_FireFlag = false;
	//	}
	//}

	//keyTrackerState

	//	スペースが押された時
	if (keyTrackerState.IsKeyPressed(Keyboard::Keys::Space))
	{
		//	スペースキーが押されたら元の位置に戻す
		if (m_FireFlag == true)
		{
			//	親を設定
			m_obj[PLAYER_PARTS_HAND_R].SetParent(&m_obj[PLAYER_PARTS_ARM_R]);
			//	角度を変更
			m_obj[PLAYER_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
			//	ローカル座標をセット
			m_obj[PLAYER_PARTS_HAND_R].SetTranslation(Vector3(0, 0, 0));
			//	大きさを元に戻す
			m_obj[PLAYER_PARTS_HAND_R].SetScale(Vector3(1, 1, 1));
			//	フラグを折る	
			m_FireFlag = false;
		}
		else
		{
			FireBullet();
			m_FireFlag = true;
		}
	}
	if (m_FireFlag == true)
	{
		//	弾丸を前進させる処理
		//	自機の座標を移動
		Vector3 pos = m_obj[PLAYER_PARTS_HAND_R].GetTranslation();
		m_obj[PLAYER_PARTS_HAND_R].SetTranslation(pos + m_BulletVel[0]);
	}


	// 3Dモデルの更新処理
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Update(); }


}

// ----------------------------
// 描画処理
// 引数無し
// 戻り値無し
// ----------------------------
void Player::Draw()
{
	// 3Dモデルの描画処理
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Draw(); }
}


//	弾を発射する
void Player::FireBullet()
{
	//	発射したいパーツのワールド座標を取得
	Matrix worldm = m_obj[PLAYER_PARTS_HAND_R].GetWorld();

	//	ワールド座標から各要素を抽出
	Vector3 scale;			//	ワールドスケーリング
	Quaternion rotation;	//	ワールド回転
	Vector3 translation;	//	ワールド座標

	if (worldm.Decompose(scale, rotation, translation))
	{
		//	発射パーツを親から分離して独立
		m_obj[PLAYER_PARTS_HAND_R].SetScale(scale);
		m_obj[PLAYER_PARTS_HAND_R].SetRotationQ(rotation);
		m_obj[PLAYER_PARTS_HAND_R].SetTranslation(translation);
		m_obj[PLAYER_PARTS_HAND_R].SetParent(nullptr);
	}

	//	弾丸の速度を設定
	m_BulletVel[0] = Vector3(0, 0, -0.1f);
	m_BulletVel[0] = Vector3::Transform(m_BulletVel[0], rotation);

}

void Player::ResetBullet()
{

}
