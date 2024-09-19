#pragma once
#include <string>
#include <SFML/Graphics.hpp>



class Button{
public:
    Button(float x, float y, const std::string& text, sf::Font& font, int size=30, bool center=true)
            : m_text(text, font, size) {
        if (center){
            m_text.setPosition(x - m_text.getGlobalBounds().width / 2, y - m_text.getGlobalBounds().height / 2);
        }
        else{
            m_text.setPosition(x, y);
        }
        X = x;
        Y = y;
    }
    Button() : m_text(){}

    bool isClicked(const sf::Vector2f& mousePosition) const {
        return m_text.getGlobalBounds().contains(mousePosition);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_text);
    }

    void setColor(const sf::Color& color){
        m_text.setFillColor(color);
    }

    void setString(std::string& newText){
        m_text.setString(newText);
    }

    void setFont(const sf::Font& font){
        m_text.setFont(font);
    }

    void setPosition(const float& x, const float& y, bool center=true){
        X = x;
        Y = y;
        if (center){
            m_text.setPosition(x - m_text.getLocalBounds().width / 2,  y - m_text.getGlobalBounds().height / 2);
        }
        else {
            m_text.setPosition(x,  y);
        }
    }

    sf::Vector2f getPosition(){
        return m_text.getPosition();
    }

private:
    sf::Text m_text;
    float X;
    float Y;
};


inline void isOnButton(Button& button, sf::RenderWindow& window, sf::Event& curEvent, sf::Color color=sf::Color::Red){
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(curEvent.mouseMove.x, curEvent.mouseMove.y));
    if (button.isClicked(mousePos)){
        button.setColor(color);
    }
    else{
        button.setColor(sf::Color::White);
    }
}