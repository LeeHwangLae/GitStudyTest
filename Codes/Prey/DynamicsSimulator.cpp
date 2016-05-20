//
//  KinematicsSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicsSimulator.h"
#include "myUtil.h"

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}

void CDynamicSimulator::init() {
	for (int i = 0;i<NPARTICLES; i++) {
		particle[i].setPosition(rand(-3, 3), rand(-3, 3), rand(-3, 3));
		particle[i].setVelocity(rand(-3, 3), rand(0, 0), rand(-3, 3)); //rand(-3,3), 0, rand(-3,3));
		particle[i].setRadius(rand(0.1, 0.2));
		particle[i].setMass(particle[i].getRadius());
	}
	particle2.setPosition(rand(-3, 3), rand(-3, 3), rand(-3, 3));
	particle2.setVelocity(rand(-3, 3), rand(0, 0), rand(-3, 3)); //rand(-3,3), 0, rand(-3,3));
	particle2.setRadius(0.5);
	particle2.setMass(particle2.getRadius());
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
	glColor3f(0, 0, 0);
	glPointSize(3);

	for (int i = 0; i<NPARTICLES; i++) {
		particle[i].simulate(dt, currentTime);
	}
	particle2.simulate(dt, currentTime);

	//add force
	CVec3d gravity(0, -9.8, 0);

	for (int i = 0; i < NPARTICLES; i++)
	{
		particle[i].clearForce();
		//particle[i].addForce(gravity);
	}
	particle2.clearForce();
	for (int i = 0; i < NPARTICLES; i++) {

		for (int j = i + 1; j < NPARTICLES; j++)
		{
			CVec3d f = computeAttraction(particle[i], particle[j]);
			CVec3d f2 = computeAttraction(particle2, particle[i]);
			particle[i].addForce(f);
			particle[j].addForce(-1*f);
			particle2.addForce(0.04*f);
			particle[i].addForce(-1*f2*0.5);
		}
	}
	
	for (int i = 0; i < NPARTICLES; i++) {

		for (int j = i + 1; j < NPARTICLES; j++)
		{
			collisionHandle(particle[i], particle[j]);
		}
	}

	// collision with boundary
	CVec3d c, v;
	double r;
	CVec3d colNorm;
	CVec3d vp, vt;
	for (int i = 0; i<NPARTICLES; i++)
	{
		c = particle[i].getPosition();
		r = particle[i].getRadius();
		v = particle[i].getVelocity();
		// collision check
		double distance = c.len();
		if (distance > BoundaryRadius - r)
		{
			colNorm = -1.0 * c.getNormalized();
			double alpha = v ^ colNorm;
			vp = alpha * colNorm;
			v = v - (1.0 + 1.0) * vp;
			particle[i].setVelocity(v[0], v[1], v[2]);
		}
	}
	c = particle2.getPosition();
	r = particle2.getRadius();
	v = particle2.getVelocity();
	// collision check
	double distance = c.len();
	if (distance > BoundaryRadius - r)
	{
		colNorm = -1.0 * c.getNormalized();
		double alpha = v ^ colNorm;
		vp = alpha * colNorm;
		v = v - (1.0 + 1.0) * vp;
		particle2.setVelocity(v[0], v[1], v[2]);
	}
}

void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
	// draw
	for (int i = 0; i<NPARTICLES; i++) {
		particle[i].drawWithGL();
	}
	glColor3d(0, 1, 0);
	particle2.drawWithGL();

	/*glBegin(GL_LINE_LOOP);
	for (int i = 0;i<100;i++) {
		double angle = 2.0*3.14*(double(i) / 100.0);
		glVertex3f(BoundaryRadius * cos(angle),
			0, BoundaryRadius * sin(angle));
	}
	glEnd();*/

	glColor3d(1, 0, 0);
	glutWireSphere(BoundaryRadius, 20, 20);
}

CVec3d CDynamicSimulator::computeAttraction(CParticle &p1, CParticle &p2)
{
	CVec3d c1 = p1.getPosition();
	CVec3d c2 = p2.getPosition();
	CVec3d N = c2 - c1;
	N.normalize();
	double dist = N.len();
	double m1 = p1.getMass();
	double m2 = p2.getMass();

	CVec3d force;
	double coffe = 0.3;
	force = coffe*((m1*m2) / (dist*dist))*N;
	return force;
}

void CDynamicSimulator::collisionHandle(CParticle &p1, CParticle &p2)
{
	CVec3d c1 = p1.getPosition();
	CVec3d c2 = p2.getPosition();
	CVec3d N;
	N = c1 - c2;
	double dist = N.len();
	double penetration = p1.getRadius() + p2.getRadius() - dist;

	if (penetration > 0)
	{
		N.normalize();
		CVec3d v1 = p1.getVelocity();
		CVec3d v2 = p2.getVelocity();
		double v1N = v1^N;
		double v2N = v2^N;
		double vr = v1N - v2N;
		double e = 0.1;
		double m1 = p1.getMass();
		double m2 = p2.getMass();

		if (vr < 0)
		{
			double J = -vr*(e + 1.0) / (1.0 / m1 + 1.0 / m2);
			double v1New = v1N + J / m1;
			double v2New = v2N - J / m2;
			v1 = v1 - v1N*N + v1New*N;
			v2 = v2 - v2N*N + v2New*N;
			p1.setVelocity(v1.x, v1.y, v1.z);
			p2.setVelocity(v2.x, v2.y, v2.z);
		}
		c1 = c1 + (0.5*(1.0 + e)*penetration)*N;
		c2 = c2 - (0.5*(1.0 + e)*penetration)*N;
		p1.setPosition(c1.x, c1.y, c1.z);
		p2.setPosition(c2.x, c2.y, c2.z);
	}
	/*double e = 1.0; //Åº¼º°è¼ö
	CVec3d c1 = p1.getPosition();
	CVec3d c2 = p2.getPosition();
	CVec3d N = c1 - c2;
	double dist = N.len();
	if (dist < p1.getRadius() + p2.getRadius())
	{
		N.normalize();
		CVec3d v1 = p1.getVelocity();
		CVec3d v2 = p2.getVelocity();
		double v1N = v1^N;
		double v2N = v2^N;
		double m1 = p1.getMass();
		double m2 = p2.getMass();

		if (v2N - v1N>0)
		{
			double v1New = ((m1 - m2)*v1N + 2.0*m2*v2N) / (m1 + m2);
			double v2New = ((m2 - m1)*v2N + 2.0*m1*v1N) / (m1 + m2);
			v1 = v1 - v1N*N + e * v1New*N;
			v2 = v2 - v2N*N + e * v2New*N;
			p1.setVelocity(v1.x, v1.y, v1.z);
			p2.setVelocity(v2.x, v2.y, v2.z);
		}
	}*/
}