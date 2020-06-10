#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "SimpleMath.h"

class dcm_Matrix
{
	DirectX::SimpleMath::Matrix _dcm;
public:
	dcm_Matrix(DirectX::SimpleMath::Vector3 endPoint, DirectX::SimpleMath::Vector3 radiusPoint)
	{
		float el = endPoint.Length();
		float rl = radiusPoint.Length();
		DirectX::SimpleMath::Vector3 cosx = endPoint / el;
		DirectX::SimpleMath::Vector3 cosy = radiusPoint / rl;
		_dcm = DirectX::SimpleMath::Matrix(cosx, cosy,
			{
				cosx.y * cosy.z - cosx.z * cosy.y,
				-(cosx.x * cosy.z - cosx.z * cosy.x),
				cosx.x * cosy.y - cosx.y * cosy.x
			}
		);


		/*Xx = endPoint.x / el;
		Yx = endPoint.y / el;
		Zx = endPoint.z / el;

		Xy = radiusPoint.x / rl;
		Yy = radiusPoint.y / rl;
		Zy = radiusPoint.z / rl;

		Xz = Yx * Zy - Zx * Yy;
		Yz = 0 - (Xx * Zy - Zx * Xy);
		Zz = Xx * Yy - Yx * Xy;*/
	};

	void ToGlob(DirectX::SimpleMath::Vector3 Lp, DirectX::SimpleMath::Vector3& gA)
	{
		DirectX::SimpleMath::Vector3::Transform(Lp, _dcm, gA);
		/*gA.x = Xx * Lp.x + Xy * Lp.y + Xz * Lp.z;
		gA.y = Yx * Lp.x + Yy * Lp.y + Yz * Lp.z;
		gA.z = Zx * Lp.x + Zy * Lp.y + Zz * Lp.z;*/
	};

	void ToLoc(DirectX::SimpleMath::Vector3 Gp, DirectX::SimpleMath::Vector3& lA)
	{
		/*lA.x = Xx * Gp.x + Yx * Gp.y + Zx * Gp.z;
		lA.y = Xy * Gp.x + Yy * Gp.y + Zy * Gp.z;
		lA.z = Xz * Gp.x + Yz * Gp.y + Zz * Gp.z;*/
	};
};