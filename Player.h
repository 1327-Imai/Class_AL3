#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"

class Player {

public:

	//�R���X�g���N�^�̐錾
	Player();

	//�f�X�g���N�^�̐錾
	~Player();

	//�����o�֐��̐錾
	//������
	void Initialize(Model* model , uint32_t textureHandle);

	//�X�V����
	void Update();

	//�`�揈��
	void Draw(ViewProjection viewprojection);


	//�����o�ϐ�
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//Input
	Input* input_;

	//DebugText
	DebugText* debugText_;

};

