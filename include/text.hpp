#ifndef TEXTHPP
#define TEXTHPP

#include <common.hpp>

#include <geometry.hpp>

class Text{
public:
	enum Style{SOLID,SHADED,BLENDED};
	enum Align{LEFT, RIGHT, CENTERED};
private:
	class TextLine;

	vector<TextLine> line_array;
	shared_ptr<TTF_Font> font;
	string font_name;
	Style style;
	int font_size;
	SDL_Color color;
	Align alignment=Text::Align::LEFT;
	Hotspot hotspot=Hotspot::TOP_LEFT;
	Rect box;
	void remake_texture();

public:
	Text(const string& text,int fSize,SDL_Color color =SDL_COLOR_WHITE,Style style=Style::BLENDED,string file_path="font/arial.ttf",int box_position_x=0,int box_position_y=0);
	~Text();

	SDL_Surface* remake_surface(SDL_Surface *surface);
	SDL_Surface* define_surface(SDL_Surface *surface);
	void render_line_texture (Rect* clipRect, TextLine line,Vec2 clipRectEnd,
														Vec2 lineBoxEnd);
	void render(Vec2 camera = {0,0}, Rect* clipRect=nullptr);

	void set_box_position(int position_x,int position_y);
	void set_box_position(Vec2 position);

	void set_text(string txt);
	void set_line(int line, string text);

	void set_color(SDL_Color color);
	void set_style(Style style);
	void set_font_size(int fSize);
	void set_alignment(Align alignment);
	void set_hotspot(Hotspot hotspot=Hotspot::CENTER);

	Rect get_box() const;
};

class Text::TextLine {
public:
	SDL_Texture* texture=nullptr;
	string text;
	Rect box;

	TextLine();
};

#endif//TEXTHPP
