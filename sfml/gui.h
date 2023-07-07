#include <SFML/Graphics.hpp>
using namespace sf;
class Inventory
{
	public:
	Image image;
	Texture t;
	Sprite s;


	Inventory()
	{
	image.loadFromFile("textures/hood_textures.png");
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 300, 50));
	}
void update(float x, float y, int viewY, float hoodScale)
{
	int diff = viewY/2 - 60;
	s.setScale(hoodScale,hoodScale);
	s.setPosition(x-150,y+diff);
}
void draw(RenderWindow &window)
{
	window.draw(s);
}
};

class StaminaBar
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;
 
	StaminaBar()
	{
		image.loadFromFile("textures/hood_textures.png");
		t.loadFromImage(image);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 100, 300, 200));
	
		bar.setFillColor(Color(0, 0, 0, 200));
		max = 20100;
	}
 
	void update(int k, float x, float y, int viewX, int viewY, float hoodScale)
 
	{
		if (k>0)
		if (k<max)
			bar.setSize(Vector2f((max - k) * 288 / max,90));
		
		int diffX = viewX/2 - 310;
		int diffY = viewY/2 - 10;
		s.setScale(hoodScale,hoodScale);
		s.setPosition(x+diffX,y-diffY);
		bar.setScale(hoodScale,hoodScale);
		bar.setPosition(x+diffX+5,y-diffY+6);
	}
 
	void draw(RenderWindow &window)
	{
 
		window.draw(s);
		window.draw(bar);
	}
 
};

class HealthBar
{
	public:
	Image image;
	Texture t;
	Sprite s;
	Sprite m;
	HealthBar()
	{
			image.loadFromFile("textures/hood_textures.png");
			t.loadFromImage(image);
			s.setTexture(t);
			s.setTextureRect(IntRect(0,50,250,50));
			m.setTexture(t);
			m.setTextureRect(IntRect(1000,0,250,50));
	}
	
	void update(float x, float y, int viewX, int viewY, int hp, float hoodScale, float CurrentFrame)
	{
		for(int i = 0; i<=hp; i++){
			int diffX = viewX/2 - 260;
			int diffY = viewY/2 - 110;
		
			s.setTextureRect(IntRect(0,50,50*i,50));
		//	s.setColor(Color::Blue);		//change color of healthpoints depending on spells or other stuff
			s.setPosition(x+diffX+((5-i)*50),y-diffY);		// 5 - max hp possible for the player(diff between real in-game hp and full healed one)(offset)
			m.setPosition(x+diffX,y-diffY);
			s.setScale(hoodScale,hoodScale);
		}
	}
	void draw(RenderWindow &window, int health)
	{	
		int a = rand()%10;
		if(health > 1) window.draw(s);
		if(health == 1&&a<4){
			s.setColor(Color::Red);
			window.draw(s);
			
		}
		else if(health == 1&&a>=4){
			s.setColor(Color::Blue);
			window.draw(s);
		}
		
	}
};
