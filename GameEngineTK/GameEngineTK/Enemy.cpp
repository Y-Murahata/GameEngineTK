// -- ヘッダファイルの読み込み -----------
#include "pch.h"
#include "Enemy.h"

// -- 名前空間の指定 ---------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;

// -- メンバ関数の定義 -------------------
// ----------------------------
// コンストラクタ
// 引数無し
// ----------------------------
Enemy::Enemy()
{
	Initialize();
}

// ----------------------------
// デストラクタ
// ----------------------------
Enemy::~Enemy()
{
}

// ----------------------------
// 初期化処理
// 引数無し
// 戻り値無し
// ----------------------------
void Enemy::Initialize()
{
	//	自機パーツの読み込み
	{
		m_obj.resize(ENEMY_PARTS_NUM);	//	パーツ分にリサイズ
		m_obj[ENEMY_PARTS_BODY].LoadModel(L"Resouces/Body.cmo");
		m_obj[ENEMY_PARTS_SHOULDER_R].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[ENEMY_PARTS_SHOULDER_L].LoadModel(L"Resouces/Shoulder.cmo");
		m_obj[ENEMY_PARTS_ARM_R].LoadModel(L"Resouces/Arm.cmo");
		m_obj[ENEMY_PARTS_ARM_L].LoadModel(L"Resouces/Arm.cmo");
		m_obj[ENEMY_PARTS_HAND_R].LoadModel(L"Resouces/Hand.cmo");
		m_obj[ENEMY_PARTS_HAND_L].LoadModel(L"Resouces/Hand.cmo");
		m_obj[ENEMY_PARTS_WEPON1].LoadModel(L"Resouces/Wepon1.cmo");
		m_obj[ENEMY_PARTS_WEPON2].LoadModel(L"Resouces/Wepon.cmo");
		m_obj[ENEMY_PARTS_HIP].LoadModel(L"Resouces/Hip.cmo");
		m_obj[ENEMY_PARTS_THIGH_R].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[ENEMY_PARTS_THIGH_L].LoadModel(L"Resouces/Thigh.cmo");
		m_obj[ENEMY_PARTS_SHIN_R].LoadModel(L"Resouces/Shin.cmo");
		m_obj[ENEMY_PARTS_SHIN_L].LoadModel(L"Resouces/Shin.cmo");
		m_obj[ENEMY_PARTS_LEG_R].LoadModel(L"Resouces/Leg.cmo");
		m_obj[ENEMY_PARTS_LEG_L].LoadModel(L"Resouces/Leg.cmo");
	}

	//	パーツの親子関係をセット（ボディが基盤	）
	{
		m_obj[ENEMY_PARTS_SHOULDER_R].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_SHOULDER_L].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_ARM_R].SetParent(&m_obj[ENEMY_PARTS_SHOULDER_R]);
		m_obj[ENEMY_PARTS_ARM_L].SetParent(&m_obj[ENEMY_PARTS_SHOULDER_L]);
		m_obj[ENEMY_PARTS_HAND_R].SetParent(&m_obj[ENEMY_PARTS_ARM_R]);
		m_obj[ENEMY_PARTS_HAND_L].SetParent(&m_obj[ENEMY_PARTS_ARM_L]);
		m_obj[ENEMY_PARTS_WEPON1].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_WEPON2].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_HIP].SetParent(&m_obj[ENEMY_PARTS_BODY]);
		m_obj[ENEMY_PARTS_THIGH_R].SetParent(&m_obj[ENEMY_PARTS_HIP]);
		m_obj[ENEMY_PARTS_THIGH_L].SetParent(&m_obj[ENEMY_PARTS_HIP]);
		m_obj[ENEMY_PARTS_SHIN_R].SetParent(&m_obj[ENEMY_PARTS_THIGH_R]);
		m_obj[ENEMY_PARTS_SHIN_L].SetParent(&m_obj[ENEMY_PARTS_THIGH_L]);
		m_obj[ENEMY_PARTS_LEG_R].SetParent(&m_obj[ENEMY_PARTS_SHIN_R]);
		m_obj[ENEMY_PARTS_LEG_L].SetParent(&m_obj[ENEMY_PARTS_SHIN_L]);
	}
	//	親からのオフセット（座標のずらし分）をセット
	{
		m_obj[ENEMY_PARTS_BODY].SetTranslation(Vector3(0, 3.0f, 0));
		m_obj[ENEMY_PARTS_SHOULDER_R].SetTranslation(Vector3(0.3f, 0, 0));
		m_obj[ENEMY_PARTS_SHOULDER_L].SetTranslation(Vector3(-0.3f, 0, 0));
		m_obj[ENEMY_PARTS_ARM_R].SetTranslation(Vector3(0.3f, 0, -0.6));
		m_obj[ENEMY_PARTS_ARM_L].SetTranslation(Vector3(0.3f, 0, 0.6));
		m_obj[ENEMY_PARTS_WEPON1].SetTranslation(Vector3(-0.3, 0, 0.5));
		m_obj[ENEMY_PARTS_WEPON2].SetTranslation(Vector3(0.5, 0, 0.5));
		m_obj[ENEMY_PARTS_HIP].SetTranslation(Vector3(0, -0.35f, 0));
		m_obj[ENEMY_PARTS_THIGH_R].SetTranslation(Vector3(0.35, -0.0f, 0.2));
		m_obj[ENEMY_PARTS_THIGH_L].SetTranslation(Vector3(-0.35, -0.0f, 0.2));
		m_obj[ENEMY_PARTS_SHIN_R].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[ENEMY_PARTS_SHIN_L].SetTranslation(Vector3(0, -0.6f, 0.0));
		m_obj[ENEMY_PARTS_LEG_R].SetTranslation(Vector3(0, -0.5, 0));
		m_obj[ENEMY_PARTS_LEG_L].SetTranslation(Vector3(0, -0.5, 0));
	}
	//	スケールを変更
	{
		m_obj[ENEMY_PARTS_BODY].SetScale(Vector3(1.5, 1.5, 1.5));
		m_obj[ENEMY_PARTS_HIP].SetScale(Vector3(1.0, 1.0, 1.0));
		m_obj[ENEMY_PARTS_WEPON1].SetScale(Vector3(2.0, 2.0, 2.0));
		m_obj[ENEMY_PARTS_WEPON2].SetScale(Vector3(0.5, 0.5, 0.5));
		m_obj[ENEMY_PARTS_SHOULDER_R].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[ENEMY_PARTS_SHOULDER_L].SetScale(Vector3(0.7, 0.7, 0.7));
		m_obj[ENEMY_PARTS_LEG_R].SetScale(Vector3(1.5, 0.7, 1));
		m_obj[ENEMY_PARTS_LEG_L].SetScale(Vector3(1.5, 0.7, 1));
	}

	//	角度を変更
	{
		m_obj[ENEMY_PARTS_SHOULDER_L].SetRotation(Vector3(0, 180, 0));
		m_obj[ENEMY_PARTS_ARM_R].SetRotation(Vector3(-90, 0, 0));
		m_obj[ENEMY_PARTS_ARM_L].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_HAND_R].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_HAND_L].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_WEPON1].SetRotation(Vector3(90, 0, 0));
		m_obj[ENEMY_PARTS_WEPON2].SetRotation(Vector3(45, 0, 0));
		m_obj[ENEMY_PARTS_THIGH_R].SetRotation(Vector3(70, 0, 0));
		m_obj[ENEMY_PARTS_THIGH_L].SetRotation(Vector3(70, 0, 0));
		m_obj[ENEMY_PARTS_SHIN_R].SetRotation(Vector3(-110, 0, 0));
		m_obj[ENEMY_PARTS_SHIN_L].SetRotation(Vector3(-110, 0, 0));
		m_obj[ENEMY_PARTS_LEG_R].SetRotation(Vector3(40, 0, 0));
		m_obj[ENEMY_PARTS_LEG_L].SetRotation(Vector3(40, 0, 0));
	}

	//	初期配置
	Vector3 pos;
	pos.x = rand()%10;
	pos.y = 2;
	pos.z = rand()%10;

	this->SetPosition(pos);


	m_Timer = 0;
	
	m_DistAngle = 0;
}

