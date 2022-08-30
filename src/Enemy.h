#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

class Enemy {
public:

	//メンバ関数の宣言
	//初期化
	void Initialize(Model* model , uint32_t textureHandle);

	//更新処理
	void Update();

	//描画処理
	void Draw(ViewProjection viewprojection);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//移動ベクトル
	Vector3 move_ = {0.0f , 0.0f , 0.0f};
};

