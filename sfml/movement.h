#include <SFML/Graphics.hpp>
void movement(int &dir, float &speed, float &CurrentFrame, float &staminaTimer, float &time, bool &life, Sprite &sprite)
{

if(life == true)
		{
		//walk
		if(Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))){ 
		dir = 1; speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 9) CurrentFrame -= 9;
		sprite.setTextureRect(IntRect(80+80*int(CurrentFrame),0,-80,80));

		}
		else if(Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))){ 
		dir = 0; speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 9) CurrentFrame -= 9;
		sprite.setTextureRect(IntRect(80*int(CurrentFrame),0,80,80));

		}
		else if(Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))){ 
		dir = 3; speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(80*int(CurrentFrame),400,80,80));

		}
		else if(Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))){ 
		dir = 2; speed = 0.15;
		CurrentFrame += 0.009*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),400,80,80));

		}
		else { sprite.setTextureRect(IntRect(640,400,80,80));

		}
        
		//run
		if(staminaTimer > 1000)
		if((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		dir = 1; speed = 0.25;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 9) CurrentFrame -= 9; 
		sprite.setTextureRect(IntRect(80+80*int(CurrentFrame),0,-80,80));

		}
		else if((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		dir = 0; speed = 0.25;
		CurrentFrame += 0.005*time;
		if(CurrentFrame > 9) CurrentFrame -= 9;
		sprite.setTextureRect(IntRect(80*int(CurrentFrame),0,80,80));
	
		}
		else if((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		dir = 3; speed = 0.25;
		CurrentFrame += 0.005*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(80*int(CurrentFrame),400,80,80));
	
		}
		else if((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) && Keyboard::isKeyPressed(Keyboard::LShift)){ 
		staminaTimer -= 3; 
		dir = 2; speed = 0.25;
		CurrentFrame += 0.005*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),400,80,80));

		}
		
		// dash
		
		if(staminaTimer > 7000){
		if((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		dir = 1; speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 5) CurrentFrame -= 5;
		sprite.setTextureRect(IntRect(560+80*int(CurrentFrame),480,-80,80));
	
		}
		else if((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		dir = 0; speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),480,80,80));
	
		}
		else if((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		dir = 3; speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(80*int(CurrentFrame),400,80,80));
	
		}
		else if((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) && Mouse::isButtonPressed(Mouse::Right)){ 
		staminaTimer -= 7; 
		dir = 2; speed = 0.5;
		CurrentFrame += 0.001*time;
		if(CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(480+80*int(CurrentFrame),400,80,80));
	
			}
		}
	}
		else {
			speed = 0;
			CurrentFrame += 0.009*time;
			if(CurrentFrame > 8) CurrentFrame = 7;
			sprite.setTextureRect(IntRect(80*int(CurrentFrame),640,80,80));
		}
}
