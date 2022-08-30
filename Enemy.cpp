#include "Enemy.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>


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

}

////�X�V����
//void Enemy::Update() {
//	//worldTransform�̍X�V
//	Myfunc::UpdateWorldTransform(worldTransform_);
//}