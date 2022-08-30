#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

#include <memory>
#include <list>

#include "EnemyBullet.h"

class Player;

class Enemy {
public:

	//�����o�֐��̐錾
	//������
	void Initialize(Model* model , uint32_t textureHandle);

	//�X�V����
	void Update();

	//�`�揈��
	void Draw(ViewProjection viewprojection);

private:
	//�ڋ߃t�F�[�Y�̊֐�
	void Approach();

	//���E�t�F�[�Y�̊֐�
	void Leave();

	//�e�̔���
	void ShotBullet();

	//�A�N�Z�b�T
public:
	void SetPlayer(Player* player);

	Vector3 GetWorldPosition();

	//�����o�ϐ�
private:
	enum class Phase {
		Approach ,	//�ڋ߂���
		Leave ,		//���E����
	};

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�ړ��x�N�g��
	Vector3 move_ = {0.0f,0.0f,0.0f};

	Phase phase_ = Phase::Approach;

	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//���˃��[�g
	static const int32_t kBulletCT = 60;

	//�f�X�^�C�}�[
	int32_t bulletTimer_ = kBulletCT;

	//���L����
	Player* player_ = nullptr;
};

