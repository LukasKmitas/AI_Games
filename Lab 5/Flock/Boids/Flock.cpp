#include "Boid.h"
#include "Flock.h"

using namespace std;

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize()
{
	return flock.size();
}

Boid Flock::getBoid(int i)
{
	return flock[i];
}

void Flock::addBoid(Boid b)
{
	flock.push_back(b);
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking() 
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].run(flock);
	}
}
// Runs the swarm function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::swarming()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].swarm(flock);
	}
}

void Flock::formation(int fLeader, float leaderSpeedChange, float leaderDirectionChange)
{
    int fSize = flock.size();
    int numRows = 5;
    int numCols = 10;
    float spacingX = 20.0f;
    float spacingY = 20.0f;

    for (int i = 0; i < fSize; i++)
    {
        if (i == fLeader)
        {
          
            float newAngle = flock[i].maxSpeed + leaderDirectionChange;
            flock[i].applyForce(Pvector(cos(newAngle), sin(newAngle)));
            flock[i].update("formation");
            flock[i].borders();
        }
        else
        {
            int row = i / numCols;
            int col = i % numCols;

            float x = flock[fLeader].location.x - (numCols / 2) * spacingX + col * spacingX;
            float y = flock[fLeader].location.y - (numRows / 2) * spacingY + row * spacingY;

            Pvector targetSlot(x, y);
            Pvector sub = Pvector(0, 0);
            Pvector sum = Pvector(0, 0);
            int npcRadius = 5;
            int closeEnough = 5;

            sub = sub.subTwoVector(targetSlot, flock[i].location);
            float D = sub.magnitude();

            if (D > closeEnough)
            {
                sum = sub;
                sum.normalize();
                sum.mulScalar(flock[i].maxSpeed);
                flock[i].applyForce(sum);
                flock[i].update("formation");
                flock[i].borders();
            }
            else
            {
                flock[i].velocity = flock[fLeader].velocity;
                flock[i].borders();
            }
        }
    }
}
