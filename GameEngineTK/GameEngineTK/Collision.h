//	�Փ˔��胉�C�u����
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>


//	��
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	//�@���S���W
	float Radius;	//	���a

	//	�R���X�g���N�^
	Sphere()
	{
		Radius = 1.0f;
	}
};

//	����
class Segment
{
public:
	DirectX::SimpleMath::Vector3	Start;
	DirectX::SimpleMath::Vector3	End;

};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
