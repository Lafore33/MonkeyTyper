#include "SavedGame.h"

SavedGame::SavedGame(GameSettings &game) {
    load = sf::Text("Resume last saved game" + game.curUser, game.font, game.ButtonFontSize);
    yes = Button (game.windowX / 4, game.windowY / 2 + 30, "Yes", game.font, game.TextFontSize);
    no = Button (3 * game.windowX / 4, game.windowY / 2 + 30, "No", game.font, game.TextFontSize);
    backToMenu = Button (20, 10, "Back To Menu", game.font, game.TextFontSize, false);
    gameSettings = &game;
}

void SavedGame::setFont(const sf::Font &font) {
    load.setFont(font);
    yes.setFont(font);
    no.setFont(font);
    backToMenu.setFont(font);

}

void SavedGame::setPosition() {
    load.setPosition((gameSettings->windowX / 2 - load.getGlobalBounds().width / 2),
                     (gameSettings->windowY / 2  - load.getGlobalBounds().height / 2));
    yes.setPosition(gameSettings->windowX / 4, gameSettings->windowY / 2 + 30);
    no.setPosition(3 * gameSettings->windowX / 4, gameSettings->windowY / 2 + 30);
    backToMenu.setPosition(20, 10);
}

void SavedGame::draw() {
    SavedGame::setFont(gameSettings->font);
    SavedGame::setPosition();
    gameSettings->window.draw(load);
    yes.draw(gameSettings->window);
    no.draw(gameSettings->window);
}

void SavedGame::loadGame(GameSession& gs) const {
    std::ifstream file(gameSettings->savedGameFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << gameSettings->savedGameFile  << std::endl;
    }
    std::string word;
    // username
    std::getline(file, word, '\n');
    gameSettings->curUser = word;
    gs.currentWords.clear();

    while (std::getline(file, word, '\n') && word != "!!"){
        std::string name;
        float x;
        float y;
        int lastIndex = 0;
        std::string temp;
        for (int i = 0; i < word.size(); i++){
            if (word[i] == ' ') {
                lastIndex = i;
                break;
            }
            temp += word[i];
        }
        name = temp;
        temp.clear();
        for (int i = lastIndex + 1; i < word.size(); i++){
            if (word[i] == ' ') {
                lastIndex = i;
                break;
            }
            temp += word[i];
        }
        x = std::stof(temp);
        temp.clear();
        for (int i = lastIndex + 1; i < word.size(); i++){
            temp += word[i];
        }
        y = std::stof(temp);
        sf::Text t = sf::Text(name, gameSettings->font, gameSettings->WordsFont);
        t.setPosition(x, y);
        t.setFillColor(sf::Color::Green);
        gs.currentWords.emplace_back(name, t);
    }
    // score
    std::getline(file, word, '\n');
    gs.count = std::stoi(word);
    gs.points.setString(word);
    // lost words
    std::getline(file, word, '\n');
    gs.lostWords = std::stoi(word);
    // timer
    std::getline(file, word, '\n');
    gameSettings->generalPausedSeconds += std::stof(word);
}


void SavedGame::handleEvent(sf::Event &event, GameSession& gs) {
    if (event.type == sf::Event::MouseMoved){
        isOnButton(no, gameSettings->window, event, sf::Color::Green);
        isOnButton(yes, gameSettings->window, event, sf::Color::Green);
    }
    if (event.type == sf::Event::MouseButtonPressed){
        sf::Vector2f mouseCoords = gameSettings->window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (yes.isClicked(mouseCoords)){
            loadGame(gs);
            gameSettings->startGame = true;
            gameSettings->savedGame = false;
            gameSettings->generalClock.restart();
        }
        else if(no.isClicked(mouseCoords)){
            gameSettings->gamePaused = false;
            gameSettings->savedGame = false;
            gameSettings->isActive = true;
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
        }
    }
}