#include "pch.h"
#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//	静的メンバ変数の実態
//	デバイス
Microsoft::WRL::ComPtr<ID3D11Device> Obj3D::m_d3dDevice;
//	デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3D::m_d3dContext;
//	カメラ
Camera* Obj3D::m_Camera;
//	汎用描画設定
std::unique_ptr<DirectX::CommonStates> Obj3D::m_states;
//	エフェクトファクトリー
std::unique_ptr<DirectX::EffectFactory>	Obj3D::m_factory;


//	静的メンバ変数の初期化
void Obj3D::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,static Camera* camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;
		
	m_states = std::make_unique<DirectX::CommonStates>(m_d3dDevice.Get());

	m_factory = std::make_unique<DirectX::EffectFactory>(m_d3dDevice.Get());
	(*m_factory).SetDirectory(L"Resouces");

}

//	コンストラクタ
Obj3D::Obj3D()
{
	//	スケールを1倍に設定
	m_scale = Vector3(1, 1, 1);

	//	親オブジェクトポインタ
	m_parent = nullptr;

	//	デフォルトではクォータニオンは使用しない
	m_UseQuaternion = false;
}

void Obj3D::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

//	アップデート
void Obj3D::Update()
{
	//	行列の計算=========================================================
	//	スケーリング行列
	Matrix scalemat = Matrix::CreateScale(m_scale);

	Matrix rotmat;
	//	回転行列
	if (m_UseQuaternion)
	{
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		//	オイラー角で回転を計算 ZXY
		Matrix rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(m_rotation.z));
		Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(m_rotation.x));
		Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(m_rotation.y));
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	//	並行移動行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);
	//	ワールドを更新
	m_world = scalemat * rotmat * transmat;

	//	親がいれば親の行列をかける
	if (m_parent)
	{
		m_world *= m_parent->m_world;
	}

}

//	描画
void Obj3D::Draw()
{
	//	カメラが何も入っていなかったら落とす
	assert(m_Camera);

	//	モデルが入っていたら
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjMatrix());
	}

}

//	行列更新
void Obj3D::Calc()
{
	Matrix scalem;
	Matrix rotm;
	Matrix transm;

	scalem = Matrix::CreateScale(m_scale);

	if (m_UseQuaternion)
	{
		rotm = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		rotm = Matrix::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z);
	}

	transm = Matrix::CreateTranslation(m_translation);

	// ワールド行列をSRTの順に合成
	m_world = Matrix::Identity;
	m_world *= scalem;
	m_world *= rotm;
	m_world *= transm;

	// 親行列があれば
	if (m_parent)
	{
		// 親行列を掛ける
		m_world = m_world * m_parent->GetWorld();
	}
}
