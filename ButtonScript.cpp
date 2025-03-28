#include "ButtonScript.h"

void ButtonScript::tickScript(float deltaTime) {
	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();
	ComponentHandle<Sprite> sprite = entity->get<Sprite>();

	if (!clicked) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			if (mouseX >= transform->position.x - collider->width / 2.0f && mouseX <= transform->position.x + collider->width / 2.0f &&
				mouseY >= transform->position.y - collider->height / 2.0f && mouseY <= transform->position.y + collider->height / 2.0f) {
				//cout << "Button Clicked " << endl;
				clicked = true;

				sprite->visible = false;

				welcRef->turnVisible(false);

				gameRef->startGame();
			}
		}
	}
}

void ButtonScript::setTextScriptRef(TextScript* welcs) {
	welcRef = welcs;
}

void ButtonScript::setGameManagerRef(GameManager* gmr) {
	gameRef = gmr;
}