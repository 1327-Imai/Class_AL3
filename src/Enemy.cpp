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
	worldTransform_.translation_.z = 100;
}

//�X�V����
void Enemy::Update() {

	worldTransform_.translation_.z -=0.5;

	//worldTransform�̍X�V
	Myfunc::UpdateWorldTransform(worldTransform_);
}

//�`�揈��
void Enemy::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

}
