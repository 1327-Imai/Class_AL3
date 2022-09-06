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

	Enemy();

	~Enemy();

	//�����o�֐��̐錾
	//������
	void Initialize(Model* model , Vector3 translation, int leaveWay);

	//�X�V����
	void Update();

	//�`�揈��
	void Draw(ViewProjection viewprojection);

private:
	//�ڋ߃t�F�[�Y�̊֐�
	void Approach();

	//��~�t�F�[�Y�̊֐�
	void Stay();

	//���E�t�F�[�Y�̊֐�
	void Leave();

	//�e�̔���
	void ShotBullet();


	//�A�N�Z�b�T
public:
	Vector3 GetWorldPosition();

	//�Փ˔���
	void Oncollision();

	void SetPlayer(Player* player);

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() {
		return bullets_;
	}

	bool GetIsDead() {
		return isDead_;
	}

	void AllClear() {
		isDead_ = true;
	}

	//�����o�ϐ�
private:
	enum class Phase {
		Approach ,	//�ڋ߂���
		Stay,		//��~����
		Leave ,		//���E����
	};

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�ړ��x�N�g��
	Vector3 move_ = {0.0f , 0.0f , 0.0f};

	//�s���t�F�[�Y
	Phase phase_ = Phase::Approach;

	//HP
	int hp_ = 0;

	bool isDead_ = false;

	bool isAtack_ = false;

	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//���˃��[�g
	static const int32_t kBulletCT = 60;

	//�f�X�^�C�}�[
	int32_t bulletTimer_ = kBulletCT;

	//�s���J�ڃ^�C�}�[
	int moveTimer = 0;

	//���E���̕���

	int leaveWay_ = 0;

	//���L����
	Player* player_ = nullptr;


	//enum
public:
	enum LeaveWay {
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

};

