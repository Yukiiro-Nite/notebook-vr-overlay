#pragma once
#define _USE_MATH_DEFINES

#include <openvr.h>
#include <math.h>

class MathUtils {
	public: 
		static vr::HmdMatrix34_t matrix(vr::HmdVector3_t pos, vr::HmdVector3_t rot);
};

// Need to be able to create 3x4 matrix from a vector and an euler rotation