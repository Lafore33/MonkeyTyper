#include "Game.h"

std::string generateWords(std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return "";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4923);

    std::string word;
    std::string randomWord;
    int index = dis(gen);

    for (int i = 0; i <= index; i++){
        file >> word;
        if (i == index){
            randomWord = word;
        }
    }

    return randomWord;
}

bool findForCoordinates(const std::vector<std::pair<std::string, sf::Text>>& curWords, float y){
    for (const std::pair<std::string, sf::Text>& pair : curWords){
        if (pair.second.getPosition().x < 50 and pair.second.getPosition().y - y < 25 and pair.second.getPosition().y - y > -25){
            return true;
        }
    }
    return false;
}


float generatePosition(const std::vector<std::pair<std::string, sf::Text>>& curWords, float newS, float oldSize=480){
    float minNumber = 1 / oldSize * newS;
    float maxNumber = 380 / oldSize * newS;
    float newPosition;
    newPosition = minNumber + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxNumber - minNumber)));
    while (findForCoordinates(curWords, newPosition)){
        newPosition = minNumber + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxNumber - minNumber)));
    }
    return newPosition;
}
Game::Game(GameSettings& gS, GameSession& gs) {
    gameSettings = &gS;
    gameSession = &gs;
}

void pushRecord(const std::string& name, int score, double ms, const std::string& path) {
    std::ofstream file;
    file.open(path, std::ofstream::app);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << std::endl;
    }
    file << name + " " + std::to_string(score) + " " + std::to_string(ms) << "\n";

}

void Game::outOfBounds(LeaderBoard& ld, AfterGame& ag) const {
    for (auto  i = 0; i < gameSession->currentWords.size(); i++){
        if (gameSession->currentWords[i].second.getPosition().x + gameSession->currentWords[i].second.getLocalBounds().width > gameSettings->windowX and
                gameSession->currentWords[i].second.getPosition().y + gameSession->currentWords[i].second.getGlobalBounds().height < gameSession->rectangle.getPosition().y)
        {
            gameSession->lostWords += 1;
            gameSession->missedWords.setString(std::to_string(gameSession->lostWords));
            if (gameSession->lostWords == gameSettings->MaxLostWords){
                ag.result.setString("Your result is " + std::to_string(gameSession->count));
                gameSettings->isActive = false;
                pushRecord(gameSettings->curUser, gameSession->count, gameSettings->moveSpeed, ld.leaderFile);
                std::vector<std::string> temp = {gameSettings->curUser, std::to_string(gameSession->count), std::to_string(gameSettings->moveSpeed)};
                ld.leaderBord.push_back(temp);
                ld.bestResult.push_back(temp);
                gameSettings->afterGame = true;
                gameSettings->startGame = false;
            }
            gameSession->currentWords.erase(gameSession->currentWords.begin() + i);
        }
    }
}



void Game::setTimer() {
    std::ostringstream ss;
    sf::Time elapsedTime = gameSettings->generalClock.getElapsedTime();
    seconds = elapsedTime.asSeconds() + gameSettings->generalPausedSeconds;
    ss << std::fixed << std::setprecision(2) << seconds;
    std::string roundedValue = ss.str();
    gameSession->timerText.setString("Time: " + roundedValue + "s");
}

void Game::Words() const {
    float deltaTime = gameSettings->intervalClock.restart().asSeconds();
    gameSettings->elapseTime += deltaTime;
    if (gameSettings->elapseTime >= gameSettings->interval){
        if (gameSession->currentWords.size() < gameSettings->MaxWords){
            gameSession->newWord = sf::Text(generateWords(gameSettings->filename), gameSettings->font, gameSettings->WordsFont);
            gameSession->newWord.setFillColor(sf::Color::Green);
            if (gameSession->currentWords.size() % 2 == 0){
                gameSession->newWord.setPosition(-gameSession->newWord.getLocalBounds().width, generatePosition(gameSession->currentWords, gameSettings->windowY));
            }
            else{
                gameSession->newWord.setPosition(-gameSession->newWord.getLocalBounds().width * 2, generatePosition(gameSession->currentWords, gameSettings->windowY) * 0.95f);
            }
            gameSession->currentWords.emplace_back(std::pair(gameSession->newWord.getString(), gameSession->newWord));
        }
        gameSettings->elapseTime = 0.0;
    }
}

void Game::handleEvent(sf::Event &event) const {
    if (event.type == sf::Event::Closed) {
        gameSettings->window.close();
    }
    if(event.type == sf::Event::Resized){
        sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
        gameSettings->window.setView(sf::View(visibleArea));
        gameSettings->windowX = (float)event.size.width;
        gameSettings->windowY = (float)event.size.height;
        gameSession->underscore.setPosition(gameSession->input.getPosition().x * 0.001f * gameSettings->windowX, gameSession->input.getPosition().y / 480 * gameSettings->windowY + 15);
    }
}
