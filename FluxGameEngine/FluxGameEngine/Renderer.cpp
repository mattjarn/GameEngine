#include "Renderer.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <iostream>
#include "Camera.h"
#include "Model.h"
#include "PhysicsEngine.h"
#include "Shader.h"

// Include Bullet
#include <btBulletDynamicsCommon.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, float deltaTime, btRigidBody *body);
void processInput(GLFWwindow *window, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void renderScene(const Shader &shader);
void renderCube();
void renderQuad();
void passOne();
void passTwo();
void setupShadowBuffers();
void init();
void installLights(Shader rendering_program, mat4 v_matrix);
unsigned int loadTexture(std::string filename);



// meshes
unsigned int planeVAO;
unsigned int quadVAO = 0;
unsigned int quadVBO;
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;

const unsigned int SCR_WIDTH = 1800, SCR_HEIGHT = 1200;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float currentFrame = 0.0f;

Camera camera(vec4(0.0f, 3.0f, 3.0f));
float lastX;
float lastY;
bool firstMouse;

// lighting
vec4 lightPos(1.2f, 1.0f, 2.0f);

bool wireFrame = false;
bool debugPhysics = false;

# define toRadians  (PI/180.0f)

// lighting info
// -------------
//vec4 lightPos(-2.0f, 4.0f, -1.0f);
vec4 globalAmbient = vec4(0.7f, 0.7f, 0.7f, 1.0f);

//Shaders for shadows
Shader rendering_program1;
Shader rendering_program2;

// shadow stuff
int scSizeX, scSizeY;
unsigned int shadow_tex[1] = {};
unsigned int shadow_buffer[1] = {};
mat4 lightV_matrix = mat4();
mat4 lightP_matrix = mat4();
mat4 shadowMVP1 = mat4();
mat4 shadowMVP2 = mat4();
mat4 b = mat4();

mat4 m_matrix = mat4();
mat4 v_matrix = mat4();
mat4 mv_matrix = mat4();
mat4 proj_matrix = mat4();

float aspect;

int number = 25;

Model dragon;
Model nanosuit;
Model sphere;
Model cyborg;
Model pyramid;

Renderer::Renderer() {}
Renderer::~Renderer() {}

struct PointLight {
	vec4 position;

	float constant;
	float linear;
	float quadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

PointLight currentLight = PointLight();
Material thisMaterial = Material();



void Renderer::StartUp(const char* name) {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

}


int Renderer::MultipleLights()
{
	return 0;
}

int Renderer::BulletPhysics() {

	StartUp("Bullet Physics");

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// build and compile shaders
	// -------------------------
	Shader modelShader("1.model_loading.vs", "1.model_loading.fs");
	Shader lightingShader("6.multiple_lights.vs", "6.multiple_lights.fs");
	Shader lampShader("light.vs", "light.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	// positions all containers
	vec4 cubePositions[] = {
		vec4(0.0f,  0.0f,  0.0f),
		vec4(2.0f,  5.0f, -15.0f),
		vec4(-1.5f, -2.2f, -2.5f),
		vec4(-3.8f, -2.0f, -12.3f),
		vec4(2.4f, -0.4f, -3.5f),
		vec4(-1.7f,  3.0f, -7.5f),
		vec4(1.3f, -2.0f, -2.5f),
		vec4(1.5f,  2.0f, -2.5f),
		vec4(1.5f,  0.2f, -1.5f),
		vec4(-1.3f,  1.0f, -1.5f)
	};
	// positions of the point lights
	vec4 pointLightPositions[] = {
		vec4(0.7f,  0.2f,  2.0f),
		vec4(2.3f, -3.3f, -4.0f),
		vec4(-4.0f,  2.0f, -12.0f),
		vec4(0.0f,  0.0f, -3.0f)
	};
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// load textures (we now use a utility function to keep the code more organized)
	// -----------------------------------------------------------------------------
	unsigned int diffuseMap = loadTexture("../Resources/textures/container2.png");
	unsigned int specularMap = loadTexture("../Resources/textures/container2_specular.png");

	// shader configuration
	// --------------------
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	vec4 pointLightColors[] = {
		vec4(0.1f, 0.1f, 0.1f),
		vec4(0.1f, 0.1f, 0.1f),
		vec4(0.1f, 0.1f, 0.1f),
		vec4(0.3f, 0.1f, 0.1f)
	};
	std::cout << "Loading Models" << std::endl;

	// load models
	// -----------
	nanosuit = Model("../Resources/nanosuit/nanosuit.obj");
	sphere = Model("../Resources/planet/planet.obj");
	cyborg = Model("../Resources/cyborg/cyborg.obj");
	dragon = Model("../Resources/Dragon/Dragon.fbx");
	pyramid = Model("../Resources/pyr.obj");

	std::cout << "Initializing Physics" << std::endl;

	// Initialize physics engine
	PhysicsEngine physics;

	physics.initialize();

	// Generate positions & rotations for number of models
	std::vector<vec4> positions(number);
	std::vector<vec4> orientations(number);
	for (int i = 0; i<number; i++) {
		positions[i] = vec4(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10);
		//orientations[i] = vec4::normalize((vec4(rand() % 360, rand() % 360, rand() % 360)));

	}

	std::vector<btRigidBody*> rigidbodies;

	btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(0.8f, 1.55f, 0.34f));

	for (int i = 0; i<number; i++) {

		btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
			btQuaternion(0,0,0,1),
			btVector3(positions[i].elts[0], positions[i].elts[1], positions[i].elts[2])
		));

		/*btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
			btQuaternion(orientations[i].elts[0], orientations[i].elts[1], orientations[i].elts[2], orientations[i].elts[3]),
			btVector3(positions[i].elts[0], positions[i].elts[1], positions[i].elts[2])
		));*/

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			1,                  // mass, in kg
			motionstate,
			boxCollisionShape,  // collision shape of body
			btVector3(0, 0, 0)    // local inertia
		);
		btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

		rigidbodies.push_back(rigidBody);
		//dynamicsWorld->addRigidBody(rigidBody);
		physics.trackRigidBody(rigidBody);

		// Small hack : store the mesh's index "i" in Bullet's User Pointer.
		// Will be used to know which object is picked. 
		// A real program would probably pass a "MyGameObjectPointer" instead.
		rigidBody->setUserPointer((void*)i);

	}
	//rigidbodies[0]->activate(true);
	//rigidbodies[0]->setLinearVelocity(btVector3(0, 0.1, 0));
	//rigidbodies[0]->applyForce(btVector3(0, 45, 0), btVector3(0, 0, 0));

	//the ground
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(
			0, 
			groundMotionState, 
			groundShape, 
			btVector3(0, 0, 0)
		);
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	physics.trackRigidBody(groundRigidBody);

	//the ground
	btCollisionShape* cameraShape = new btBoxShape(btVector3(0.5f, 1.0f, 0.5f));

	btDefaultMotionState* cameraMotionState = new btDefaultMotionState(btTransform(
		btQuaternion(0, 0, 0, 1),
		btVector3(camera.Position.elts[0], camera.Position.elts[1], camera.Position.elts[2])));
	btRigidBody::btRigidBodyConstructionInfo
		cameraRigidBodyCI(
			1,
			cameraMotionState,
			cameraShape,
			btVector3(0, 0, 0)
		);
	btRigidBody* cameraRigidBody = new btRigidBody(cameraRigidBodyCI);
	physics.trackRigidBody(cameraRigidBody);

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float planeVertices[] = {
		// positions            // normals         // texcoords
		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};
	// plane VAO
	unsigned int planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	// load textures
	// -------------
	unsigned int woodTexture = loadTexture("../Resources/textures/wood.png");


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		if (wireFrame) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window, deltaTime, cameraRigidBody);

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setFloat("material.shininess", 32.0f);

		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("dirLight.diffuse", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
		// point light 1
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0] * 0.1);
		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0]);
		lightingShader.setVec3("pointLights[0].specular", pointLightColors[0]);
		lightingShader.setFloat("pointLights[0].constant", 1.0f);
		lightingShader.setFloat("pointLights[0].linear", 0.14);
		lightingShader.setFloat("pointLights[0].quadratic", 0.07);
		// point light 2
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1] * 0.1);
		lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1]);
		lightingShader.setVec3("pointLights[1].specular", pointLightColors[1]);
		lightingShader.setFloat("pointLights[1].constant", 1.0f);
		lightingShader.setFloat("pointLights[1].linear", 0.14);
		lightingShader.setFloat("pointLights[1].quadratic", 0.07);
		// point light 3
		lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2] * 0.1);
		lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2]);
		lightingShader.setVec3("pointLights[2].specular", pointLightColors[2]);
		lightingShader.setFloat("pointLights[2].constant", 1.0f);
		lightingShader.setFloat("pointLights[2].linear", 0.22);
		lightingShader.setFloat("pointLights[2].quadratic", 0.2);
		// point light 4
		lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3] * 0.1);
		lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3]);
		lightingShader.setVec3("pointLights[3].specular", pointLightColors[3]);
		lightingShader.setFloat("pointLights[3].constant", 1.0f);
		lightingShader.setFloat("pointLights[3].linear", 0.14);
		lightingShader.setFloat("pointLights[3].quadratic", 0.07);
		// spotLight
		lightingShader.setVec3("spotLight.position", camera.Position);
		lightingShader.setVec3("spotLight.direction", camera.Front);
		lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("spotLight.constant", 1.0f);
		lightingShader.setFloat("spotLight.linear", 0.09);
		lightingShader.setFloat("spotLight.quadratic", 0.032);
		lightingShader.setFloat("spotLight.cutOff", cos(12.5f * toRadians));
		lightingShader.setFloat("spotLight.outerCutOff", cos(15.0f * toRadians));

		// view/projection transformations
		mat4 projection = mat4::perspective(camera.Zoom * toRadians, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// world transformation
		mat4 model;
		lightingShader.setMat4("model", model);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// render containers
		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			mat4 model;
			model = mat4::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			mat4 rot = mat4::createRotationMat(angle * toRadians, angle * toRadians, angle * toRadians);
			model = model * rot;
			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTexture);
		renderScene(lightingShader);

		btTransform trans;
		for (int i = 0; i < number; i++) {
			rigidbodies[i]->getMotionState()->getWorldTransform(trans);
			positions[i] = vec4(trans.getOrigin().x(), trans.getOrigin().y() - 1.55, trans.getOrigin().z());
			// render the model
			mat4 model = mat4();
			model = mat4::translate(model, positions[i]);
			model = mat4::scale(model, 0.2f);
			lightingShader.setMat4("model", model);
			nanosuit.Draw(lightingShader);
		}

		cameraRigidBody->getMotionState()->getWorldTransform(trans);
		camera.Position = vec4(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());

		// also draw the lamp object(s)
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);

		// we now draw as many light bulbs as we have point lights.
		glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = mat4();
			model = mat4::translate(model, pointLightPositions[i]);
			model = mat4::scale(model, 0.1f); // Make it a smaller cube
			lampShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// view/projection transformations
		//mat4 projection = mat4::perspective(cam.Zoom * toRadians, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//mat4 view = cam.GetViewMatrix();
		//modelShader.setMat4("projection", projection);
		//modelShader.setMat4("view", view);

		if (debugPhysics) {
			// Each frame, call it :
			physics.setDebugMatrices(view, projection);
			physics.Debug();
		}

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
											 // printf and reset
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		float deltaTime = currentTime - lastTime;

		// Step the simulation
		//dynamicsWorld->stepSimulation(deltaTime, 7);
		physics.dynamicsWorld->stepSimulation(deltaTime, 7);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	// Clean up behind ourselves like good little programmers

	for (int i = 0; i < rigidbodies.size(); i++) {
		physics.dynamicsWorld->removeRigidBody(rigidbodies[i]);
		delete rigidbodies[i]->getMotionState();
		delete rigidbodies[i];
	}
	delete boxCollisionShape;
	physics.deinitialize();

	return 0;

}

