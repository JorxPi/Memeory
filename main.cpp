#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "ScriptManager.h"
#include "BallScript.h"
#include "PaddleScript.h"
#include "BlockScript.h"
#include "Script.h"
#include "CardScript.h"
#include "GameManager.h"
#include "TextScript.h"
#include "ButtonScript.h"

#include "ECS.h"

using std::cout;
using std::endl;
using namespace ECS;

GLFWwindow* window; // Game window
const unsigned int width = 800;
const unsigned int height = 800;

float t = 0;
time_t current_time;

World* world;

void SetupGLFW() {

	glfwInit();

	// Tell GLFW we are using OpenGL 3.3 and the CORE profile (only the modern functions)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

bool SetupWindow() {
	//Create a GLFWwindow with size 800x800
	window = glfwCreateWindow(800, 800, "ProgramacioVideojocs", NULL, NULL);
	if (window == NULL) {

		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make window part of the current context
	glfwMakeContextCurrent(window);

	//Load GLAD and specify the viewport
	gladLoadGL();
	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

Entity* CreateEntity(glm::vec2 position, float rotation, float scale, const char* filepath, glm::vec3 color,
	bool autoSize = true, glm::vec2 size = glm::vec2(1.0, 1.0), const char* shaderName = "default") {
	Entity* ent = world->create();
	ent->assign<Transform>(position, rotation, scale);
	ent->assign<Sprite>(filepath, color, autoSize, size, shaderName);

	return ent;
}

/*Entity* CreateGameOverEntity() {
	Entity* ent = world->create();
	ent->assign<Transform>(glm::vec2(300.f, 300.f), 0.f, 1.f);
	ent->assign<Sprite>("Textures/win.png", glm::vec3(1., 1., 1.), true, glm::vec2(1.0, 1.0), "default");
	ent->get<Sprite>()->visible = false; // Set visibility to false initially
	return ent;
}*/

void SetupWorldOld() {

	//cout << "World" << endl;

	world = World::createWorld();
	world->registerSystem(new RenderSystem(width, height));
	ScriptSystem* scriptSystem = new ScriptSystem();
	world->registerSystem(scriptSystem);

	ScriptManager* scriptManager = scriptSystem->getScriptManager();

	Entity* bg_ent = CreateEntity(glm::vec2(400.f, 400.f), 0.f, 1.f, "Textures/background_brown.png", glm::vec3(1., 1., 1.), false, glm::vec2(width, height), "repeating");

	Entity* paddle_ent = CreateEntity(glm::vec2(400.f, 700.f), 0.f, 1.f, "Textures/button_yellow.png", glm::vec3(1., 1., 1.));
	paddle_ent->assign<BoxCollider>(128.f, 53.f);

	Entity* ball_ent = CreateEntity(glm::vec2(400.f, 300.f), 0.f, 1.f, "Textures/ball_blue_small.png", glm::vec3(1., 1., 1.));
	ball_ent->assign<BoxCollider>(32.f, 32.f);

	BallScript* ball_script = new BallScript(window, world, ball_ent);
	ball_ent->assign<ScriptComponent>(scriptManager->AddScript(ball_script));

	scriptManager->tickScript(0, 0);

	PaddleScript* paddle_script = new PaddleScript(window, world, paddle_ent);
	paddle_ent->assign<ScriptComponent>(scriptManager->AddScript(paddle_script));

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			Entity* block_ent = CreateEntity(glm::vec2(140.f + 128.f * i, 100.f + 53.f * j), 0.f, 1.f, "Textures/button_blue.png", glm::vec3(1., 1., 1.));
			block_ent->assign<BoxCollider>(128.f, 53.f);

			BlockScript* block_script = new BlockScript(window, world, block_ent);
			block_ent->assign<ScriptComponent>(scriptManager->AddScript(block_script));
		}
	}

}

void SetupWorld() {

	world = World::createWorld();
	world->registerSystem(new RenderSystem(width, height));
	ScriptSystem* scriptSystem = new ScriptSystem();
	world->registerSystem(scriptSystem);

	ScriptManager* scriptManager = scriptSystem->getScriptManager();
	GameManager* gameManager = new GameManager();

	Entity* welcome_entity = CreateEntity(glm::vec2(400.f, 300.f), 0.f, 1.f, "Textures/Memeory.png", glm::vec3(1., 1., 1.), false, glm::vec2(484., 98.));
	welcome_entity->get<Sprite>()->shaderName = "memeory";

	TextScript* welcome_script = new TextScript(window, world, welcome_entity);
	welcome_entity->assign<ScriptComponent>(scriptManager->AddScript(welcome_script));

	Entity* start_button = CreateEntity(glm::vec2(400.f, 500.f), 0.f, 1.f, "Textures/Start_game.png", glm::vec3(1., 1., 1.), false, glm::vec2(210., 90.));
	start_button->assign<BoxCollider>(210.f, 90.f);

	ButtonScript* start_script = new ButtonScript(window, world, start_button);
	start_button->assign<ScriptComponent>(scriptManager->AddScript(start_script));

	start_script->setTextScriptRef(welcome_script);
	start_script->setGameManagerRef(gameManager);

	Entity* memeory_entity = CreateEntity(glm::vec2(400.f, 75.f), 0.f, 1.f, "Textures/Memeory.png", glm::vec3(1., 1., 1.), true);
	memeory_entity->get<Sprite>()->visible = false;

	TextScript* memeory_script = new TextScript(window, world, memeory_entity);
	memeory_entity->assign<ScriptComponent>(scriptManager->AddScript(memeory_script));

	int cardList[] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7 };
	int cardDeckSize = sizeof(cardList) / sizeof(cardList[0]);;
	int pick = 0;

	gameManager->shuffleCardsId(cardList, cardDeckSize);

	/*cout << cardList[0] << " ";
	cout << cardList[1] << " ";
	cout << cardList[2] << " ";
	cout << cardList[3] << " ";
	cout << cardList[4] << " ";
	cout << cardList[5] << " ";
	cout << cardList[6] << " ";
	cout << cardList[7] << " ";
	cout << cardList[8] << " ";
	cout << cardList[9] << " ";
	cout << cardList[10] << " ";
	cout << cardList[11] << " ";
	cout << cardList[12] << " ";
	cout << cardList[13] << " ";
	cout << cardList[14] << " ";
	cout << cardList[15] << " ";
	cout << cardList[15] << " ";*/

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Entity* card_ent = CreateEntity(glm::vec2(125.f + 175.f * i, 175.f + 175.f * j), 0.f, 1.f, "Textures/descarga.png", glm::vec3(1., 1., 1.), false, glm::vec2(96., 96.));
			card_ent->assign<BoxCollider>(96.f, 96.f);
			card_ent->get<Sprite>()->visible = false;

			CardScript* card_script = new CardScript(window, world, card_ent);
			card_ent->assign<ScriptComponent>(scriptManager->AddScript(card_script));

			gameManager->setCardsScriptListRef(card_script, (i * 4) + j);

			card_script->assignIdAndPos(cardList[pick], i, j);
			card_script->setGameManagerRef(gameManager);
			//cout << "Card ID: " << card_script->getId() << endl;
			pick++;
		}
	}

	Entity* win_entity = CreateEntity(glm::vec2(400.f, 225.f), 0.f, 1.f, "Textures/Win.png", glm::vec3(1., 1., 1.), false, glm::vec2(633., 147.));
	win_entity->get<Sprite>()->visible = false;

	TextScript* win_script = new TextScript(window, world, win_entity);
	win_entity->assign<ScriptComponent>(scriptManager->AddScript(win_script));

	Entity* pro_entity = CreateEntity(glm::vec2(400.f, 475.f), 0.f, 1.f, "Textures/que_pro.png", glm::vec3(1., 1., 1.), false, glm::vec2(512., 288.));
	pro_entity->get<Sprite>()->visible = false;

	TextScript* pro_script = new TextScript(window, world, pro_entity);
	pro_entity->assign<ScriptComponent>(scriptManager->AddScript(pro_script));

	gameManager->setTextScriptRef(win_script, memeory_script, pro_script);

}

int main() {

	SetupGLFW();

	if (!SetupWindow()) {
		return -1;
	}

	SetupWorld();

	float dt = 0;
	float time = clock();

	//Program core loop
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		dt = clock() - time;
		time = clock();
		if (dt < 50) {
			world->tick(dt);
		}


		//std::cout << "tick" << std::endl;
		//std::cout << dt << std::endl;

		glfwSwapBuffers(window); //Swap buffers

		// Take care of GLFW events
		glfwPollEvents();
	}

	// Cleanup

	glfwDestroyWindow(window);
	glfwTerminate();

	world->destroyWorld();

	return 0;
}