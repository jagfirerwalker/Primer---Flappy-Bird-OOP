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
		gravity = 0.005;
		flapStrength = -1.0f;
	}

	void flap() {
		// Apply flap strength to the bird's velocity
		birdVelocity.y = flapStrength;
	}

	void update(const sf::RenderWindow& window) {
		// Apply gravity to the bird's velocity
		birdVelocity.y += gravity;

		// Update the position of the bird
		birdSprite.move(birdVelocity);

		// Keep the bird within the window bounds
		sf::Vector2f birdPosition = birdSprite.getPosition();
		sf::FloatRect birdBounds = birdSprite.getGlobalBounds();

		// Check if the bird is above the window bounds
		if (birdPosition.y < 0) {
			birdSprite.setPosition(birdPosition.x, 0);
			birdVelocity.y = -birdVelocity.y * 0.08f; // Reverse the velocity and apply damping
		}

		// Check if the bird is going below the window bounds
		if (birdPosition.y + birdBounds.height > window.getSize().y) {
			birdSprite.setPosition(birdPosition.x, window.getSize().y - birdBounds.height);
			birdVelocity.y = -birdVelocity.y * 0.8f; // Reverse the velocity and apply damping
		}
	}

	// Draw the bird on the window
	void drawBird(sf::RenderWindow& window) const {
		// Draw the bird sprite
		window.draw(birdSprite);
	}

	sf::Vector2f getVelocity() const {
		return birdVelocity;
	}
};

int main() {
	// create the game window
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Flappy Bird");

	// Create the background sprite
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");
	sf::Sprite backgroundSprite(backgroundTexture);


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
		bird.update(window);

		// Clear the window
		window.clear();

		// Draw the background
		window.draw(backgroundSprite);

		// Draw the bird
		bird.drawBird(window);

		std::cout << "Bird position: " << bird.getVelocity().x << ", " << bird.getVelocity().y << std::endl;

		// Display the window
		window.display();
	}

	return 0;
}