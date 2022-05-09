#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	DebugCamera* debugCamera_ = nullptr;

	const double PI = 3.141592;

	Vector3 vertex[8] = {
		{10.0f , 10.0f , 10.0f} ,
		{10.0f , 20.0f , 10.0f} ,
		{20.0f , 20.0f , 10.0f} ,
		{20.0f , 10.0f , 10.0f} ,
		{10.0f , 10.0f , 20.0f} ,
		{10.0f , 20.0f , 20.0f} ,
		{20.0f , 20.0f , 20.0f} ,
		{20.0f , 10.0f , 20.0f} ,
	};

	Vector3 boxMoved[8];
	Vector3 boxRotatedX[8];
	Vector3 boxRotatedY[8];
	Vector3 boxRotatedZ[8];
	Vector3 boxEnlarged[8];

	int edgeList[12][2] = {
		{0 , 1} ,
		{1 , 2} ,
		{2 , 3} ,
		{3 , 0} ,
		{0 , 4} ,
		{1 , 5} ,
		{2 , 6} ,
		{3 , 7} ,
		{4 , 5} ,
		{5 , 6} ,
		{6 , 7} ,
		{7 , 4} ,
	};

	float transrateX = 10.0f;
	float transrateY = 10.0f;
	float transrateZ = 10.0f;
	float scaleX = 2.0f;
	float scaleY = 2.0f;
	float scaleZ = 2.0f;
	float angleX = -PI / 4;
	float angleY = PI / 4;
	float angleZ = PI / 6;


	Matrix4 affineTransrate = {
		1.0f , 0.0f , 0.0f , transrateX ,
		0.0f , 1.0f , 0.0f , transrateY ,
		0.0f , 0.0f , 1.0f , transrateZ ,
		0.0f , 0.0f , 0.0f , 1.0f};

	Matrix4 affineRotationX = {
		1.0f , 0.0f , 0.0f , 0.0f ,
		0.0f , cos(angleX) , -sin(angleX) , 0.0f ,
		0.0f , sin(angleX) , cos(angleX) , 0.0f ,
		0.0f , 0.0f , 0.0f , 1.0f
	};

	Matrix4 affineRotationY = {
		cos(angleY) , 0.0f , sin(angleY) , 0.0f ,
		0.0f , 1.0f , 0.0f , 0.0f ,
		-sin(angleY) , 0.0f , cos(angleY) , 0.0f ,
		0.0f , 0.0f , 0.0f , 1.0f
	};

	Matrix4 affineRotationZ = {
		cos(angleZ) , -sin(angleZ) , 0.0f , 0.0f ,
		sin(angleZ) , cos(angleZ) , 0.0f , 0.0f ,
		0.0f , 0.0f , 1.0f , 0.0f ,
		0.0f , 0.0f , 0.0f , 1.0f
	};

	Matrix4 affineScale = {
		scaleX , 0.0f , 0.0f , 0.0f ,
		0.0f , scaleY , 0.0f , 0.0f ,
		0.0f , 0.0f , scaleZ , 0.0f ,
		0.0f , 0.0f , 0.0f , 1.0f
	};

	Vector3 distanceFromOrigin = {0 , 0 , 0};

	const Vector4 WHITE = {255 , 255 , 255 , 255};
	const Vector4 RED = {255 , 0 , 0 , 255};
	const Vector4 YELLOW = {255 , 255 , 0 , 255};
	const Vector4 PURPLE = {255 , 0 , 255 , 255};
	const Vector4 GREEN = {0 , 255 , 0 , 255};
	const Vector4 BLUE = {0 , 0 , 255 , 255};

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
