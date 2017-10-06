#ifndef SPRITEHPP
#define SPRITEHPP

#include <common.hpp>

#include <geometry.hpp>

class Sprite{
	shared_ptr<SDL_Texture> texture;
	int width;
	int height;
	SDL_Rect clipRect;
	float scaleX=1.0f;
	float scaleY=1.0f;
	bool flipH=false;
	bool flipV=false;

	int frameCountX;
	int frameCountY=1;
	int frameCount;
	int currentFrame;
	float timeElapsed=0.0f;
	float frameTime;
public:
	bool looped=false;

	Sprite();
	Sprite(const string& file,int fCountX=1,float fTime=1.0f,int fCount=-1);
	Sprite(const string& file,int fCountX,int fCountY,float fTime=1.0f,int fCount=-1);
	~Sprite();

	void Open(const string& file,int fCountX=1,int fCountY=1,float fTime=1.0f,int fCount=-1);
	void SetClip(int x,int y,int w,int h);
	void render(float x,float y,float angle=0.0f, float extScale = 1.0f);
	void render(const Vec2& v, float angle=0.0f, float extScale = 1.0f);//extScale = External Scale. Example: camera zoom

	void update(float time);
	void set_frame(int frame);
	void SetFrameCount(int fCountX,int fCountY = 1,int fCount = -1);
	void SetFrameTime(float fTime);

	int GetWidth()const;
	int GetHeight()const;
	int get_current_frame()const;
	int get_frame_count()const;
	Vec2 get_frame_count(bool b)const;

	bool IsOpen()const;
	bool is_looped()const;

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
	
	void SetBlend(bool b);
};

#endif//SPRITEHPP
