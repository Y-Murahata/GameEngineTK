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

// �@���t���O�p�`�i�����v��肪�\�ʁj
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// �@���x�N�g��
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3 & _point, const Triangle & _triangle);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _tri, DirectX::SimpleMath::Vector3 * _inter);

bool CheckSegment2Triangle(const Segment & _segment, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);
