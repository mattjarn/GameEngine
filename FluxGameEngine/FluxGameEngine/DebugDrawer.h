// Helper class; draws the world as seen by Bullet.
// This is very handy to see if Bullet's world matches yours.
// How to use this class :
// Declare an instance of the class :
// DebugDrawer mydebugdrawer;
// dynamicsWorld->setDebugDrawer(&mydebugdrawer);
// Each frame, call it :
// mydebugdrawer.SetMatrices(ViewMatrix, ProjectionMatrix);
// dynamicsWorld->debugDrawWorld();
#include <vector>
#include <btBulletDynamicsCommon.h>
#include <glad\glad.h>
#include "mat4.h"
#include "Shader.h"

class DebugDrawer : public btIDebugDraw {
public:
	struct btLine {
		GLfloat vertices[6];
		btLine(const btVector3& f, const btVector3& t) {
			vertices[0] = f.x();
			vertices[1] = f.y();
			vertices[2] = f.z();

			vertices[3] = t.x();
			vertices[4] = t.y();
			vertices[5] = t.z();
		}
	};
	std::vector<btLine> LINES;

	DebugDrawer() {}
	~DebugDrawer() {}

	void SetMatrices(mat4 pViewMatrix, mat4 pProjectionMatrix) {
		DebugPhysicsShader.use();
		DebugPhysicsShader.setMat4("view", pViewMatrix);
		DebugPhysicsShader.setMat4("projection", pProjectionMatrix);
		DebugPhysicsShader.setMat4("model", model);

	}
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
		//LINES.push_back(btLine(from, to));
		DebugPhysicsShader.use();
		vec4 myColor = vec4(color.getX(), color.getY(), color.getZ());
		DebugPhysicsShader.setVec4("color", myColor);


		glDisable(GL_CULL_FACE);
		glLineWidth(2.0);

		btLine line = btLine(from, to);
		// first, configure the VAO and VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(btLine), line.vertices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//use geometry
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glDrawArrays(GL_LINES, 0, sizeof(btLine));
		glBindVertexArray(0);

		//delete buffers
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Draw() {
		glDisable(GL_CULL_FACE);
		glLineWidth(2.5);


		//btLine line(from, to);

		// first, configure the VAO and VBO
		//unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, LINES.size() * sizeof(btLine), &LINES[0], GL_STATIC_DRAW);

		glBindVertexArray(VAO);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//use geometry
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glDrawArrays(GL_LINES, 0, LINES.size() * sizeof(btLine));
		glBindVertexArray(0);

		//delete buffers
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		LINES.clear();
	}
	virtual void drawContactPoint(const btVector3 &, const btVector3 &, btScalar, int, const btVector3 &) {}
	virtual void reportErrorWarning(const char *) {}
	virtual void draw3dText(const btVector3 &, const char *) {}
	virtual void setDebugMode(int p) {
		m = p;
	}
	int getDebugMode(void) const { return 1; }
	int m;

private:
	mat4 model = mat4();

	DebugDrawModes debugModes;

	bool isDebuggingPhysics;
	unsigned int VAO, VBO;

	int vertexCount;
	int vertIndex;
	Shader DebugPhysicsShader = Shader("DebugPhysics.vs", "DebugPhysics.fs");
};