#include "Color.h"

sf::Color colorTransition(sf::Color colorBefore, sf::Color colorAfter, float percent) {
	return sf::Color(
		colorBefore.r + (colorAfter.r - colorBefore.r) * percent,
		colorBefore.g + (colorAfter.g - colorBefore.g) * percent,
		colorBefore.b + (colorAfter.b - colorBefore.b) * percent,
		colorBefore.a + (colorAfter.a - colorBefore.a) * percent
	);
}

AVL::Color::Color(sf::Color _fillColor, sf::Color _outlineColor, sf::Color _valueColor, sf::Color _variableColor) :
	fillColor(_fillColor), outlineColor(_outlineColor), valueColor(_valueColor), variableColor(_variableColor) {}

AVL::Color AVL::colorTypeTransition(colorType colorBefore, colorType colorAfter, colorTheme theme, float percent)
{
	return AVL::Color(
		colorTransition(AVL::color[theme][colorBefore].fillColor, AVL::color[theme][colorAfter].fillColor, percent),
		colorTransition(AVL::color[theme][colorBefore].outlineColor, AVL::color[theme][colorAfter].outlineColor, percent),
		colorTransition(AVL::color[theme][colorBefore].valueColor, AVL::color[theme][colorAfter].valueColor, percent),
		colorTransition(AVL::color[theme][colorBefore].variableColor, AVL::color[theme][colorAfter].variableColor, percent)
	);
}

const AVL::Color AVL::color[numColorTheme][numColorType] =
{
	{
		Color(LightNodeBlue, DarkBlue, DarkBlue, DarkBlue),
		Color(HoverBlue, HoverBlue, DarkBlue, DarkBlue),
		Color(NeonPink, NeonPink, DarkBlue, DarkBlue),
		Color(LightNodeBlue, HoverBlue, DarkBlue, DarkBlue)
	} ,
	{
		Color(DarkNodeBlue, LightBlue, LightBlue, LightBlue),
		Color(HoverBlue, HoverBlue, LightBlue, LightBlue),
		Color(NeonPink, NeonPink, LightBlue, LightBlue),
		Color(DarkNodeBlue, HoverBlue, LightBlue, LightBlue)
	}
};

HEAP::Color::Color(sf::Color _fillColor, sf::Color _outlineColor, sf::Color _valueColor, sf::Color _variableColor) :
	fillColor(_fillColor), outlineColor(_outlineColor), valueColor(_valueColor), variableColor(_variableColor) {}

HEAP::Color HEAP::colorTypeTransition(colorType colorBefore, colorType colorAfter, colorTheme theme, float percent)
{
	return HEAP::Color(
		colorTransition(HEAP::color[theme][colorBefore].fillColor, HEAP::color[theme][colorAfter].fillColor, percent),
		colorTransition(HEAP::color[theme][colorBefore].outlineColor, HEAP::color[theme][colorAfter].outlineColor, percent),
		colorTransition(HEAP::color[theme][colorBefore].valueColor, HEAP::color[theme][colorAfter].valueColor, percent),
		colorTransition(HEAP::color[theme][colorBefore].variableColor, HEAP::color[theme][colorAfter].variableColor, percent)
	);
}

const HEAP::Color HEAP::color[numColorTheme][numColorType] =
{
	{
		Color(LightNodeBlue, DarkBlue, DarkBlue, DarkBlue),
		Color(HoverBlue, HoverBlue, DarkBlue, DarkBlue),
		Color(NeonPink, NeonPink, DarkBlue, DarkBlue),
		Color(LightNodeBlue, HoverBlue, DarkBlue, DarkBlue)
	} ,
	{
		Color(DarkNodeBlue, LightBlue, LightBlue, LightBlue),
		Color(HoverBlue, HoverBlue, LightBlue, LightBlue),
		Color(NeonPink, NeonPink, LightBlue, LightBlue),
		Color(DarkNodeBlue, HoverBlue, LightBlue, LightBlue)
	}
};

