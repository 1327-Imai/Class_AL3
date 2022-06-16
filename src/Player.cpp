#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

#include "Myfunc.h"

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

	//プレイヤーの移動速度を設定
	const float speed = 0.5f;

	//プレイヤーの移動ベクトル
	Vector3 move = {0 , 0 , 0};

	//移動限界座標
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	//キー入力による移動処理
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= speed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += speed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += speed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= speed;
	}

	//座標移動
	worldTransform_.translation_ += move;

	//移動限界を超えないようにする処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x , -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x , +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y , -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y , +kMoveLimitY);

	//worldTransformの更新
	Myfunc::UpdateWorldTransform(worldTransform_);

}

//描画処理
void Player::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

	//デバッグ表示
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