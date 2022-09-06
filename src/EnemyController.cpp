#include "EnemyController.h"

#include <cassert>

EnemyController::EnemyController() {

	debugText_ = nullptr;

}

EnemyController::~EnemyController() {

}

void EnemyController::Initialize(Model* model) {

	assert(model);

	model_ = model;

	gameTimer_ = 150 * 60;

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->AllClear();
	}

	debugText_ = DebugText::GetInstance();

}

void EnemyController::Update() {

	if (gameTimer_ == 140 * 60) {
		CreateEnemy({0 , 2 , 65} , Enemy::LeaveWay::UP);
	}
	else if (gameTimer_ == 110 * 60) {
		CreateEnemy({4 , 0 , 65} , Enemy::LeaveWay::RIGHT);
		CreateEnemy({-4 , 0 , 65} , Enemy::LeaveWay::LEFT);
	}
	else if (gameTimer_ == 80 * 60) {
		CreateEnemy({0 , 4 , 65} , Enemy::LeaveWay::UP);
		CreateEnemy({6 , -2 , 65} , Enemy::LeaveWay::RIGHT);
		CreateEnemy({-6 , -2 , 65} , Enemy::LeaveWay::LEFT);
	}
	else if (gameTimer_ == 50 * 60) {
		CreateEnemy({4 , 4 , 65} , Enemy::LeaveWay::UP);
		CreateEnemy({-4 , -4 , 65} , Enemy::LeaveWay::DOWN);
		CreateEnemy({4 , -4 , 65} , Enemy::LeaveWay::RIGHT);
		CreateEnemy({-4 , 4 , 65} , Enemy::LeaveWay::LEFT);
	}
	else if (gameTimer_ == 30 * 60) {
		CreateEnemy({2 , 2 , 65} , Enemy::LeaveWay::UP);
		CreateEnemy({-2 , -2 , 65} , Enemy::LeaveWay::DOWN);
		CreateEnemy({2 , -2 , 65} , Enemy::LeaveWay::RIGHT);
		CreateEnemy({-2 , 2 , 65} , Enemy::LeaveWay::LEFT);
	}

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->Update();
	}
	enemies_.remove_if([](std::unique_ptr<Enemy>& enemy) {

		return enemy->GetIsDead();

					   });

	if (0 < gameTimer_) {
		gameTimer_--;
	}

	debugText_->SetPos(15 ,70);
	debugText_->Printf(
		"Timer:%d" ,
		gameTimer_ / 60
	);

	if (gameTimer_ <= 0) {
		debugText_->SetPos(15 , 45);
		debugText_->Printf(
			"Gameover Press [R] to restart."
		);
	}
}

void EnemyController::Draw(ViewProjection viewprojection) {

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->Draw(viewprojection);
	}

}

void EnemyController::CreateEnemy(Vector3 translation , int leaveWay) {

	//ˆø”‚©‚ç‰ŠúˆÊ’u‚ğæ“¾
	Vector3 position = translation;

	//“G‚ğ¶¬‚µ‰Šú‰»
	//’e‚ğ¶¬‚µ‰Šú‰»
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->Initialize(model_ , position , leaveWay);

	enemies_.push_back(std::move(newEnemy));

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->SetPlayer(player_);

	}

}

