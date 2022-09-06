#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

#include <memory>
#include <list>

#include "PlayerBullet.h"
#include "PlayerShield.h"

class Player {

public:

	//コンストラクタの宣言
	Player();

	//デストラクタの宣言
	~Player();

	//メンバ関数の宣言
	//初期化
	void Initialize(Model* model);

	//更新処理
	void Update(ViewProjection viewProjection);

	//描画処理
	void Draw(ViewProjection viewprojection);

	void DrawUI();

	//衝突判定
	void Oncollision();

	void ShieldOncollision(int shieldNum);

private:
	//移動処理
	void Move();

	//回転処理
	void Rotate();

	//弾の発射
	void ShotBullet();

	void CalShieldPos(int shieldNum);

	//アクセッサ
public:
	Vector3 GetWorldPosition();

	Vector3 GetShieldWorldPosition(int shieldNum);

	WorldTransform* GetWorldTransform() {
		return &worldTransform_;
	}

	bool GetIsPlayerShieldBrake(int shieldNum);

	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() {
		return bullets_;
	}

	//メンバ変数
private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	WorldTransform worldTransform3DReticle_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandleReticle_ = 0u;

	//2Dレティクル用スプライト
	std::unique_ptr<Sprite> sprite2DReticle_;

	//Input
	Input* input_;

	//DebugText
	DebugText* debugText_;

	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	//発射レート
	static const int32_t kBulletCT = 10;

	//デスタイマー
	int32_t bulletTimer_ = kBulletCT;

	int rotatoValueX_ = 0;

	int rotatoValueY_ = 0;

	//シールド
	const int shieldNum_ = 6;

	const float distans2Shield = 2;

	const float distance2Reticle = 25.0f;

	int forwardShieldNum = 0;

	PlayerShield* playerShield_[6] = {nullptr};

	bool isAlive = true;

};

