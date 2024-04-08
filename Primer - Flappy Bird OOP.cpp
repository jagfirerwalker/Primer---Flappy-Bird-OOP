// Flappy Bird Clone - Object-oriented Programming in C++

#include <SFML/Graphics.hpp>
#include <iostream>

// Bird class
class Bird {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	float gravity;
	float flapStrength;

public:
	Bird(const std::string& texturePath, const sf::Vector2f& position);
	void flap();
	void update(bool gravityEnabled = true);
	void draw(sf::RenderWindow& window) const;
	sf::FloatRect getBrounds() const;
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& velocity);
};

// Bird class functions
// Constructor setting bird texture and position, gravity and flap strength
Bird::Bird(const std::string& texturePath, const sf::Vector2f& position)
	: gravity(0.0005f), flapStrength(-0.5f) {
	if (!texture.loadFromFile(texturePath)) {
		std::cout << "Error loading bird texture" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setScale(1.0f, 1.0f);

}

// Flap function to make bird jump
void Bird::flap() {
	velocity.y = flapStrength;
}

// Update bird position by applying gravity
void Bird::update(bool gravityEnabled) {
	if (gravityEnabled) {
		velocity.y += gravity;
	}
	sprite.move(velocity);
}

// Draw bird on window
void Bird::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}

// Get bird bounds for collision detection
sf::FloatRect Bird::getBrounds() const {
	return sprite.getGlobalBounds();
}

// Get and set bird position for collision detection
void Bird::setPosition(const sf::Vector2f& position) {
	sprite.setPosition(position);
}

// Get and set bird velocity for gravity and jumping
sf::Vector2f Bird::getVelocity() const {
	return velocity;
}

// Set bird velocity for gravity and jumping
void Bird::setVelocity(const sf::Vector2f& velocity) {
	this -> velocity = velocity;
}



// ScrollingBackground class
class ScrollingBackground {
private:
	sf::Texture texture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	float scrollSpeed;

public:
	ScrollingBackground(const std::string& texturePath, float scrollSpeed);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
};

// ScrollingBackground class functions
// Constructor setting background texture and scroll speed
ScrollingBackground::ScrollingBackground(const std::string& texturePath, float scrollSpeed)
	: scrollSpeed(scrollSpeed) {
	if (!texture.loadFromFile(texturePath)) {
		std::cout << "Error loading background texture" << std::endl;
	}
	sprite1.setTexture(texture);
	sprite2.setTexture(texture);
	sprite2.setPosition(texture.getSize().x, 0); // setting second background sprite position to the right of the first sprite
}

// Update background position by scrolling it to the left
void ScrollingBackground::update(float deltaTime) {
	float scrollOffset = scrollSpeed * deltaTime;
	sprite1.move(-scrollOffset, 0);
	sprite2.move(-scrollOffset, 0);

	// Wrap the background sprites when they go off the screen
	if (sprite1.getPosition().x <= -sprite1.getTextureRect().width) {
		sprite1.setPosition(sprite2.getPosition().x + sprite2.getTextureRect().width, 0);
	}
	if (sprite2.getPosition().x <= -sprite2.getTextureRect().width) {
		sprite2.setPosition(sprite1.getPosition().x + sprite1.getTextureRect().width, 0);
	}
}

// Draw background on window
void ScrollingBackground::draw(sf::RenderWindow& window) const {
	window.draw(sprite1);
	window.draw(sprite2);
}

// Ground class
class ScrollingGround {
private:
	sf::Texture texture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	float scrollSpeed;

public:
	ScrollingGround(const std::string& texturePath, float scrollSpeed, const sf::Vector2u& windowSize);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
};

