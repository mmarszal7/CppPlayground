#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = 500;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(300.f, 300.0f));
	body.setPosition(256.f, 256.f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0 * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0)
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	if (velocity.y < 0)
		row = 3;

	if (velocity.y > 10)
		row = 0;

	if (abs(velocity.x) > 1 || abs(velocity.y) > 5)
		animation.Update(row, deltaTime, faceRight);

	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}

	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
