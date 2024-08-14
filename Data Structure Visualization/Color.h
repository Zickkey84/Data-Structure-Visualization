#pragma once

#include "SFML/Graphics.hpp"

const sf::Color DarkBlue(49, 53, 110);
const sf::Color LightBlue(205, 214, 255);
const sf::Color HoverBlue(0, 71, 255);
const sf::Color PressBlue(0, 10, 246);
const sf::Color LightNodeBlue(150, 195, 227);
const sf::Color DarkNodeBlue(101, 106, 178);
const sf::Color NeonPink(248, 0, 246);


enum colorTheme {Light = 0, Dark};
const int numColorTheme = 2;

sf::Color colorTransition(sf::Color colorBefor, sf::Color colorAfter, float percent);

namespace AVL {

    enum colorType { Normal = 0, Highlight, Highlight2, Lowlight };
    const int numColorType = 4;

    struct Color {
        sf::Color fillColor, outlineColor, valueColor, variableColor;
        Color(sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor, sf::Color variableColor);
    };

    Color colorTypeTransition(colorType before, colorType after, colorTheme theme, float percent);

    extern const Color color[numColorTheme][numColorType];
}


namespace HEAP {

    enum colorType { Normal = 0, Highlight, Highlight2, Lowlight };
    const int numColorType = 4;

    struct Color {
        sf::Color fillColor, outlineColor, valueColor, variableColor;
        Color(sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor, sf::Color variableColor);
    };

    Color colorTypeTransition(colorType before, colorType after, colorTheme theme, float percent);

    extern const Color color[numColorTheme][numColorType];
}


namespace HASH {

    enum colorType { Normal = 0, Highlight, Highlight2, Lowlight };
    const int numColorType = 4;

    struct Color {
        sf::Color fillColor, outlineColor, valueColor, variableColor;
        Color(sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor, sf::Color variableColor);
    };

    Color colorTypeTransition(colorType before, colorType after, colorTheme theme, float percent);

    extern const Color color[numColorTheme][numColorType];
}