#include "GameSession.h"

GameSession::GameSession(GameSettings& game){
    lastSpeed = 0;
    input = sf::Text ("", game.font, game.TextFontSize);
    score = sf::Text ("Score: ", game.font, game.TextFontSize);
    points = sf::Text(std::to_string(count), game.font, game.TextFontSize);
    missed = sf::Text ("Missed:", game.font, game.TextFontSize);
    maxMissed = sf::Text(" / " + std::to_string(9), game.font, game.TextFontSize);
    missedWords = sf::Text(std::to_string(lostWords), game.font, game.TextFontSize);
    left = sf::Text("[", game.font, game.TextFontSize + 5);
    right = sf::Text("]", game.font, game.TextFontSize + 5);
    timerText = sf::Text("", game.font, game.TextFontSize);
    showUser = sf::Text("Username: ", game.font, game.TextFontSize);
    result = sf::Text ("", game.font, game.ButtonFontSize);
    saving = Button (0.920f * game.windowX, 0.875f * game.windowY, "Save the game", game.font, game.TextFontSize);
    underscore = sf::RectangleShape (sf::Vector2f(12, 2));
    rectangle = sf::RectangleShape(sf::Vector2f(game.windowX, 80));
    rectangle.setFillColor(sf::Color::Blue);
    gameSettings = &game;



}

void GameSession::moveWords() {
    for (std::pair<std::string, sf::Text>& pair : currentWords){
        pair.second.setCharacterSize(gameSettings->WordsFont);
        pair.second.move((float)gameSettings->moveSpeed, 0);
    }
}

void GameSession::setFont(const sf::Font &font) {
    input.setFont(font);
    score.setFont(font);
    points.setFont(font);
    missed.setFont(font);
    maxMissed.setFont(font);
    missedWords.setFont(font);
    left.setFont(font);
    right.setFont(font);
    timerText.setFont(font);
    showUser.setFont(font);
    saving.setFont(font);
    for (auto& pair : currentWords){
        pair.second.setFont(font);
    }
}

void GameSession::setPosition() {
    rectangle = sf::RectangleShape(sf::Vector2f(gameSettings->windowX, 80.f / 480 * gameSettings->windowY));
    rectangle.setFillColor(sf::Color::Blue);
    showUser.setPosition(0.230f * gameSettings->windowX, 0.875f * gameSettings->windowY);
    score.setPosition(5, 0.875f * gameSettings->windowY);
    points.setPosition(0.070f * gameSettings->windowX, 0.875f * gameSettings->windowY);
    missed.setPosition(0.230f * gameSettings->windowX, 0.9375f * gameSettings->windowY);
    missedWords.setPosition(0.300f * gameSettings->windowX, 0.9375f * gameSettings->windowY);
    maxMissed.setPosition(missedWords.getPosition().x + 10, 0.9375f * gameSettings->windowY);
    left.setPosition(0, input.getPosition().y);
    right.setPosition(0.200f * gameSettings->windowX, input.getPosition().y);
    timerText.setPosition(0.890f * gameSettings->windowX, 0.9375f * gameSettings->windowY);
    rectangle.setPosition(0, 0.833f * gameSettings->windowY);
    input.setPosition(15, 0.95f * gameSettings->windowY);
    if (input.getString().isEmpty()) underscore.setPosition(15, 0.95f * gameSettings->windowY + 15);
    saving.setPosition(0.920f * gameSettings->windowX, 0.875f * gameSettings->windowY);
}
void GameSession::draw() {


    GameSession::setFont(gameSettings->font);
    GameSession::setPosition();
    showUser.setString("Username: " + gameSettings->curUser);
    gameSettings->window.draw(rectangle);
    gameSettings->window.draw(showUser);
    gameSettings->window.draw(input);
    gameSettings->window.draw(score);
    gameSettings->window.draw(points);
    gameSettings->window.draw(missed);
    gameSettings->window.draw(missedWords);
    gameSettings->window.draw(left);
    gameSettings->window.draw(right);
    gameSettings->window.draw(timerText);
    gameSettings->window.draw(maxMissed);
    saving.draw(gameSettings->window);

    if (blinkClock.getElapsedTime().asSeconds() < blinkingInterval){
        if (!hide){
            gameSettings->window.draw(underscore);
        }
    }
    else{
        blinkClock.restart();
        hide = !hide;
    }
    for (std::pair<std::string, sf::Text> pair : currentWords){
        if(pair.second.getLocalBounds().width + pair.second.getPosition().x > 0.9 * gameSettings->windowX){
            pair.second.setFillColor(sf::Color::Red);
        }
        else if(pair.second.getLocalBounds().width + pair.second.getPosition().x > 0.7 * gameSettings->windowX){
            pair.second.setFillColor(sf::Color::Yellow);
        }
        pair.second.setFont(gameSettings->font);
        if (pair.second.getPosition().y + pair.second.getGlobalBounds().height < rectangle.getPosition().y) gameSettings->window.draw(pair.second);
    }
}

