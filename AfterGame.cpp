#include "AfterGame.h"

AfterGame::AfterGame(GameSettings& game){
    gameSettings = &game;
    result = sf::Text("", game.font, game.ButtonFontSize);
    backToMenu = Button(20, 10, "Back To Menu", game.font, game.TextFontSize, false);
    restartGame = Button(game.windowX / 2, game.windowY / 2, "Restart the game", game.font, game.ButtonFontSize);
}

void AfterGame::setFont() {
    result.setFont(gameSettings->font);
    backToMenu.setFont(gameSettings->font);
    restartGame.setFont(gameSettings->font);
}

void AfterGame::setPosition() {
    result.setPosition(gameSettings->windowX / 2 - result.getGlobalBounds().width / 2, 100);
    backToMenu.setPosition(20, 10, false);
    restartGame.setPosition(gameSettings->windowX / 2, gameSettings->windowY / 2);
}

void AfterGame::draw() {
    AfterGame::setFont();
    AfterGame::setPosition();
    gameSettings->window.draw(result);
    backToMenu.draw(gameSettings->window);
    restartGame.draw(gameSettings->window);
}

void AfterGame::handleEvent(sf::Event &event, GameSession& gs) {
    gameSettings->generalPausedSeconds = 0;
    gs.count=0;
    gs.points.setString(std::to_string(gs.count));
    gs.lostWords=0;
    gs.missedWords.setString(std::to_string(gs.lostWords));
    gs.currentWords.clear();
    gs.inputText.clear();
    gs.input.setString(gs.inputText);
    gameSettings->generalClock.restart();
    gameSettings->intervalClock.restart();
    if (event.type == sf::Event::MouseMoved) {
        isOnButton(backToMenu, gameSettings->window, event, sf::Color::Yellow);
        isOnButton(restartGame, gameSettings->window, event, sf::Color::Red);
    }
    else if (event.type == sf::Event::MouseButtonPressed){
        sf::Vector2f mousePosition = gameSettings->window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (backToMenu.isClicked(mousePosition)) {
            gameSettings->afterGame=false;
            gameSettings->menu = true;
        }
        else if (restartGame.isClicked(mousePosition)){
            gameSettings->isActive=true;
            gameSettings->afterGame=false;
            gameSettings->startGame=false;
        }
    }
}
