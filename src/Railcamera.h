#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"

class Railcamera {

public:
	void Initialize(Vector3 translation, Vector3 rotation);

	void Update();

private:

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


};

