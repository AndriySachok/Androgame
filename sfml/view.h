#include<SFML/Graphics.hpp>
using namespace sf;
View view;
View Setplayercoordinateforview(float x, float y){
	view.setCenter(x,y);
	return view;
}
