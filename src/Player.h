#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

#include <memory>
#include <list>

#include "PlayerBullet.h"

class Player {

public:

	//コンストラクタの宣言
	Player();

	//デストラクタの宣言
	~Player();

	//メンバ関数の宣言
	//初期化
	void Initialize(Model* model , uint32_t textureHandle);

	//更新処理
	void Update();

	//描画処理
	void Draw(ViewProjection viewprojection);

	//移動処理
	void Move();

	//回転処理
	void Rotate();

	//弾の発射
	void ShotBullet();

	//メンバ変数
private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//Input
	Input* input_;

	//DebugText
	DebugText* debugText_;

	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};

