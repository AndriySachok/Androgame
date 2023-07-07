#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include"map.h"
#include"view.h"
#include"gui.h"
	const float hoodScale = 1;
	const int viewX = 1024;
    const int viewY = 768;
using namespace sf;

class Player{
private: float x, y;
public:
	float dx,dy,speed = 0;
	bool life;
	int dir, health, w, h; //направление
	String File; //Название текстурки спрайта
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, int X, int Y, int W, int H){ // Конструктор с параметрами игрока
		dir = 0; health = 5; life = true;
		File = F;
		w = W; h = H;
		image.loadFromFile("textures/"+File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y; // Координаты появления спрайта
		sprite.setTextureRect(IntRect(w,h,80,80));
		sprite.setOrigin(80/2, 80/2);
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
}

float getplayercoordinateX(){
	return x;
}
float getplayercoordinateY(){
	return y;
}
};

int main()
{

    RenderWindow window(VideoMode(viewX, viewY), "ANDROGAME(Strilyalki i puhtelki)");
    
    view.reset(FloatRect(0,0,viewX,viewY));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);

	Player p("man.png", 500, 400, 560, 640);
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
	float staminaTimer = 0;
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
        
        if(staminaTimer < 20000) staminaTimer += time;
    
        //stamina colours
       /* if(staminaTimer > 20100 ){p.sprite.setColor(Color::Black);}
		if(staminaTimer > 5000 && staminaTimer < 19000){p.sprite.setColor(Color::Blue);}
		if(staminaTimer > 0 && staminaTimer < 5000){p.sprite.setColor(Color::White);}*/
		
        /////////////////////////movement//////////////////////////////////
        
        if(p.life)
		{
		//walk
		if(Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))){ 
		p.dir = 1; p.speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 9) CurrentFrame -= 9;
		p.sprite.setTextureRect(IntRect(80+80*int(CurrentFrame),0,-80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if(Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))){ 
		p.dir = 0; p.speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 9) CurrentFrame -= 9;
		p.sprite.setTextureRect(IntRect(80*int(CurrentFrame),0,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if(Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))){ 
		p.dir = 3; p.speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(80*int(CurrentFrame),400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if(Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))){ 
		p.dir = 2; p.speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else { p.sprite.setTextureRect(IntRect(640,400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
        
		//run
		if(staminaTimer > 1000)
		if((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		p.dir = 1; p.speed = 0.25;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 9) CurrentFrame -= 9; 
		p.sprite.setTextureRect(IntRect(80+80*int(CurrentFrame),0,-80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		p.dir = 0; p.speed = 0.25;
		CurrentFrame += 0.005*time;
		if(CurrentFrame > 9) CurrentFrame -= 9;
		p.sprite.setTextureRect(IntRect(80*int(CurrentFrame),0,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		p.dir = 3; p.speed = 0.25;
		CurrentFrame += 0.005*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(80*int(CurrentFrame),400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		p.dir = 2; p.speed = 0.25;
		CurrentFrame += 0.005*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		
		// dash
		
		if(staminaTimer > 7000 || staminaTimer < 1000){
		if((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		p.dir = 1; p.speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 5) CurrentFrame -= 5;
		p.sprite.setTextureRect(IntRect(560+80*int(CurrentFrame),480,-80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		p.dir = 0; p.speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),480,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		p.dir = 3; p.speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(80*int(CurrentFrame),400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		p.dir = 2; p.speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		p.sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),400,80,80));
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			}
		}
	}
		else {
			p.speed = 0;
			CurrentFrame += 0.009*time;
			if(CurrentFrame > 8) CurrentFrame = 7;
			p.sprite.setTextureRect(IntRect(80*int(CurrentFrame),640,80,80));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		
		inv.update(p.sprite.getPosition().x, p.sprite.getPosition().y, viewY, hoodScale);
		stmbar.update(staminaTimer, p.sprite.getPosition().x, p.sprite.getPosition().y, viewX, viewY, hoodScale);
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

