#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Menu.h"
#include "Settings.h"
#include "LeaderBoard.h"
#include "GameSession.h"
#include "PreGame.h"
#include "SavedGame.h"
#include "AfterGame.h"
#include "Game.h"



int main(){
    GameSettings gSettings;
    GameSession gs(gSettings);
    Game game(gSettings, gs);
    Menu menu(gSettings);
    Settings settings(gSettings, gSettings.fonts);
    LeaderBoard ld(gSettings);
    PreGame preGame(gSettings);
    SavedGame sg(gSettings);
    AfterGame ag(gSettings);

    sf::Music music;
    gSettings.music.setLoop(true);
    gSettings.music.play();
    while (gSettings.window.isOpen()){
        gSettings.window.setFramerateLimit(240);
        sf::Event event{};

        while (gSettings.window.pollEvent(event)){
            game.handleEvent(event);
            if (gSettings.isActive && gSettings.startGame) gs.handleEvent(event);
            else if (gSettings.isActive && gSettings.savedGame) sg.handleEvent(event, gs);
            else if (gSettings.isActive && !gSettings.startGame) preGame.handleEvent(event);
            else if (gSettings.menu) menu.handleEvent(event);
            else if (gSettings.isSetting) settings.handleEvent(event);
            else if (gSettings.showLeaders) ld.handleEvent(event);
            else if (gSettings.afterGame) ag.handleEvent(event, gs);

        }

        if (gSettings.startGame and !gSettings.gamePaused){
            game.setTimer();
            game.Words();
            gs.moveWords();
            game.outOfBounds(ld, ag);
        }

        gSettings.window.clear();
        if (gSettings.isActive){
            if (gSettings.startGame) gs.draw();
            else if (gSettings.savedGame) sg.draw();
            else if (!gSettings.startGame) preGame.draw();
        }
        else if (gSettings.menu) menu.draw();
        else if (gSettings.isSetting) settings.draw();
        else if (gSettings.showLeaders) ld.draw();
        else if (gSettings.afterGame) ag.draw();
        gSettings.window.display();
    }

}