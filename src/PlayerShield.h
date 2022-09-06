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

	//衝突判定
	void Oncollision();

	//アクセッサ
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

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	int hp_ = 0;

	bool isBrake = 0;
};

