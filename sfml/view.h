#include<SFML/Graphics.hpp>
using namespace sf;
View view;
View getplayercoordinateforview(float x, float y){
	view.setCenter(x,y);
	return view;
}
