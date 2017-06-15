//--------------------------------------------------------------------------------------
// File: DXTKResouces.h
//
// A wrapper for the DirectXTK
//
// Date: 2017.4.1
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "Singleton.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "SpriteFont.h"
#include "CommonStates.h"

//////////////////////////////
// グローバル変数			//
//////////////////////////////

namespace DXTK
{
	class DXTKResources : public Singleton<DXTKResources>
	{
	public:
		void Initializer(ID3D11Device* device, ID3D11DeviceContext* context);

		void UpdateInputState();

		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;

		// キーボード関係
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;

		// マウス関係
		std::unique_ptr<DirectX::Mouse> m_mouse;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;

		// コモンステート
		std::unique_ptr<DirectX::CommonStates> m_states;

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		// スプライトフォント
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	private:
		friend class Singleton<DXTKResources>;

		// コンストラクタ
		DXTKResources();
	};
}


