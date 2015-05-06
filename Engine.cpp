/**
 * 
 * Engine for 2D games
 * Modular engine for 2d games focused on component driven objects
 * 
 * To do: 
 * 	-Rendering (Renderer Component)
 * 	-Input Handler
 * 
 * Last Updated 5-6-15
 * 
 */
 
#include <math.h>

const int MAX_CHILDREN = 256;
const int MAX_COMPONENTS = 64;

class Vector;
class GameObject;
class Component;

/* 
 * 2D Vector class with x and y components and methods for addition
 * and vector multiplication 
 */
class Vector{
	public:
	float x;	//X value
	float y;	//Y value
	
	/* Returns the magnitude of the vector */
	float Magnitude(){
		return sqrtf((x * x) + (y * y));
	}
	/* Multiplies the vector by a given scalar */
	void Scale(float scalar){
		x *= scalar;
		y *= scalar;
	}
	/* Scales the vector to have length 1 */
	void Normalize(){
		Scale(1.0 / Magnitude());
	}
	/* Returns the direction in degrees that this vector is pointing in */
	float Angle(){
		return atanf(y / x);
	}
	
	/* Add 2 Vectors */
	static Vector Add(Vector a, Vector b){
		Vector result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		return result;
	}
	/* Subtract 2 Vectors */
	static Vector Subtract(Vector a, Vector b){
		Vector result;
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		return result;
	}
	/* Compute the Dot Product of 2 vectors */
	static float Dot(Vector a, Vector b){ return (a.x * b.x) + (a.y * b.y); }
	/* Compute the Z component of the cross product of 2 vectors */
	static float Cross(Vector a, Vector b){ return (a.x * b.y) - (b.x * a.y); }
};

/*
 * Component Class
 * Designed to be extended by anything that should be attatched to a GameObject
 */ 
class Component{
	public:
	bool enabled;	//Is this component enabled
	GameObject* parent;
	/* Called once when this component or the object it is attatched to is initialized */
	virtual void Start();
	/* Called once per frame */
	virtual void Update();
	/* Called when we need to redraw the screen */
	virtual void Draw();
};

/* 
 * GameObject Class
 * Holder for everything game objects need to know and do
 * Can have up to 256 (MAX_CHILDREN) child objects which will each be called by update
 * Can have up to 64 (MAX_COMPONENTS) component objects
 */
class GameObject{
	public:
	bool active; //Is this object currently enabled
	bool processChildren;	//Should the children of this object recieve update calls
	
	Vector position;
	float rotation;
	
	Component components[MAX_COMPONENTS];
	
	GameObject* parent;
	GameObject* children[MAX_CHILDREN];
	
	/* Calls Update Method in all components and calls update in children */
	void Update(){
		if(active){
			//Run Update on all components
			for(int i = 0; i < MAX_COMPONENTS; i++){
				if(components[i].enabled) components[i].Update();
			}
			if(processChildren){
				//Run Update on all children
				for(int i = 0; i < MAX_CHILDREN; i++){
					if(children[i]->active) children[i]->Update();
				}
			}
		}
	}
	
	/* Calls Draw Method in all components and tells all children to do the same */
	void Draw(){
		if(active){
			//Run Update on all components
			for(int i = 0; i < MAX_COMPONENTS; i++){
				if(components[i].enabled) components[i].Draw();
			}
			if(processChildren){
				//Run Update on all children
				for(int i = 0; i < MAX_CHILDREN; i++){
					if(children[i]->active) children[i]->Draw();
				}
			}
		}
	}
};

int main(int argc, char** argv){
	return 0;
}
