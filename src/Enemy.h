#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

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
	void Approach();

	void Leave();

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

};