// Ground class functions
// Constructor setting ground texture and scroll speed
ScrollingGround::ScrollingGround(const std::string& texturePath, float scrollSpeed, const sf::Vector2u& windowSize)
	: scrollSpeed(scrollSpeed) {
	if (!texture.loadFromFile(texturePath)) {
		std::cout << "Error loading ground texture" << std::endl;
	}
	sprite1.setTexture(texture);
	sprite2.setTexture(texture);
	sprite1.setPosition(0, windowSize.y - texture.getSize().y); // setting first ground sprite position at the bottom of the window
	sprite2.setPosition(texture.getSize().x, windowSize.y - texture.getSize().y); // setting second ground sprite position to the right of the first sprite
}

// Update ground position by scrolling it to the left
void ScrollingGround::update(float deltaTime) {
	float scrollOffset = scrollSpeed * deltaTime;
	sprite1.move(-scrollOffset, 0);
	sprite2.move(-scrollOffset, 0);

	// Get the width of the sprite
	float spriteWidth = sprite1.getTextureRect().width;

	// Wrap the ground sprites when they go off the screen
	if (sprite1.getPosition().x <= -spriteWidth) {
		sprite1.setPosition(sprite2.getPosition().x + spriteWidth, sprite1.getPosition().y);
	}
	if (sprite2.getPosition().x <= -spriteWidth) {
		sprite2.setPosition(sprite1.getPosition().x + spriteWidth, sprite2.getPosition().y);
	}


}

// Draw ground on window
void ScrollingGround::draw(sf::RenderWindow& window) const {
	window.draw(sprite1);
	window.draw(sprite2);
}
// Game Class
class Game {
private :
	sf::RenderWindow window;
	Bird bird;
	ScrollingBackground background;
	ScrollingGround ground;
	bool firstSpacePress;

public:
	Game();
	void run();
	
private:
	void processEvents();
	void update(float deltaTime);
	void render();
};

// Game class functions
// Constructor setting window size and title, bird file and position, background file and scroll speed
Game::Game()
	: window(sf::VideoMode(1440, 1080), "Flappy Bird"), // setting window size and title
	bird("assets/bird.png", sf::Vector2f(200.0f, window.getSize().y / 2)), // setting bird file and position
	background("assets/background.png", 150.0f), // setting backgound file and scroll speed
	ground("assets/ground.png", 50.0f, window.getSize()),  // placing ground file
	firstSpacePress(true) {} // setting first space press to true

// Game run function
void Game::run() {
	sf::Clock clock; // creating clock object to measure time
	while (window.isOpen()) {
		processEvents(); // check for user input
		sf::Time elapsed = clock.restart(); // get time elapsed since last restart
		update(elapsed.asSeconds()); // update the game objects (bird and background)
		render();
	}
}

// Get user input events => close window or flap bird (space key)
void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
			if (firstSpacePress) {
				bird.update(firstSpacePress); // update bird position and enable gravity
				firstSpacePress = false; // set first space press to false

			}
			bird.flap(); // flap bird when space key is pressed
		}
	}
}

// Update game objects (bird and background)
void Game::update(float deltaTime) {
	bird.update(!firstSpacePress); // update bird position
	background.update(deltaTime); // update background position
	ground.update(deltaTime); // update ground position

	sf::FloatRect birdBounds = bird.getBrounds();
	if (birdBounds.top < 0) {
		bird.setPosition(sf::Vector2f(birdBounds.left, 0));
		bird.setVelocity(sf::Vector2f(bird.getVelocity().x, -bird.getVelocity().y * 0.3f));
	}
	else if (birdBounds.top + birdBounds.height > window.getSize().y) {
		bird.setPosition(sf::Vector2f(birdBounds.left, window.getSize().y - birdBounds.height));
		bird.setVelocity(sf::Vector2f(bird.getVelocity().x, -bird.getVelocity().y * 0.5f));
	}

}

void Game::render() {
	window.clear();
	background.draw(window);
	ground.draw(window);
	bird.draw(window);
	window.display();

}

// Main function
int main() {

	Game game; // creating game object
	game.run(); // running game
	return 0;	
}