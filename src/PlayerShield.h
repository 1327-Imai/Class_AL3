#pragma once
#include "Model.h"
#include "WorldTransform.h"

class PlayerShield {

public:

	PlayerShield();

	~PlayerShield();

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewprojection);

	//�Փ˔���
	void Oncollision();

	//�A�N�Z�b�T
	void SetTranslation(Vector3 translation);

	void SetRotation(Vector3 rotation);

	bool GetIsBrake() {
		return isBrake;
	}

	void SetParent(WorldTransform* parent);

	Vector3 GetWorldPosition();

	WorldTransform GetWorldTransform();

private:
	Model* model_ = nullptr;

	WorldTransform worldTransform_;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	int hp_ = 0;

	bool isBrake = 0;
};

