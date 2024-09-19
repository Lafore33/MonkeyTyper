#include "GameSettings.h"

GameSettings::GameSettings(){
    window.create(sf::VideoMode(1000, 480), "Monkey Typer");
    gamePaused = false;
    afterGame = false;
    isActive = false;
    menu = true;
    isSetting = false;
    showLeaders = false;
    LShift = false;
    Tab = false;
    startGame = false;
    std::ofstream file(savedGameFile, std::ios::app);
    if (file) savedGame = true;
    music.openFromFile("assets/backMusic.mp3");
    fonts = {"Orbitron.ttf", "Standard.otf"};
    font.loadFromFile(defaultFont);
    music.setVolume(volume);
    windowX = (float) window.getSize().x;
    windowY = (float) window.getSize().y;
}