#include<SFML/Graphics.hpp>
using namespace sf;
View view;
View Setplayercoordinateforview(float x, float y, int viewX, int viewY){
	float tempX;
	float tempY;
	if(x>viewX/2 && x<3200-viewX/2 && y>viewY/2 && y<3200-viewY/2) view.setCenter(x,y);
	
	else {
		if(x<viewX/2 && y<viewY/2){tempX = viewX/2; tempY = viewY/2; view.setCenter(tempX,tempY);}
		else if(x<viewX/2 && y>3200-viewY/2){tempX = viewX/2; tempY = 3200-viewY/2; view.setCenter(tempX,tempY);}
		else if(x>3200-viewX/2 && y<viewY/2){tempX = 3200-viewX/2; tempY = viewY/2; view.setCenter(tempX,tempY);}
		else if(x>3200-viewX/2 && y>3200-viewY/2){tempX = 3200-viewX/2; tempY = 3200-viewY/2; view.setCenter(tempX,tempY);}
		else if(x<viewX/2){tempX = viewX/2; view.setCenter(tempX,y);}
		else if(x>3200-viewX/2){tempX = 3200-viewX/2; view.setCenter(tempX,y);}
		else if(y<viewY/2){tempY = viewY/2; view.setCenter(x,tempY);}
		else if(y>3200-viewY/2){tempY = 3200-viewY/2; view.setCenter(x,tempY);}
	}
	
	return view;
}
