// Flappy Bird Clone - Object-oriented Programming in C++

#include <SFML/Graphics.hpp>

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
		birdTexture.loadFromFile("bird.png");
		birdSprite.setTexture(birdTexture);


		// Set the initial position of the bird
		birdSprite.setPosition(100, 200);
		birdSprite.setScale(0.1f, 0.1f);

		// Initial velocity, gravity and flap strength
		velocity = sf::Vector2f(0, 0);
		gravity = 0.5f;
		flapStrength = -8.0f;
	}

	void flap() {
		// Apply flap strength to the bird's velocity
		velocity.y = flapStrength;
	}

	void update() {
		// Apply gravity to the bird's velocity
		velocity.y += gravity;

		// Update the position of the bird
		birdSprite.move(velocity);
	}

	// Draw the bird on the window
	void draw(sf::RenderWindow& window) {
		// Draw the bird sprite
		window.draw(birdSprite);
	}
};

int main() {
	// create the game window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");

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
		bird.update();

		// Clear the window
		window.clear();

		// Draw the background
		window.draw(backgroundSprite);

		// Draw the bird
		bird.draw(window);

		// Display the window
		window.display();
	}

	return 0;
}