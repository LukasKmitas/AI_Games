#include "Pvector.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"

using namespace std;

#ifndef BOID_H_
#define BOID_H_

/*
Brief description of Boid Class:
//The boid class creates an object which has multiple vectors (location, velocity, acceleration)
//Boids are given certain properties and rules to follow when interacting with other boids.
//They are being used to simulate flocking patterns and properties

For predators:
Predators should act by themselves. Thus, their maxSpeed should be different,
and they should not adhere to the three laws. However, they should adhere to
cohesion -- how should they seek prey? Also, prey should be able to run away
from predators. There are several ways to do this. The easiest way:

	Predators are part of the flock. This means that when the boids check
	through the vector of other boids, the predators are included. Check if
	the boid being looked at is a predator, and if it is, calculate a Pvector
	that maximizes separation.
*/

class Boid
{
public:
	bool predator;
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;
	int neighbourDistance = 30;

	Boid() {}
	Boid(float x, float y)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(-2.0f, 2.0f); // Adjust the range as needed

		acceleration = Pvector(0, 0);
		velocity = Pvector(dist(gen), dist(gen)/*rand()%3-2, rand()%3-2*/); // Allows for range of -2 -> 2
		location = Pvector(x, y);
		maxSpeed = 3.5;
		maxForce = 0.5;
	}
	Boid(float x, float y, bool predCheck) 
	{
		predator = predCheck;
		if (predCheck == true) {
			maxSpeed = 7.5;
			maxForce = 0.5;
			velocity = Pvector(rand()%3-1, rand()%3-1);
		} else {
			maxSpeed = 3.5;
			maxForce = 0.5;
			velocity = Pvector(rand()%3-2, rand()%3-2); // Allows for range of -2 -> 2
		}
		acceleration = Pvector(0, 0);
		location = Pvector(x, y);
	}

	bool operator==(const Boid& other) const {
		// Define your equality comparison logic here.
		// You can compare properties like location, velocity, or other relevant attributes.
		return (location == other.location && velocity == other.velocity);
	}

/* 
Destructors are commented out for now. g++ throws errors if they are included.
   If compiling on Visual Studio, however, no errors are thrown.
	//Destructor
	Boid::~Boid()
	{
		//cout << "Boid is being deleted by destructor!" << endl;
	}
*/	
	void applyForce(Pvector& force);
	// Three Laws that boids follow
	Pvector Separation(vector<Boid>& Boids);
	Pvector Alignment(vector<Boid>& Boids);
	Pvector Cohesion(vector<Boid>& Boids);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector& v);
	void run(vector <Boid>& v);
	void update();
	void flock(vector <Boid>& v);
	void borders();
	float angle(Pvector& v);
	void swarm(vector <Boid>& v);
	sf::Clock clock;
};

#endif