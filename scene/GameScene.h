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

	const Vector4 WHITE = {255 , 255 , 255 , 255};

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
