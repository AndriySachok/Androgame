#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
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
			x = X; y = Y; dir = 4; life = true; dx = 0; dy = 0; speed = 0;
			coordX = CoordX; coordY = CoordY; w = W; h = H;
			name = Name;
			
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		//	sprite.setOrigin(w/2,h/2);
		}
		FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
};

class Player :public Entity{
public:
	bool IsShoot, isDamaged;
	float staminaTimer, stunTimer;
	String weapon;
	int itemChosen, stunTime;
	Player(Image &image, Level &trees, float X, float Y, int CoordX, int CoordY, int W, int H, String Name):Entity(image,X,Y,CoordX,CoordY,W,H,Name){ // Constructor of the player(CoordX and CoordY are to set the right texture rect)
		staminaTimer = 0; stunTimer = 0; stunTime = 1000; health = 5; obj = trees.GetAllObjects(); IsShoot = false; weapon = ""; itemChosen = 0; isDamaged = false;
		if(name == "Player1"){
			sprite.setTextureRect(IntRect(coordX,coordY,w,h));
		}
	}

void stopMoving(float Dx, float Dy){
	for (int i = 0; i<obj.size(); i++)
		   if (getRect().intersects(obj[i].rect))
		   {
	 	if (Dy>0)	{ y = obj[i].rect.top - h; dy = 0;}
		if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;  dy = 0;  }
		if (Dx>0)	{ x = obj[i].rect.left - w; dx = 0;}
		if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0;}
	}
}

void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)
		   if (getRect().intersects(obj[i].rect))
		   {
			   if (obj[i].name == "solid")
			   {
			   	stopMoving(Dx,Dy);
			   }
			   if(obj[i].name == "cactus"){
			   		isDamaged = true;
			   		health--;
			   		obj[i].name = "solid";
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

class Enemy :public Entity{
	public:
	Enemy(Image &image, Level &trees, float X, float Y, int CoordX, int CoordY, int W, int H, String Name):Entity(image, X, Y, CoordX, CoordY, W, H, Name){
		if(name == "Pigeon"){
			health = 1;
			sprite.setTextureRect(IntRect(coordX,coordY,w,h));
		}
	}
	
/*	void update(float time){
		
	}*/
};


class Bullet :public Entity{
	public:
	int tempx, tempy;
	float dist;

	Bullet(Image &image, Level &trees, float X, float Y, int CoordX, int CoordY, int W, int H, String Name, int tempX, int tempY, float distance):Entity(image,X,Y,CoordX,CoordY,W,H,Name){
		sprite.setTextureRect(IntRect(coordX,coordY,w,h));
		obj = trees.GetObjects("solid");
		speed = 2.5;
		life = true;
		tempx = tempX; tempy = tempY; dist = distance;
	}
	
	void update(float time){
		float a = tempx - x;
		float b = tempy - y;
	//	float angleRotat = -((atan2(a,b))*180/3.14159265-90);
		float angleShoot = (atan2(a,b))*180/3.14159265359;
		
		bool poss = true;
		if(dist < 100) poss = false;
		float speedX = speed * cos(angleShoot);
		float speedY = speed * sin(angleShoot);
		if (poss){
		x += speedX;
		y += speedY;
		

		if (x <= 0 || y <= 0 || x >= 3200 || y >= 3200) life = false;
		
		for (int i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect)) 
			{
				life = false;
			}
		}
		sprite.setOrigin(w/2,h/2);
		sprite.setRotation(-(angleShoot+90));
		sprite.setPosition(x+25, y+10);
	}
}
};

class Weapons{
	public:
		String name;
		Texture texture;
		Sprite sprite;
		float coolDownTimer;
		int coolDown;
		bool isTaken;
		
		Weapons(Image &image, String Name, int CoolDown){
			name = Name;
			coolDown = CoolDown;
			coolDownTimer = 0;
			isTaken = false;
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			
	}
	
	void update(float time, float x, float y, int tempX, int tempY, int coordX, int coordY, int w, int h, String weapon, int itemChosen, String itemName[]){
		
		if(itemName[itemChosen] == "Bow"){
			isTaken = true;
		sprite.setTextureRect(IntRect(coordX,coordY,w,h));
		float a = tempX - x;
		float b = tempY - y;
	//	float angleRotat = -((atan2(a,b))*180/3.14159265-90);
		float angleShoot = (atan2(a,b))*180/3.14159265359;
		sprite.setOrigin(w/2,h/2);
		sprite.setRotation(-(angleShoot+90));
	
		sprite.setPosition(x+55,y+50);
		}
		else isTaken = false;
	
	}
	
};