int Renderer::shadows() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	rendering_program1 = Shader("shadow_depth.vs", "shadow_depth.fs");
	rendering_program2 = Shader("shadow_map.vs", "shadow_map.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float planeVertices[] = {
		// positions            // normals         // texcoords
		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};
	// plane VAO
	unsigned int planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	// load textures
	// -------------
	unsigned int woodTexture = loadTexture("../Resources/textures/wood.png");

	//Set up the Material
	thisMaterial.shininess = 51.2;
	thisMaterial.ambient = vec4(0.24725, 0.1995, 0.0745, 1.0);
	thisMaterial.diffuse = vec4(0.75164, 0.60648, 0.22648, 1.0);
	thisMaterial.specular = vec4(0.62828, 0.5558, 0.36607, 1.0);

	//Set up the point light
	currentLight.position = vec4(-3.8f, 2.2f, 1.1f);
	currentLight.ambient = vec4(0.1, 0.1, 0.1);
	currentLight.diffuse = vec4(0.4, 0.4, 0.4);
	currentLight.specular = vec4(0.3, 0.3, 0.3);

	init();

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window, deltaTime);

		//currentLight.setPosition(lightLoc);
		aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;
		mat4 proj_matrix = mat4::perspective(50.0f, aspect, 0.1f, 1000.0f);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindFramebuffer(GL_FRAMEBUFFER, shadow_buffer[0]);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_tex[0], 0);

		glDrawBuffer(GL_NONE);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_POLYGON_OFFSET_FILL);	// for reducing
		glPolygonOffset(2.0f, 4.0f);			//  shadow artifacts

		passOne();

		glDisable(GL_POLYGON_OFFSET_FILL);	// artifact reduction, continued

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shadow_tex[0]);

		glDrawBuffer(GL_FRONT);

		passTwo();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &planeVBO);

	glfwTerminate();
	return 0;
}

