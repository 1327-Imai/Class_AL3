#include "Enemy.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>


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

}

////更新処理
//void Enemy::Update() {
//	//worldTransformの更新
//	Myfunc::UpdateWorldTransform(worldTransform_);
//}