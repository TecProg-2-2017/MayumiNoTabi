#include <sprite.hpp>

#include <common.hpp>

#include <camera.hpp>
#include <game.hpp>
#include <resources.hpp>

Sprite::Sprite():texture{nullptr}{

}

Sprite::Sprite(const string& file,int fCountX,int fCountY,float fTime,int fCount):texture{nullptr}{
	if (fCount==-1) { 
        fCount=fCountX*fCountY;
    }
    else {
        // Do nothing
    }

	Open(file,fCountX,fCountY,fTime,fCount);
}
Sprite::Sprite(const string& file,int fCountX,float fTime,int fCount):texture{nullptr}{
	if (fCount==-1) {
        fCount=fCountX;
    }
    else {
        // Do nothing
    }

	Open(file,fCountX,1,fTime,fCount);
}
Sprite::~Sprite() {

}

void Sprite::Open(const string& file,int fCountX,int fCountY,float fTime,int fCount) {
	if (fCount==-1) {
        fCount=fCountX*fCountY;
    }
    else {
        // Do nothing
    }

	texture = Resources::game_get_image(file);

	if (SDL_QueryTexture(texture.get(),nullptr,nullptr,&width,&height)) {
		cerr << "Erro ao carregar as dimensões da textura \"" << file << "\", o programa ira encerrar agora" << endl;
		exit(EXIT_FAILURE);
	}
    else {
        // Do nothing
    }

	SetFrameCount(fCountX,fCountY,fCount);
	SetFrameTime(fTime);
	set_frame(0);
}
void Sprite::SetClip(int x,int y,int w,int h) {
	clipRect.x=x;
	clipRect.y=y;
	clipRect.w=w;
	clipRect.h=h;
}

void Sprite::render(float x,float y,float angle, float extScale) {
	SDL_Rect dest = NULL;
	
	dest.x=(x);
	dest.y=(y);
	dest.w=ceil(clipRect.w * scaleX * extScale);
	dest.h=ceil(clipRect.h * scaleY * extScale);
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if (flipH && flipV) {
        angle += (angle<180?180:-180);
    }
	else if (flipH) {
        flip = SDL_FLIP_HORIZONTAL;
    }
	else if (flipV) {
        flip = SDL_FLIP_VERTICAL;
    }
	//cout << "rendering with size " << dest.w << "," << dest.h << " fCount = " << frameCount << endl;
	//SDL_RenderCopyEx(GAMERENDER,texture,nullptr,nullptr,angle,nullptr,SDL_FLIP_NONE);
	SDL_RenderCopyEx(GAMERENDER,texture.get(),&clipRect,&dest,angle,nullptr,flip);
}

void Sprite::render(const Vec2& v, float angle, float extScale) {
	render(v.x, v.y, angle, extScale);
}

void Sprite::update(float time) {
	if (get_frame_count()==1 || frameTime<0) {
        return;
    }
    else {
        // Do nothing
    }

	timeElapsed+=time;

	if (timeElapsed>frameTime) {
		timeElapsed-=frameTime;
		set_frame((currentFrame+1)%get_frame_count());
		looped = (currentFrame==0);
	}
    else {
        // Do nothing
    }
}
void Sprite::set_frame(int frame) {
	currentFrame = frame;
	SetClip((frame%frameCountX)*GetWidth(),(frame/frameCountX)*GetHeight(),GetWidth(),GetHeight());
}
void Sprite::SetFrameCount(int fCountX,int fCountY,int fCount) {
	if (fCount==-1) {
        fCount=fCountX*fCountY;
    }
    else {
        // Do nothing
    }

	frameCountX=fCountX;
	frameCountY=fCountY;
	frameCount=fCount;
}
void Sprite::SetFrameTime(float fTime) {
	frameTime=fTime;
}

int Sprite::GetWidth()const{
	return (width*scaleX)/frameCountX;
}

int Sprite::GetHeight()const{
	return (height*scaleY)/frameCountY;
}

int Sprite::get_current_frame()const{
	return currentFrame;
}

int Sprite::get_frame_count()const{
	return frameCount;
}

Vec2 Sprite::get_frame_count(bool b)const{
	UNUSED(b);
	return {(float)frameCountX,(float)frameCountY};
}

bool Sprite::IsOpen()const{
	return (texture!=nullptr);
}
bool Sprite::is_looped()const{
	return looped;
}

void Sprite::SetScale(float scale) {
	scaleX = scaleY = scale;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}

void Sprite::SetScaleToFit(float w, float h) {
	if (w > h) {
		scaleX = scaleY = (w/width);
    }
	else {
		scaleX = scaleY = (h/height); 
    }
}

void Sprite::SetScaleToFit(Vec2 v) {
	SetScaleToFit(v.x, v.y);
}

void Sprite::StretchToFit(float w, float h) {
	scaleX = w/width;
	scaleY = h/height;
}

void Sprite::StretchToFit(Vec2 v) {
	StretchToFit(v.x, v.y);
}

void Sprite::FlipH() {
	flipH = !flipH;
}

void Sprite::FlipV() {
	flipV = !flipV;
}

void Sprite::SetFlipH(bool f) {
	flipH = f;
}

void Sprite::SetFlipV(bool f) {
	flipV = f;
}

void Sprite::SetBlend(bool b) {
	if (b) {
        SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
    }
	else {
        SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_NONE);
    }
}
