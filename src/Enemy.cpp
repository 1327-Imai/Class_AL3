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
	worldTransform_.translation_.z = 100;
}

//更新処理
void Enemy::Update() {

	worldTransform_.translation_.z -=0.5;

	//worldTransformの更新
	Myfunc::UpdateWorldTransform(worldTransform_);
}

//描画処理
void Enemy::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

}
