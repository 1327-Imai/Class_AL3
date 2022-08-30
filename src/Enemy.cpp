#include "Enemy.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

#include "Myfunc.h"

//�����o�֐��̒�`
//������
void Enemy::Initialize(Model* model , uint32_t textureHandle) {

	//null�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	worldTransform_.translation_.y = 2;
	worldTransform_.translation_.z = 10;

}

//�X�V����
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

	ShotBullet();
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
	move_.z -= 0.1;
	worldTransform_.translation_ += move_;
	//����̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

//���E�t�F�[�Y�̊֐�
void Enemy::Leave() {
	//�ړ�(�x�N�g�������Z)
	move_.x -= 0.1;
	move_.y += 0.1;
	worldTransform_.translation_ += move_;
}

//�e�̔���
void Enemy::ShotBullet() {

	if (bulletTimer_-- <= 0) {
		//�e�̑��x
		const float kBulletSpeed = -1.0f;
		Vector3 velocity(0 , 0 , kBulletSpeed);

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