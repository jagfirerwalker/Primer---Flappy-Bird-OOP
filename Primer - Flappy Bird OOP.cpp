// Flappy Bird Clone - Object-oriented Programming in C++
// Possible pivot: Make it based on poem like the one from Tomorrow tomorrow and Tomorrow
// Poem  from Emily Dickinson
		//That Love is is all there is,
		//Is all we know of Love;
		//It is enough, the freight should be
		//Proportioned to the groove.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


// CLOUD CLASS
class Cloud {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	float cloudFloatSpeed;
	float respawnXPosition;

public:
	Cloud(const std::string& texturePath, float cloudFloatSpeed, float respawnXPosition);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	bool isOffScreen() const;
};

// Cloud class functions
// Constructore setting cloud texture and speed of cloud float
Cloud::Cloud(const std::string& texturePath, float cloudFloatSpeed, float respawnXPosition)
	: cloudFloatSpeed(cloudFloatSpeed), respawnXPosition(respawnXPosition) {
	if (!texture.loadFromFile(texturePath)) {
		std::cout << "Error loading cloud texture" << std::endl;
	}
	// Set the cloud sprite 
	sprite.setTexture(texture);
	sprite.setPosition(std::rand() % static_cast<int>(respawnXPosition), std::rand() % 500); // Set the cloud position to a random position on the y-axis

}

// Draw cloud on window, spawn multiple on screen and respawning it when it goes off the screen
void Cloud::update(float deltaTime){
	// Move the cloud to the left
	sprite.move(-cloudFloatSpeed * deltaTime, 0); // Move the cloud to the left, based on the frame rate


	// Respawn the cloud when it goes off the screen
	if (isOffScreen()) { // Check if the cloud has gone off the screen
		sprite.setPosition(respawnXPosition, std::rand() % 500); // Respawn the cloud to the right of the window
	}
}

// Check if the cloud has gone off the screen
void Cloud::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}

// Check if the cloud has gone off the screen
bool Cloud::isOffScreen() const {
	return sprite.getPosition().x < -sprite.getTextureRect().width;
}



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
	: gravity(0.0003f), flapStrength(-0.3f) {
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
		velocity.y += gravity * 60.0f; // Multiply gravity by the frame rate
	}
	sprite.move(velocity * 60.0f);
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
	this->velocity = velocity;
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
	sprite2.setPosition(static_cast<float>(texture.getSize().x), 0); // setting second background sprite position to the right of the first sprite
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
	sf::Vector2u getSize() const;
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
	sprite1.setPosition(0, static_cast<float>(windowSize.y - texture.getSize().y)); // setting first ground sprite position at the bottom of the window
	sprite2.setPosition(static_cast<float>(texture.getSize().x), static_cast<float>(windowSize.y - texture.getSize().y)); // setting second ground sprite position to the right of the first sprite
}

// Update ground position by scrolling it to the left
void ScrollingGround::update(float deltaTime) {
	float scrollOffset = scrollSpeed * deltaTime;
	sprite1.move(-scrollOffset, 0);
	sprite2.move(-scrollOffset, 0);

	// Get the width of the sprite
	float spriteWidth = static_cast<float>(sprite1.getTextureRect().width);

	// Wrap the ground sprites when they go off the screen
	if (sprite1.getPosition().x <= -spriteWidth) {
		sprite1.setPosition(sprite2.getPosition().x + spriteWidth, sprite1.getPosition().y);
	}
	if (sprite2.getPosition().x <= -spriteWidth) {
		sprite2.setPosition(sprite1.getPosition().x + spriteWidth, sprite2.getPosition().y);
	}


}

// Get the size of the ground sprite
sf::Vector2u ScrollingGround::getSize() const {
	return texture.getSize();
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
	sf::Text scoreText;

public:
	sf::Font font;
	ExitScreen(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window) const;
	bool isVisible;
	void setScore(int score);
};