// ----------------------------
// 更新処理
// 引数無し
// 戻り値無し
// ----------------------------
void Enemy::Update()
{
	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;

		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	//if (keyboardState.D)
	//{
	//	//m_tankRot -= 5.0f;
	//	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	//	m_obj[ENEMY_PARTS_BODY].SetRotation(Vector3(0, angle - 5.0f, 0));
	//}
	//if (keyboardState.A)
	//{
	//	//m_tankRot += 5.0f;
	//	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	//	m_obj[ENEMY_PARTS_BODY].SetRotation(Vector3(0, angle + 5.0f, 0));
	//}

	{
		//	角度の変更
		Vector3 rotv = m_obj[ENEMY_PARTS_BODY].GetRotation();

		float angle = m_DistAngle - rotv.y;

		//　180度を超えている場合、逆回りのほうが近い
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}
		//	補間
		rotv.y += angle * 0.05;

		

		m_obj[ENEMY_PARTS_BODY].SetRotation(rotv);
	}

	//	向いている方向に移動する
	Vector3 moveV(0, 0, -0.1f);
	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	//	自機の座標を移動
	Vector3 pos = m_obj[ENEMY_PARTS_BODY].GetTranslation();
	m_obj[ENEMY_PARTS_BODY].SetTranslation(pos + moveV);

	//if (keyboardState.S)
	//{
	//	//	移動ベクトル（W座標前進）
	//	Vector3 moveV(0, 0, 0.1f);
	//	float angle = m_obj[ENEMY_PARTS_BODY].GetRotation().y;
	//	//	移動ベクトルを自機の角度に合わせて回転する(スケールを加味しない計算)		
	//	Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(angle));
	//	moveV = Vector3::TransformNormal(moveV, rotmat);

	//	//	自機の座標を移動
	//	Vector3 pos = m_obj[ENEMY_PARTS_BODY].GetTranslation();
	//	m_obj[ENEMY_PARTS_BODY].SetTranslation(pos + moveV);
	//}

	// 3Dモデルの更新処理
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Update(); }
}

// ----------------------------
// 描画処理
// 引数無し
// 戻り値無し
// ----------------------------
void Enemy::Draw()
{
	// 3Dモデルの描画処理
	for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++) { itr->Draw(); }
}