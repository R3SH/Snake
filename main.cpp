#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <fstream>
#include <chrono>
#include <Windows.h>

using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;	// weight
int h = size * M;	// height
int a = 0;			//acces to f2
int ms = 0;			//music selecting
int score = 0;
int nScreenWidth = 40;
int nScreenHeight = 40;

int dir, num = 4;	//dir -- direction, num -- length of snake;

void menu(RenderWindow & window)
{
	SoundBuffer sb1;
	sb1.loadFromFile("Sounds/Menu2.ogg");
	Sound s1;
	s1.setBuffer(sb1);

	Texture mt1, mt2, mt3, mtOpMus, musT1, musT2, musT3;
	mt1.loadFromFile("images/start.png");
	mt2.loadFromFile("images/options.png");
	mt3.loadFromFile("images/exit.png");
	mtOpMus.loadFromFile("images/music.png");
	musT1.loadFromFile("images/ADG.png");
	musT2.loadFromFile("images/ttcd.png");
	musT3.loadFromFile("images/mib.png");

	Sprite ms1(mt1), ms2(mt2), ms3(mt3), musOpS(mtOpMus);

	int isMenu = 1;
	int menuNum = 0;
	int imp = 0;

	ms1.setPosition(20, 30);
	ms2.setPosition(20, 120);
	ms3.setPosition(20, 210);

	while (isMenu != 0)
	{
		if (isMenu == 1)
		{
			ms1.setColor(Color::Black);
			ms2.setColor(Color::Black);
			ms3.setColor(Color::Black);
			menuNum = 0;
			window.clear(Color(100, 100, 100));

			if (IntRect(20, 30, 250, 70).contains(Mouse::getPosition(window)))
			{
				ms1.setColor(Color::Red);
				menuNum = 1;
			}
			if (IntRect(20, 120, 350, 70).contains(Mouse::getPosition(window))) 
			{
				ms2.setColor(Color::Red);
				menuNum = 2;
			}
			if (IntRect(20, 210, 170, 70).contains(Mouse::getPosition(window))) 
			{
				ms3.setColor(Color::Red); 
				menuNum = 3;
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1)
				{
					isMenu = 0;
					s1.play();
				}
				if (menuNum == 2)
				{
					isMenu = 2;
					s1.play();
				}
				if (menuNum == 3) 
				{ 
					window.close();
					isMenu = 0;
					s1.play();
				};
			}

			window.draw(ms1);
			window.draw(ms2);
			window.draw(ms3);

			window.display();
		};

		if (isMenu == 2)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				isMenu = 1;
				s1.play();
			}

			Sprite musS1, musS2, musS3;
			musS1.setTexture(musT1);
			musS2.setTexture(musT2);
			musS3.setTexture(musT3);
			musOpS.setPosition(20, 30);
			musOpS.setColor(Color::Black);
			window.clear(Color(100, 100, 100));

			musS1.setPosition(200, 30);
			musS2.setPosition(200, 30);
			musS3.setPosition(200, 30);

			if (imp == 0)
			{
				window.draw(musS1);
				musS1.setColor(Color::Red);
			}
			else if (imp == 1)
			{
				window.draw(musS2);				
				musS2.setColor(Color::Red);
			}
			else if (imp == 2)
			{
				window.draw(musS3);
				musS3.setColor(Color::Red);
			};

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (imp != 3) { ++imp; }
				printf("%i\n", imp);
			}

			if (IntRect(20, 30, 250, 70).contains(Mouse::getPosition(window))) 
			{
				musOpS.setColor(Color::Red);

				if (Mouse::isButtonPressed(Mouse::Left))
					{
						if (imp != 3) { ++imp; }
						else if (imp = 3) { imp = 0; }
						printf("%i\n", imp);
					}
				else if (imp == 3)
				{
					imp = 0;
					printf("!\n");
				}
			}
			
			else if (imp == 3) 
			{
				imp = 0;
				printf("!\n");
			}
			
			ms = imp;
			window.draw(musOpS);
			window.display();
		};
	}
};

struct Snake
{
	int x, y;
}  s[100];

struct Fruct1
{
	int x, y;
} f1;

struct Fruct2
{
	int x, y;
} f2;

void Tick()
{
	SoundBuffer buffer1;
	buffer1.loadFromFile("Sounds/S1.ogg");
	Sound sound1;
	sound1.setBuffer(buffer1);

	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;


	if ((s[0].x == f1.x) && (s[0].y == f1.y))
	{
		sound1.play();
		num++;
		++score;
		if (a != 5)
		{
			++a;
		}
		printf("Score = %i\n", score);
		f1.x = rand() % N;
		f1.y = rand() % M;
		for (int i = 0; i < num; ++i)
		{
			while (f1.x == s[i].x && f1.y == s[i].y)
			{
				f1.x = rand() % N;
				f1.y = rand() % M;
				printf("1\n");
			}
		}
	}

	if (((s[0].x == f2.x) && (s[0].y == f2.y)) && (a == 5))
	{
		sound1.play();
		num += 5;
		score += 5;
		a = 0;
		printf("Score = %i\n", score);
		f2.x = rand() % N;
		f2.y = rand() % M;
		for (int i = 0; i < num; ++i)
		{
			while (f2.x == s[i].x && f2.y == s[i].y)
			{
				f2.x = rand() % N;
				f2.y = rand() % M;
				printf("2\n");
			}
		}
	}

	if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
	if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i;
}

int main()
{
	srand(time(0));

	printf("Red = 1, white = 5;\n");

	RenderWindow window(VideoMode(w + size, h + size), "Snake Game!");
	menu(window);

	wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	DWORD dwBytesWritten = 0;

	Music m1, m2, m3;
	m1.openFromFile("Sounds/ADG.ogg");
	m2.openFromFile("Sounds/ttcd.ogg");
	m3.openFromFile("Sounds/mib.ogg");
	
	if (ms == 0)
	{
		m1.play();
		m1.setLoop(true);
	}
	else if (ms == 1)
	{
		m2.play();
		m2.setLoop(true);
	}
	else
	{
		m3.play();
		m3.setLoop(true);
	};

	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/texture2.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	t4.loadFromFile("images/white.png");

	Sprite s1, s2, s3, s4;
	s1.setTexture(t1);
	s2.setTexture(t2);
	s3.setTexture(t3);
	s4.setTexture(t4);

	Clock clock;

	f1.x = f1.y = 10;
	f2.x = f2.y = 8;

	auto tp1 = std::chrono::system_clock::now();	//time point 1
	auto tp2 = std::chrono::system_clock::now();	//time point 2

	while (window.isOpen())
	{
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		//printf("FPS:%3.2f\n", 1.0f / fElapsedTime);

		Tick();

		clock.restart();

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1)  dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3) dir = 0;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

		////// Draw  ///////
		window.clear();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				s1.setPosition(i * size, j * size);
				window.draw(s1);
			}

		for (int i = 0; i < num; i++)
		{
			s2.setPosition(s[i].x * size, s[i].y * size);
			window.draw(s2);
		}

		s3.setPosition(f1.x * size, f1.y * size); 
		window.draw(s3);

		if (a == 5)
		{
			s4.setPosition(f2.x * size, f2.y * size);
			window.draw(s4);
		}
		window.display();

		swprintf_s(screen, 40, L"FPS:%3.2f", 1.0f / fElapsedTime);
		WriteConsoleOutputCharacter(hConsole, screen, 9, { 0, 0 }, &dwBytesWritten);

	}

	return 0;
}