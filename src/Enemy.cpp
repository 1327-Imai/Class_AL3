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

//�����o�֐��̒�`
//������
void Enemy::Initialize(Model* model , Vector3 translation , int leaveWay) {

	//null�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	textureHandle_ = TextureManager::Load("orange.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	worldTransform_.translation_ = translation;
	worldTransform_.scale_ = {2 , 2 , 2};

	leaveWay_ = leaveWay;

	hp_ = 5;
}

//�X�V����
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

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {

		return bullet->IsDead();

					   });

	//worldTransform�̍X�V
	Myfunc::UpdateWorldTransform(worldTransform_);
}

//�`�揈��
void Enemy::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewprojection);
	}
}

//�ڋ߃t�F�[�Y�̊֐�
void Enemy::Approach() {
	//�ړ�(�x�N�g�������Z)
	move_.z -= 0.1f;
	worldTransform_.translation_ += move_;
	//����̈ʒu�ɓ��B�����痣�E
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

//���E�t�F�[�Y�̊֐�
void Enemy::Leave() {

	//�ړ�(�x�N�g�������Z)
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

//�e�̔���
void Enemy::ShotBullet() {

	if (bulletTimer_-- <= 0) {
		assert(player_);

		//�e�̑��x
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

		//�G�̈ʒu���R�s�[
		Vector3 position = worldTransform_.translation_;

		//�e�𐶐���������
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(model_ , position , velocity);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));

		bulletTimer_ = kBulletCT;
	}
}

//�Փ˔���
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