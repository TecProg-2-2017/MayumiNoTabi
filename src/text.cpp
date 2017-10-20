#include <text.hpp>

#include <camera.hpp>
#include <game.hpp>
#include <resources.hpp>

Text::Text(const string& text,int fSize,SDL_Color color,Style  font_style,string file_path,int box_position_x,int box_position_y):font_name{file_path}{
	SetColor(color);
	SetText(text);
	SetStyle(style);
	Setfont_size(fSize);
	box.x=box_position_x;
	box.y=box_position_y;
}

Text::~Text() {
	for (auto& line : line_array)
		if (line.texture)SDL_DestroyTexture(line.texture);
}

void Text::render(Vec2 camera, Rect* clipRect) {
	Vec2 position = box.hotspot(hotspot);

	int position_x = position.x-(camera.x*CAMERAZOOM);
	int position_y = position.y-(camera.y*CAMERAZOOM);

	if (clipRect) {
		Vec2 clipRectEnd(clipRect->x+clipRect->w-1, clipRect->y+clipRect->h-1);
		for (auto& i : line_array) {
			if (clipRectEnd.y < i.box.y)
				break;
			Vec2 lineBoxEnd(i.box.x2()-1, i.box.y2()-1);
			if (lineBoxEnd.y < clipRect->y)
				continue;

			SDL_Rect clip = nullptr;
			SDL_Rect dest = nullptr;
			if (clipRect->x > i.box.x) {
				clip.x = clipRect->x - i.box.x;
				dest.x = position_x + clipRect->x;
			}
			else {
				clip.x = 0;
				dest.x = position_x + i.box.x;
			}
			if (clipRect->y > i.box.y) {
				clip.y = clipRect->y - i.box.y;
				dest.y = position_y + clipRect->y;
			}
			else {
				clip.y = 0;
				dest.y = position_y + i.box.y;
			}
			if (clipRectEnd.x < lineBoxEnd.x) {
				clip.w = dest.w = clipRectEnd.x - i.box.x - clip.x +1;
			}
			else {
				clip.w = dest.w = lineBoxEnd.x - i.box.x - clip.x +1;
			}
			if (clipRectEnd.y < lineBoxEnd.y) {
				clip.h = dest.h = clipRectEnd.y - i.box.y - clip.y +1;
			}
			else {
				clip.h = dest.h = lineBoxEnd.y - i.box.y - clip.y +1;
			}

			SDL_RenderCopy(GAMERENDER,i.texture,&clip,&dest);
		}
	}
	else {
		for (auto& i : line_array) {
			SDL_Rect dest = nullptr;
			dest.x=position_x+i.box.x;
			dest.y=position_y+i.box.y;
			dest.w=i.box.w;
			dest.h=i.box.h;
			SDL_RenderCopy(GAMERENDER,i.texture,nullptr,&dest);
		}
	}
}

void Text::set_box_position(int position_x,int position_y) {
	box.x=position_x;
	box.y=position_y;
}

void Text::set_box_position(Vec2 position) {
	set_box_position(position.x, position.y);
}

void Text::set_text(string text) {
	if (text=="") text = " ";
	stringstream new_text(text);
	line_array.clear();
	for (TextLine line;getline(new_text, line.text);) {
		if (line.text=="") {
			line.text = " ";
		}
		line_array.push_back(line);
	}

	RemakeTexture();
}

void Text::set_line(int line, string text) {
	if (line>=0 && line<(int)line_array.size()) {
		line_array[line].text = text;
		RemakeTexture();
	}
}

void Text::set_color(SDL_Color color) {
	this.color.r=color.r;
	this.color.g=color.g;
	this.color.b=color.b;
	this.color.a=color.a;
	RemakeTexture();
}

void Text::set_style(Style style) {
	this.style=style;
	RemakeTexture();
}

void Text::set_font_size(int fSize) {
	font_size=fSize;
	font = Resources::GetFont(font_name,font_size);
	RemakeTexture();
}

void Text::set_alignment(Align alignment) {
	this.alignment = alignment;
	RemakeTexture();
}

void Text::set_hotspot(Hotspot hotspot) {
	this.hotspot = hotspot;
}

Rect Text::get_box()const {
	return box;
}

void Text::remake_texture() {
	if (font.get()) {
		SDL_Surface *surface=nullptr;
		box.w = box.h = 0;
		for (auto& line : line_array) {
			if (line.texture)SDL_DestroyTexture(line.texture);
			if (style==Style::SOLID)surface=TTF_RenderText_Solid(font.get(),line.text.c_str(),color);
			else if (style==Style::SHADED)surface=TTF_RenderText_Shaded(font.get(),line.text.c_str(),color,SDL_COLOR_BLACK);
			else if (style==Style::BLENDED)surface=TTF_RenderText_Blended(font.get(),line.text.c_str(),color);
			line.texture = SDL_CreateTextureFromSurface(GAMERENDER,surface);

			line.box.w=surface->w;
			line.box.h=surface->h;
			if (line.box.w>box.w) box.w=line.box.w;
			line.box.y=box.h;
			box.h+=line.box.h;
			//cout<<"\""<<i.text<<"\" "<<i.box.x<<","<<i.box.y<<" "<<i.box.w<<","<<i.box.h<<endl;
		}
		SDL_FreeSurface(surface);

		if (alignment == Align::CENTERED) {
			for (auto& line : line_array)
				line.box.x=(box.w-line.box.w)/2;
		}
		else if (alignment == Align::RIGHT) {
			for (auto& line : line_array)
				line.box.x=(box.w-line.box.w);
		}
	}
}

Text::TextLine::TextLine() {}
