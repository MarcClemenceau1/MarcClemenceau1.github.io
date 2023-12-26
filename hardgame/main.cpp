#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>	
#include <String.h>
#include <iostream>
#include "Square.h"
#include "Block.h"
#include "Line.h"
#include "Spot.h"
#include "Bot.h"
#include "Coin.h"


using namespace sf;
using namespace std;
#define B 1000
#define L 750
//#define B 1920
//#define	L 1080

#define FPS 200

#define countLinesLvl1  16
#define countLinesLvl2  20

//Długości
#define E   50
#define T   6
#define HT  T/2
#define X0  B/2 - 400
#define Y0  L/2 - 175

bool* ghostMode;

template <class T1, class T2> bool isIntersecting(T1& AA, T2 BB)
{
	if (AA.left() > BB.right() || AA.right() < BB.left()
		|| AA.top() > BB.bottom() || AA.bottom() < BB.top()) {
		return false;
	}
	return true;
}
bool isIntersecting(Line& AA, Square BB)
{
	float v = BB.getVelocity();
	if (AA.left()+v > BB.right() || AA.right()-v < BB.left()
		|| AA.top()+v > BB.bottom() || AA.bottom()-v < BB.top()) {
		return false;
	}
	return true;
}

void collisionTest(Square& square, Coin& coin)
{
	if (!isIntersecting(square, coin) || square.getFrozen()) return;

	coin.setCollected(true);
}

bool endLvl(Spot& spot) 
{
	if (spot.tap()) return true;

	return false;

}

void squareHandling(Square& square, vector<Line> lines)
{
	square.stepUp(true);
	for (auto& line : lines) if (isIntersecting(line, square)) {
		square.stepUp(false);
	}
	square.stepDown(true);
	for (auto& line : lines) if (isIntersecting(line, square)) {
		square.stepDown(false);
	}
	square.stepRight(true);
	for (auto& line : lines) if (isIntersecting(line, square)) {
		square.stepRight(false);
	}
	square.stepLeft(true);
	for (auto& line : lines) if (isIntersecting(line, square)) {
		square.stepLeft(false);
	}
}

//****************************************************