// ExitScreen font, background and text setup
ExitScreen::ExitScreen(const sf::Vector2u& windowSize) : isVisible(false) {
	// Load the font
	if (!font.loadFromFile("assets/arial.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}

	// Set up the background box
	backgroundBox.setSize(sf::Vector2f(400.0f, 400.0f));
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
		(windowSize.y - text_heading.getGlobalBounds().height) / 2.0f - 30.0f // center the text vertically
	);

	text_body.setFont(font);
	text_body.setString("Press 'Space' to Restart");
	text_body.setCharacterSize(24);
	text_body.setFillColor(sf::Color::White);
	text_body.setPosition(
		(windowSize.x - text_body.getGlobalBounds().width) / 2.0f, // center the text horizontally
		(windowSize.y - text_body.getGlobalBounds().height) / 2.0f + 20.0f // center the text vertically
	);

}
// Set the score text on the exit screen
void ExitScreen::setScore(int score) {
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("Final Score: " + std::to_string(score));
	scoreText.setPosition(
		(backgroundBox.getGlobalBounds().width - scoreText.getGlobalBounds().width) / 2.0f + backgroundBox.getPosition().x,
		backgroundBox.getPosition().y + backgroundBox.getGlobalBounds().height + 20.0f
	);
}

// Draw the ExitScreen when isVisible is true
void ExitScreen::draw(sf::RenderWindow& window) const {
	if (isVisible) {
		window.draw(backgroundBox);
		window.draw(text_heading);
		window.draw(text_body);
		window.draw(scoreText);
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
	backgroundBox.setSize(sf::Vector2f(400.0f, 100.0f));
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

// FloatingWords class
// Class to display floating words on the screen
class FloatingWords {
private:
	sf::Font font;
	float speed;
	float startTime;


public:
	FloatingWords(const std::string& filePath, const sf::Font& font, float speed, float spawnInterval, const sf::Vector2u& windowSize, float groundHeight);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	bool isVisible;
	void setStartTime(float time);
	sf::FloatRect getBounds(size_t index) const; // Move this function inside the class	
	std::vector<sf::Text> words;
	std::vector<float> spawnTimes;
	float spawnInterval;
	float floorPosition;
	float skyPosition;
};

// Load words from file and set their position and speed
// push_back words and spawn times to vectors
FloatingWords::FloatingWords(const std::string& filePath, const sf::Font& font, float speed, float spawnInterval, const sf::Vector2u& windowSize, float groundHeight)
	: font(font), speed(speed), spawnInterval(spawnInterval), isVisible(false), startTime(-1.0f), floorPosition(windowSize.y + groundHeight + 40.0f), skyPosition(1.0f) {

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
			float yPosition = std::rand() % static_cast<int>(floorPosition - skyPosition - text.getGlobalBounds().height) + skyPosition;
			text.setPosition(windowSize.x, yPosition);
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

// SCORE SETUP

class Score {
private:
	int value;
	sf::Text text;

public:
	Score(const sf::Font& font, const sf::Vector2f& position);
	void increment();
	void decrement(int amount);
	void reset();
	void update();
	void draw(sf::RenderWindow& window) const;
	int getValue() const;
};

Score::Score(const sf::Font& font, const sf::Vector2f& position)
	: value(0) {
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(position);
}

void Score::increment() {
	value++;
}

void Score::decrement(int amount) {
	value -= amount;
}

void Score::reset() {
	value = 0;
}

void Score::update() {
	text.setString("Score: " + std::to_string(value));
}

void Score::draw(sf::RenderWindow& window) const {
	window.draw(text);
}

int Score::getValue() const {
	return value;
}

// GAME SETUP 

// Game Class
class Game {
private:
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
	Score score;
	sf::Texture cloudTexture;
	std::vector<sf::Sprite> clouds;


public:
	Game();
	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();
	void restartGame();
	void handleClouds(float deltaTime);
};

// Game class functions
// Constructor setting window size and title, bird file and position, background file and scroll speed
Game::Game()
	: window(sf::VideoMode(1440, 1080), "Flappy Bird") // setting window size and title
	, bird("assets/bird.png", sf::Vector2f(200.0f, window.getSize().y / 2)) // setting bird file and position
	, background("assets/background.png", 150.0f) // setting backgound file and scroll speed
	, ground("assets/ground.png", 50.0f, window.getSize())  // placing ground file
	, startScreen(window.getSize()) // use window size to place start screen
	, floatingWords("assets/James Henry - Pigeons.txt", startScreen.font, 100.0f, 1.0f, window.getSize(), ground.getSize().y) // setting floating words file, font, speed, interval and window size
	, firstSpacePress(true) // setting first space press to true
	, gameStartTime(0.0f) // setting game start time to 0
	, exitScreen(window.getSize()) // setting exit screen to window size
	, score(startScreen.font, sf::Vector2f(10.0f, window.getSize().y - 40.0f)) // setting score font and position
{
}


void Game::handleClouds(float deltaTime) {

	static float cloudTimer = 0.0f;
	cloudTimer += deltaTime;
	
	if (cloudTimer >= 10.0f) {  // spawn a cloud every 3 seconds
		// Spawn a new cloud at random interval
		cloudTimer = 0.0f; // reset the cloud timer
		if (!cloudTexture.loadFromFile("assets/cloud.png")) {
			std::cout << "Error loading cloud texture" << std::endl;
		}

		sf::Sprite cloudSprite(cloudTexture);
		cloudSprite.setPosition(window.getSize().x, std::rand() % static_cast<int>(window.getSize().y - cloudSprite.getGlobalBounds().height));
		clouds.push_back(cloudSprite);
	}

	// Move the clouds to the left
	for (auto it = clouds.begin(); it != clouds.end();) { // iterate through the clouds
		it->move(-50.0f * deltaTime, 0.0f); // move the cloud to the left

		// Remove clouds that have gone off the screen
		if (it->getPosition().x < -it -> getGlobalBounds().width) {
			it = clouds.erase(it);
		}
		else {
			++it;
		}
	}
}

// Game run function
void Game::run() {
	sf::Clock clock; // creating clock object to measure time
	sf::Time accumulator = sf::Time::Zero; // setting time accumulator to zero
	sf::Time deltaTime = sf::seconds(1.0f / frameRate); // setting time delta to 1/frameRate
	while (window.isOpen()) {
		processEvents(); // check for user input
		accumulator += clock.restart(); // add time elapsed since last restart to accumulator


		while (accumulator >= deltaTime) { // 
			update(deltaTime.asSeconds()); // update the game objects (bird and background)
			accumulator -= deltaTime; // subtract delta time from accumulator
		}

		render();
	}
}

// Game restart function
void Game::restartGame() {
	// Reset the bird position and velocity
	bird.setPosition(sf::Vector2f(200.0f, window.getSize().y / 2)); // set bird position
	bird.setVelocity(sf::Vector2f(0.0f, 0.0f)); // set bird velocity	

	// Reset the floating words
	floatingWords.isVisible = false; // show floating words
	float startSpawnTime = 0.5f; // set start spawn time to 0.5 seconds
	for (size_t i = 0; i < floatingWords.words.size(); i++) {
		float yPosition = std::rand() % static_cast<int>(floatingWords.floorPosition - floatingWords.skyPosition - floatingWords.words[i].getGlobalBounds().height) + floatingWords.skyPosition;
		floatingWords.words[i].setPosition(window.getSize().x, yPosition);
		floatingWords.spawnTimes[i] = i * floatingWords.spawnInterval;
	}

	exitScreen.isVisible = false; // hide exit screen

	gameClock.restart(); // restart game clock

	gameStartTime = 0.0f; // set game start time to 0
	floatingWords.setStartTime(gameStartTime); // set floating words start time to 0

	firstSpacePress = true; // set first space press to true

	score.reset(); // reset the score
}

// Get user input events => close window or flap bird (space key)
void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
			if (startScreen.isVisible) {
				startScreen.isVisible = false; // hide start screen
				bird.update(firstSpacePress); // update bird position and enable gravity
				firstSpacePress = false; // set first space press to false
				floatingWords.isVisible = true; // show floating words
				gameStartTime = gameClock.getElapsedTime().asSeconds(); // set game start time to current time
				floatingWords.setStartTime(gameStartTime); // set floating words start time to current time
			}
			else if (exitScreen.isVisible) {
				restartGame();
				bird.update(firstSpacePress); // update bird position and enable gravity
				firstSpacePress = false; // set first space press to false
				floatingWords.isVisible = true; // show floating words

			}
			else {
				bird.flap(); // flap bird when space key is pressed
			}
		}
	}
}

// Update game objects (bird, background, check for collision)
void Game::update(float deltaTime) {
	bird.update(!firstSpacePress); // update bird position
	background.update(deltaTime); // update background position
	ground.update(deltaTime); // update ground position
	floatingWords.update(deltaTime); // update floating words position
	handleClouds(deltaTime); // update clouds position	


	// Check for collision between bird, window bounds and floating words
	sf::FloatRect birdBounds = bird.getBrounds();

	// Check for collision between bird and window bounds
	for (size_t i = 0; i < floatingWords.words.size(); i++) { //check each word
		if (floatingWords.spawnTimes[i] <= gameClock.getElapsedTime().asSeconds() - gameStartTime) { // check if the word has spawned
			sf::FloatRect wordBounds = floatingWords.getBounds(i); // get the bounds of the word
			if (birdBounds.intersects(wordBounds)) { // check for collision between bird and word
				bird.setPosition(sf::Vector2f(-100.0f, -100.0f)); // move bird off screen
				floatingWords.isVisible = false; // hide floating words
				exitScreen.isVisible = true; // show exit screen
				exitScreen.setScore(score.getValue()); // set the score on the exit screen
				break;
			}
		}
	}
	if (!exitScreen.isVisible) {
		score.increment(); // Increase the score based on the seconds survived

		if (birdBounds.top < 0.0f) {
			bird.setPosition(sf::Vector2f(birdBounds.left, 0.0f));
			bird.setVelocity(sf::Vector2f(bird.getVelocity().x, -bird.getVelocity().y * 0.3f));
			score.decrement(10); // Decrease the score by 10 points if the bird hits the top of the window
		}
		else if (birdBounds.top + birdBounds.height > window.getSize().y - ground.getSize().y) { // check for collision between bird and ground
			bird.setPosition(sf::Vector2f(birdBounds.left, window.getSize().y - ground.getSize().y - birdBounds.height)); // set bird position to the top of the ground
			bird.setVelocity(sf::Vector2f(bird.getVelocity().x, -bird.getVelocity().y * 0.5f)); // set bird velocity
			score.decrement(10); // Decrease the score by 10 points if the bird hits the ground
		}
	}

	score.update(); // update the score text

}

// Render game objects (bird and background)
void Game::render() {
	window.clear();
	background.draw(window);
	ground.draw(window);
	for (const auto& cloud : clouds) {
		window.draw(cloud);
	}
	if (bird.getPosition().x >= 0 && bird.getPosition().y >= 0) {
		bird.draw(window);
	}
	startScreen.draw(window);
	exitScreen.draw(window);
	floatingWords.draw(window);
	if (!startScreen.isVisible && !exitScreen.isVisible) {
		score.draw(window);
	}

	window.display();

}


// MAIN FUNCTION

// Main function to run the game
int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // setting random seed based on current time
	Game game; // creating game object
	game.run(); // running game
	return 0;
}