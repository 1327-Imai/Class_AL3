#include "Enemy.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

#include "Myfunc.h"

class Player {
public:
	Vector3 GetWorldPosition();
};

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

//メンバ関数の定義
//初期化
void Enemy::Initialize(Model* model , Vector3 translation , int leaveWay) {

	//nullポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	textureHandle_ = TextureManager::Load("orange.png");

	//ワールド変換の初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = translation;
	worldTransform_.scale_ = {2 , 2 , 2};

	leaveWay_ = leaveWay;

	hp_ = 5;
}

//更新処理
void Enemy::Update() {
	move_ = {0.0f , 0.0f , 0.0f};

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
	Approach();
	break;

	case Enemy::Phase::Stay:
	Stay();
	break;

	case Enemy::Phase::Leave:
	Leave();
	break;
	}

	if (isAtack_ == true) {
		ShotBullet();
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {

		return bullet->IsDead();

					   });

	//worldTransformの更新
	Myfunc::UpdateWorldTransform(worldTransform_);
}

//描画処理
void Enemy::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewprojection);
	}
}

//接近フェーズの関数
void Enemy::Approach() {
	//移動(ベクトルを加算)
	move_.z -= 0.1f;
	worldTransform_.translation_ += move_;
	//既定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 50.0f) {

		moveTimer = 5 * 60;
		isAtack_ = true;
		phase_ = Phase::Stay;
	}
}

void Enemy::Stay() {
	moveTimer--;
	if (moveTimer <= 0) {
		moveTimer = 10 * 60;
		isAtack_ = false;
		phase_ = Phase::Leave;
	}
}

//離脱フェーズの関数
void Enemy::Leave() {

	//移動(ベクトルを加算)
	if (leaveWay_ == UP) {
		move_.y += 0.2f;
	}
	else if (leaveWay_ == DOWN) {
		move_.y -= 0.2f;
	}
	else if (leaveWay_ == RIGHT) {
		move_.x += 0.2f;
	}
	else if (leaveWay_ == LEFT) {
		move_.x -= 0.2f;
	}

	worldTransform_.translation_ += move_;

	moveTimer--;
	if (moveTimer <= 0) {
		isDead_ = true;
	}

}

//弾の発射
void Enemy::ShotBullet() {

	if (bulletTimer_-- <= 0) {
		assert(player_);

		//弾の速度
		const float kBulletSpeed = 1.0f;

		Vector3 playerWorldPos = player_->GetWorldPosition();
		Vector3 enemyWorldPos = GetWorldPosition();

		Vector3 angle = playerWorldPos;
		angle -= enemyWorldPos;

		Vector3 velocity = {
			angle.x / sqrt(angle.x * angle.x + angle.y * angle.y + angle.z * angle.z) * kBulletSpeed ,
			angle.y / sqrt(angle.x * angle.x + angle.y * angle.y + angle.z * angle.z) * kBulletSpeed ,
			angle.z / sqrt(angle.x * angle.x + angle.y * angle.y + angle.z * angle.z) * kBulletSpeed ,
		};

		//敵の位置をコピー
		Vector3 position = worldTransform_.translation_;

		//弾を生成し初期化
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(model_ , position , velocity);

		//弾を登録する
		bullets_.push_back(std::move(newBullet));

		bulletTimer_ = kBulletCT;
	}
}

//衝突判定
void Enemy::Oncollision() {

	hp_--;
	if (hp_ <= 0) {
		isDead_ = true;
	}

}

void Enemy::SetPlayer(Player* player) {
	player_ = player;
}

Vector3 Enemy::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}