void passOne()
{
	rendering_program1.use();

	vec4 origin = vec4(0.0, 0.0, 0.0);
	vec4 up = vec4(0.0, 1.0, 0.0);
	lightV_matrix = mat4();
	lightP_matrix = mat4();

	lightV_matrix = mat4::lookAt(currentLight.position, origin, up);	// vector from light to origin
	lightP_matrix = mat4::perspective(50.0f * toRadians, aspect, 0.1f, 1000.0f);

	// draw the torus

	m_matrix = mat4();
	m_matrix = mat4::translate(m_matrix, vec4(2.0f, -0.5f, -5.0f)); // translate it down so it's at the center of the scene
	m_matrix = mat4::scale(m_matrix, vec4(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

	shadowMVP1 = mat4();
	shadowMVP1 = shadowMVP1 * lightP_matrix;
	shadowMVP1 = shadowMVP1 * lightV_matrix;
	shadowMVP1 = shadowMVP1 * m_matrix;
	
	rendering_program1.setMat4("shadowMVP", shadowMVP1);

	//// set up torus vertices buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//glEnableVertexAttribArray(0);

	//glClear(GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	//glDrawArrays(GL_TRIANGLES, 0, numTorusVertices);
	nanosuit.Draw(rendering_program1);

	// ---- draw the pyramid
	//  build the MODEL matrix
	m_matrix = mat4();
	m_matrix = mat4::translate(m_matrix, vec4(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

	shadowMVP1 = mat4();
	shadowMVP1 = shadowMVP1 * lightP_matrix;
	shadowMVP1 = shadowMVP1 * lightV_matrix;
	shadowMVP1 = shadowMVP1 * m_matrix;

	rendering_program1.setMat4("shadowMVP", shadowMVP1);

	//// set up vertices buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//glEnableVertexAttribArray(0);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	//glDrawArrays(GL_TRIANGLES, 0, pyramid.getNumVertices());
	pyramid.Draw(rendering_program1);
}

void passTwo()
{
	rendering_program2.use();

	//  build the MODEL matrix
	m_matrix = mat4();
	m_matrix = mat4::translate(m_matrix, vec4(2.0f, -0.5f, -5.0f)); // translate it down so it's at the center of the scene
	m_matrix = mat4::scale(m_matrix, vec4(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

	//  build the VIEW matrix
	v_matrix = mat4();
	v_matrix = mat4::translate(v_matrix, camera.Position);

	installLights(rendering_program2, v_matrix);

	//  build the MODEL-VIEW matrix
	mv_matrix = mat4();
	mv_matrix = mv_matrix * v_matrix;
	mv_matrix = mv_matrix * m_matrix;

	shadowMVP2 = mat4();
	shadowMVP2 = shadowMVP2 * (b);
	shadowMVP2 = shadowMVP2 * (lightP_matrix);
	shadowMVP2 = shadowMVP2 * (lightV_matrix);
	shadowMVP2 = shadowMVP2 * (m_matrix);

	mat4 normalMat = mat4::transpose(mat4::inverse(mv_matrix));

	//  put the MV and PROJ matrices into the corresponding uniforms
	rendering_program2.setMat4("mv_matrix", mv_matrix);
	rendering_program2.setMat4("proj_matrix", proj_matrix);
	rendering_program2.setMat4("normalMat", normalMat);
	rendering_program2.setMat4("shadowMVP", shadowMVP2);

	// set up torus vertices buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//gl.glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//gl.glEnableVertexAttribArray(0);

	//// set up torus normals buffer
	//gl.glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	//gl.glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
	//gl.glEnableVertexAttribArray(1);

	//gl.glClear(GL_DEPTH_BUFFER_BIT);
	//gl.glEnable(GL_CULL_FACE);
	//gl.glFrontFace(GL_CCW);
	//gl.glEnable(GL_DEPTH_TEST);
	//gl.glDepthFunc(GL_LEQUAL);

	//gl.glDrawArrays(GL_TRIANGLES, 0, numTorusVertices);
	nanosuit.Draw(rendering_program2);

	// draw the pyramid
	installLights(rendering_program2, v_matrix);

	//  build the MODEL matrix
	m_matrix = mat4();
	m_matrix = mat4::translate(m_matrix, vec4(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

	//  build the MODEL-VIEW matrix
	mv_matrix = mat4();
	mv_matrix = mv_matrix * v_matrix;
	mv_matrix = mv_matrix * m_matrix;

	shadowMVP2 = mat4();
	shadowMVP2 = shadowMVP2 * (b);
	shadowMVP2 = shadowMVP2 * (lightP_matrix);
	shadowMVP2 = shadowMVP2 * (lightV_matrix);
	shadowMVP2 = shadowMVP2 * (m_matrix);

	normalMat = mat4::transpose(mat4::inverse(mv_matrix));

	rendering_program2.setMat4("mv_matrix", mv_matrix);
	rendering_program2.setMat4("proj_matrix", proj_matrix);
	rendering_program2.setMat4("normalMat", normalMat);
	rendering_program2.setMat4("shadowMVP", shadowMVP2);

	// set up vertices buffer
	//gl.glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//gl.glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//gl.glEnableVertexAttribArray(0);

	//// set up normals buffer
	//gl.glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	//gl.glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
	//gl.glEnableVertexAttribArray(1);

	//gl.glEnable(GL_CULL_FACE);
	//gl.glFrontFace(GL_CCW);
	//gl.glEnable(GL_DEPTH_TEST);
	//gl.glDepthFunc(GL_LEQUAL);

	//gl.glDrawArrays(GL_TRIANGLES, 0, pyramid.getNumVertices());
	pyramid.Draw(rendering_program2);

}

void renderScene(const Shader &shader) {
	// floor
	mat4 model;
	shader.setMat4("model", model);
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// render models
	model = mat4();
	model = mat4::translate(model, vec4(2.0f, -0.5f, -5.0f)); // translate it down so it's at the center of the scene
	model = mat4::scale(model, vec4(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	shader.setMat4("model", model);
	nanosuit.Draw(shader);

	model = mat4();
	model = mat4::translate(model, vec4(-2.0f, 0.75f, -5.0f)); // translate it down so it's at the center of the scene
	model = mat4::scale(model, 0.8f);	// it's a bit too big for our scene, so scale it down
	shader.setMat4("model", model);
	sphere.Draw(shader);

	model = mat4();
	model = mat4::translate(model, vec4(0.0f, 0.0f, -3.0f)); // translate it down so it's at the center of the scene
	model = mat4::scale(model, 0.8f);	// it's a bit too big for our scene, so scale it down
	shader.setMat4("model", model);
	cyborg.Draw(shader);

	model = mat4();
	model = mat4::translate(model, vec4(0.0f, -6.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = mat4::scale(model, 0.05f);	// it's a bit too big for our scene, so scale it down
	shader.setMat4("model", model);
	dragon.Draw(shader);

	model = mat4();
	model = mat4::translate(model, vec4(-5.0f, 2.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = mat4::scale(model, 1.0f);	// it's a bit too big for our scene, so scale it down
	shader.setMat4("model", model);
	pyramid.Draw(shader);
}

void init()
{
	setupShadowBuffers();

	b.m_elements[0][0] = 0.5; b.m_elements[0][1] = 0.0; b.m_elements[0][2] = 0.0; b.m_elements[0][3] = 0.5;
	b.m_elements[1][0] = 0.0; b.m_elements[1][1] = 0.5; b.m_elements[1][2] = 0.0; b.m_elements[1][3] = 0.5;
	b.m_elements[2][0] = 0.0; b.m_elements[2][1] = 0.0; b.m_elements[2][2] = 0.5; b.m_elements[2][3] = 0.5;
	b.m_elements[3][0] = 0.0; b.m_elements[3][1] = 0.0; b.m_elements[3][2] = 0.0; b.m_elements[3][3] = 1.0;

	// may reduce shadow border artifacts
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void setupShadowBuffers()
{
	scSizeX = SCR_WIDTH;
	scSizeY = SCR_HEIGHT;

	glGenFramebuffers(1, shadow_buffer);

	glGenTextures(1, shadow_tex);
	glBindTexture(GL_TEXTURE_2D, shadow_tex[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
		scSizeX, scSizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
}

void installLights(Shader rendering_program, mat4 v_matrix)
{
	Material currentMaterial = Material();
	currentMaterial = thisMaterial;

	vec4 lightP = currentLight.position;
	vec4 lightPv = mat4::mulVectorMatrix(lightP, v_matrix);

	vec4 currLightPos = vec4(lightPv.elts[0], lightPv.elts[1], lightPv.elts[2]);

	//rendering_program2.use();
	// set the current globalAmbient settings
	rendering_program.setVec4("globalAmbient", globalAmbient);

	// set the light and material fields in the shader
	rendering_program.setVec4("light.ambient", currentLight.ambient);
	rendering_program.setVec4("light.diffuse", currentLight.diffuse);
	rendering_program.setVec4("light.specular", currentLight.specular);
	rendering_program.setVec4("light.position", currLightPos);

	rendering_program.setVec4("material.ambient", currentMaterial.ambient);
	rendering_program.setVec4("material.diffuse", currentMaterial.diffuse);
	rendering_program.setVec4("material.specular", currentMaterial.specular);
	rendering_program.setFloat("material.shininess", currentMaterial.shininess);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, float deltaTime, btRigidBody *body)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		body->activate();
		body->setLinearVelocity(btVector3(0, 0, -1.1));
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		body->activate();
		body->setLinearVelocity(btVector3(0, 0, 1.1));
	}
		//cam.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		body->activate();
		body->setLinearVelocity(btVector3(1.1, 0, 0));
	}
		//cam.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		body->activate();
		body->setLinearVelocity(btVector3(-1.1, 0, 0));
	}
		//cam.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		wireFrame = true;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		wireFrame = false;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		debugPhysics = !debugPhysics;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		body->activate();
		body->setLinearVelocity(btVector3(0, 3, 0));
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		wireFrame = true;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		wireFrame = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

	//	if (firstMouse)
	//	{
	//		lastX = xpos;
	//		lastY = ypos;
	//		firstMouse = false;
	//	}

	//	float xoffset = xpos - lastX;
	//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	//	lastX = xpos;
	//	lastY = ypos;

	//	cam.ProcessMouseMovementOther(xoffset, yoffset);
	//}
	lastX = xpos;
	lastY = ypos;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(std::string filename)
{
	unsigned int textureID = 0;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

