//	衝突判定ライブラリ
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>


//	球
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	//　中心座標
	float Radius;	//	半径

	//	コンストラクタ
	Sphere()
	{
		Radius = 1.0f;
	}
};

//	線分
class Segment
{
public:
	DirectX::SimpleMath::Vector3	Start;
	DirectX::SimpleMath::Vector3	End;

};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
