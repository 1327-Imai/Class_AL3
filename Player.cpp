#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

//コンストラクタの定義
Player::Player() {

}

//デストラクタの定義
Player::~Player() {

}

//メンバ関数の定義
//初期化
void Player::Initialize(Model* model , uint32_t textureHandle) {

	//nullポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();

}

//更新処理
void Player::Update() {

	const float speed = 4.0f;
	Vector3 move = {0 , 0 , 0};

	//移動ベクトルを変更する処理
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= speed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += speed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y -= speed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y += speed;
	}

	//座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	//行列の更新
	worldTransform_.TransferMatrix();

}

//描画処理
void Player::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

	debugText_->SetPos(50 , 150);
	debugText_->Printf(
		"worldTransform:(%f,%f,%f)" ,
		worldTransform_.translation_.x ,
		worldTransform_.translation_.y ,
		worldTransform_.translation_.z
	);
	debugText_->SetPos(50 , 165);
	debugText_->Printf(
		"viewprojection:(%f,%f,%f)" ,
		viewprojection.eye.x ,
		viewprojection.eye.y ,
		viewprojection.eye.z
	);
}