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
	static float dotProduct(Vector a, Vector b);
	static Vector crossProduct(Vector a, Vector b);
	static Vector sum(Vector a, Vector b);
	static Vector rotate(Vector turnable, Quaternion rotator);
	static Vector rotate(Vector turnable, Vector rotationAxis, float angle);
	static void rotationBetween(float& angle, Vector& rotationAxis, Vector& start, Vector& end); //Normalizes start and end vectors.
	static Quaternion rotatorBetween(Vector start, Vector end);
};

} /* namespace gyrospinner */

#endif /* QUICKMAFS_H_ */
