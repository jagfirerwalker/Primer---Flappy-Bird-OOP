// Flappy Bird Clone - Object-oriented Programming in C++

#include <SFML/Graphics.hpp>
#include <iostream>

// Bird class
class Bird {
private:
	sf::Texture birdTexture;
	sf::Sprite birdSprite;
	sf::Vector2f birdVelocity;
	float gravity;
	float flapStrength;

public:
	Bird() {
		// Load the bird texture
		if (!birdTexture.loadFromFile("bird.png")) {
			std::cout << "Error loading bird.png" << std::endl;
		}
		birdSprite.setTexture(birdTexture);

		// Set the initial position of the bird
		birdSprite.setPosition(200, 144);
		birdSprite.setScale(1.0f, 1.0f);

		// Initial velocity, gravity and flap strength
		birdVelocity = sf::Vector2f(0, 0);
		gravity = 0.05;
		flapStrength = -1.0f;
	}

	void flap() {
		// Apply flap strength to the bird's velocity
		birdVelocity.y = flapStrength;
	}

	void update() {
		// Apply gravity to the bird's velocity
		birdVelocity.y += gravity;

		// Limit the maximum falling speed
		const float maxFallSpeed = 0.5;
		if (birdVelocity.y > maxFallSpeed) {
			birdVelocity.y = maxFallSpeed;
		}	

		// Update the position of the bird
		birdSprite.move(birdVelocity);
	}

	// Draw the bird on the window
	void draw(sf::RenderWindow& window) const {
		// Draw the bird sprite
		window.draw(birdSprite);
	}

	sf::Vector2f getPosition() const {
		return birdSprite.getPosition();
	}
};

int main() {
	// create the game window
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Flappy Bird");

	// Create the background sprite
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");
	sf::Sprite backgroundSprite(backgroundTexture);
	//backgroundSprite.setScale(1.0f, 2.0f);

	// Create the bird object
	Bird bird;

	// Game loop
	while (window.isOpen()) {
		// Handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close the window when the close button is clicked
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			// Handle spacebar key press to make the bird flap
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				bird.flap();
			}
		}

		// Update the bird
		bird.update();

		// Clear the window
		window.clear();

		// Draw the background
		window.draw(backgroundSprite);

		// Draw the bird
		bird.draw(window);

		std::cout << "Bird position: " << bird.getPosition().x << ", " << bird.getPosition().y << std::endl;

		// Display the window
		window.display();
	}

	return 0;
}