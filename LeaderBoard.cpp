#include "LeaderBoard.h"
#include <fstream>

LeaderBoard::LeaderBoard(GameSettings& game){
    leaderBoard = sf::Text("Leader Board", game.font, game.ButtonFontSize);
    userName = sf::Text("User", game.font, game.ButtonFontSize);
    ms = sf::Text("Move Speed", game.font, game.ButtonFontSize);
    maxResult = sf::Text("Result", game.font, game.ButtonFontSize);
    backToMenu = Button(0.02f * game.windowX, 0.010f * game.windowY, "Back To Menu", game.font, game.TextFontSize, false);
    currentSession = Button(game.windowX / 4, 0.1f * game.windowY, "Current Session", game.font, game.TextFontSize);
    bestResults = Button(3 * game.windowX / 4, 0.1f * game.windowY, "All Time", game.font, game.TextFontSize);
    gameSettings = &game;
}
void LeaderBoard::setFont(const sf::Font& font) {
    leaderBoard.setFont(font);
    userName.setFont(font);
    ms.setFont(font);
    maxResult.setFont(font);
    backToMenu.setFont(font);
    currentSession.setFont(font);
    bestResults.setFont(font);
}

void LeaderBoard::setPosition() {
    userName.setPosition(gameSettings->windowX / 4 - userName.getGlobalBounds().width / 2,
                         (gameSettings->windowY / 4.8f - userName.getGlobalBounds().height / 2));

    ms.setPosition((gameSettings->windowX / 2 - ms.getGlobalBounds().width / 2),
                   (gameSettings->windowY / 4.8f - userName.getGlobalBounds().height / 2));

    maxResult.setPosition((3 * gameSettings->windowX / 4 - maxResult.getGlobalBounds().width / 2),
                          (gameSettings->windowY / 4.8f - maxResult.getGlobalBounds().height / 2));

    leaderBoard.setPosition((gameSettings->windowX / 2 - leaderBoard.getGlobalBounds().width / 2),
                            (gameSettings->windowY / 9.9f - leaderBoard.getGlobalBounds().height / 2));
    bestResults.setPosition(3 * gameSettings->windowX / 4, 0.1f * gameSettings->windowY);
    backToMenu.setPosition(0.02f * gameSettings->windowX, 0.010f * gameSettings->windowY, false);
    currentSession.setPosition(gameSettings->windowX / 4, 0.1f * gameSettings->windowY);
}

void LeaderBoard::draw() {

    LeaderBoard::setFont(gameSettings->font);
    LeaderBoard::setPosition();
    bestResults.draw(gameSettings->window);
    currentSession.draw(gameSettings->window);
    backToMenu.draw(gameSettings->window);
    gameSettings->window.draw(ms);
    gameSettings->window.draw(leaderBoard);
    gameSettings->window.draw(userName);
    gameSettings->window.draw(maxResult);
    float i = 0;
    if (currentS){
        for (const auto& vec : leaderBord){
            sf::Text username(vec[0], gameSettings->font, gameSettings->ButtonFontSize);
            sf::Text mvs(vec[2].substr(0,4), gameSettings->font, gameSettings->ButtonFontSize);
            sf::Text record(vec[1], gameSettings->font, gameSettings->ButtonFontSize);

            username.setPosition((gameSettings->windowX / 4 - username.getGlobalBounds().width / 2),
                                 (gameSettings->windowY / 3 - username.getGlobalBounds().height / 2 + 50.f * (i + k)));

            mvs.setPosition((gameSettings->windowX / 2 - mvs.getGlobalBounds().width / 2),
                            (gameSettings->windowY / 3 - mvs.getGlobalBounds().height / 2 + 50.f * (i + k)));

            record.setPosition((3 * gameSettings->windowX / 4 - record.getGlobalBounds().width / 2),
                               (gameSettings->windowY / 3 - record.getGlobalBounds().height / 2 + 50.f * (i + k)));
            if (record.getPosition().y + record.getGlobalBounds().height < gameSettings->windowY and i + k >= 0){
                gameSettings->window.draw(username);
                gameSettings->window.draw(record);
                gameSettings->window.draw(mvs);
            }
            i ++;
        }
    }
    else {
        std::ifstream file(leaderFile);
        bestResult.clear();
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << leaderFile << std::endl;
        }
        std::string word;
        std::string tempUser;
        std::string curS;
        std::string tempScore;
        std::string tempMs;
        std::vector<std::string> elements;
        while (std::getline(file, word, '\n')){
            for (int c = 0; c < word.length(); c++){
                if (word[c] == ' ' or c == word.length() - 1){
                    if (tempUser.empty()) tempUser = curS;
                    else if (tempScore.empty()) tempScore = curS;
                    else tempMs = curS;
                    curS = "";
                }
                else curS += word[c];
            }
            std::vector<std::string> temp = {tempUser, tempScore, tempMs};
            bestResult.push_back(temp);
            tempUser.clear();
            tempScore.clear();
        }
        int j = 0;
        for (const auto& vec : bestResult){
            sf::Text username(vec[0], gameSettings->font, gameSettings->ButtonFontSize);
            sf::Text mvs(vec[2].substr(0,4), gameSettings->font, gameSettings->ButtonFontSize);
            sf::Text record(vec[1], gameSettings->font, gameSettings->ButtonFontSize);

            username.setPosition((gameSettings->windowX / 4 - username.getGlobalBounds().width / 2),
                                 (gameSettings->windowY / 3 - username.getGlobalBounds().height / 2 + 50 * (j + k)));

            mvs.setPosition((gameSettings->windowX / 2 - mvs.getGlobalBounds().width / 2),
                            (gameSettings->windowY / 3 - mvs.getGlobalBounds().height / 2 + 50 * (j + k)));

            record.setPosition((3 * gameSettings->windowX / 4 - record.getGlobalBounds().width / 2),
                               (gameSettings->windowY / 3 - record.getGlobalBounds().height / 2 + 50 * (j + k)));
            if (record.getPosition().y + record.getGlobalBounds().height < gameSettings->windowY and j + k >= 0){
                gameSettings->window.draw(username);
                gameSettings->window.draw(record);
                gameSettings->window.draw(mvs);
            }
            j ++;
        }

    }

}

void LeaderBoard::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            gameSettings->showLeaders = false;
            gameSettings->menu = true;
        }
        else if (event.key.code == sf::Keyboard::Up){
            if (k < 0) k ++;
        }
        else if (event.key.code == sf::Keyboard::Down){
            if (currentS){
                if (k > (int)leaderBord.size() * -1 + 1) {
                    k--;
                }
            }
            else {
                if (k > (int)bestResult.size() * -1 + 1) {
                    k--;
                }
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosition = gameSettings->window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (backToMenu.isClicked(mousePosition)) {
            gameSettings->showLeaders = false;
            gameSettings->menu = true;
        }
        else if (currentSession.isClicked(mousePosition)){
            k = 0;
            currentS = true;
        }
        else if (bestResults.isClicked(mousePosition)){
            k = 0;
            currentS = false;
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        isOnButton(currentSession, gameSettings->window, event, sf::Color::Magenta);
        isOnButton(bestResults, gameSettings->window, event, sf::Color::Red);
        isOnButton(backToMenu, gameSettings->window, event, sf::Color::Yellow);
    }
}