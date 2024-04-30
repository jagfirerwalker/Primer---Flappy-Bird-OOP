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
#include <sstream>


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
	sprite.setScale(0.5f, 0.5f); // Set the cloud scale to 0.5 on the x and y axis
	sprite.setPosition(std::rand() % static_cast<int>(respawnXPosition), std::rand() % 500); // Set the cloud position to a random position on the y-axis

}

// Draw cloud on window, spawn multiple on screen and respawning it when it goes off the screen
void Cloud::update(float deltaTime) {
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


// SCORE BOARD FUNCTION

// ScoreBoard class

class ScoreBoard {
private:
	sf::RectangleShape backgroundBox;
	sf::Text text;
	std::vector<std::pair<std::string, int>> scores;
	const std::string filename = "scoreboard.txt";
	

public:
	sf::Font font;
	ScoreBoard(const sf::Vector2u& windowSize);
	void addScore(const std::string& name, int score);
	void saveScores();
	void loadScores();
	void draw(sf::RenderWindow& window);
	bool isVisible;

};

ScoreBoard::ScoreBoard(const sf::Vector2u& windowSize)
	: isVisible(false) {

	// Load the font
	if (!font.loadFromFile("assets/arial.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}

	// Set the background box
	backgroundBox.setSize(sf::Vector2f(400.0f, 400.0f));
	backgroundBox.setFillColor(sf::Color::Black);
	backgroundBox.setPosition(
		(windowSize.x - backgroundBox.getSize().x) / 2.0f,
		(windowSize.y - backgroundBox.getSize().y) / 2.0f
	); // center the box

	// Set the text
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);

	loadScores();

	std::stringstream ss;

	ss << "Scoreboard" << std::endl;
	for (const auto& score : scores) {
		ss << score.first << " " << score.second << std::endl;
	}

	text.setString(ss.str());
	text.setPosition(
		(windowSize.x - text.getGlobalBounds().width) / 2.0f,
		(windowSize.y - text.getGlobalBounds().height) / 2.0f
	);

}

void ScoreBoard::loadScores() {
	std::ifstream file(filename);
	if (file.is_open()) {
		scores.clear();
		std::string name;
		int score;
		while (file >> name >> score) {
			scores.push_back(std::make_pair(name, score));
		}
		file.close();
	}
}

void ScoreBoard::addScore(const std::string& name, int score) {
	scores.push_back(std::make_pair(name, score));
	std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
		return a.second > b.second; // a.second is the score in the pair
		}); // sort the scores in descending order
	if (scores.size() > 10) {
		scores.resize(10); // keep only the top 10 scores
	}
}

void ScoreBoard::saveScores() {
	std::ofstream file(filename);
	if (file.is_open()) {
		for (const auto& score : scores) {
			file << score.first << " " << score.second << std::endl;
		}
		file.close();
	}
}

void ScoreBoard::draw(sf::RenderWindow& window) {
	if (isVisible) {
		window.draw(backgroundBox);
		window.draw(text);

	}
}

// Save ScoreBoard function
class SaveScoreScreen {
private:
	sf::RectangleShape backgroundBox;
	sf::Text text;
	sf::Text nameText;
	std::string playerName;
	sf::Vector2u windowSize;

public:
	sf::Font font;
	SaveScoreScreen(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window);
	void handleInput(sf::Event& event);
	bool isVisible;
	std::string getPlayerName() const;
};

SaveScoreScreen::SaveScoreScreen(const sf::Vector2u& windowSize)
	: isVisible(false), playerName(""), windowSize(windowSize) {

	// Load the font
	if (!font.loadFromFile("assets/arial.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}

	// Set the background box
	backgroundBox.setSize(sf::Vector2f(400.0f, 200.0f));

	backgroundBox.setFillColor(sf::Color::Black);
	backgroundBox.setPosition(
		(windowSize.x - backgroundBox.getSize().x) / 2.0f,
		((windowSize.y / 2.0f) - backgroundBox.getSize().y) / 2.0f
	); // center the box

	// Set up the text
	text.setFont(font);
	text.setString("Enter your name (3 letters):");

	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(
		(windowSize.x - text.getGlobalBounds().width) / 2.0f,
		((windowSize.y / 2.0f) - text.getGlobalBounds().height) / 2.0f - 50.0f

	); // center the text above the input


	// Set up the name text
	nameText.setFont(font);
	nameText.setCharacterSize(24);
	nameText.setFillColor(sf::Color::White);
	nameText.setPosition(
		(windowSize.x - nameText.getGlobalBounds().width) / 2.0f,
		(windowSize.y - nameText.getGlobalBounds().height) / 2.0f
	); // center the text
}


// Draw SaveScoreScreen when isVisible is true
void SaveScoreScreen::draw(sf::RenderWindow& window) {
	if (isVisible) {
		window.draw(backgroundBox);
		window.draw(text);
		window.draw(nameText);
	}
}

void SaveScoreScreen::handleInput(sf::Event& event) {
	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode == '\b' && playerName.size() > 0) {
			playerName.pop_back();
		}
		else if (std::isalpha(event.text.unicode)) {
			// Convert the unicode character to uppercase
			char upercaseChar = static_cast<char>(std::toupper(event.text.unicode));
			
			// Limit the player name to 3 characters
			if (playerName.size() < 3) {
				playerName += upercaseChar;
			}
			// Replace the first character if the player name is already 3 characters long
			else {
				playerName.erase(0, 1); // erase the first character
				playerName += upercaseChar;
			}
		}
		nameText.setString(playerName);
		nameText.setPosition(
			(windowSize.x- nameText.getGlobalBounds().width) / 2.0f,
			((windowSize.y / 2.0 ) - nameText.getGlobalBounds().height) / 2.0f
		); // center the text

	}
}

