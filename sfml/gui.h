#include <SFML/Graphics.hpp>
using namespace sf;
class Inventory
{
	public:
	Image image;
	Texture t;
	Sprite s;
	String itemName[6] = {};
	
	Image bow;
	Texture tBow;
	Sprite sBow;
	
	Inventory()
	{
	image.loadFromFile("textures/hood_textures.png");
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 300, 50));
	
	bow.loadFromFile("textures/PicsForInvent.png");
	tBow.loadFromImage(bow);
	sBow.setTexture(tBow);
	sBow.setTextureRect(IntRect(0,0,45,45));
	
	}
void update(float x, float y, int viewX, int viewY, float hoodScale)
{
	s.setScale(hoodScale,hoodScale);
	float tempX, tempY;
	for(int i = 0; i<6; i++){
	if(itemName[i] == "Bow"){
	if(x>viewX/2 && x<3200-viewX/2 && y>viewY/2 && y<3200-viewY/2) sBow.setPosition(x-147+(50*(i-1)),y+viewY/2-60+3);
	
	else {
		if(x<viewX/2 && y<viewY/2){tempX = viewX/2; tempY = viewY/2; sBow.setPosition(tempX-147+(50*(i-1)),tempY+viewY/2-60+3);}
		else if(x<viewX/2 && y>3200-viewY/2){tempX = viewX/2; tempY = 3200-viewY/2; sBow.setPosition(tempX-147+(50*(i-1)),tempY+viewY/2-60+3);}
		else if(x>3200-viewX/2 && y<viewY/2){tempX = 3200-viewX/2; tempY = viewY/2; sBow.setPosition(tempX-147+(50*(i-1)),tempY+viewY/2-60+3);}
		else if(x>3200-viewX/2 && y>3200-viewY/2){tempX = 3200-viewX/2; tempY = 3200-viewY/2; sBow.setPosition(tempX-147+(50*(i-1)),tempY+viewY/2-60+3);}
		else if(x<viewX/2){tempX = viewX/2; sBow.setPosition(tempX-147+(50*(i-1)),y+viewY/2-60+3);}
		else if(x>3200-viewX/2){tempX = 3200-viewX/2; sBow.setPosition(tempX-147+(50*(i-1)),y+viewY/2-60+3);}
		else if(y<viewY/2){tempY = viewY/2; sBow.setPosition(x-147+(50*(i-1)),tempY+viewY/2-60+3);}
		else if(y>3200-viewY/2){tempY = 3200-viewY/2; sBow.setPosition(x-147+(50*(i-1)),tempY+viewY/2-60+3);}
	}
	}
}
	
	if(x>viewX/2 && x<3200-viewX/2 && y>viewY/2 && y<3200-viewY/2) s.setPosition(x-150,y+viewY/2-60);
	
	else {
		if(x<viewX/2 && y<viewY/2){tempX = viewX/2; tempY = viewY/2; s.setPosition(tempX-150,tempY+viewY/2-60);}
		else if(x<viewX/2 && y>3200-viewY/2){tempX = viewX/2; tempY = 3200-viewY/2; s.setPosition(tempX-150,tempY+viewY/2-60);}
		else if(x>3200-viewX/2 && y<viewY/2){tempX = 3200-viewX/2; tempY = viewY/2; s.setPosition(tempX-150,tempY+viewY/2-60);}
		else if(x>3200-viewX/2 && y>3200-viewY/2){tempX = 3200-viewX/2; tempY = 3200-viewY/2; s.setPosition(tempX-150,tempY+viewY/2-60);}
		else if(x<viewX/2){tempX = viewX/2; s.setPosition(tempX-150,y+viewY/2-60);}
		else if(x>3200-viewX/2){tempX = 3200-viewX/2; s.setPosition(tempX-150,y+viewY/2-60);}
		else if(y<viewY/2){tempY = viewY/2; s.setPosition(x-150,tempY+viewY/2-60);}
		else if(y>3200-viewY/2){tempY = 3200-viewY/2; s.setPosition(x-150,tempY+viewY/2-60);}
	}
}
void draw(RenderWindow &window)
{
	window.draw(s);
	window.draw(sBow);
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
	
		bar.setFillColor(Color(0, 0, 0, 220));
		max = 20100;
	}
 
	void update(int k, float x, float y, int viewX, int viewY, float hoodScale)
 
	{
		if (k>0)
		if (k<max)
			bar.setSize(Vector2f((max - k) * 288 / max,90));
		
		s.setScale(hoodScale,hoodScale);

		bar.setScale(hoodScale,hoodScale);

	
		float tempX, tempY;
	if(x>viewX/2 && x<3200-viewX/2 && y>viewY/2 && y<3200-viewY/2) { s.setPosition(x+viewX/2-310,y-viewY/2+10); bar.setPosition(x+viewX/2-310+5,y-viewY/2+10+6);}
	
	else {
		if(x<viewX/2 && y<viewY/2){tempX = viewX/2; tempY = viewY/2; s.setPosition(tempX+viewX/2-310,tempY-viewY/2+10); bar.setPosition(tempX+viewX/2-310+5,tempY-viewY/2+10+6);}
		else if(x<viewX/2 && y>3200-viewY/2){tempX = viewX/2; tempY = 3200-viewY/2; s.setPosition(tempX+viewX/2-310,tempY-viewY/2+10); bar.setPosition(tempX+viewX/2-310+5,tempY-viewY/2+10+6);}
		else if(x>3200-viewX/2 && y<viewY/2){tempX = 3200-viewX/2; tempY = viewY/2; s.setPosition(tempX+viewX/2-310,tempY-viewY/2+10); bar.setPosition(tempX+viewX/2-310+5,tempY-viewY/2+10+6);}
		else if(x>3200-viewX/2 && y>3200-viewY/2){tempX = 3200-viewX/2; tempY = 3200-viewY/2; s.setPosition(tempX+viewX/2-310,tempY-viewY/2+10); bar.setPosition(tempX+viewX/2-310+5,tempY-viewY/2+10+6);}
		else if(x<viewX/2){tempX = viewX/2; s.setPosition(tempX+viewX/2-310,y-viewY/2+10); bar.setPosition(tempX+viewX/2-310+5,y-viewY/2+10+6);}
		else if(x>3200-viewX/2){tempX = 3200-viewX/2; s.setPosition(tempX+viewX/2-310,y-viewY/2+10); bar.setPosition(tempX+viewX/2-310+5,y-viewY/2+10+6);}
		else if(y<viewY/2){tempY = viewY/2; s.setPosition(x+viewX/2-310,tempY-viewY/2+10); bar.setPosition(x+viewX/2-310+5,tempY-viewY/2+10+6);}
		else if(y>3200-viewY/2){tempY = 3200-viewY/2; s.setPosition(x+viewX/2-310,tempY-viewY/2+10); bar.setPosition(x+viewX/2-310+5,tempY-viewY/2+10+6);}
	}
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
	}
	
	void update(float x, float y, int viewX, int viewY, int hp, float hoodScale, float CurrentFrame)
	{
		for(int i = 0; i<=hp; i++){
			int diffX = viewX/2 - 260;
			int diffY = viewY/2 - 120;
		
			s.setTextureRect(IntRect(0,50,50*i,50));
		//	s.setColor(Color::Blue);		//change color of healthpoints depending on spells or other stuff
		
			s.setScale(hoodScale,hoodScale);
			
			float tempX, tempY;
			if(x>viewX/2 && x<3200-viewX/2 && y>viewY/2 && y<3200-viewY/2) s.setPosition(x+diffX+((5-i)*50),y-diffY);// 5 - max hp possible for the player(diff between real in-game hp and full healed one)(offset)
	
			else {
		if(x<viewX/2 && y<viewY/2){tempX = viewX/2; tempY = viewY/2; s.setPosition(tempX+diffX+((5-i)*50),tempY-diffY);}
		else if(x<viewX/2 && y>3200-viewY/2){tempX = viewX/2; tempY = 3200-viewY/2; s.setPosition(tempX+diffX+((5-i)*50),tempY-diffY);}
		else if(x>3200-viewX/2 && y<viewY/2){tempX = 3200-viewX/2; tempY = viewY/2; s.setPosition(tempX+diffX+((5-i)*50),tempY-diffY);}
		else if(x>3200-viewX/2 && y>3200-viewY/2){tempX = 3200-viewX/2; tempY = 3200-viewY/2; s.setPosition(tempX+diffX+((5-i)*50),tempY-diffY);}
		else if(x<viewX/2){tempX = viewX/2; s.setPosition(tempX+diffX+((5-i)*50),y-diffY);}
		else if(x>3200-viewX/2){tempX = 3200-viewX/2; s.setPosition(tempX+diffX+((5-i)*50),y-diffY);}
		else if(y<viewY/2){tempY = viewY/2; s.setPosition(x+diffX+((5-i)*50),tempY-diffY);}
		else if(y>3200-viewY/2){tempY = 3200-viewY/2; s.setPosition(x+diffX+((5-i)*50),tempY-diffY);}
			}
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
