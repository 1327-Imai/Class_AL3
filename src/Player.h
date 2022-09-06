#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

#include <memory>
#include <list>

#include "PlayerBullet.h"
#include "PlayerShield.h"

class Player {

public:

	//�R���X�g���N�^�̐錾
	Player();

	//�f�X�g���N�^�̐錾
	~Player();

	//�����o�֐��̐錾
	//������
	void Initialize(Model* model);

	//�X�V����
	void Update(ViewProjection viewProjection);

	//�`�揈��
	void Draw(ViewProjection viewprojection);

	void DrawUI();

	//�Փ˔���
	void Oncollision();

	void ShieldOncollision(int shieldNum);

private:
	//�ړ�����
	void Move();

	//��]����
	void Rotate();

	//�e�̔���
	void ShotBullet();

	void CalShieldPos(int shieldNum);

	//�A�N�Z�b�T
public:
	Vector3 GetWorldPosition();

	Vector3 GetShieldWorldPosition(int shieldNum);

	WorldTransform* GetWorldTransform() {
		return &worldTransform_;
	}

	bool GetIsPlayerShieldBrake(int shieldNum);

	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() {
		return bullets_;
	}

	//�����o�ϐ�
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	WorldTransform worldTransform3DReticle_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandleReticle_ = 0u;

	//2D���e�B�N���p�X�v���C�g
	std::unique_ptr<Sprite> sprite2DReticle_;

	//Input
	Input* input_;

	//DebugText
	DebugText* debugText_;

	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	//���˃��[�g
	static const int32_t kBulletCT = 10;

	//�f�X�^�C�}�[
	int32_t bulletTimer_ = kBulletCT;

	int rotatoValueX_ = 0;

	int rotatoValueY_ = 0;

	//�V�[���h
	const int shieldNum_ = 6;

	const float distans2Shield = 2;

	const float distance2Reticle = 25.0f;

	int forwardShieldNum = 0;

	PlayerShield* playerShield_[6] = {nullptr};

	bool isAlive = true;

};