int main()
{
	cout << "B: " << B << " L: " << L << " X0: " << X0 << " Y0: " << Y0 ;

	int numberSec = 0;
	bool ghostMode = false;
	bool win = false;
	bool frozen = false;
	bool p = true;
	int blocksX{ 10 }, blocksY{ 7 };
	


	RenderWindow window{ VideoMode{B,L}, "WORLD'S HARDEST GAME IN C++" };
	window.setFramerateLimit(FPS);

	Event event;
	SoundBuffer sb, ssb, rsb, tsb;
	Font font;
	font.loadFromFile("OpenSans-Bold.ttf");

	//Podpis
	String str{"Made by: Krzysztof Cmiel"};
	Text signature(str,font);
	signature.setCharacterSize(20);
	signature.setPosition(B-signature.getGlobalBounds().width - 10, L - signature.getGlobalBounds().height - 10);

	//Muzyka:
	sb.loadFromFile("music.ogg");
	ssb.loadFromFile("sadTrombone.ogg");
	rsb.loadFromFile("rumble.ogg");
	tsb.loadFromFile("trololo.ogg");
	Sound song,sadSong,rumbleSong,trololoSong;
	song.setBuffer(sb);
	sadSong.setBuffer(ssb);
	rumbleSong.setBuffer(rsb);
	trololoSong.setBuffer(tsb);
	song.play();

	//Bohater
	Square square(X0 + 1.5 * E, Y0 + 3.5 * E);

	//Boty
	vector<Bot> bots;
	for (int i = 0; i < 5; i++) {
		if (i % 2 != 0)
		{
			bots.emplace_back(X0 + 8 * E,Y0 + (i + 1.5) * E, 'P', 4 * E);
		}
		else bots.emplace_back(X0 + 8 * E,Y0 + (i + 1.5) * E, 'L', 4 * E);
	}

	//Linie
	float lines1Lvl[countLinesLvl1][5] = {
	{X0 - HT,Y0 - HT,T,7 * E + T},             {X0 - HT,Y0 - HT,3 * E + T,T},                 {X0 - HT + 3 * E,Y0 - HT,T,6 * E + T},     {X0 - HT + 3 * E,Y0 - HT + 6 * E,E + T,T},
	{X0 - HT + 4 * E,Y0 - HT + E,T,5 * E + T}, {X0 - HT + 4 * E,Y0 - HT + E,7 * E + T,T},     {X0 - HT + 11 * E,Y0 - HT,T,E + T},        {X0 - HT + 11 * E,Y0 - HT,5 * E + T,T},
	{X0 - HT + 16 * E,Y0 - HT,T,7 * E + T},    {X0 - HT + 13 * E,Y0 - HT + 7 * E,3 * E + T,T},{X0 - HT + 13 * E,Y0 - HT + E,T,6 * E + T},{X0 - HT + 12 * E,Y0 - HT + E,E + T,T},
	{X0 - HT + 12 * E,Y0 - HT + E,T,5 * E + T},{X0 - HT + 5 * E,Y0 - HT + 6 * E,7 * E + T,T}, {X0 - HT + 5 * E,Y0 - HT + 6 * E,T,E + T}, {X0 - HT,Y0 - HT + 7 * E,5 * E + T,T} };
	vector<Line> lines;
	for (int i = 0; i < countLinesLvl1; i++) {
		lines.emplace_back(lines1Lvl[i][0], lines1Lvl[i][1], lines1Lvl[i][2], lines1Lvl[i][3]);
	}

	//Spoty
	Spot startSpot(X0, Y0, 3 * E, 7 * E);
	Spot endSpot(X0 + 13 * E, Y0, 3 * E, 7 * E);

	//Bloki planszy
	vector<Block> blocks;
	for (int i = 0; i < blocksX; i++) {
		for (int j = 0; j < blocksY; j++) {
			if (i == 0 && j != 6) continue;
			if (i == 9 && j != 0) continue;
			if (j == 0 && i < 8) continue;
			if (j == 6 && i > 1) continue;
			if ((i + j) % 2 != 0)
			{
				blocks.emplace_back(X0+(i + 3) * E,Y0 + j * E, E, true);
			}
			else blocks.emplace_back(X0 + (i + 3) * E, Y0 + j * E, E, false);
		}
	}

	//Kontrolka oszustwa
	CircleShape pilotLight(10);
	pilotLight.setFillColor(Color::Green);
	

	//################################################################################################################
	//##################################################____LVL_1____#################################################
	//################################################################################################################
	
	while (true) 
	{
		window.clear(Color(170, 165, 255));

		//Obsługa zdarzeń
		window.pollEvent(event);
		if (event.type == Event::Resized)
		{
			unsigned wy = window.getSize().y;
			if (wy > 1080) wy = 1080;
			unsigned wx = wy * 1.333;
			window.setSize({wx, wy});
		}
		if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
		{
			window.close();
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))
		{
			if (event.key.code == Keyboard::Tilde && event.key.alt)
			{
				numberSec++;
				if (numberSec > FPS * 3) 
				{
					numberSec = 0;
					ghostMode = !ghostMode;
				}
				
			}
		}

		//Kolizje z botami
		if (!frozen && !ghostMode) {
			for (auto& bot : bots) if (isIntersecting(bot, square)) {
				song.stop();
				sadSong.play();
				for (auto& bot : bots) bot.setFrozen(true);
				square.setFrozen(true);
				square.comeBack();
				frozen = true;
			}
		}
		else if (!square.getFrozen()) {
			song.play();
			for (auto& bot : bots) bot.setFrozen(false);
			frozen = false;
		}
			
		//Aktualizacje obiektów
		for (auto& bot : bots) bot.update();
		if (frozen)square.comeBack(); else squareHandling(square, lines);
		
		//Koniec
		if (isIntersecting(square, endSpot)) win = true;
		if (win) {
			if (p)
			{
				song.stop();
				rumbleSong.play();
				p = false;
			}
			if (endLvl(endSpot)) break;
		}


		//Rysowanie obiektów
		if (ghostMode) window.draw(pilotLight);
		window.draw(startSpot);
		window.draw(endSpot);
		for (auto& block : blocks) window.draw(block);
		for (auto& bot : bots) window.draw(bot);
		for (auto& line : lines) window.draw(line);
		window.draw(square);
		window.draw(signature);

		window.display();
	}
	
	//****************************************************************************************************************
	//**********************************************_____LVL_2_____***************************************************
	//****************************************************************************************************************
