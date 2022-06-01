#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

//�R���X�g���N�^�̒�`
Player::Player() {

}

//�f�X�g���N�^�̒�`
Player::~Player() {

}

//�����o�֐��̒�`
//������
void Player::Initialize(Model* model , uint32_t textureHandle) {

	//null�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

}

//�X�V����
void Player::Update() {

	const float speed = 4.0f;
	Vector3 move = {0 , 0 , 0};

	//�ړ��x�N�g����ύX���鏈��
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

	//���W�ړ�
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	//�s��̍X�V
	worldTransform_.TransferMatrix();

}

//�`�揈��
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