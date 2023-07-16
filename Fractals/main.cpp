#include <SFML/Graphics.hpp>
#include <conio.h>
#include <iostream>

using namespace sf;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

void setPoint(Image * image, Texture * texture, unsigned int x, unsigned int y) {
	if(x < WIDTH && x >= 0)
		if (y < HEIGHT && y >= 0) {
			image->setPixel(x, y, Color(0, 255, 0));
			texture->loadFromImage(*image);
		}
}

float getDistance(Vector2f start, Vector2f end) {
	return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
}

Vector2f getSmallVec(Vector2f start, Vector2f end) {
	return Vector2f((end.x - start.x) / getDistance(start, end), (end.y - start.y) / getDistance(start, end));
}
/*
short int gen(float *Chance, short pCount) {
	int num = rand() % 10000;
	float sum = 0;
	for (int i = 0; i < pCount; i++) {
		sum += Chance[i];
		if (i < pCount - 1) {
			if ((num < sum * 100) && (num > sum + Chance[i + 1] * 100)) {
				return i;
			}
			else {}
		}
		else {
			return pCount - 1;
		}
	}
	std::cout << "ERROR!" << std::endl;
	return rand() % pCount;
}*/

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Fractals");

	Image im;
	im.create(WIDTH, HEIGHT, Color(0, 0, 0));
	Texture tex;
	tex.loadFromImage(im);
	Sprite spr;
	spr.setTexture(tex);

	Vector2f sv;
	float dis = 0.0;
	short num = 0;
	short urav = 0;
	short int i = 0;
	const short pCount = 6;

	Vector2f vPoint[pCount] = {
		/*Огромный треугольник
		Vector2f(960, 0),
		Vector2f(0, 1439),
		Vector2f(1919, 1439),*/

		/*пятиугольник
		Vector2f(320, 50),
		Vector2f(550, 150),
		Vector2f(90, 140),
		Vector2f(150, 350),
		Vector2f(490, 350),*/
		
		//2 треугольника для папоротника
		Vector2f(177, 299),
		Vector2f(333, 306),
		Vector2f(375, 364),
		Vector2f(366, 408),
		Vector2f(508, 323),
		Vector2f(550, 96),
	};
	//Vector2f p(rand()%(WIDTH - 1), rand()%(HEIGHT - 1));
	Vector2f p(0, 0);
	setPoint(&im, &tex, p.x, p.y);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (Keyboard::isKeyPressed(Keyboard::F12))
					im.saveToFile("result.png");
		}
		
		//num = rand() % pCount;
		//num = gen(drawChance, pCount);
		//std::cout << num << std::endl;

		i = rand() % 100;

		if (i == 1)urav = 0;
		else if (i > 1 && i < 87)urav = 1;
		else if (i > 87 && i < 94)urav = 2;
		else urav = 3;

		switch (urav)
		{
		case 0:
			p.x = 0;
			p.y = 0.16 * p.y;
			break;
		case 1:
			p.x = (0.85 * p.x) + (0.04 * p.y);
			p.y = (-0.04 * p.x) + (0.85 * p.y) + 1.6;
			break;
		case 2:
			p.x = (0.2 * p.x) + (-0.26 * p.y);
			p.y = (0.23 * p.x) + (0.22 * p.y) + 1.6;
			break;
		case 3:
			p.x = (-0.15 * p.x) + (0.28 * p.y);
			p.y = (0.26 * p.x) + (0.24 * p.y) + 0.44;
			break;
		default:
			std::cout << "ERROR" << std::endl;
			break;
		}
		setPoint(&im, &tex, p.x * 50 + 400, p.y * 50 + 50);

		/*sv = getSmallVec(p, vPoint[num]);
		dis = getDistance(p, vPoint[num]);
		p.x += sv.x * (dis / 2);
		p.y += sv.y * (dis / 2);
		setPoint(&im, &tex, p.x, p.y);*/

		window.clear();
		window.draw(spr);
		window.display();
	}

	return 0;
}