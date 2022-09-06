#pragma once
#include "Enemy.h"

#include <memory>
#include <list>

#include "DebugText.h"

class EnemyController {

public:
	EnemyController();

	~EnemyController();

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewprojection);

	//アクセッサ
	const std::list < std::unique_ptr<Enemy>>& GetEnemyList() {
		return enemies_;
	}

	void SetPlayer(Player* player) {
		player_ = player;
	}

private:
	void CreateEnemy(Vector3 translation, int leaveWay);


private:
	int gameTimer_ = 0;

	std::list < std::unique_ptr<Enemy>> enemies_;

	Model* model_ = nullptr;

	Player* player_ = nullptr;

	//DebugText
	DebugText* debugText_;
};