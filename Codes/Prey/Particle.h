#ifndef _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_
#define _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "Vec3d.h"

class CParticle {
	CVec3d center;
	CVec3d vel;
	CVec3d acc;
	float mass;
	float radius;

public:
	CParticle();

	void init(void);
	void simulate(double dt, double currentTime);
	void addForce(CVec3d f);
	void addAcc(CVec3d f);
	void clearForce(void);

	void setPosition(double x, double y, double z);
	void setVelocity(double vx, double vy, double vz);
	void setRadius(double r);
	void setMass(double m);

	double getMass(void) { return mass; }
	double getRadius(void) { return radius; }
	CVec3d getPosition(void) { return center; }
	CVec3d getVelocity(void) { return vel; }

	void drawWithGL(void);
};

#endif