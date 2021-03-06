﻿
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "SimpleMath.h"

class dcm_t
{
	float Xx;
	float Yx;
	float Zx;

	float Xy;
	float Yy;
	float Zy;

	float Xz;
	float Yz;
	float Zz;
public:
	dcm_t(DirectX::SimpleMath::Vector3 endPoint, DirectX::SimpleMath::Vector3 radiusPoint)
	{
		float el = endPoint.Length();
		float rl = radiusPoint.Length();
		Xx = endPoint.x / el;
		Yx = endPoint.y / el;
		Zx = endPoint.z / el;

		Xy = radiusPoint.x / rl;
		Yy = radiusPoint.y / rl;
		Zy = radiusPoint.z / rl;

		Xz = Yx * Zy - Zx * Yy;
		Yz = 0 - (Xx * Zy - Zx * Xy);
		Zz = Xx * Yy - Yx * Xy;
	};

	void ToGlob(DirectX::SimpleMath::Vector3 Lp, DirectX::SimpleMath::Vector3&gA)
	{
		gA.x = Xx * Lp.x + Xy * Lp.y + Xz * Lp.z;
		gA.y = Yx * Lp.x + Yy * Lp.y + Yz * Lp.z;
		gA.z = Zx * Lp.x + Zy * Lp.y + Zz * Lp.z;
	};

	void ToLoc(DirectX::SimpleMath::Vector3 Gp, DirectX::SimpleMath::Vector3&lA)
	{
		lA.x = Xx * Gp.x + Yx * Gp.y + Zx * Gp.z;
		lA.y = Xy * Gp.x + Yy * Gp.y + Zy * Gp.z;
		lA.z = Xz * Gp.x + Yz * Gp.y + Zz * Gp.z;
	};
};