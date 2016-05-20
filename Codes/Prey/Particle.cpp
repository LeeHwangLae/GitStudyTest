#include "Particle.h"
#include "myUtil.h"

CParticle::CParticle() {
	center.set(0.0, 0.0, 0.0);
	radius = mass = rand(0.01, 0.3);
}

void CParticle::init(void) {
	center.set(0, 0, 0);
	vel.set(0, 0, 0);
	mass = radius = 1.0;
}

void CParticle::addForce(CVec3d f)
{
	acc = acc + (1.0 / mass)*f;
}

void CParticle::addAcc(CVec3d a)
{
	acc = acc + a;
}

void CParticle::clearForce(void)
{
	acc.set(0, 0, 0);
}

void CParticle::simulate(double dt, double curTime) {
	if (dt > 0.02) dt = 0.02;

	// change velocity
	vel = vel + acc * dt;
	// change position
	center = center + vel * dt;
}

void CParticle::setPosition(double x, double y, double z) {
	center.set(x, y, z);
}

void CParticle::setVelocity(double x, double y, double z) {
	vel.set(x, y, z);
}

void CParticle::setRadius(double r) {
	radius = r;

}

void CParticle::setMass(double m) {
	mass = m;
}

void CParticle::drawWithGL(void) {
	glPushMatrix();
	glTranslated(center[0], center[1], center[2]);
	glutWireSphere(radius, 20, 20);
	glPopMatrix();
}