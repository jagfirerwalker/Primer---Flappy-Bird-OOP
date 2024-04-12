// Flappy Bird Clone - Object-oriented Programming in C++

#include <SFML/Graphics.hpp>
#include <iostream>


// BIRD CLASS

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
	sf::Vector2f getPosition() const;
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

// get bird position
sf::Vector2f Bird::getPosition() const {
	return sprite.getPosition();
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



// SCROLLING GROUND CLASS

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

// EXIT SCREEN CLASS

class ExitScreen {
private:
	sf::RectangleShape backgroundBox;
	sf::Text text_heading;
	sf::Text text_body;

public:
	sf::Font font;
	ExitScreen(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window) const;
	bool isVisible;
};

// ExitScreen font, background and text setup
ExitScreen::ExitScreen(const sf::Vector2u& windowSize) : isVisible(false) {
	// Load the font
	if (!font.loadFromFile("assets/arial.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}

	// Set up the background box
	backgroundBox.setSize(sf::Vector2f(400.0f, 100.0f));
	backgroundBox.setFillColor(sf::Color::Black);
	backgroundBox.setPosition(
		(windowSize.x - backgroundBox.getGlobalBounds().width) / 2.0f, // center the box horizontally
		(windowSize.y - backgroundBox.getGlobalBounds().height) / 2.0f // center the box vertically
	);

	text_heading.setFont(font);
	text_heading.setString("Game Over!");
	text_heading.setCharacterSize(40);
	text_heading.setFillColor(sf::Color::White);
	text_heading.setPosition(
		(windowSize.x - text_heading.getGlobalBounds().width) / 2.0f, // center the text horizontally
		(windowSize.y - text_heading.getGlobalBounds().height) / 2.0f - 20.0f // center the text vertically
	);

	text_body.setFont(font);
	text_body.setString("Press 'Space' to Restart");
	text_body.setCharacterSize(24);
	text_body.setFillColor(sf::Color::White);
	text_body.setPosition(
		(windowSize.x - text_body.getGlobalBounds().width) / 2.0f, // center the text horizontally
		(windowSize.y - text_body.getGlobalBounds().height) / 2.0f // center the text vertically
	);

}

// Draw the ExitScreen when isVisible is true
void ExitScreen::draw(sf::RenderWindow& window) const {
	if (isVisible) {
		window.draw(backgroundBox);
		window.draw(text_heading);
		window.draw(text_body);
	}
}

// StartScreen class
// Start screen to display before the game starts
class StartScreen {
private:
	sf::RectangleShape backgroundBox;
	sf::Text text;

public:
	sf::Font font;
	StartScreen(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window) const;
	bool isVisible;
};

// StartScreen font, background and text setup
StartScreen::StartScreen(const sf::Vector2u& windowSize) : isVisible(true) {
	// Load the font
	if (!font.loadFromFile("assets/arial.ttf")) {
		std::cout << "Error loading front" << std::endl;
	}

	// Set up the background box
	backgroundBox.setSize(sf::Vector2f( 400.0f, 100.0f));
	backgroundBox.setFillColor(sf::Color::Black);
	backgroundBox.setPosition(
		(windowSize.x - backgroundBox.getSize().x) / 2.0f,
		(windowSize.y - backgroundBox.getSize().y) / 2.0f
	);

	// Set up the text
	text.setFont(font);
	text.setString("Press 'Space' to Start");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(
		(windowSize.x - text.getGlobalBounds().width) / 2.0f,
		(windowSize.y - text.getGlobalBounds().height) / 2.0f
	);

}

// Draw the StartScreen when isVisible is true
void StartScreen::draw(sf::RenderWindow& window) const {
	if (isVisible) {
		window.draw(backgroundBox);
		window.draw(text);
	}
}

// FLOATING WORDS CLASS FUNCTIONS


// Class to display floating words on the screen
class FloatingWords {
private:
	sf::Font font;
	float speed;
	float spawnInterval;
	float startTime;

public:
	FloatingWords(const std::string& filePath, const sf::Font& font, float speed, float speedspawnIntervalInterval, const sf::Vector2u& windowSize);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	bool isVisible;
	void setStartTime(float time); 
    sf::FloatRect getBounds(size_t index) const; // Move this function inside the class	
	std::vector<sf::Text> words;
	std::vector<float> spawnTimes;
};

// Load words from file and set their position and speed
// push_back words and spawn times to vectors
FloatingWords::FloatingWords(const std::string& filePath, const sf::Font& font, float speed, float spawnInterval, const sf::Vector2u& windowSize)
	: font(font), speed(speed), spawnInterval(spawnInterval), isVisible(false), startTime(-1.0f) {

	// Read the text from the file

	std::ifstream file(filePath);
	if (file.is_open()) {
		std::string word;
		float currentTime = 0.0f; // Set the current time to 0

		while (file >> word) { // Read each word from the file
			sf::Text text;
			text.setFont(font);
			text.setString(word);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setPosition(windowSize.x, std::rand() % (windowSize.y - static_cast<int>(text.getGlobalBounds().height)));
			words.push_back(text);
			spawnTimes.push_back(currentTime);
			currentTime += spawnInterval;
		}
		file.close();

	}
	
}

// Get the bounds of the floating words
sf::FloatRect FloatingWords::getBounds(size_t index) const {
	return words[index].getGlobalBounds();
}

// Update floating words position by moving them to the left
// if the start time is greater than 0, move the words to the left
void FloatingWords::update(float deltaTime) {
	if (startTime >= 0.0f) {
		float elapsedTime = deltaTime - startTime;
		for (size_t i = 0; i < words.size(); i++) {
			if (spawnTimes[i] <= elapsedTime) {
				words[i].move(-speed * deltaTime, 0);
			}
			else {
				spawnTimes[i] -= deltaTime;
			}
		}
	}
}

// Set the start time to the current time
void FloatingWords::setStartTime(float time) {
	startTime = time;
}

// Draw floating words on window if isVisible is true
void FloatingWords::draw(sf::RenderWindow& window) const {
	if (isVisible) {
		for (const auto& word : words) {
			window.draw(word);
		}
	}
}


// GAME SETUP 


// Game Class
class Game {
private :
	sf::RenderWindow window;
	Bird bird;
	ScrollingBackground background;
	ScrollingGround ground;
	bool firstSpacePress;
	const float frameRate = 60.0f;
	StartScreen startScreen;
	FloatingWords floatingWords;
	float gameStartTime;
	sf::Clock gameClock;
	ExitScreen exitScreen;

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
	startScreen(window.getSize()), // use window size to place start screen
	floatingWords("assets/James Henry - Pigeons.txt", startScreen.font, 100.0f, 1.0f, window.getSize()), // setting floating words file, font, speed, interval and window size
	firstSpacePress(true), // setting first space press to true
	gameStartTime(0.0f), // setting game start time to 0
	exitScreen(window.getSize()) // setting exit screen to window size
	{}  


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

// Update game objects (bird, background, check for collision)
void Game::update(float deltaTime) {
	bird.update(!firstSpacePress); // update bird position
	background.update(deltaTime); // update background position
	ground.update(deltaTime); // update ground position

	// Check for collision between bird, window bounds and floating words
	sf::FloatRect birdBounds = bird.getBrounds();

	for (size_t i = 0; i < floatingWords.words.size(); i++) {
		if (floatingWords.spawnTimes[i] <= gameClock.getElapsedTime().asSeconds() - gameStartTime) {
			sf::FloatRect wordBounds = floatingWords.getBounds(i);
			if (birdBounds.intersects(wordBounds)) {
				bird.setPosition(sf::Vector2f(-100.0f, -100.0f)); // move bird off screen
				floatingWords.isVisible = false; // hide floating words
				exitScreen.isVisible = true; // show exit screen
				break;
			}
		}
	}

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
	if (bird.getPosition().x >= 0 && bird.getPosition().y >= 0) {
		bird.draw(window);
	}
	startScreen.draw(window);
	exitScreen.draw(window);
	floatingWords.draw(window);
	window.display();

}


// MAIN FUNCTION


// Main function to run the game
int main() {

	Game game; // creating game object
	game.run(); // running game
	return 0;	
}