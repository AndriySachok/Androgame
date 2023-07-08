#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include"map.h"
#include"view.h"
#include"gui.h"
#include"movement.h"
	const float hoodScale = 1;
	const int viewX = 1024;
    const int viewY = 768;
using namespace sf;

class Entity{
	public:
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
			sprite.setOrigin(w/2,h/2);
		}
};

class Player :public Entity{
public:
	float staminaTimer;
	Player(Image &image, float X, float Y, int CoordX, int CoordY, int W, int H, String Name):Entity(image,X,Y,CoordX,CoordY,W,H,Name){ // Constructor of the player(CoordX and CoordY are to set the right texture rect)
		staminaTimer = 0; health = 5;
		if(name == "Player1"){
			sprite.setTextureRect(IntRect(coordX,coordY,w,h));
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
	if(life) Setplayercoordinateforview(sprite.getPosition().x, sprite.getPosition().y);
}

};

int main()
{
    RenderWindow window(VideoMode(viewX, viewY), "ANDROGAME(Strilyalki i puhtelki)");
    
    view.reset(FloatRect(0,0,viewX,viewY));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);
	
	Image heroImage;
	heroImage.loadFromFile("textures/man.png");
	
	Player p(heroImage, 500, 400, 560, 640, 80, 80, "Player1");
	Inventory inv;
	StaminaBar stmbar;
	HealthBar hpbar;
	
	Image map1_image;
	map1_image.loadFromFile("textures/tiles1_32x32.png");
	Texture map1_texture;
	map1_texture.loadFromImage(map1_image);
	Sprite map1_sprite;
	map1_sprite.setTexture(map1_texture);
	map1_sprite.setScale(3,3);


	Image background;
	background.loadFromFile("textures/dd8208640e636edec2d90d8b0c9a7fa9.png");
	Texture backtexture;
	backtexture.loadFromImage(background);
	Sprite backsprite;
	backsprite.setTexture(backtexture);
	backsprite.setScale(3,4);
	backsprite.setPosition(-700,-400);
	

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
    
        //stamina colours
       /* if(p.staminaTimer > 20000 ){p.sprite.setColor(Color::Black);}
		if(p.staminaTimer > 5000 && p.staminaTimer < 19000){p.sprite.setColor(Color::Blue);}
		if(p.staminaTimer > 0 && p.staminaTimer < 5000){p.sprite.setColor(Color::White);}*/
        
       movement(p.dir, p.speed, CurrentFrame, p.staminaTimer, time, p.life, p.sprite);
		
		inv.update(p.sprite.getPosition().x, p.sprite.getPosition().y, viewY, hoodScale);
		stmbar.update(p.staminaTimer, p.sprite.getPosition().x, p.sprite.getPosition().y, viewX, viewY, hoodScale);
		hpbar.update(p.sprite.getPosition().x, p.sprite.getPosition().y, viewX, viewY, p.health, hoodScale, CurrentFrame);
		p.update(time);
		window.setView(view);
		
		window.clear();
		window.draw(backsprite);
		
		for(int i = 0; i < HEIGHT_MAP; i++){
			for(int j = 0; j < WIDTH_MAP; j++){
				switch(TileMap[i][j]){
					case '0' : map1_sprite.setTextureRect(IntRect(512,512,32,32));	break;
					case ' ' : map1_sprite.setTextureRect(IntRect(608,288,32,32)); break;
					case 't' : map1_sprite.setTextureRect(IntRect(0,32,32,32)); break;
					case 'T' : map1_sprite.setTextureRect(IntRect(128,64,32,32)); break;
					case 's' : map1_sprite.setTextureRect(IntRect(544,352,32,32)); break;
					case 'S' : map1_sprite.setTextureRect(IntRect(704,256,32,32)); break;
					case '1' : map1_sprite.setTextureRect(IntRect(448,256,32,32)); break;
					case '2' : map1_sprite.setTextureRect(IntRect(352,320,32,32)); break;
					case '3' : map1_sprite.setTextureRect(IntRect(0,0,32,32)); break;
					case '4' : map1_sprite.setTextureRect(IntRect(288,320,32,32)); break;
					case '5' : map1_sprite.setTextureRect(IntRect(352,64,32,32)); break;
					case '6' : map1_sprite.setTextureRect(IntRect(384,320,32,32)); break;
					case '7' : map1_sprite.setTextureRect(IntRect(224,320,32,32)); break;
					case '8' : map1_sprite.setTextureRect(IntRect(256,320,32,32)); break;
					case '9' : map1_sprite.setTextureRect(IntRect(288,608,32,32)); break;
				}
				if(j*96>p.sprite.getPosition().x-viewX&&j*96<p.sprite.getPosition().x+viewX&&i*96<p.sprite.getPosition().y+viewY&&i*96>p.sprite.getPosition().y-viewY)
				map1_sprite.setPosition(j*96, i*96);
				
				window.draw(map1_sprite);
			}
		}
		if(p.life)
		{
			inv.draw(window);
			stmbar.draw(window);
			hpbar.draw(window,p.health);
		}
		
        window.draw(p.sprite);
        window.display();
    }

    return 0;
}

