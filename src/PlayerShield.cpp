#include "PlayerShield.h"
#include <cassert>

#include "Myfunc.h"

PlayerShield::PlayerShield() {

}

PlayerShield::~PlayerShield() {

}

void PlayerShield::Initialize(Model* model) {

	//nullポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	worldTransform_.scale_ = {1.5 , 1.5 , 0.5};

	hp_ = 3;
}

void PlayerShield::Update() {
	Myfunc::UpdateWorldTransform(worldTransform_);

	if (hp_ == 3) {
		textureHandle_ = TextureManager::Load("white.png");
	}
	else if (hp_ == 2) {
		textureHandle_ = TextureManager::Load("cyan.png");
	}
	else if (hp_ <= 1) {
		textureHandle_ = TextureManager::Load("blue.png");
	}
}

void PlayerShield::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);
}

void PlayerShield::SetTranslation(Vector3 translation) {
	worldTransform_.translation_ = translation;
}

void PlayerShield::SetRotation(Vector3 rotation) {
	worldTransform_.rotation_ = rotation;
}

void PlayerShield::SetParent(WorldTransform* parent) {
	worldTransform_.parent_ = parent;
}

Vector3 PlayerShield::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

WorldTransform PlayerShield::GetWorldTransform() {
	return worldTransform_;
}

//衝突判定
void PlayerShield::Oncollision() {

	hp_--;

	if (hp_ <= 0) {
		isBrake = true;
	}

}