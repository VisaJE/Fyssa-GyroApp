/*
 * QuickMafs.cpp
 *
 *  Created on: 27.8.2018
 *      Author: Eemil
 */

#include "QuickMafs.h"
#include <math.h>
namespace gyrospinner {

QuickMafs::QuickMafs() {
}
QuickMafs::~QuickMafs() {

}

Vector QuickMafs::scale(Vector v, float a) {
	Vector res;
	res.i = v.i*a;
	res.j = v.j*a;
	res.k = v.k*a;
	return res;
}

Vector QuickMafs::negate(Vector v){
	Vector res;
	res.i = -v.i;
	res.j = -v.j;
	res.k = -v.k;
	return res;
}

float QuickMafs::normalize(Vector* v) {
	float cur = v->i*v->i + v->j*v->j + v->k*v->k;
	cur = sqrt(cur);
	v->i /= cur;
	v->j /= cur;
	v->k /= cur;
	return cur;
}

Quaternion QuickMafs::product(Quaternion a, Quaternion b) {
	Quaternion res;
	res.r = a.r*b.r -a.v.i*b.v.i - a.v.j*b.v.j - b.v.k*a.v.k;
	res.v.i = a.r*b.v.i + a.v.i*b.r + a.v.j*b.v.k - a.v.k*b.v.j;
	res.v.j = a.r*b.v.j -a.v.i*b.v.k + a.v.j*b.r + a.v.k*b.v.i;
	res.v.k = a.r*b.v.k + a.v.i*b.v.j - a.v.j*b.v.i + a.v.k*b.r;
	return res;
}

Quaternion QuickMafs::sum(Quaternion a, Quaternion b) {
	Quaternion res;
	res.r = a.r + b.r;
	res.v.i = a.v.i + b.v.i;
	res.v.j = a.v.j + b.v.j;
	res.v.k = a.v.k + b.v.k;
	return res;
}

Quaternion QuickMafs::constructRotator(Vector rotationAxis, float angle) {
	Quaternion rotator;
	rotator.r = cos(angle/2);
	rotator.v = scale(rotationAxis, sin(angle/2));
	return rotator;
}

Vector QuickMafs::rotate(Vector turnable, Quaternion rotator) {
	return product(product(rotator, {0.0, turnable}), {rotator.r, negate(rotator.v)}).v;
}

Vector QuickMafs::rotate(Vector turnable, Vector rotationAxis, float angle) {
	Quaternion rotator = constructRotator(rotationAxis, angle);
	return rotate(turnable, rotator);
}

} /* namespace gyrospinner */
