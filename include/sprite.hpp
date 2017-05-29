#ifndef SPRITEHPP
#define SPRITEHPP

#include <common.hpp>

#include <geometry.hpp>

class Sprite{
	shared_ptr<SDL_Texture> texture;
	int width;
	int height;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;
	bool flipH;
	bool flipV;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
public:
	Sprite();
	Sprite(string file,int fCount=1,float fTime=1.0f);
	~Sprite();

	void Open(string file,int fCount=1,float fTime=1.0f);
	void SetClip(int x,int y,int w,int h);
	void Render(int x,int y,float angle=0.0f, float extScale = 1.0f);
	void Render(Vec2 v, float angle=0.0f, float extScale = 1.0f);//extScale = External Scale. Example: camera zoom

	void Update(float time);
	void SetFrame(int frame);
	void SetFrameCount(int fCount);
	void SetFrameTime(float fTime);

	int GetWidth();
	int GetHeight();

	bool IsOpen();

	void SetScale(float scale); //Set both scales
	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void SetScaleToFit(float w, float h);//Set both scales to fit within the dimensions without affecting the aspect ratio
	void SetScaleToFit(Vec2 v);
	void StretchToFit(float w, float h);//Set both scales to fit within the dimensions affecting the aspect ratio
	void StretchToFit(Vec2 v);
	
	void FlipH();
	void FlipV();
	void SetFlipH(bool f);
	void SetFlipV(bool f);
};

#endif//SPRITEHPP
