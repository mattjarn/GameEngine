#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {}
PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::StartUp() {
}

void PhysicsEngine::initialize() {
	// Build the broadphase
	broadphase = new btDbvtBroadphase();
	// Set up the collision configuration and dispatcher
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	// The actual physics solver
	solver = new btSequentialImpulseConstraintSolver;
	// The world.
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

	dynamicsWorld->setDebugDrawer(&physicsDebugDrawer);

}

void PhysicsEngine::deinitialize() {
	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}


void PhysicsEngine::setGravity(float gravity) {
	dynamicsWorld->setGravity(btVector3(0, -gravity, 0));
}

void PhysicsEngine::trackRigidBody(btRigidBody *rigidBody) {
	dynamicsWorld->addRigidBody(rigidBody);
}

void PhysicsEngine::setDebugMatrices(mat4 view, mat4 projection) {
	physicsDebugDrawer.SetMatrices(view, projection);
}

void PhysicsEngine::Debug() {
	dynamicsWorld->debugDrawWorld();
	//physicsDebugDrawer.Draw();
}


