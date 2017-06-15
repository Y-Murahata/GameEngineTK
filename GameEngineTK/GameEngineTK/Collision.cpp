#include "pch.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;


//	���Q�̓����蔻��
//	argument:	sphereA , SphereB
//	return: yes/no
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//	��A��B�̒��S���W���v�Z����
	Vector3 sub = sphereB.Center - sphereA.Center;

	//	�O�����̒藝�Ńx�N�g���̒������v�Z����
	//	�����x�N�g���̒����͂Q�_�Ԃ̋���
	float distanceSquare;

	distanceSquare = sub.x * sub.x + sub.y*sub.y + sub.z * sub.z;

	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//	������傫����Γ������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}