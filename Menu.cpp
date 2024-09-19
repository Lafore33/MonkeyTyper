#include "Menu.h"




Menu::Menu(GameSettings& game){
    playButton = Button (game.windowX / 2, game.windowY / 5, "Play", game.font, game.ButtonFontSize);
    settingsButton = Button (game.windowX / 2, 2 * game.windowY / 5, "Settings", game.font, game.ButtonFontSize);
    showLeaderBoard = Button (game.windowX / 2, 3 * game.windowY / 5, "Leaderboard", game.font, game.ButtonFontSize);
    exitButton = Button (game.windowX / 2, 4 * game.windowY / 5, "Exit", game.font, game.ButtonFontSize);
    gameSettings = &game;
}


void Menu::handleEvent(sf::Event& event){
    if (event.type == sf::Event::MouseMoved){
        isOnButton(playButton, gameSettings->window, event);
        isOnButton(settingsButton, gameSettings->window, event, sf::Color::Green);
        isOnButton(exitButton, gameSettings->window, event, sf::Color::Cyan);
        isOnButton(showLeaderBoard, gameSettings->window, event, sf::Color::Magenta);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePosition = gameSettings->window.mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            if (playButton.isClicked(mousePosition)) {
                gameSettings->window.clear();
                gameSettings->isActive = true;
                gameSettings->savedGame = true;
                gameSettings->menu = false;
            } else if (settingsButton.isClicked(mousePosition)) {
                gameSettings->menu = false;
                gameSettings->isSetting = true;
            } else if (exitButton.isClicked(mousePosition)) {
                gameSettings->window.close();
            } else if (showLeaderBoard.isClicked(mousePosition)) {
                gameSettings->menu = false;
                gameSettings->showLeaders = true;
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased){
        if (event.key.code == sf::Keyboard::LShift){
            gameSettings->LShift = false;
        }
        else if (event.key.code == sf::Keyboard::Tab){
            gameSettings->Tab = false;
        }
    }


}

void Menu::setFont(const sf::Font& ft) {
    playButton.setFont(ft);
    settingsButton.setFont(ft);
    showLeaderBoard.setFont(ft);
    exitButton.setFont(ft);
}

void Menu::setPosition() {
    playButton.setPosition(gameSettings->windowX / 2, gameSettings->windowY / 5);
    settingsButton.setPosition(gameSettings->windowX / 2, 2 * gameSettings->windowY / 5);
    showLeaderBoard.setPosition(gameSettings->windowX / 2, 3 * gameSettings->windowY / 5);
    exitButton.setPosition(gameSettings->windowX / 2, 4 * gameSettings->windowY / 5);
}

void Menu::draw(){
    Menu::setFont(gameSettings->font);
    Menu::setPosition();
    playButton.draw(gameSettings->window);
    settingsButton.draw(gameSettings->window);
    showLeaderBoard.draw(gameSettings->window);
    exitButton.draw(gameSettings->window);
}

