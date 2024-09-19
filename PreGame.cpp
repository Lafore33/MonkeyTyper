#include "PreGame.h"

PreGame::PreGame(GameSettings &game) {
    input = sf::Text("", game.font, game.TextFontSize);
    enterName = sf::Text ("Enter username", game.font, game.ButtonFontSize);
    backToMenu = Button (game.windowX / 50, 10, "Back To Menu", game.font, game.TextFontSize, false);;
    gameSettings = &game;
}

void PreGame::setFont(const sf::Font& font) {
    input.setFont(font);
    enterName.setFont(font);
    backToMenu.setFont(font);
}

void PreGame::setPosition() {
    enterName.setPosition((gameSettings->windowX / 2 - enterName.getGlobalBounds().width / 2),
                          (gameSettings->windowY / 5 - enterName.getGlobalBounds().height / 2));
    input.setPosition((gameSettings->windowX / 2 - input.getGlobalBounds().width / 2),
                      (gameSettings->windowY / 4 - input.getGlobalBounds().height / 2) + 20);
    backToMenu.setPosition(gameSettings->windowX / 50, 10, false);
}

void PreGame::draw() {
    PreGame::setFont(gameSettings->font);
    PreGame::setPosition();
    gameSettings->window.draw(input);
    gameSettings->window.draw(enterName);
    backToMenu.draw(gameSettings->window);

}

void PreGame::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode <= 122 and event.text.unicode >= 65 &&
            event.text.unicode != 8) { // ASCII characters except backspace
            inputText += static_cast<char>(event.text.unicode);
            input.setString(inputText);
        } else if (event.text.unicode == 8 && !inputText.empty()) { // Backspace
            inputText.pop_back();
            input.setString(inputText);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            if (inputText.empty()) return;
            gameSettings->curUser = inputText;
            gameSettings->generalClock.restart();
            gameSettings->intervalClock.restart();
            inputText.clear();
            input.setString(inputText);
            input.setPosition(15, 455);
            gameSettings->startGame = true;
            gameSettings->generalPausedSeconds = 0;
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            inputText.clear();
            input.setString(inputText);
            gameSettings->isActive = false;
            gameSettings->startGame = false;
            gameSettings->menu = true;
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        isOnButton(backToMenu, gameSettings->window, event, sf::Color::Yellow);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosition = gameSettings->window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (backToMenu.isClicked(mousePosition)) {
            inputText.clear();
            input.setString(inputText);
            gameSettings->isActive = false;
            gameSettings->startGame = false;
            gameSettings->menu = true;
        }
    }
}