#define X0 B/2 - 400
#define Y0 L/2 - 75
#define SC 26

	win = false;
	p = true;

	//Gracz
	square.setPossition({ X0 + E,Y0 + 1.5 * E });

	//Spoty
	Spot startSpot2(X0, Y0, 2 * E, 3 * E);
	Spot endSpot2(X0+14*E, Y0, 2 * E, 3 * E);
	
	//Linie
	vector<Line> lines2;
	float lines2Lvl[countLinesLvl2][5] = {
{X0 - HT,Y0 - HT,T,3 * E + T},             {X0 - HT,Y0 - HT,2 * E + T,T},                 {X0 - HT + 2 * E,Y0 - HT,T,E + T},     {X0 - HT + 2 * E,Y0 - HT + E,E + T,T},
{X0 - HT + 3 * E,Y0 - HT - 2 * E,T,3 * E + T}, {X0 - HT + 3 * E,Y0 - HT - 2 * E,10 * E + T,T},     {X0 - HT + 13 * E,Y0 - HT - 2 * E,T,3 * E + T},        {X0 - HT + 13 * E,Y0 - HT + E,E + T,T},
{X0 - HT + 14 * E,Y0 - HT,T,E + T},    {X0 - HT + 14 * E,Y0 - HT,2 * E + T,T},{X0 - HT + 16 * E,Y0 - HT,T,3 * E + T},{X0 - HT + 14 * E,Y0 - HT + 3 * E,2 * E + T,T},
{X0 - HT + 14 * E,Y0 - HT + 2 * E,T,E + T},{X0 - HT + 13 * E,Y0 - HT + 2 * E,E + T,T}, {X0 - HT + 13 * E,Y0 - HT + 2 * E,T,3 * E + T}, {X0 - HT + 3 * E,Y0 - HT + 5 * E,10 * E + T,T},
{X0 - HT + 3 * E,Y0 - HT + 2 * E,T,3 * E + T}, {X0 - HT + 2 * E,Y0 - HT + 2 * E,E + T,T}, {X0 - HT + 2 * E,Y0 - HT + 2 * E,T,E + T}, {X0 - HT,Y0 - HT + 3 * E,2 * E + T,T} };
	for (int i = 0; i < countLinesLvl2; i++) {
		lines2.emplace_back(lines2Lvl[i][0], lines2Lvl[i][1], lines2Lvl[i][2], lines2Lvl[i][3]);
	}

	//Bloki planszy
	vector<Block> blocks2;
	for (int i = 0; i < blocksX; i++) {
		for (int j = 0; j < blocksY; j++) {
			if ((i + j) % 2 != 0)
			{
				blocks2.emplace_back(X0+(i + 3) * E,Y0 + (j - 2) * E, E, true);
			}
			else blocks2.emplace_back(X0+(i + 3) * E,Y0 + (j - 2) * E, E, false);
		}
	}
	blocks2.emplace_back(X0 + 2 * E, Y0 + E, E, false);
	blocks2.emplace_back(X0 + 13 * E, Y0 + E, E, true);

	//Boty
	vector<Bot> bots2;
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)
		{
			bots2.emplace_back(X0 + (i+3.5) * E, Y0 + 1.5 * E, 'U', 3.5 * E);
		}
		else bots2.emplace_back(X0 + (i+3.5) * E, Y0 + 1.5 * E, 'D', 3.5 * E);
	}

	//Monety
	vector<Coin> coins2;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			coins2.emplace_back(X0 + 7.5 * E + x * SC, Y0 + E + y * SC);
		}
	}


	while (true) {
		window.clear(Color(170, 165, 255));

		//Obsługa zdarzeń
		window.pollEvent(event);
		if (event.type == Event::Resized)
		{
			unsigned wy = window.getSize().y;
			if (wy > 1080) wy = 1080;
			unsigned wx = wy * 1.333;
			window.setSize({ wx, wy });
		}
		if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
		{
			window.close();
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))
		{
			if (event.key.code == Keyboard::Tilde && event.key.alt)
			{
				numberSec++;
				if (numberSec > FPS * 3)
				{
					numberSec = 0;
					ghostMode = !ghostMode;
				}

			}
		}

		//Kolizje
		for (auto& coin : coins2) collisionTest(square, coin);

		//Kolizje z botami
		if (!frozen && !ghostMode) {
			for (auto& bot : bots2) if (isIntersecting(bot, square)) {
				for (auto& bot : bots2) bot.setFrozen(true);
				for (auto& coin : coins2) coin.setCollected(false);
				sadSong.play();
				square.setFrozen(true);
				square.comeBack();
				frozen = true;
			}
		}
		else if (!square.getFrozen()) {
			for (auto& bot : bots2) bot.setFrozen(false);
			frozen = false;
		}

		//Aktualizacje obiektów
		for (auto& bot : bots2) bot.update();
		if (frozen)square.comeBack(); else squareHandling(square, lines2);

		//Koniec
		if (isIntersecting(square, endSpot2)) win = true;
		for (auto& coin : coins2) if (!coin.isCollected()) win = false;
		if (win) {
			if (p)
			{
				rumbleSong.stop();
				trololoSong.play();
				p = false;
			}
			if (endLvl(endSpot2)) break;
		}

		//Rysowanie obiektów
		if (ghostMode) window.draw(pilotLight);
		window.draw(startSpot2);
		window.draw(endSpot2);
		for (auto& block : blocks2) window.draw(block);
		for (auto& line : lines2) window.draw(line);
		for (auto& coin : coins2) window.draw(coin);
		for (auto& bot : bots2) window.draw(bot);
		window.draw(square);
		window.draw(signature);

		window.display();
	}

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___THE_END___@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//Napis
	String inscription{ "YOU WON!" };
	Text text(inscription, font);
	text.setCharacterSize(100);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	text.setPosition({ B / 2 , L / 2 });


	while (true) {
		window.clear(Color(170, 165, 255));

		//Obsługa zdarzeń
		window.pollEvent(event);
		if (event.type == Event::Resized)
		{
			unsigned wy = window.getSize().y;
			if (wy > 1080) wy = 1080;
			unsigned wx = wy * 1.333;
			window.setSize({ wx, wy });
		}
		if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
		{
			window.close();
			break;
		}
	
		text.setFillColor(Color(rand(),rand(),rand()));
		text.setOutlineThickness(5);

		window.draw(text);
		window.draw(signature);

		window.display();
	}


	return 0;
}

