#include "Settings.h"


Settings::Settings(GameSettings& game, std::vector<std::string>& fts) {
    fonts = fts;
    isDragging = false;
    deleteFontButtons = false;
    changingFont = false;
    volumeSetter = sf::RectangleShape(sf::Vector2f(game.windowX / 5, 2.0f));
    volumePointer = sf::CircleShape(10);
    enterSpeed  = Button (game.windowX / 2, 50.f / 480 * game.windowY , "Set the speed ", game.font, game.ButtonFontSize);
    setFontSize = Button (game.windowX / 2, 100.f / 480 * game.windowY, "Font Size", game.font, game.ButtonFontSize);
    changeVolume = Button (game.windowX / 2, 150.f / 480 * game.windowY, "Set the volume", game.font, game.ButtonFontSize);
    changeFont = Button (game.windowX / 2, 250.f / 480 * game.windowY, "Change the Font", game.font, game.ButtonFontSize);
    backToMenu = Button (game.windowX / 50, 10.f / 480 * game.windowY, "Back To Menu", game.font, game.TextFontSize, false);
    newSpeed = Button(game.windowX * 0.7f, 50.f / 480 * game.windowY, speed, game.font, game.ButtonFontSize);
    newSize = Button(game.windowX * 0.7f, 100.f / 480 * game.windowY, std::to_string(game.ButtonFontSize / 2), game.font, game.ButtonFontSize);

    incSpeed = Button(game.windowX * 0.75f, 45.f / 480 * game.windowY, "+", game.font, game.ButtonFontSize);
    decSpeed = Button(game.windowX * 0.65f, 40.f / 480 * game.windowY, "-", game.font, game.ButtonFontSize);
    incSize = Button(game.windowX * 0.75f, 95.f / 480 * game.windowY, "+", game.font, game.ButtonFontSize);
    decSize = Button(game.windowX * 0.65f, 90.f / 480 * game.windowY, "-", game.font, game.ButtonFontSize);
    rest = volumeSetter.getGlobalBounds().width / 2;

    gameSettings = &game;

}

void Settings::handleEvent(sf::Event &event) {
    std::string size;
    float volume = gameSettings->maxVolume / 2;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && volumePointer.getGlobalBounds().contains(gameSettings->window.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
        isDragging = true;
    }

    // Check if mouse is being released
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    }

    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            gameSettings->isSetting = false;
            deleteFontButtons = true;
            changingFont = false;
            gameSettings->menu = true;
        }
    }

    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosition = gameSettings->window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (incSpeed.isClicked(mousePosition) and gameSettings->moveSpeed < gameSettings->maxSpeed){
            gameSettings->moveSpeed += gameSettings->speedStep;
            speed = std::to_string(gameSettings->moveSpeed).substr(0, 4);
            newSpeed.setString(speed);
            gameSettings->interval = 0.1f / (float)gameSettings->moveSpeed;

        }
        else if (decSpeed.isClicked(mousePosition) and gameSettings->moveSpeed > gameSettings->minSpeed){
            gameSettings->moveSpeed -= gameSettings->speedStep;
            speed = std::to_string(gameSettings->moveSpeed).substr(0, 4);
            newSpeed.setString(speed);
            gameSettings->interval = 0.1f /(float) gameSettings->moveSpeed;

        }
        else if (incSize.isClicked(mousePosition) and gameSettings->WordsFont < gameSettings->maxSize){
            gameSettings->WordsFont += gameSettings->fontStep;
            size = std::to_string(gameSettings->WordsFont);
            newSize.setString(size);
        }
        else if (decSize.isClicked(mousePosition) and gameSettings->WordsFont > gameSettings->minSize){
            gameSettings->WordsFont -= gameSettings->fontStep;
            size = std::to_string(gameSettings->WordsFont);
            newSize.setString(size);
        }

        if (backToMenu.isClicked(mousePosition)) {
            gameSettings->isSetting = false;
            gameSettings->menu = true;
            changingFont = false;
            deleteFontButtons = true;
        }
        if (changeFont.isClicked(mousePosition)) {
            if (changingFont) {
                curFonts.clear();
                deleteFontButtons = true;
                changingFont = false;
            } else {
                deleteFontButtons = false;
                changingFont = true;
            }
        }
        int i = 0;
        for (const Button &but: curFonts) {
            if (but.isClicked(mousePosition)) {
                gameSettings->font.loadFromFile(fonts[i]);
                break;
            }
            i++;
        }

    }
    else if (event.type == sf::Event::MouseMoved) {
        isOnButton(incSpeed, gameSettings->window, event, sf::Color::Red);
        isOnButton(decSpeed, gameSettings->window, event, sf::Color::Red);
        isOnButton(incSize, gameSettings->window, event, sf::Color::Red);
        isOnButton(decSize, gameSettings->window, event, sf::Color::Red);

        isOnButton(changeVolume, gameSettings->window, event, sf::Color::Blue);
        isOnButton(setFontSize, gameSettings->window, event, sf::Color::Green);
        isOnButton(newSize, gameSettings->window, event, sf::Color::Red);
        isOnButton(backToMenu, gameSettings->window, event, sf::Color::Yellow);
        isOnButton(changeFont, gameSettings->window, event, sf::Color::Magenta);
        isOnButton(newSpeed, gameSettings->window, event, sf::Color::Green);
        isOnButton(enterSpeed, gameSettings->window, event, sf::Color::Red);
        for (Button& but: curFonts) {
            isOnButton(but, gameSettings->window, event, sf::Color::Green);
        }
        if (isDragging ) {
            // Calculate new volume based on mouse position
            if (sf::Mouse::getPosition(gameSettings->window).x >= volumeSetter.getPosition().x && sf::Mouse::getPosition(gameSettings->window).x <= volumeSetter.getPosition().x + volumeSetter.getGlobalBounds().width){
                volume = static_cast<float>(sf::Mouse::getPosition(gameSettings->window).x - volumeSetter.getPosition().x)  * gameSettings->maxVolume / volumeSetter.getGlobalBounds().width;
                gameSettings->music.setVolume(volume);
            }

            // Update pointer position
            if (sf::Mouse::getPosition(gameSettings->window).x - volumePointer.getRadius() < volumeSetter.getPosition().x){
                volumePointer.setPosition(volumeSetter.getPosition().x, volumePointer.getPosition().y);
            }
            else if (sf::Mouse::getPosition(gameSettings->window).x + volumePointer.getRadius() > volumeSetter.getPosition().x + volumeSetter.getGlobalBounds().width){
                volumePointer.setPosition((volumeSetter.getPosition().x + volumeSetter.getGlobalBounds().width), volumePointer.getPosition().y);
            }
            else{
                volumePointer.setPosition(sf::Mouse::getPosition(gameSettings->window).x - volumePointer.getRadius(), volumePointer.getPosition().y);
            }
            rest = volumePointer.getPosition().x - volumeSetter.getPosition().x;

        }
    }
}