int main()
{
	srand(time(NULL));
    RenderWindow window(VideoMode(viewX, viewY), "ANDROGAME");

    view.reset(FloatRect(0,0,viewX,viewY));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);
	
	Image BulletImage;
	BulletImage.loadFromFile("textures/arrows.png");
	
	Level trees;
	trees.LoadFromFile("trees.tmx");
	
	Level ground;
	ground.LoadFromFile("ground.tmx");
	
	Image heroImage;
	heroImage.loadFromFile("textures/mikey.png");
	Object player=trees.GetObject("player");
	Player p(heroImage, trees, player.rect.left, player.rect.top, 560, 640, 80, 80, "Player1");
	
	Image pigeonImage;
	pigeonImage.loadFromFile("texture/pigeons_50.png");
	Enemy enemy(pigeonImage, trees, 0, 0, 0, 0, 50, 50, "Pigeon");
	
	Inventory inv;
	StaminaBar stmbar;
	HealthBar hpbar;
		inv.itemName[1] = "Bow";
	
	Image bowImage;
	bowImage.loadFromFile("textures/bow.png");
	Weapons bow(bowImage, "Bow", 2000);
	

	
	Music music;
	music.openFromFile("audio/forest.wav");
	music.play();
	music.setLoop(true);
	
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("audio/shoot.wav");
	Sound shoot(shootBuffer);
	
	SoundBuffer damageBuffer;
	damageBuffer.loadFromFile("audio/bird-01-collision-a4_1.wav");
	Sound damage(damageBuffer);
	
	float distance = 0;
	float CurrentFrame = 0;

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	Clock clock;
        
    while (window.isOpen())
    {	
    	Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
        	
    	float time = clock.getElapsedTime().asMicroseconds();
    	clock.restart();
    	time = time/800;
        Event event;
        while (window.pollEvent(event))
        {
        	if(p.IsShoot == true)  {
        		distance = sqrt((pos.x - p.sprite.getPosition().x)*(pos.x - p.sprite.getPosition().x) + (pos.y - p.sprite.getPosition().y)*(pos.y - p.sprite.getPosition().y));
				entities.push_back(new Bullet(BulletImage, trees, p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, 0, 40, 53, 10, "Bullet1", pos.x, pos.y, distance));
				shoot.play();
				p.IsShoot = false;
			}
			
			if(p.isDamaged){
				damage.play();
				p.isDamaged = false;
			}
			
            if (event.type == Event::Closed)
                window.close();
        }
        
        	for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false)	{ it = entities.erase(it); delete b; }
			else it++;
		}
        if(bow.coolDownTimer < bow.coolDown) bow.coolDownTimer += time;
        if(p.staminaTimer < 20000) p.staminaTimer += time;
        
       	movement(p.dir, p.speed, CurrentFrame, p.staminaTimer, time, p.life, p.sprite, p.IsShoot, bow.coolDownTimer, bow.coolDown, p.stunTimer, p.stunTime, p.itemChosen, bow.isTaken, p.isDamaged);
	
		
		inv.update(p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, viewX, viewY, hoodScale);
		stmbar.update(p.staminaTimer, p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, viewX, viewY, hoodScale);
		hpbar.update(p.sprite.getPosition().x+p.w/2, p.sprite.getPosition().y+p.h/2, viewX, viewY, p.health, hoodScale, CurrentFrame);
		
		p.checkCollisionWithMap(p.dx,p.dy);
		p.update(time);
		
		if(!p.IsShoot && bow.coolDownTimer < bow.coolDown) bow.update(time, p.x, p.y, pos.x, pos.y, 55, 0, 15, 46, "Bow", p.itemChosen, inv.itemName);
		else bow.update(time, p.x, p.y, pos.x, pos.y, 0, 0, 40, 46, "Bow", p.itemChosen, inv.itemName);
		
		window.setView(view);
		
		window.clear();

		ground.Draw(window);
		for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite); 
		}
		window.draw(p.sprite);
		
		if(p.life && bow.isTaken) window.draw(bow.sprite);
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

