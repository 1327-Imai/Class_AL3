#include "Myfunc.h"

#pragma region//���[���h�ϊ��s��𐶐�����֐�

void Myfunc::SetMatScale(Matrix4& affineMat , Vector3 scale) {
	//�X�P�[�����O�s���錾
	Matrix4 matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	affineMat *= matScale;

}

void Myfunc::SetMatRotation(Matrix4& affineMat , Vector3 rotation) {

	//��]�s���錾
	Matrix4 matRotX = {
		1 , 0 , 0 , 0 ,
		0 , cos(rotation.x) , sin(rotation.x) , 0 ,
		0 , -sin(rotation.x) , cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	Matrix4 matRotY = {
		cos(rotation.y) , 0 , -sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		sin(rotation.y) , 0 , cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	Matrix4 matRotZ = {
		cos(rotation.z) , sin(rotation.z) , 0 , 0 ,
		-sin(rotation.z) , cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	affineMat *= matRotX;
	affineMat *= matRotY;
	affineMat *= matRotZ;

}

void Myfunc::SetMatTranslation(Matrix4& affineMat , Vector3 translation) {

	Matrix4 matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	affineMat *= matTranslation;
}

#pragma endregion

#pragma region//�x���@�̌ʓx�@�̊֐�

float Myfunc::dig2rad(float dig) {

	float PI = 3.141592;

	return dig * PI / 180;

}

float Myfunc::rad2dig(float rad) {

	float PI = 3.141592;

	return rad / PI * 180;

}

#pragma endregion

//�q��WorldTransform���X�V����֐�
void Myfunc::UpdateChildeWorldTransform(WorldTransform& worldTransform) {
	Matrix4 affineMat = MathUtility::Matrix4Identity();

	Myfunc::SetMatScale(affineMat , worldTransform.scale_);
	Myfunc::SetMatRotation(affineMat , worldTransform.rotation_);
	Myfunc::SetMatTranslation(affineMat , worldTransform.translation_);

	worldTransform.matWorld_ = MathUtility::Matrix4Identity();

	worldTransform.matWorld_ *= affineMat;

	worldTransform.matWorld_ *= worldTransform.parent_->matWorld_;

	worldTransform.TransferMatrix();
}