std::string SaveScoreScreen::getPlayerName() const {
	return playerName;
}

// EXIT SCREEN CLASS

class ExitScreen {
private:
	sf::RectangleShape backgroundBox;
	sf::Text text_heading;
	sf::Text text_body;
	sf::Text scoreText;
	sf::Text saveScoreText;
	bool saveScoreSelected;

public:
	sf::Font font;
	ExitScreen(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window) const;
	bool isVisible;
	void setScore(int score);
};

// ExitScreen font, background and text setup
ExitScreen::ExitScreen(const sf::Vector2u& windowSize) : isVisible(true) {
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
	text_body.setString("Press 'Enter' to Restart");
	text_body.setCharacterSize(24);
	text_body.setFillColor(sf::Color::White);
	text_body.setPosition(
		(windowSize.x - text_body.getGlobalBounds().width) / 2.0f, // center the text horizontally
		(windowSize.y - text_body.getGlobalBounds().height) / 2.0f + 20.0f // center the text vertically
	);

	saveScoreText.setFont(font);
	saveScoreText.setString("Press 'S' for Scoreboard");
	saveScoreText.setCharacterSize(24);
	saveScoreText.setFillColor(sf::Color::White);
	saveScoreText.setPosition(
		(windowSize.x - saveScoreText.getGlobalBounds().width) / 2.0f, // center the text horizontally
		(windowSize.y - saveScoreText.getGlobalBounds().height) / 2.0f + 60.0f // center the text vertically
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
		window.draw(saveScoreText);
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
StartScreen::StartScreen(const sf::Vector2u& windowSize) : isVisible(false) {
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
	std::string filePath;
	sf::Vector2u windowSize;


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
	void reset();
};

// Load words from file and set their position and speed
// push_back words and spawn times to vectors
FloatingWords::FloatingWords(const std::string& filePath, const sf::Font& font, float speed, float spawnInterval, const sf::Vector2u& windowSize, float groundHeight)
	: font(font), speed(speed), spawnInterval(spawnInterval), isVisible(false), startTime(-1.0f), floorPosition(windowSize.y + groundHeight + 60.0f), skyPosition(1.0f), filePath(filePath), windowSize(windowSize) {
	reset();
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

// Reset floating words
void FloatingWords::reset() {
	words.clear();
	spawnTimes.clear();

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
			float yPosition = std::rand() % static_cast<int>(floorPosition - skyPosition - text.getGlobalBounds().height) + skyPosition; // Set the y position of the word to a random position between the sky and the floor
			text.setPosition(windowSize.x, yPosition);
			words.push_back(text);
			spawnTimes.push_back(currentTime);
			currentTime += spawnInterval;
		}
		file.close();

	}
}

// SCORE SETUP

class Score {
private:
	int value;
	int multiplier;
	sf::Text scoreText;
	sf::Text multiplierText;

public:
	Score(const sf::Font& font, const sf::Vector2f& position);
	void increment(int amount);
	void decrement(int amount);
	void reset();
	void update();
	void draw(sf::RenderWindow& window) const;
	int getValue() const;
	void incrementMultiplier();
	void resetMultiplier();
};

Score::Score(const sf::Font& font, const sf::Vector2f& position)
	: value(0), multiplier(1) {
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(position);

	multiplierText.setFont(font);
	multiplierText.setCharacterSize(24);
	multiplierText.setFillColor(sf::Color::White);
}

void Score::increment(int amount) {
	value += amount * multiplier;
}

void Score::decrement(int amount) {
	value -= amount;
}

void Score::reset() {
	value = 0;
	multiplier = 1;
}

void Score::update() {
	scoreText.setString("Score: " + std::to_string(value));
	multiplierText.setString(" X " + std::to_string(multiplier));
	sf::FloatRect scoreBounds = scoreText.getGlobalBounds();
	multiplierText.setPosition(scoreBounds.left + scoreBounds.width + 10.0f, scoreText.getPosition().y);
}

void Score::draw(sf::RenderWindow& window) const {
	window.draw(scoreText);
	window.draw(multiplierText);
}

int Score::getValue() const {
	return value;
}

void Score::incrementMultiplier() {
	multiplier++;
}

void Score::resetMultiplier() {
	multiplier = 1;
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
	ScoreBoard scoreBoard;
	SaveScoreScreen saveScoreScreen;
	sf::Texture cloudTexture;
	std::vector<sf::Sprite> clouds;
	int consecutiveMissedWords;

public:
	Game();
	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();
	void restartGame();
	void handleClouds(float deltaTime);
	bool checkBirdWordCollision(const sf::FloatRect& birdBounds, const sf::FloatRect& wordBounds);
};

// Game class functions
// Constructor setting window size and title, bird file and position, background file and scroll speed
Game::Game()
	: window(sf::VideoMode(1440, 1080), "By what mistake were pigeons made so happy") // setting window size and title
	, bird("assets/bird.png", sf::Vector2f(200.0f, window.getSize().y / 2)) // setting bird file and position
	, background("assets/background.png", 150.0f) // setting backgound file and scroll speed
	, ground("assets/ground.png", 50.0f, window.getSize())  // placing ground file
	, startScreen(window.getSize()) // use window size to place start screen
	, floatingWords("assets/James Henry - Pigeons.txt", startScreen.font, 300.0f, 0.5f, window.getSize(), ground.getSize().y) // setting floating words file, font, speed, interval and window size
	, firstSpacePress(true) // setting first space press to true
	, gameStartTime(0.0f) // setting game start time to 0
	, exitScreen(window.getSize()) // setting exit screen to window size
	, scoreBoard(window.getSize()) // setting score board to window size
	, score(startScreen.font, sf::Vector2f(10.0f, window.getSize().y - 40.0f)) // setting score font and position
	, saveScoreScreen(window.getSize()) // setting save score screen to window size
{
}


void Game::handleClouds(float deltaTime) {

	static float cloudTimer = 0.0f;
	cloudTimer += deltaTime;

	const int cloudSpeed = 200.0f; // set cloud speed

	if (cloudTimer >= 10.0f) {  // spawn a cloud every 10 seconds
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
		it->move(-cloudSpeed * deltaTime, 0.0f); // move the cloud to the left with cloudSpeed

		// Remove clouds that have gone off the screen
		if (it->getPosition().x < -it->getGlobalBounds().width) {
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
	bird.update(firstSpacePress); // update bird position and enable gravity
	firstSpacePress = false; // set first space press to false

	// Consecutive missed words reset
	consecutiveMissedWords = 0;

	// Reset the multiplier
	score.reset();

	// restart game clock
	gameClock.restart();
	gameStartTime = 0.0f; // set game start time to 0

	// Hide screens
	saveScoreScreen.isVisible = false; // hide save score screen
	exitScreen.isVisible = false; // hide exit screen
	scoreBoard.isVisible = false; // hide score board

	// Reset the floating words
	floatingWords.reset(); // reset floating words
	float startSpawnTime = 0.5f; // set start spawn time to 0.5 seconds
	for (size_t i = 0; i < floatingWords.words.size(); i++) {
		float yPosition = std::rand() % static_cast<int>(floatingWords.floorPosition - floatingWords.skyPosition - floatingWords.words[i].getGlobalBounds().height) + floatingWords.skyPosition;
		floatingWords.words[i].setPosition(window.getSize().x, yPosition);
		floatingWords.spawnTimes[i] = i * floatingWords.spawnInterval;
	}

	floatingWords.setStartTime(gameStartTime); // set floating words start time to 0
	floatingWords.isVisible = true; // show floating words
	score.reset(); // reset the score
}

// Get user input events => close window or flap bird (space key)
void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		// 'Space' key is pressed
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
			// Start screen is visible only
			if (startScreen.isVisible) {
				startScreen.isVisible = false; // hide start screen
				bird.update(firstSpacePress); // update bird position and enable gravity
				firstSpacePress = false; // set first space press to false
				floatingWords.isVisible = true; // show floating words
				gameStartTime = gameClock.getElapsedTime().asSeconds(); // set game start time to current time
				floatingWords.setStartTime(gameStartTime); // set floating words start time to current time
			}
			else {
				// In Game Screen
				if (!exitScreen.isVisible && !saveScoreScreen.isVisible && !scoreBoard.isVisible) {
					bird.flap(); // flap bird when space key is pressed
				}
			}
		}

		// General Character input
		if (event.type == sf::Event::TextEntered) {
			// Start screen is visible only
			if (saveScoreScreen.isVisible) {
				saveScoreScreen.handleInput(event);
			}
		}
		
		// IF 'S' key is pressed
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S ) {
			// Exit screen is visible only
			if (exitScreen.isVisible && !saveScoreScreen.isVisible) {
				saveScoreScreen.isVisible = true; // show save score screen
				exitScreen.isVisible = false; // hide exit screen
				scoreBoard.isVisible = true; // show score board
			}
		}
		
		// IF 'Enter' key is pressed
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
			// Exit screen is visible only
			if (exitScreen.isVisible) {
				restartGame();
			}
			if (saveScoreScreen.isVisible) {
				std::string playerName = saveScoreScreen.getPlayerName(); 

				if (playerName.size() == 3) {
					scoreBoard.addScore(saveScoreScreen.getPlayerName(), score.getValue());
					scoreBoard.saveScores();
					restartGame();

				}
			}
		}

	}
}

