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

	//	���ƂŒǉ������ϐ�
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::unique_ptr<DirectX::BasicEffect>  m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//	�f�o�b�N�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	//	�J����
	std::unique_ptr<FollowCamera> m_Camera;

	//	�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	//	���f��
	Obj3D m_objSkydome;										//	��
	Obj3D m_objGround;									//	�n��
	std::unique_ptr<DirectX::Model> m_modelSphere;			//	��
	std::unique_ptr<DirectX::Model> m_modelTeapot;			//	�e�B�[�|�b�h
	std::unique_ptr<DirectX::Model> m_modelHead;			//	��
	
	//	�����[���h�s��
	DirectX::SimpleMath::Matrix m_worldSphere[20];
	//	�n�ʃ��[���h�s��
	DirectX::SimpleMath::Matrix m_worldTeapot[20];

	float m_teaPotPosX[20];
	float m_teaPotPosZ[20];

	float m_worldTimer;

	//	��]�J�E���^�[
	float m_rotateCnt;

	////	�L�[�{�[�h
	//std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//	���@�̍��W
	DirectX::SimpleMath::Vector3 tank_pos;

	//	���@�̌X��
	float m_tankRot;

	//	���@�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldTank;
	//	���@2�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldTank2;


	std::vector<Obj3D> m_objPlayer;
	//std::vector<Obj3D> m_ObjPlayer;

	//	�e��t���O
	bool CannonFlag = false;
	bool CannonDoingFlag = false;
	bool HandFlag = false;

	//	�v���C���[
	Player* m_player;

	//	�G�l�~�[
	std::vector<std::unique_ptr<Enemy>> m_Enemies;
};