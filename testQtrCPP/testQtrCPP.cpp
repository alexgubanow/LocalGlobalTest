// testQtrCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "SimpleMath.h"
#include "Stopwatch.h"

#include <chrono>  // for high_resolution_clock
#include <stdio.h>
#include <conio.h>
#include "dcm_t.h"
#include "dcm_Matrix.hpp"

using namespace DirectX;
using namespace DirectX::SimpleMath;

static void CalcDCM(Vector3 rV, Vector3 radiusPoint, float a, Vector3& gFn)
{
	dcm_t dcm(rV, radiusPoint);
	Vector3 lv(0, a, 0);
	dcm.ToGlob(lv, gFn);

	//Vector3 gv = new Vector3() { X = 60.3228f, Y = 20.1210f };
	//Vector3 lBpUx = new Vector3();
	//dcm.ToLoc(gv, ref lBpUx);
}
static void CalcDCMmatrix(Vector3 rV, Vector3 radiusPoint, float a, Vector3& gFn)
{
	dcm_Matrix dcm(rV, radiusPoint);
	Vector3 lv(0, a, 0);
	dcm.ToGlob(lv, gFn);

	//Vector3 gv = new Vector3() { X = 60.3228f, Y = 20.1210f };
	//Vector3 lBpUx = new Vector3();
	//dcm.ToLoc(gv, ref lBpUx);
}
static void CalcQTR(Vector3 rV, Vector3 rLocV, float a, Vector3& globVq)
{
	/*rV.Normalize();
	float halfCosAngle = 0.5f * rV.Dot(rLocV);
	Quaternion q(sqrtf(0.5f + halfCosAngle), sqrtf(0.5f - halfCosAngle), 0, 0);*/


	Quaternion q(rV.Length() + rV.x, rV.y, 0, 0);
	q.Normalize();
	Vector3 lv(0, a, 0);

	globVq = Vector3::Transform(lv, q);


	/*float cosXa = rV.x / rV.Length();
	Quaternion q(cosf(acosf(cosXa) / 2), sinf(acosf(cosXa) / 2), 0, 0);

	Vector3 lv(63.59f + a, 0, 0);

	globVq = Vector3::Transform(lv, q);*/

	//Quaternion qr = Quaternion.Negate(q);
	//Vector3 gv = new Vector3() { X = 60.3228f, Y = 20.1210f };
	//Vector3 locVq = Vector3.Transform(globVq, qr);
}

int main()
{
	//double iter = 1;
	double iter = 1E5;
	Vector3 rV(14.2982f, -47.9282f, 0);
	Vector3 radiusPoint(19.1802f, 5.7016f, 0);
	//Vector3 globVq;
	Vector3 gFn;
	Vector3 gFnMatrix;
	for (int i = 0; i < 5; i++)
	{
		CalcDCM(rV, radiusPoint, 30, gFn);
		CalcDCMmatrix(rV, radiusPoint, 30, gFn);
		//CalcQTR(rV, rLocV, i / 1E3f, globVq);
	}
	for (size_t k = 1; k < 4; k++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < iter; i++)
		{
			CalcDCM(rV, radiusPoint, 30, gFn);
		}
		auto finish = std::chrono::high_resolution_clock::now();
		std::cout << k << ": dcm: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms\n";
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < iter; i++)
		{
			CalcDCMmatrix(rV, radiusPoint, 30, gFnMatrix);
		}
		finish = std::chrono::high_resolution_clock::now();
		std::cout << k << ": dcm_Matrix: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms\n";
		//start = std::chrono::high_resolution_clock::now();
		//for (int i = 0; i < iter; i++)
		//{
		//	CalcQTR(rV, rLocV, i / 1E3f, globVq);

		//	/*rV.Normalize();
		//	float halfCosAngle = 0.5f * rV.Dot(rLocV);
		//	Quaternion q(sqrtf(0.5f + halfCosAngle), sqrtf(0.5f - halfCosAngle), 0, 0);
		//	Vector3 lv(63.59f + i / 1E3, 0, 0);

		//	globVq = Vector3::Transform(lv, q);*/
		//}
		//finish = std::chrono::high_resolution_clock::now();
		//std::cout << k << ": qtr: "
		//	<< std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms\n";
	}
	std::cout << "gFn.x: " << gFn.x << "\n";
	std::cout << "gFn.y: " << gFn.y << "\n";
	std::cout << "gFn.z: " << gFn.z << "\n";
	std::cout << "\n";
	std::cout << "gFnMatrix.x: " << gFnMatrix.x << "\n";
	std::cout << "gFnMatrix.y: " << gFnMatrix.y << "\n";
	std::cout << "gFnMatrix.z: " << gFnMatrix.z << "\n";
	//std::cout << "globVq.x: " << globVq.x << "\n";
	int ch;
	printf("Press any key to exit...\n");
	ch = _getch();
}
