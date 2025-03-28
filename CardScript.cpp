#include "CardScript.h"

void CardScript::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();
	ComponentHandle<Sprite> sprite = entity->get<Sprite>();

	if (sprite->visible) {
		if (!flipped) {
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				double mouseX, mouseY;
				glfwGetCursorPos(window, &mouseX, &mouseY);


				if (mouseX >= transform->position.x - collider->width / 2.0f && mouseX <= transform->position.x + collider->width / 2.0f &&
					mouseY >= transform->position.y - collider->height / 2.0f && mouseY <= transform->position.y + collider->height / 2.0f) {
					//cout << "Click Card " << (ypos * 4) + xpos << endl;
					flipCard();
				}

			}
		}
	}

}

void CardScript::assignIdAndPos(int numId, int xpos, int ypos) {
	id = numId;
	this->xpos = xpos;
	this->ypos = ypos;
}

void CardScript::flipCard() {
	ComponentHandle<Sprite> sprite = entity->get<Sprite>();

	switch (id) {
	case 0:
		sprite->filepath = "Textures/science_dog.png";
		break;
	case 1:
		sprite->filepath = "Textures/meme_id_1.png";
		break;
	case 2:
		sprite->filepath = "Textures/meme_id_2.png";
		break;
	case 3:
		sprite->filepath = "Textures/meme_id_3.png";
		break;
	case 4:
		sprite->filepath = "Textures/meme_id_4.png";
		break;
	case 5:
		sprite->filepath = "Textures/meme_id_5.png";
		break;
	case 6:
		sprite->filepath = "Textures/meme_id_6.png";
		break;
	case 7:
		sprite->filepath = "Textures/meme_id_7.png";
		break;
	}

	flipped = true;

	gameRef->flipCard(this);

}

void CardScript::unflipCard() {
	ComponentHandle<Sprite> sprite = entity->get<Sprite>();
	sprite->filepath = "Textures/descarga.png";
	flipped = false;
}

void CardScript::setGameManagerRef(GameManager* gmr) {
	gameRef = gmr;
}

void CardScript::turnVisible(bool vis) {
	ComponentHandle<Sprite> sprite = entity->get<Sprite>();

	sprite->visible = vis;
}