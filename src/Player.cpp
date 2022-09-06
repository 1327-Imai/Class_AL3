#include "Player.h"
#include "Input.h"
#include <cassert>

#include "Myfunc.h"

//�R���X�g���N�^�̒�`
Player::Player() {
	input_ = nullptr;
	debugText_ = nullptr;
}

//�f�X�g���N�^�̒�`
Player::~Player() {
	for (int i = 0; i < shieldNum_; i++) {
		delete playerShield_[i];
	}
}

//�����o�֐��̒�`
//������
void Player::Initialize(Model* model) {

	//null�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	textureHandle_ = TextureManager::Load("green.png");
	textureHandleReticle_ = TextureManager::Load("reticle.png");

	//�X�v���C�g����
	sprite2DReticle_.reset(Sprite::Create(
		textureHandleReticle_ ,
		{1280.0f / 2 , 720.0f / 2} ,
		{1 , 1 , 1 , 1} ,
		{0.5f , 0.5f})
	);

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	worldTransform_.translation_.x = 0;
	worldTransform_.translation_.y = 0;

	isAlive = true;

	worldTransform3DReticle_.Initialize();

	rotatoValueX_ = 0;

	rotatoValueY_ = 0;

	//�V�[���h
	for (int i = 0; i < shieldNum_; i++) {
		playerShield_[i] = new PlayerShield();
		playerShield_[i]->Initialize(model);

		playerShield_[i]->SetParent(&worldTransform_);

		playerShield_[i]->SetTranslation({0 , 0 , 0});
		playerShield_[i]->SetRotation({Myfunc::MyMathUtility::Deg2Rad(90) , 0 , 0});
	}
	playerShield_[0]->SetTranslation({-distans2Shield , 0 , 0});
	playerShield_[0]->SetRotation({0 , Myfunc::MyMathUtility::Deg2Rad(90) , 0});

	playerShield_[1]->SetTranslation({0 , distans2Shield , 0});
	playerShield_[1]->SetRotation({Myfunc::MyMathUtility::Deg2Rad(90) , 0 , 0});

	playerShield_[2]->SetTranslation({distans2Shield , 0 , 0});
	playerShield_[2]->SetRotation({0 , Myfunc::MyMathUtility::Deg2Rad(90) , 0});

	playerShield_[3]->SetTranslation({0 , -distans2Shield , 0});
	playerShield_[3]->SetRotation({Myfunc::MyMathUtility::Deg2Rad(90) , 0 , 0});

	playerShield_[4]->SetTranslation({0 , 0 , -distans2Shield});
	playerShield_[4]->SetRotation({0 , 0 , 0});

	playerShield_[5]->SetTranslation({0 , 0 , distans2Shield});
	playerShield_[5]->SetRotation({0 , 0 , 0});


}

//�X�V����
void Player::Update(ViewProjection viewProjection) {

	if (isAlive == true) {
		Move();
		Rotate();

		worldTransform3DReticle_.translation_ = worldTransform_.translation_;
		worldTransform3DReticle_.translation_.z += distance2Reticle;

		//worldTransform�̍X�V
		Myfunc::UpdateWorldTransform(worldTransform_);
		Myfunc::UpdateWorldTransform(worldTransform3DReticle_);

		ShotBullet();
	}

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {

		return bullet->IsDead();

					   });

	for (int i = 0; i < shieldNum_; i++) {
		if (playerShield_[i]->GetIsBrake() == false) {
			playerShield_[i]->Update();
		}
	}

	for (int i = 0; i < shieldNum_; i++) {
		CalShieldPos(i);
	}

	Vector3 positionReticle = worldTransform3DReticle_.translation_;
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x * (1280.0f / 100.0f/2.0f) + 1280.0f / 2 , -positionReticle.y * (720.0f / 56.25f / 2.0f) + 720 / 2));
}

//�`�揈��
void Player::Draw(ViewProjection viewprojection) {

	if (isAlive == true) {

		model_->Draw(worldTransform_ , viewprojection , textureHandle_);

		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Draw(viewprojection);
		}

		for (int i = 0; i < shieldNum_; i++) {
			if (playerShield_[i]->GetIsBrake() == false) {
				playerShield_[i]->Draw(viewprojection);
			}
		}
	}

	//�f�o�b�O�e�L�X�g
	debugText_->SetPos(15 , 15);
	debugText_->Printf(
		"Cubic:ShotingGame"
	);

	if (isAlive == false) {
		debugText_->SetPos(15 , 45);
		debugText_->Printf(
			"Gameover Press [R] to restart."
		);
	}


	debugText_->SetPos(30 , 90);
	debugText_->Printf(
		"[W][A][S][D]:Move"
	);
	debugText_->SetPos(30 , 110);
	debugText_->Printf(
		"[UP_Arrow][Down_Arrow]RotatoX"
	);
	debugText_->SetPos(30 , 130);
	debugText_->Printf(
		"[L_Arrow][R_Arrow]RotatoY"
	);
	debugText_->SetPos(30 , 150);
	debugText_->Printf(
		"[SPACE]ShotBullet"
	);

}

