#include "pch.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;


//	球２つの当たり判定
//	argument:	sphereA , SphereB
//	return: yes/no
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//	球AとBの中心座標を計算する
	Vector3 sub = sphereB.Center - sphereA.Center;

	//	三平方の定理でベクトルの長さを計算する
	//	差分ベクトルの長さは２点間の距離
	float distanceSquare;

	distanceSquare = sub.x * sub.x + sub.y*sub.y + sub.z * sub.z;

	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//	判定より大きければ当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}