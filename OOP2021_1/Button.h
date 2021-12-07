#pragma once
#include <iostream>
#include "Input.h"
#include "GameObject.h"
#include "Position.h"
#include "Renderer.h"
#include <functional>

using namespace std;

class Button : public Renderer
{
	function<void(void)> onClick;
	string text;
protected:
	Input* input;
public:
	Button(GameObject* gameObject)
		:Renderer(gameObject, nullptr, gameObject->getRenderer()->getDimension() + Position::ones) {}
	
	void setText(const string& text) { this->text = text; }

	void isButtonDown(std::function<void(void)> onClick = []() {})
	{
		this->onClick = onClick;
	}

	void draw() override {
		Position pos = transform->local2World();
		screen->drawRectangle({ pos.x - 1, pos.y - 1 }, { dim.x, dim.y });
		if (text.length() == 0) return;
		screen->draw({ pos.x + 1, pos.y + 1 }, text.c_str());
	}

	bool isInside(const Position& pos)
	{
		return gameObject->getTransform()->getPosition().x < pos.x
			&& pos.x < Renderer::getTransform()->getPosition().x + Renderer::getWidth() &&
			gameObject->getTransform()->getPosition().y < pos.y
			&& pos.x < Renderer::getTransform()->getPosition().y + Renderer::getHeight();
	}


	void update() override {
		/*if (!input->getMouseButtonDown(1))return;
		auto pos = input->getMousePosition();
		if (isInside(pos)) onClick();*/
		
	}
};