void Settings::setFont(const sf::Font& font) {
    percentage.setFont(font);

    changeVolume.setFont(font);
    incSize.setFont(font);
    decSize.setFont(font);
    incSpeed.setFont(font);
    decSpeed.setFont(font);
    setFontSize.setFont(font);
    newSize.setFont(font);
    changeFont.setFont(font);
    backToMenu.setFont(font);
    newSpeed.setFont(font);
    enterSpeed.setFont(font);
}

void Settings::setPosition() {
    percentage.setString(std::to_string((int)(rest / volumeSetter.getGlobalBounds().width * 100)) + "%");
    percentage.setPosition(gameSettings->windowX * 0.7f - percentage.getGlobalBounds().width / 2, volumeSetter.getPosition().y - percentage.getGlobalBounds().height / 2);
    volumeSetter.setPosition(gameSettings->windowX / 2 - volumeSetter.getGlobalBounds().width / 2, changeVolume.getPosition().y + 50);
    volumePointer.setPosition(volumeSetter.getPosition().x + rest - volumePointer.getRadius(), volumeSetter.getPosition().y  - volumeSetter.getGlobalBounds().height / 2 - volumePointer.getRadius());
    changeVolume.setPosition(gameSettings->windowX / 2, 150.f / 480 * gameSettings->windowY);
    incSize.setPosition(gameSettings->windowX * 0.75f,95.f / 480 * gameSettings->windowY);
    decSize.setPosition(gameSettings->windowX * 0.65f,90.f / 480 * gameSettings->windowY);
    incSpeed.setPosition(gameSettings->windowX * 0.75f,45.f / 480 * gameSettings->windowY);
    decSpeed.setPosition(gameSettings->windowX * 0.65f,40.f / 480 * gameSettings->windowY);
    setFontSize.setPosition(gameSettings->windowX / 2, 100.f / 480 * gameSettings->windowY);
    newSize.setPosition(gameSettings->windowX * 0.7f, 100.f / 480 * gameSettings->windowY);
    changeFont.setPosition(gameSettings->windowX / 2, 250.f / 480 * gameSettings->windowY);
    backToMenu.setPosition(gameSettings->windowX / 50, 10.f / 480 * gameSettings->windowY, false);
    newSpeed.setPosition(gameSettings->windowX * 0.7f, 50.f / 480 * gameSettings->windowY);
    enterSpeed.setPosition(gameSettings->windowX / 2, 50.f / 480 * gameSettings->windowY);
}
void Settings::draw() {
    Settings::setFont(gameSettings->font);
    Settings::setPosition();
    changeVolume.draw(gameSettings->window);
    incSize.draw(gameSettings->window);
    decSize.draw(gameSettings->window);
    incSpeed.draw(gameSettings->window);
    decSpeed.draw(gameSettings->window);
    setFontSize.draw(gameSettings->window);
    newSize.draw(gameSettings->window);
    changeFont.draw(gameSettings->window);
    backToMenu.draw(gameSettings->window);
    newSpeed.draw(gameSettings->window);
    enterSpeed.draw(gameSettings->window);
    gameSettings->window.draw(percentage);
    gameSettings->window.draw(volumePointer);
    gameSettings->window.draw(volumeSetter);

    if (changingFont and !deleteFontButtons){
        if (curFonts.empty()){
            float i = 1;
            for (const std::string& path : fonts){
                if (i == 1){
                    Button tempFontButton(gameSettings->windowX / 2, (changeFont.getPosition().y + 60.f), std::to_string((int)i) + ". " + path.substr(0, path.size() - 4), gameSettings->font, gameSettings->ButtonFontSize);
                    curFonts.emplace_back(tempFontButton);

                }
                else {
                    Button tempFontButton(gameSettings->windowX / 2, (curFonts[curFonts.size() - 1].getPosition().y + 60.f),
                                          std::to_string((int) i) + ". " + path.substr(0, path.size() - 4),
                                          gameSettings->font, gameSettings->ButtonFontSize);
                    curFonts.emplace_back(tempFontButton);

                }
                i++;
            }
        }
        for (Button& but : curFonts ){
            but.setFont(gameSettings->font);
            but.draw(gameSettings->window);
        }
    }
}