void Player::DrawUI() {
	sprite2DReticle_->Draw();
}

//�ړ�����
void Player::Move() {
	//�v���C���[�̈ړ����x��ݒ�
	const float speed = 0.5f;

	//�v���C���[�̈ړ��x�N�g��
	Vector3 move = {0 , 0 , 0};

	//�ړ����E���W
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	//�L�[���͂ɂ��ړ�����
	if (input_->PushKey(DIK_A)) {
		move.x -= speed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += speed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y += speed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= speed;
	}

	//���W�ړ�
	worldTransform_.translation_ += move;

	//�ړ����E�𒴂��Ȃ��悤�ɂ��鏈��
	worldTransform_.translation_.x = max(worldTransform_.translation_.x , -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x , +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y , -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y , +kMoveLimitY);

}

//��]����
void Player::Rotate() {
	//�v���C���[�̉�]���x��ݒ�
	const float rotationSpeed = Myfunc::MyMathUtility::Deg2Rad(5.0f);

	//�v���C���[�̉�]�x�N�g��
	Vector3 rotation = {0 , 0 , 0};

	//��]���E

	//�L�[���͂ɂ���]����
	if (input_->TriggerKey(DIK_LEFT) || input_->TriggerKey(DIK_RIGHT)) {
		if (input_->TriggerKey(DIK_LEFT)) {
			rotatoValueY_ -= 90;

		}

		if (input_->TriggerKey(DIK_RIGHT)) {
			rotatoValueY_ += 90;

		}
	}

	if (input_->TriggerKey(DIK_UP) || input_->TriggerKey(DIK_DOWN)) {
		if (input_->TriggerKey(DIK_UP)) {
			rotatoValueX_ += 90;
		}
		if (input_->TriggerKey(DIK_DOWN)) {
			rotatoValueX_ -= 90;
		}
	}

	if (0 < rotatoValueX_) {
		rotation.x += rotationSpeed;
		rotatoValueX_ -= (int)Myfunc::MyMathUtility::Rad2Deg(rotationSpeed);

		if (rotatoValueX_ <= 0) {
			rotatoValueX_ = 0;
		}
	}
	else if (rotatoValueX_ < 0) {
		rotation.x -= rotationSpeed;
		rotatoValueX_ += (int)Myfunc::MyMathUtility::Rad2Deg(rotationSpeed);

		if (0 <= rotatoValueX_) {
			rotatoValueX_ = 0;
		}

	}

	if (0 < rotatoValueY_) {
		rotation.y += rotationSpeed;
		rotatoValueY_ -= (int)Myfunc::MyMathUtility::Rad2Deg(rotationSpeed);

		if (rotatoValueY_ < 0) {
			rotatoValueY_ = 0;
		}

	}
	else if (rotatoValueY_ < 0) {
		rotation.y -= rotationSpeed;
		rotatoValueY_ += (int)Myfunc::MyMathUtility::Rad2Deg(rotationSpeed);


		if (0 <= rotatoValueY_) {
			rotatoValueY_ = 0;
		}
	}

	//��]
	worldTransform_.rotation_ += rotation;

	if (Myfunc::MyMathUtility::Rad2Deg(worldTransform_.rotation_.x) <= -360 ||
		360 <= Myfunc::MyMathUtility::Rad2Deg(worldTransform_.rotation_.x)) {
		worldTransform_.rotation_.x = 0;
	}
	if (Myfunc::MyMathUtility::Rad2Deg(worldTransform_.rotation_.y) <= -360 ||
		360 <= Myfunc::MyMathUtility::Rad2Deg(worldTransform_.rotation_.y)) {
		worldTransform_.rotation_.y = 0;
	}
}

