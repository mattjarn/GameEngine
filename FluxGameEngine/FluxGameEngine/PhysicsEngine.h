#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "mat4.h"
#include "DebugDrawer.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void StartUp();

	void initialize();

	void deinitialize();

	void setGravity(float gravity);

	void trackRigidBody(btRigidBody *rigidBody);

	void setDebugMatrices(mat4 view, mat4 projection);

	void Debug();

	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

	DebugDrawer physicsDebugDrawer;
};

#endif // PHYSICS_ENGINE_H