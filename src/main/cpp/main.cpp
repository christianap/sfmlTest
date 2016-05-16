#include <iostream>

#include <SFML/Graphics.hpp>

//static sf::CircleShape circle(100.f); // Set the origin
static bool leftMouseButton = false;
static bool moveTo = true;
static int mousePressedX = 0;
static int mousePressedY = 0;

struct Objects {
	sf::CircleShape circle;
	
	Objects(sf::CircleShape pCircle) {
		circle = pCircle;
	}
};

void update(Objects &objects);
void render(sf::RenderWindow &window, Objects &Objects);

int main() {
	using namespace sf;
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(800, 600), "SFML works!", Style::Titlebar | Style::Close, settings);
	window.setVerticalSyncEnabled(true);
    Objects objects(sf::CircleShape(100.f));
    objects.circle.setFillColor(Color::Green); // sf::Color(100, 250, 50)
    objects.circle.setOutlineThickness(6);
    objects.circle.setOutlineColor(sf::Color(250, 150, 100));
    objects.circle.setPosition(200, 200);

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

        update(objects);
        // Rendering
        render(window, objects);

        window.display();
    }

	return(0);
}

void update(Objects &objects) {
	using namespace sf;
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
		objects.circle.move(6, 0);
	} else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
		objects.circle.move(-6, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
		objects.circle.move(0, -6);
	} else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
		objects.circle.move(0, 6);
	}

	if (moveTo) {
		if (objects.circle.getPosition().x <= mousePressedX + 6 && objects.circle.getPosition().x >= mousePressedX - 6) {
			objects.circle.setPosition(mousePressedX, objects.circle.getPosition().y);
		}
		if (objects.circle.getPosition().y <= mousePressedY + 6 && objects.circle.getPosition().y >= mousePressedY - 6) {
			objects.circle.setPosition(objects.circle.getPosition().x, mousePressedY);
		}
		if (objects.circle.getPosition().x > mousePressedX) {
			objects.circle.move(-6, 0);
		} else if (objects.circle.getPosition().x < mousePressedX) {
			objects.circle.move(6, 0);
		}
		if (objects.circle.getPosition().y > mousePressedY) {
			objects.circle.move(0, -6);
		} else if (objects.circle.getPosition().y < mousePressedY) {
			objects.circle.move(0, 6);
		}
		if (objects.circle.getPosition().x == mousePressedX && objects.circle.getPosition().y == mousePressedY) {
			moveTo = false;
		}
	}
}

void render(sf::RenderWindow &window, Objects &objects) {
	using namespace sf;
	window.draw(objects.circle);
}
