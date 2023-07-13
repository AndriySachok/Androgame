#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include"view.h"
#include"gui.h"
#include"movement.h"
#include "level.h"
#include <vector>
#include <list>
	const float hoodScale = 1;
	const int viewX = 1024;
    const int viewY = 768;
using namespace sf;

class Entity{
	public:
		std::vector<Object> obj;
		float x, y, dx, dy, speed;
		int health, coordX, coordY, w, h, dir;
		bool life;
		String name;
		Texture texture;
		Sprite sprite;
		
		Entity(Image &image, float X, float Y, int CoordX, int CoordY, int W, int H, String Name){
			x = X; y = Y; dir = 0; life = true; dx = 0; dy = 0; speed = 0;
			coordX = CoordX; coordY = CoordY; w = W; h = H;
			name = Name;
			
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		//	sprite.setOrigin(w/2,h/2);
		}
		FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}
};

class Player :public Entity{
public:
	float staminaTimer;
	Player(Image &image, Level &trees, float X, float Y, int CoordX, int CoordY, int W, int H, String Name):Entity(image,X,Y,CoordX,CoordY,W,H,Name){ // Constructor of the player(CoordX and CoordY are to set the right texture rect)
		staminaTimer = 0; health = 5; obj = trees.GetAllObjects();
		if(name == "Player1"){
			sprite.setTextureRect(IntRect(coordX,coordY,w,h));
		}
	}


void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)
		   if (getRect().intersects(obj[i].rect))
		   {
			   if (obj[i].name == "solid")
			   {
				   if (Dy>0)	{ y = obj[i].rect.top - h; dy = 0;}
				   if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;  dy = 0;  }
				   if (Dx>0)	{ x = obj[i].rect.left - w; dx = 0;}
				   if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0;}
			   }
		   }
	   }

void update(float time){
	switch(dir){
		case 0 : dx = speed; dy = 0; break;
		case 1 : dx = -speed; dy = 0; break;
		case 2 : dx = 0; dy = speed; break;
		case 3 : dx = 0; dy = - speed; break;
	}
	x+=dx*time;
	y+=dy*time;
	speed = 0;
	sprite.setPosition(x,y);
	if(health <= 0) life = false;
	if(life) Setplayercoordinateforview(sprite.getPosition().x+w/2, sprite.getPosition().y+h/2, viewX, viewY);
}

};

int main()
{
    RenderWindow window(VideoMode(viewX, viewY), "ANDROGAME");
    
    view.reset(FloatRect(0,0,viewX,viewY));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);
	
	Level trees;
	trees.LoadFromFile("trees.tmx");
	
	Level ground;
	ground.LoadFromFile("ground.tmx");
	
	Image heroImage;
	heroImage.loadFromFile("textures/me.png");
	Object player=trees.GetObject("player");
	
	Player p(heroImage, trees, player.rect.left, player.rect.top, 560, 640, 80, 80, "Player1");
	
	Inventory inv;
	StaminaBar stmbar;
	HealthBar hpbar;
	

	float CurrentFrame = 0;

	Clock clock;
        
    while (window.isOpen())
    {
    	float time = clock.getElapsedTime().asMicroseconds();
    	clock.restart();
    	time = time/800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        if(p.staminaTimer < 20000) p.staminaTimer += time;
        
        
       movement(p.dir, p.speed, CurrentFrame, p.staminaTimer, time, p.life, p.sprite);
		
		inv.update(p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, viewX, viewY, hoodScale);
		stmbar.update(p.staminaTimer, p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, viewX, viewY, hoodScale);
		hpbar.update(p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, viewX, viewY, p.health, hoodScale, CurrentFrame);
		
		p.checkCollisionWithMap(p.dx,p.dy);
		p.update(time);
		window.setView(view);
		
		window.clear();

		ground.Draw(window);
		window.draw(p.sprite);
        trees.Draw(window);
        
		if(p.life)
		{
			inv.draw(window);
			stmbar.draw(window);
			hpbar.draw(window,p.health);
		}
		
        
        window.display();
    }

    return 0;
}

