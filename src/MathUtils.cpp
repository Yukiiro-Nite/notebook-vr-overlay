#include "MathUtils.h"

vr::HmdMatrix34_t MathUtils::matrix(vr::HmdVector3_t pos, vr::HmdVector3_t rot)
{
	float px = pos.v[0];
	float py = pos.v[1];
	float pz = pos.v[2];

	float rx = rot.v[2];
	float ry = rot.v[1];
	float rz = rot.v[0];

	float m0x0 = cos(rx) * cos(ry);
	float m1x0 = cos(rx) * sin(ry) * sin(rz) - sin(rx) * cos(rz);
	float m2x0 = cos(rx) * sin(ry) * cos(rz) + sin(rx) * sin(rz);
	float m3x0 = px;

	float m0x1 = sin(rx) * cos(ry);
	float m1x1 = sin(rx) * sin(ry) * sin(rz) + cos(rx) * cos(rz);
	float m2x1 = sin(rx) * sin(ry) * cos(rz) - cos(rx) * sin(rz);
	float m3x1 = py;

	float m0x2 = -sin(ry);
	float m1x2 = cos(ry) * sin(rz);
	float m2x2 = cos(ry) * cos(rz);
	float m3x2 = pz;

	return vr::HmdMatrix34_t{
		m0x0, m1x0, m2x0, m3x0,
		m0x1, m1x1, m2x1, m3x1,
		m0x2, m1x2, m2x2, m3x2,
	};
}
