#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

#include <memory>
#include <list>

#include "EnemyBullet.h"

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
	//接近フェーズの関数
	void Approach();

	//離脱フェーズの関数
	void Leave();

	//弾の発射
	void ShotBullet();

	//メンバ変数
private:
	enum class Phase {
		Approach ,	//接近する
		Leave ,		//離脱する
	};

	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//移動ベクトル
	Vector3 move_ = {0.0f,0.0f,0.0f};

	Phase phase_ = Phase::Approach;

	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//発射レート
	static const int32_t kBulletCT = 60;

	//デスタイマー
	int32_t bulletTimer_ = kBulletCT;
};