void GameSession::saveGame(){
    std::ofstream file;
    file.open(gameSettings->savedGameFile, std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << std::endl;
    }
    file << gameSettings->curUser << "\n";
    for (const std::pair<std::string, sf::Text>& pair : currentWords){
        file << pair.first << " " << pair.second.getPosition().x << " " << pair.second.getPosition().y << "\n";
    }
    file << "!!" << "\n";
    file << count << "\n";
    file << lostWords << "\n";
    file << gameSettings->generalClock.restart().asSeconds()<< "\n";
}

void GameSession::handleEvent(sf::Event &event) {
    std::string size;
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode <= 122 and event.text.unicode >= 65 &&
            event.text.unicode != 8 and inputText.size() <= maxLen) { // ASCII characters except backspace
            inputText += static_cast<char>(event.text.unicode);
            input.setString(inputText);
        } else if (event.text.unicode == 8 && !inputText.empty()) { // Backspace
            inputText.pop_back();
            input.setString(inputText);
        }
        sf::FloatRect textBounds = input.getGlobalBounds();
        underscore.setPosition((textBounds.left + textBounds.width), input.getPosition().y + 15);
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            std::string findable = input.getString();
            auto findWord = std::ranges::find(currentWords, findable,
                                              [](const auto &pair) { return pair.first; });
            if (findWord != currentWords.end()) {
                currentWords.erase(findWord);
                count += 1;
                points.setString(std::to_string(count));
            }
            inputText.clear();
            input.setString(inputText);
            sf::FloatRect textBounds = input.getGlobalBounds();
            underscore.setPosition((textBounds.left + textBounds.width), input.getPosition().y + 15);
        } else if (event.key.code == sf::Keyboard::Escape) {
            if (gameSettings->gamePaused){
                gameSettings->gamePaused = false;
                gameSettings->generalClock.restart();
                gameSettings->moveSpeed = lastSpeed;
            }
            count=0;
            points.setString(std::to_string(count));
            lostWords=0;
            missedWords.setString(std::to_string(lostWords));
            currentWords.clear();
            gameSettings->isActive = false;
            gameSettings->startGame = false;
            inputText.clear();
            input.setString(inputText);
            gameSettings->menu = true;
        }

        else if(event.key.code == sf::Keyboard::Space){
            if (!gameSettings->gamePaused){
                gameSettings->music.pause();
                lastSpeed = (float)gameSettings->moveSpeed;
                gameSettings->generalPausedSeconds += gameSettings->generalClock.restart().asSeconds();
                gameSettings->moveSpeed = 0.f;
                gameSettings->gamePaused = true;
            }
            else{
                gameSettings->music.play();
                gameSettings->generalClock.restart();
                gameSettings->moveSpeed = lastSpeed;
                gameSettings->gamePaused = false;
            }
        }
        else if (event.key.code == sf::Keyboard::LShift){
            gameSettings->LShift = true;
        }
        else if (event.key.code == sf::Keyboard::Tab){
            gameSettings->Tab = true;
        }
        if (gameSettings->LShift && gameSettings->Tab){
            saveGame();
            gameSettings->savedGame = true;
            gameSettings->isActive = false;
            gameSettings->startGame = false;
            gameSettings->menu = true;
        }
        gameSettings->interval = 0.1f / (float)gameSettings->moveSpeed;

    }
    else if (event.type == sf::Event::MouseMoved){
        isOnButton(saving, gameSettings->window, event, sf::Color::Magenta);
    }
    else if (event.type == sf::Event::MouseButtonPressed){
        sf::Vector2f mouseCoords = gameSettings->window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (saving.isClicked(mouseCoords) ){
            saveGame();
            gameSettings->savedGame = true;
            gameSettings->isActive = false;
            gameSettings->startGame = false;
            gameSettings->menu = true;
        }
    }
}