//�e�̔���
void Player::ShotBullet() {

	if (input_->PushKey(DIK_SPACE)) {

		if (bulletTimer_-- <= 0) {
			//�e�̑��x
			const float kBulletSpeed = 1.0f;
			Vector3 velocity(0 , 0 , kBulletSpeed);

			//���L�����̈ʒu���R�s�[
			Vector3 position = worldTransform_.translation_;

			//�e�𐶐���������
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(model_ , position , velocity);

			//�e��o�^����
			bullets_.push_back(std::move(newBullet));

			bulletTimer_ = kBulletCT;
		}
	}

}

//�Փ˔���
void Player::Oncollision() {
	isAlive = false;
}

void Player::ShieldOncollision(int shieldNum) {
	if (playerShield_[shieldNum]->GetIsBrake() == false) {
		playerShield_[shieldNum]->Oncollision();
	}
}

Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

Vector3 Player::GetShieldWorldPosition(int shieldNum) {
	Vector3 worldPos;

	if (shieldNum == 0) {

		worldPos.x = distans2Shield * -cos(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * sin(worldTransform_.rotation_.z);
		worldPos.z = distans2Shield * sin(worldTransform_.rotation_.y);


	}

	else if (shieldNum == 1) {

		worldPos.x = distans2Shield * sin(worldTransform_.rotation_.x) * -sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * cos(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * -sin(worldTransform_.rotation_.x);

	}

	else if (shieldNum == 2) {

		worldPos.x = distans2Shield * cos(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * sin(worldTransform_.rotation_.z);
		worldPos.z = distans2Shield * -sin(worldTransform_.rotation_.y);

	}

	else if (shieldNum == 3) {

		worldPos.x = distans2Shield * sin(worldTransform_.rotation_.x) * sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * -cos(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * sin(worldTransform_.rotation_.x);

	}

	else if (shieldNum == 4) {

		worldPos.x = distans2Shield * cos(worldTransform_.rotation_.x) * -sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * -sin(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * -cos(worldTransform_.rotation_.x);

	}

	else if (shieldNum == 5) {

		worldPos.x = distans2Shield * cos(worldTransform_.rotation_.x) * sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * sin(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * cos(worldTransform_.rotation_.x);
	}

	worldPos.x += worldTransform_.translation_.x;
	worldPos.y += worldTransform_.translation_.y;
	worldPos.z += worldTransform_.translation_.z;

	return worldPos;

}

bool Player::GetIsPlayerShieldBrake(int shieldNum) {
	return playerShield_[shieldNum]->GetIsBrake();
}

void Player::CalShieldPos(int shieldNum) {
	if (shieldNum == 0) {
		Vector3 worldPos;

		worldPos.x = distans2Shield * -cos(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * sin(worldTransform_.rotation_.z);
		worldPos.z = distans2Shield * sin(worldTransform_.rotation_.y);

		if (distans2Shield <= worldPos.z) {
			forwardShieldNum = shieldNum;
		}
	}

	else if (shieldNum == 1) {
		Vector3 worldPos;

		worldPos.x = distans2Shield * sin(worldTransform_.rotation_.x) * -sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * cos(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * -sin(worldTransform_.rotation_.x);

		if (distans2Shield <= worldPos.z) {
			forwardShieldNum = shieldNum;
		}
	}

	else if (shieldNum == 2) {
		Vector3 worldPos;

		worldPos.x = distans2Shield * cos(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * sin(worldTransform_.rotation_.z);
		worldPos.z = distans2Shield * -sin(worldTransform_.rotation_.y);

		if (distans2Shield <= worldPos.z) {
			forwardShieldNum = shieldNum;
		}
	}

	else if (shieldNum == 3) {
		Vector3 worldPos;

		worldPos.x = distans2Shield * sin(worldTransform_.rotation_.x) * sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * -cos(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * sin(worldTransform_.rotation_.x);

		if (distans2Shield <= worldPos.z) {
			forwardShieldNum = shieldNum;
		}
	}

	else if (shieldNum == 4) {
		Vector3 worldPos;

		worldPos.x = distans2Shield * cos(worldTransform_.rotation_.x) * -sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * -sin(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * -cos(worldTransform_.rotation_.x);

		if (distans2Shield <= worldPos.z) {
			forwardShieldNum = shieldNum;
		}
	}

	else if (shieldNum == 5) {
		Vector3 worldPos;

		worldPos.x = distans2Shield * cos(worldTransform_.rotation_.x) * sin(worldTransform_.rotation_.y);
		worldPos.y = distans2Shield * sin(worldTransform_.rotation_.x);
		worldPos.z = distans2Shield * cos(worldTransform_.rotation_.y) * cos(worldTransform_.rotation_.x);

		if (distans2Shield <= worldPos.z) {
			forwardShieldNum = shieldNum;
		}
	}

}