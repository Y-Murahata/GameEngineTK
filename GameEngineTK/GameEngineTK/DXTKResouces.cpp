//--------------------------------------------------------------------------------------
// File: DirectXTK.cpp
//
// A wrapper for the DirectXTK
//
// Date: 2017.4.1
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DXTKResouces.h"

using namespace DirectX;

DXTK::DXTKResources::DXTKResources()
{
	m_keyboard = std::make_unique<Keyboard>();
	m_keyTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	m_mouse = std::make_unique<Mouse>();
	m_mouseTracker = std::make_unique<Mouse::ButtonStateTracker>();
}

void DXTK::DXTKResources::Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_device = device;
	m_context = context;

	// �R�����X�e�[�g���쐬
	m_states = std::make_unique<CommonStates>(device);

	// �X�v���C�g�o�b�`
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	// �X�v���C�g�t�H���g
	m_spriteFont = std::make_unique<SpriteFont>(device, L"myfile.spritefont");
}

void DXTK::DXTKResources::UpdateInputState()
{
	// �L�[���͏����擾
	Keyboard::State key = m_keyboard->GetState();
	m_keyTracker->Update(key);

	// �}�E�X�����擾
	Mouse::State mouse = m_mouse->GetState();
	m_mouseTracker->Update(mouse);
}
