/*
 * QuickMafs.h
 *
 *  Created on: 27.8.2018
 *      Author: Eemil
 */

#ifndef QUICKMAFS_H_
#define QUICKMAFS_H_

namespace gyrospinner {


typedef struct {
	float i;
	float j;
	float k;
} Vector;

typedef struct {
	double r;
	Vector v;
} Quaternion;


class QuickMafs {
public:
	QuickMafs();
	virtual ~QuickMafs();
	static Vector scale(Vector v, float a);
	static Vector negate(Vector v);
	static float normalize(Vector* v);
	static Quaternion product(Quaternion a, Quaternion b);
	static Quaternion sum(Quaternion a, Quaternion b);
	static Quaternion constructRotator(Vector rotationAxis, float angle);
	static Vector rotate(Vector turnable, Quaternion rotator);
	static Vector rotate(Vector turnable, Vector rotationAxis, float angle);

};

} /* namespace gyrospinner */

#endif /* QUICKMAFS_H_ */
