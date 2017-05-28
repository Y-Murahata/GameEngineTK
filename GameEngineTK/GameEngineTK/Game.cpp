//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Obj3D.h"

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
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */


	//	========== 初期化はここに書く ===========
	//	キーボードをセット
	m_keyboard = std::make_unique<Keyboard>();
	//	カメラの作成
	m_Camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	//	3Dオブジェクトのメンバ変数
	Obj3D::InitializeStatic(m_d3dDevice,m_d3dContext,m_Camera.get());


	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());

	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());

	//m_view = Matrix::CreateLookAt(Vector3(0.f, 2.f, 5.f),
	//	Vector3::Zero, Vector3::UnitY);
	//m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
	//	float(m_outputWidth) / float(m_outputHeight), 0.1f, 300.f);

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

	//	デバッグカメラ生成
	//m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth,m_outputHeight);

	//	エフェクトファクトリー生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	(*m_factory).SetDirectory(L"Resouces");
	//	モデルの読み込み
	m_objSkydome.LoadModel(L"Resouces/skydome.cmo");
	m_objGround.LoadModel(L"Resouces/ground200m.cmo");
	m_modelSphere = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resouces/sphere5m.cmo", *m_factory);
	m_modelTeapot = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resouces/teapod1m.cmo", *m_factory);
	m_modelHead = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resouces/Leg.cmo", *m_factory);

	//	ティーポッドの初期座標を決定
	for (int i = 0; i < 20; i++)
	{
		//	スケール
		Matrix scalemat = Matrix::CreateScale(1.0f);

		//	ロール
		Matrix rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
		//	ピッチ
		Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
		//	ヨー
		Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(0.0f));
		//	回転行列
		Matrix rotmat = rotmatZ * rotmatX * rotmatY;

		//	位置
		Matrix transmat;
		float rad = rand() % 360;
		m_teaPotPosX[i] = cosf(rad) * (rand() % 100);		//ランダムな角度＊ランダムな距離
		m_teaPotPosZ[i] = sinf(rad) * (rand() % 100);

		transmat = Matrix::CreateTranslation(m_teaPotPosX[i], 0, m_teaPotPosZ[i]);

		//	球マトリックスの更新
		m_worldTeapot[i] = scalemat * transmat * rotmat;
	}

	m_worldTimer = 1.0f;

	//	回転カウンター
	m_rotateCnt = 0;

	//	回転角を初期化
	m_tankRot = 0;


	//	自機パーツの読み込み
	m_objPlayer.resize(PLAYER_PARTS_NUM);	//	パーツ分にリサイズ
	m_objPlayer[PLAYER_PARTS_LEG].LoadModel(L"Resouces/Leg.cmo");
	m_objPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resouces/Body.cmo");
	m_objPlayer[PLAYER_PARTS_SHOULDER].LoadModel(L"Resouces/Shoulder.cmo");
	m_objPlayer[PLAYER_PARTS_ARM].LoadModel(L"Resouces/Arm.cmo");
	m_objPlayer[PLAYER_PARTS_WEPON].LoadModel(L"Resouces/Wepon.cmo");
	m_objPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resouces/head.cmo");
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

	//========== 毎フレーム更新処理はここに書く ==========
	//	カメラのアップデート
	m_Camera->Update();
	m_view = m_Camera->GetViewMatrix();
	m_proj = m_Camera->GetProjMatrix();


	//	球のワールド行列を計算------------------------
	//	内側の球
	for (int i = 0; i < 20; i++)
	{
		//	スケール
		Matrix scalemat = Matrix::CreateScale(1.0f);

		//	ロール
		Matrix rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
		//	ピッチ
		Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(0.0f));

		Matrix rotmatY;
		//	ヨー
		if (i < 10)
		rotmatY = Matrix::CreateRotationY(XMConvertToRadians((i + m_rotateCnt) * 36.0f));
		if (i >= 10)
		rotmatY = Matrix::CreateRotationY(XMConvertToRadians((i - m_rotateCnt) * 36.0f));
		
		//	回転行列
		Matrix rotmat = rotmatZ * rotmatX * rotmatY;

		//	位置
		Matrix transmat;		
		if (i < 10)
		transmat = Matrix::CreateTranslation(20.0f, 0, 0);
		if(i >= 10)
		transmat = Matrix::CreateTranslation(40.0f, 0, 0);


		//	球マトリックスの更新
		m_worldSphere[i] = scalemat * transmat * rotmat;
	}

	//	ティーポットのワールド行列を計算------------------------
	for (int i = 0; i < 20; i++)
	{
		//	スケール
		Matrix scalemat = Matrix::CreateScale((sinf(m_rotateCnt) + 1.0f)  * 2.0f + 1.0f);

		//	ロール
		Matrix rotmatZ = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
		//	ピッチ
		Matrix rotmatX = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
		//	ヨー
		Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(0.0f));

		//	Y軸を回転
		rotmatY = Matrix::CreateRotationY(XMConvertToRadians((m_rotateCnt) * 36.0f));


		//	回転行列
		Matrix rotmat = rotmatZ * rotmatX * rotmatY;

		Matrix transmat = Matrix::CreateTranslation(m_teaPotPosX[i] * m_worldTimer, 0, m_teaPotPosZ[i] * m_worldTimer);

		//	球マトリックスの更新
		m_worldTeapot[i] = scalemat * rotmat * transmat;
	}

	//	回転カウンター更新
	m_rotateCnt += 1.0f/60.0f;
	if (m_rotateCnt >= 360)
		m_rotateCnt = 0;
	
	m_worldTimer -= 0.1f / 60.0f;
	if (m_worldTimer <= 0)
		m_worldTimer = 0;

	//	キーボードのアップデート
	Keyboard::State key = (*m_keyboard).GetState();

	//	Wキーが押されたら
	if (key.W)
	{
		//	移動ベクトル（W座標前進）
		Vector3 moveV(0, 0, -0.1f);
		//	移動ベクトルを自機の角度に合わせて回転する(スケールを加味しない計算)		
		Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(m_tankRot));
		moveV = Vector3::TransformNormal(moveV, rotmat);
		
		//	自機の座標を移動
		tank_pos += moveV;
	}
	if (key.S)
	{
		//	移動ベクトル（S座標前進）
		Vector3 moveV(0, 0, 0.1f);
		//	移動ベクトルを自機の角度に合わせて回転する(スケールを加味しない計算)
		Matrix rotmat = Matrix::CreateRotationY(XMConvertToRadians(m_tankRot));
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//	自機の座標を移動
		tank_pos += moveV;
	}
	if (key.D)
	{
		m_tankRot -= 5.0f;
	}
	if (key.A)
	{
		m_tankRot += 5.0f;
	}

	{//	自機の座標を計算
		//	パーツ１（親）
		Matrix transmat = Matrix::CreateTranslation(tank_pos);
		Matrix rotmatY = Matrix::CreateRotationY(XMConvertToRadians(m_tankRot));	
		//	ワールドを更新
		m_worldTank = rotmatY * transmat;

		//	パーツ２（子）
		Matrix transmat2 = Matrix::CreateTranslation(Vector3(0,0.5f,0));
		Matrix rotmatY2 = Matrix::CreateRotationY(XM_PIDIV2);
		//	ワールドを更新
		m_worldTank2 = rotmatY2 * transmat2 * rotmatY * transmat;
	}	

	m_Camera->SetTargetPos(tank_pos);
	m_Camera->SetTargetAngle(m_tankRot);

	//	スカイドームの更新処理
	m_objSkydome.Update();
	//	地面オブジェの更新
	m_objGround.Update();

	//	プレイヤーオブジェクトの更新処理
	for (std::vector<Obj3D>::iterator it = m_objPlayer.begin();
		it != m_objPlayer.end();
		it++)
	{
		it->Update();
	}
	//------------------------------------------------
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();	//キャンバスを消す

    // TODO: Add your rendering code here.

	//========== 毎フレーム描画処理はここに書く ==========
	DirectX::CommonStates m_states(m_d3dDevice.Get());
	m_d3dContext->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states.DepthNone(), 0);
	m_d3dContext->RSSetState(m_states.CullNone());

	//	ビュー行列の取得
	m_view = m_Camera->GetViewMatrix();

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	m_effect->SetWorld(m_world);

	(*m_effect).Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	//	地面モデルの描画
	m_objGround.Draw();
	//	スカイドームの描画
	m_objSkydome.Draw();
	
	
		for (std::vector<Obj3D>::iterator it = m_objPlayer.begin();
			it != m_objPlayer.end();
			it++)
	{
			it->Draw();
	}



	//	球の表示
	/*for (int i = 0; i < 20; i++)
	{
		m_modelSphere->Draw(m_d3dContext.Get(), m_states, m_worldSphere[i], m_view, m_proj);
	}*/

	//	ティーポッドの描画
	for (int i = 0; i < 20; i++)
	{
		//m_modelTeapot->Draw(m_d3dContext.Get(), m_states, m_worldTeapot[i], m_view, m_proj);
	}
	

	m_batch->Begin();

	//	三角形を表示
	VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::Yellow);
	VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow);
	VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow);
	
	m_batch->End();


    Present();	//キャンバスに反映させる
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
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
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