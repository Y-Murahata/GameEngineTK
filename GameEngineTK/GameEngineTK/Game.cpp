//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Obj3D.h"
#include "ModelEffect.h"

#include<time.h>




extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;



Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{

}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	srand((unsigned)time(NULL));

    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:

	//	========== �������͂����ɏ��� ===========
	//	�J�����̍쐬
	m_Camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	//	3D�I�u�W�F�N�g�̃����o�ϐ�
	Obj3D::InitializeStatic(m_d3dDevice, m_d3dContext, m_Camera.get());

	//	�n�`�̏�����
	LandShapeCommonDef lsdef;
	lsdef.pDevice = m_d3dDevice.Get();
	lsdef.pDeviceContext = m_d3dContext.Get();
	lsdef.pCamera = m_Camera.get();
	LandShape::InitializeCommon(lsdef);



	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());

	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());

	m_view = (*m_Camera).GetViewMatrix();

	m_proj = (*m_Camera).GetProjMatrix();;

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
			  
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//	�t�H���g�̐ݒ�
	m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());
	m_spriteFont = std::make_unique<SpriteFont>(m_d3dDevice.Get(), L"myfile.spritefont");

	//	�G�t�F�N�g�t�@�N�g���[����
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	(*m_factory).SetDirectory(L"Resouces");
	
	//	�n�`�f�[�^�̓ǂݍ���  landshape�t�@�C�����Acmo�t�@�C����
	m_landShape.Initialize(L"ground200m", L"ground200m");
	m_landShape.SetRot(Vector3(0, 0, 0));

	//	���f���̓ǂݍ���
	m_objSkydome.LoadModel(L"Resouces/skydome.cmo");
	//m_objGround.LoadModel(L"Resouces/ground200m.cmo");
	m_modelSphere = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resouces/sphere5m.cmo", *m_factory);
	m_modelTeapot = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resouces/teapod1m.cmo", *m_factory);
	m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resouces/Leg.cmo", *m_factory);

	m_worldTimer = 1.0f;

	//	��]�J�E���^�[
	m_rotateCnt = 0;

	//	��]�p��������
	m_tankRot = 0;

	//	�v���C���[�̐���
	m_player = new Player();
	//	�v���C���[�̏�����
	m_player->Initialize();

	//	�G�l�~�[�̐���
	int enemyNum = rand() % 10+1;
	m_Enemies.resize(enemyNum);
	for (int i = 0; i < enemyNum; i++)
	{
		m_Enemies[i] = std::make_unique<Enemy>();

		m_Enemies[i]->Initialize();
	}



}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	//========== ���t���[���X�V�����͂����ɏ��� ==========
	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	//	�L�[�{�[�h�̍X�V
	keyTrackerState.Update(dxtk.m_keyboard->GetState());

	//	�G�t�F�N�g�̍X�V
	ModelEffectManager::getInstance()->Update();

	{// ���@�ɒǏ]����J����
		m_Camera->SetTargetPos(m_player->GetPosition());
		m_Camera->SetTargetAngle(m_player->GetAngle().y);

		// �J�����̍X�V
		m_Camera->Update();
		m_view = m_Camera->GetViewMatrix();
		m_proj = m_Camera->GetProjMatrix();
	}

	//	��]�J�E���^�[�X�V
	m_rotateCnt += 1.0f/60.0f;
	if (m_rotateCnt >= 360)
		m_rotateCnt = 0;
	
	m_worldTimer -= 0.1f / 60.0f;
	if (m_worldTimer <= 0)
		m_worldTimer = 0;

	//	���@�̍X�V����
	m_player->Update();

	//	�G�l�~�[�̃A�b�v�f�[�g
	for (std::vector<std::unique_ptr<Enemy>>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end();itr++) 
	{
		//Enemy* enemy = itr->get();		//	�f�o�b�N���Ղ�

		//enemy->Update();

		(*itr)->Update();					//	�Z��
	}

	//	�e�ۂƓG�̓����蔻��
	{
		const Sphere& bulletSphere = m_player->GetCollisionNodeBullet();

		//	�G�̐������������s��
		for (std::vector<std::unique_ptr<Enemy>>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end();)
		{
			Enemy* enemy = itr->get();
			//	�G�̃X�t�B�A���擾
			const Sphere& enemySphere = enemy->GetCollisionNodeBullet();

			//	��̋����������Ă�����
			if (CheckSphere2Sphere(bulletSphere,enemySphere))
			{
				//	���ʃG�l�~�[�̍��W���擾
				Vector3 postion = enemy->GetPosition();

				//	�G���E��(�E�����G�̎��̃C�e���[�^�[��Ԃ�)
				itr = m_Enemies.erase(itr);

				ModelEffectManager::getInstance()->Entry(
					L"Resouces/Effect.cmo",	// ���f���t�@�C��
					30,	// �����t���[����
					postion,
					Vector3(0, 0, 0),	// ���x
					Vector3(0, 0, 0),	// �����x
					Vector3(0, 0, 0),	// ��]�p�i�����j
					Vector3(0, 0, 0),	// ��]�p�i�ŏI�j
					Vector3(1, 1, 1),	// �X�P�[���i�����j
					Vector3(3, 3, 3)	// �X�P�[���i�ŏI�j
				);
			}
			else
			{
				//	�C�e���[�^�[���P�i�߂�
				itr++;
			}
		}

	}

	//	�X�J�C�h�[���̍X�V����
	m_objSkydome.Update();
	//	�n�ʃI�u�W�F�̍X�V
	m_landShape.Update();

	{//	���@�̒n�`�ւ̂߂荞�݂𒼂�
		//	���@�̃{�f�B�̓����蔻����擾
		Sphere sphere = m_player->GetCollisionNodeBody();
		//	���@�̃��[���h���W���擾
		Vector3 trans = m_player->GetPosition();
		//	���̒��S���玩�@�Z���^�[�ւ̃x�N�g��
		Vector3 sphere2player = trans - sphere.Center;

		//	�߂荞�ݔr�˃x�N�g��
		Vector3 reject;

		//	�n�`�Ƌ��̓����蔻��
		if (m_landShape.IntersectSphere(sphere, &reject))
		{
			//	�߂荞�݂���������悤�ɂ��炷
			sphere.Center += reject;
		}
		//	���̒��S���瑫���ɂ��炵�����W���v���C���[�ɓn��
		m_player->SetPosition(sphere.Center + sphere2player);

		m_player->Calc();
	}

	{//	���@���n�ʂɗ�����
		if (m_player->GetVelosity().y <= 0.0f)
		{
			//	���@�̓����瑫���ւ̐���
			Segment player_segment;
			//	���@�̃��[���h���W���擾
			Vector3 trans = m_player->GetPosition();
			player_segment.Start = trans + Vector3(0, 1, 0);
			//	��������≺�܂ŋz��
			player_segment.End = trans + Vector3(0, -0.5f, 0);

			//	��_���W
			Vector3 inter;
			if (m_landShape.IntersectSegment(player_segment, &inter))
			{
				//	Y���W�̂݌�_�̈ʒu�Ɉړ�
				trans.y = inter.y;
				//	�����I��
				m_player->StopJump();
			}
			else
			{
				//	�����J�n
				m_player->StartFall();
			}

			//	���@���ړ�
			m_player->SetPosition(trans);

			m_player->Calc();
		}

	}

	//m_objGround.Update();

	//	�f�o�b�N�\���t���O��؂�ւ���
	if (keyTrackerState.IsKeyPressed(Keyboard::Keys::C))
	{
		debugDrawFlag = !debugDrawFlag;
	}

}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();	//�L�����o�X������

    // TODO: Add your rendering code here.

	//========== ���t���[���`�揈���͂����ɏ��� ==========
	DirectX::CommonStates m_states(m_d3dDevice.Get());
	m_d3dContext->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states.DepthNone(), 0);
	m_d3dContext->RSSetState(m_states.CullNone());

	//	�r���[�s��̎擾
	m_view = m_Camera->GetViewMatrix();

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	m_effect->SetWorld(m_world);

	(*m_effect).Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_landShape.Draw();
	//	�n�ʃ��f���̕`��
	//m_objGround.Draw();
	//	�X�J�C�h�[���̕`��
	m_objSkydome.Draw();
	
	//	�v���C���[�̕`��
	m_player->Draw();
	//	�G�̕`��
	for (std::vector<std::unique_ptr<Enemy>>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
	{
		//Enemy* enemy = itr->get();		//	�f�o�b�N���Ղ�

		//enemy->Update();

		(*itr)->Draw();					//	�Z��
	}

	//	�����蔻��̕`��
	if (debugDrawFlag == true)
	{
		//	�v���C���[�̕`��
		m_player->DebugDraw();
		//	�G�̕`��
		for (std::vector<std::unique_ptr<Enemy>>::iterator itr = m_Enemies.begin(); itr != m_Enemies.end(); itr++)
		{
			(*itr)->DebugDraw();
		}
	}

	//	�G�t�F�N�g�̕`��
	ModelEffectManager::getInstance()->Draw();

	//	�t�H���g�̕\��
	m_spriteBatch->Begin();
	
	if (m_Enemies.size() <= 0)
	{
		m_spriteFont->DrawString(m_spriteBatch.get(), L"GameClear!!!!", XMFLOAT2(400, 300));

	}

	m_spriteBatch->End();

    Present();	//�L�����o�X�ɔ��f������
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    //creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}

void Game::DrawGOMA()
{
	m_batch->DrawQuad(
		VertexPositionColor(Vector3(50, 50, 0), Color(0, 0, 0)),
		VertexPositionColor(Vector3(50, 600 - 50, 0), Color(0, 0, 0)),
		VertexPositionColor(Vector3(800 - 50, 600 - 50, 0), Color(0, 0, 0)),
		VertexPositionColor(Vector3(800 - 50, 50, 0), Color(0, 0, 0))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(100, 200, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(300, 200, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(100, 400, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(300, 400, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(300, 200, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(300, 400, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(300, 150, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(350, 200, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(350, 150, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(400, 200, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(450, 200, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(650, 200, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(650, 200, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(500, 320, 0), Color(1, 1, 1))
	);
	m_batch->DrawLine(
		VertexPositionColor(Vector3(450, 300, 0), Color(1, 1, 1)),
		VertexPositionColor(Vector3(600, 350, 0), Color(1, 1, 1))
	);
}