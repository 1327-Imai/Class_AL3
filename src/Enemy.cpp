#include "Enemy.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

#include "Myfunc.h"

//メンバ関数の定義
//初期化
void Enemy::Initialize(Model* model , uint32_t textureHandle) {

	//nullポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	worldTransform_.translation_.y = 2;
	worldTransform_.translation_.z = 10;

}

//更新処理
void Enemy::Update() {
	move_ = {0.0f , 0.0f , 0.0f};

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
	Approach();
	break;

	case Enemy::Phase::Leave:
	Leave();
	break;
	}

	//worldTransformの更新
	Myfunc::UpdateWorldTransform(worldTransform_);
}

//描画処理
void Enemy::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

}

void Enemy::Approach() {
	//移動(ベクトルを加算)
	move_.z -= 0.1f;
	worldTransform_.translation_ += move_;
	//既定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	//移動(ベクトルを加算)
	move_.x -= 0.1f;
	move_.y += 0.1f;
	worldTransform_.translation_ += move_;
}