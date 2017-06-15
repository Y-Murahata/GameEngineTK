//
// Game.h
//

#pragma once

#include <windows.h>

#include <wrl/client.h>

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "StepTimer.h"
#include <PrimitiveBatch.h>
#include <VertexTypes.h>>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include "DebugCamera.h"
#include <Keyboard.h>
#include "FollowCamera.h"
#include "Obj3D.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

	void DrawGOMA();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;



    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	//	授業で追加した変数
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::unique_ptr<DirectX::BasicEffect>  m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//	デバックカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//	カメラ
	std::unique_ptr<FollowCamera> m_Camera;

	//	エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	//	モデル
	Obj3D m_objSkydome;										//	空
	Obj3D m_objGround;									//	地面
	std::unique_ptr<DirectX::Model> m_modelSphere;			//	球
	std::unique_ptr<DirectX::Model> m_modelTeapot;			//	ティーポッド
	std::unique_ptr<DirectX::Model> m_modelHead;			//	頭
	
	//	球ワールド行列
	DirectX::SimpleMath::Matrix m_worldSphere[20];
	//	地面ワールド行列
	DirectX::SimpleMath::Matrix m_worldTeapot[20];

	float m_teaPotPosX[20];
	float m_teaPotPosZ[20];

	float m_worldTimer;

	//	回転カウンター
	float m_rotateCnt;

	////	キーボード
	//std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//	自機の座標
	DirectX::SimpleMath::Vector3 tank_pos;

	//	自機の傾き
	float m_tankRot;

	//	自機のワールド行列
	DirectX::SimpleMath::Matrix m_worldTank;
	//	自機2のワールド行列
	DirectX::SimpleMath::Matrix m_worldTank2;


	std::vector<Obj3D> m_objPlayer;
	//std::vector<Obj3D> m_ObjPlayer;

	//	各種フラグ
	bool CannonFlag = false;
	bool CannonDoingFlag = false;
	bool HandFlag = false;

	//	プレイヤー
	Player* m_player;

	//	エネミー
	std::vector<std::unique_ptr<Enemy>> m_Enemies;
};