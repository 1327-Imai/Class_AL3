#include "Myfunc.h"

#pragma region//ワールド変換行列を生成する関数

//スケーリング行列を設定する関数
void Myfunc::Affine::SetMatScale(Matrix4& affineMat , Vector3 scale) {
	//スケーリング行列を宣言
	Matrix4 matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//行列の計算
	affineMat *= matScale;

}

//回転行列を設定する関数
void Myfunc::Affine::SetMatRotation(Matrix4& affineMat , Vector3 rotation) {

	//回転行列を宣言
	//Z軸回転
	Matrix4 matRotZ = {
		cos(rotation.z) , sin(rotation.z) , 0 , 0 ,
		-sin(rotation.z) , cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X軸回転
	Matrix4 matRotX = {
		1 , 0 , 0 , 0 ,
		0 , cos(rotation.x) , sin(rotation.x) , 0 ,
		0 , -sin(rotation.x) , cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y軸回転
	Matrix4 matRotY = {
		cos(rotation.y) , 0 , -sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		sin(rotation.y) , 0 , cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//行列の計算
	affineMat *= matRotZ;
	affineMat *= matRotX;
	affineMat *= matRotY;

}

//平行移動行列の設定をする関数
void Myfunc::Affine::SetMatTranslation(Matrix4& affineMat , Vector3 translation) {

	//平行移動行列の宣言
	Matrix4 matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//行列の計算
	affineMat *= matTranslation;
}

#pragma endregion

#pragma region//度数法⇔弧度法の関数

//度数法を弧度法に変換する関数
float Myfunc::MyMathUtility::Deg2Rad(float Deg) {

	const float PI = 3.141592f;

	return Deg * PI / 180;

}

//弧度法を度数法に変換する関数
float Myfunc::MyMathUtility::Rad2Deg(float rad) {

	const float PI = 3.141592f;

	return rad / PI * 180;

}

#pragma endregion

//WorldTransformを更新する関数
void Myfunc::UpdateWorldTransform(WorldTransform& worldTransform) {
	//ワールド変換行列を用意
	Matrix4 affineMat = MathUtility::Matrix4Identity();

	//ワールド変換行列にスケーリング,回転,平行移動の行列を合成
	Myfunc::Affine::SetMatScale(affineMat , worldTransform.scale_);
	Myfunc::Affine::SetMatRotation(affineMat , worldTransform.rotation_);
	Myfunc::Affine::SetMatTranslation(affineMat , worldTransform.translation_);

	//ワールド行列に単位行列を代入
	worldTransform.matWorld_ = MathUtility::Matrix4Identity();

	//行列の計算
	worldTransform.matWorld_ *= affineMat;

	//もし親がある場合
	if (worldTransform.parent_ != nullptr) {
		//親のワールド行列との計算を行う
		worldTransform.matWorld_ *= worldTransform.parent_->matWorld_;
	}

	//行列の転送
	worldTransform.TransferMatrix();
}