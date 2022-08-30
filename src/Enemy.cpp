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

	//worldTransform�̍X�V
	Myfunc::UpdateWorldTransform(worldTransform_);
}

//�`�揈��
void Enemy::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

}

void Enemy::Approach() {
	//�ړ�(�x�N�g�������Z)
	move_.z -= 0.1f;
	worldTransform_.translation_ += move_;
	//����̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	//�ړ�(�x�N�g�������Z)
	move_.x -= 0.1f;
	move_.y += 0.1f;
	worldTransform_.translation_ += move_;
}