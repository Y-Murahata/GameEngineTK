//	
//	3Dオブジェクトのクラス
//
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3D
{
public:
	//	静的メンバ変数の初期化
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		static Camera* camera);
private:
	//	staticメンバ変数
	//	デバイス
	static	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//	デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//	カメラ
	static Camera* m_Camera;
	//	汎用描画設定
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//	エフェクトファクトリー
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	

public:
	//	コンストラクラ
	Obj3D();
	//	モデルをロード
	void LoadModel(const wchar_t* fileName);
	//　更新
	void	Update();

	//	描画
	void	Draw();

	//	Setter
	//	スケーリング
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	並行移動(XYZ)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotation) { m_rotationQ = rotation;  m_UseQuaternion = true; }
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation;  m_UseQuaternion = false; }

	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation;}
	//	親の3Dオブジェクトのポインタ
	void SetParent(Obj3D* parent) { m_parent = parent; }
	//	Getter
	//	スケーリング
	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }
	//	回転角(XYZ)
	DirectX::SimpleMath::Vector3 GetRotation() { return m_rotation; }
	//	並行移動(XYZ)
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_translation; }
	//	ワールド行列
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }
	//	親の3Dオブジェクトのポインタ
	Obj3D* GetParent() { return m_parent; }

private:
	//	メンバ変数（プライベート）
	//	3Dモデル
	std::unique_ptr<DirectX::Model> m_model;
	//	スケーリング
	DirectX::SimpleMath::Vector3 m_scale;
	//	回転角(XYZ オイラー角)
	DirectX::SimpleMath::Vector3 m_rotation;
	//	回転角(クォータニオン)
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//	並行移動(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	//	親の3Dオブジェクトのポインタ
	Obj3D* m_parent;
	//	クォータニオン使用フラグ
	bool m_UseQuaternion;

};

