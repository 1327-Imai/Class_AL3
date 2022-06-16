#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

#include "Myfunc.h"

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

	//�v���C���[�̈ړ����x��ݒ�
	const float speed = 0.5f;

	//�v���C���[�̈ړ��x�N�g��
	Vector3 move = {0 , 0 , 0};

	//�ړ����E���W
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	//�L�[���͂ɂ��ړ�����
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

	//���W�ړ�
	worldTransform_.translation_ += move;

	//�ړ����E�𒴂��Ȃ��悤�ɂ��鏈��
	worldTransform_.translation_.x = max(worldTransform_.translation_.x , -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x , +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y , -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y , +kMoveLimitY);

	//worldTransform�̍X�V
	Myfunc::UpdateWorldTransform(worldTransform_);

}

//�`�揈��
void Player::Draw(ViewProjection viewprojection) {

	model_->Draw(worldTransform_ , viewprojection , textureHandle_);

	//�f�o�b�O�\��
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