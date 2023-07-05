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
void update(float x, float y, int viewY)
{
	int diff = viewY/2 - 60;
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
 
	void update(int k, float x, float y, int viewX, int viewY)
 
	{
		if (k>0)
		if (k<max)
			bar.setSize(Vector2f((max - k) * 288 / max,90));
		
		int diffX = viewX/2 - 310;
		int diffY = viewY/2 - 10;
		s.setPosition(x+diffX,y-diffY);
		
		bar.setPosition(x+diffX+5,y-diffY+6);
	}
 
	void draw(RenderWindow &window)
	{
 
		window.draw(s);
		window.draw(bar);
	}
 
};