bool Game::checkBirdWordCollision(const sf::FloatRect& birdBounds, const sf::FloatRect& wordBounds) {
	return birdBounds.intersects(wordBounds);
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
	for (size_t i = 0; i < floatingWords.words.size(); i++) {
		if (floatingWords.spawnTimes[i] <= gameClock.getElapsedTime().asSeconds() - gameStartTime) {
			sf::FloatRect wordBounds = floatingWords.getBounds(i);
			if (checkBirdWordCollision(birdBounds, wordBounds)) { // check for collision between bird and word
				score.increment(10); // Increase the score by 10 points
				score.incrementMultiplier(); // Increase the multiplier
				floatingWords.words.erase(floatingWords.words.begin() + i); // erase the word
				floatingWords.spawnTimes.erase(floatingWords.spawnTimes.begin() + i); // erase the spawn time
				i--; // decrement i
				consecutiveMissedWords = 0; // reset the consecutive missed words
			}
			else if (wordBounds.left + wordBounds.width < birdBounds.left) { // check if the word has gone off the screen
				score.resetMultiplier(); // reset the multiplier
				floatingWords.words.erase(floatingWords.words.begin() + i); // erase the word
				floatingWords.spawnTimes.erase(floatingWords.spawnTimes.begin() + i); // erase the spawn time
				i--; // decrement i
				consecutiveMissedWords++; // increment the consecutive missed words
				if (consecutiveMissedWords >= 3) {
					floatingWords.isVisible = false; // hide floating words
					exitScreen.isVisible = true; // show exit screen
					exitScreen.setScore(score.getValue()); // set the score on the exit screen
					bird.setPosition(sf::Vector2f(-400.0f, -400.0f)); // set bird position off the screen
					break;
				}
			}
		}
	}
	if (!exitScreen.isVisible) {

		if (birdBounds.top < 0.0f) {
			bird.setPosition(sf::Vector2f(birdBounds.left, 0.0f));
			bird.setVelocity(sf::Vector2f(bird.getVelocity().x, -bird.getVelocity().y * 0.3f));
			score.decrement(1); // Decrease the score by 10 points if the bird hits the top of the window
		}
		else if (birdBounds.top + birdBounds.height > window.getSize().y - ground.getSize().y) { // check for collision between bird and ground
			bird.setPosition(sf::Vector2f(birdBounds.left, window.getSize().y - ground.getSize().y - birdBounds.height)); // set bird position to the top of the ground
			bird.setVelocity(sf::Vector2f(bird.getVelocity().x, -bird.getVelocity().y * 0.5f)); // set bird velocity
			score.decrement(1); // Decrease the score by 10 points if the bird hits the ground
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
	if (startScreen.isVisible) {
		startScreen.draw(window);
	}
	if (exitScreen.isVisible && !saveScoreScreen.isVisible && !scoreBoard.isVisible) {
		exitScreen.draw(window);
	}
	if (saveScoreScreen.isVisible) {
		saveScoreScreen.draw(window);
	}
	if (floatingWords.isVisible) {
		floatingWords.draw(window);
	}
	if (!startScreen.isVisible && !exitScreen.isVisible) {
		score.draw(window);
	}
	scoreBoard.draw(window);
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