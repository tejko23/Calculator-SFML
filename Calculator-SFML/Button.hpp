#pragma once
#pragma warning(disable : 4996)

#include <SFML\Graphics.hpp>

//https://github.com/SFML/SFML/wiki/Source:-Radial-Gradient-Shader
//shader
const std::string RadialGradient =
"uniform vec4 color;"
"uniform float expand;"
"uniform vec2 center;"
"uniform float radius;"
"uniform float windowHeight;"
"void main(void)"
"{"
"vec2 centerFromSfml = vec2(center.x, windowHeight - center.y);"
"vec2 p = (gl_FragCoord.xy - centerFromSfml) / radius;"
"float r = sqrt(dot(p, p));"
"if (r < 1.0)"
"{"
"gl_FragColor = mix(color, gl_Color, (r - expand) / (1 - expand));"
"}"
"else"
"{"
"gl_FragColor = gl_Color;"
"}"
"}";
const std::string VertexShader =
"void main()"
"{"
"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
"gl_FrontColor = gl_Color;"
"}";

class Button : public sf::Drawable {
public:
	std::string value;
	sf::RectangleShape rec;
	sf::RectangleShape recin;
	sf::Color color;

	//value, pos x, pos y, color, size x, size y
	Button(std::string, float, float, sf::Uint32 = 0x483e3dff,
		float = 80.f, float = 55.f);

	std::string selected();
	void deselected();
	void update(sf::RenderWindow* win, std::string command);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Font font;
	sf::Text txt;
	sf::Shader shader;
	sf::Shader shader2;
	sf::RenderWindow* window{};
	sf::Vector2f mouse_pos{};
	bool active = true;
	std::string commandlist{};
};