#include <iostream>

#include <SFML/Graphics.hpp>

static sf::CircleShape circle(100.f);
static bool leftMouseButton = false;
static bool moveTo = true;
static int mousePressedX = 0;
static int mousePressedY = 0;

void update();
void render(sf::RenderWindow &window);

int main() {
	using namespace sf;
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(800, 600), "SFML works!", Style::Titlebar | Style::Close, settings);
	window.setVerticalSyncEnabled(true);
    circle.setFillColor(Color::Green); // sf::Color(100, 250, 50)
    circle.setOutlineThickness(6);
    circle.setOutlineColor(sf::Color(250, 150, 100));
    circle.setPosition(200, 200);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
            	moveTo = false;
            } else if (event.type == Event::MouseButtonPressed) {
            	if (event.mouseButton.button == Mouse::Left) {
            		leftMouseButton = true;
            		moveTo = true;
            		mousePressedX = event.mouseButton.x;
            		mousePressedY = event.mouseButton.y;
            	}
            } else if (event.type == Event::MouseButtonReleased) {
            	leftMouseButton = false;
            }/* else if (event.type == Event::MouseMoved) {
            	if (leftMouseButton) {
            		circle.setPosition(event.mouseMove.x, event.mouseMove.y);
            	}
            }*/
        }

        window.clear();

        update();
        // Rendering
        render(window);

        window.display();
    }

	return(0);
}

void update() {
	using namespace sf;
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
		circle.move(6, 0);
	} else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
		circle.move(-6, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
		circle.move(0, -6);
	} else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
		circle.move(0, 6);
	}

	if (moveTo) {
		if (circle.getPosition().x <= mousePressedX + 6 && circle.getPosition().x >= mousePressedX - 6) {
			circle.setPosition(mousePressedX, circle.getPosition().y);
		}
		if (circle.getPosition().y <= mousePressedY + 6 && circle.getPosition().y >= mousePressedY - 6) {
			circle.setPosition(circle.getPosition().x, mousePressedY);
		}
		if (circle.getPosition().x > mousePressedX) {
			circle.move(-6, 0);
		} else if (circle.getPosition().x < mousePressedX) {
			circle.move(6, 0);
		}
		if (circle.getPosition().y > mousePressedY) {
			circle.move(0, -6);
		} else if (circle.getPosition().y < mousePressedY) {
			circle.move(0, 6);
		}
		if (circle.getPosition().x == mousePressedX && circle.getPosition().y == mousePressedY) {
			moveTo = false;
		}
	}
}

void render(sf::RenderWindow &window) {
	using namespace sf;
	window.draw(circle);
}
