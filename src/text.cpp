 /*!
 *  \file File text.cpp
 *  \brief Implementation of the class Text
 *
 *  Auxiliary documentation
 *  \sa text.hpp
 */
#include <text.hpp>
#include <camera.hpp>
#include <game.hpp>
#include <resources.hpp>
#include <assert.h>

/*!
	@class Text
	@brief This class provides the all the text and text box related methods

*/


//! A constructor.
    /*!
    *	This is a constructor method of Text
		*	\param txt
		*	\brief A address to string, that represents the text message
		*	\param fSize
		*	\brief A positive integer, that represents the size of the text font
		*	\param c
		*	\brief A SDL_Color, that represents the text color
		*	\param st
		*	\brief A Style, that represents the style of the text
		*	\param file
		*	\brief A string, that represents the name of the the text font
		*	\param x
		*	\brief A positive integer, that represents the width of the text box
		*	\param y
		*	\brief A positive integer, that represents the height of the text box
    */
Text::Text(const string& txt, int fSize, SDL_Color c, Style st,
						string file, int x, int y) : font_name{file} {
	LOG_METHOD_START("Text::Text");
	LOG_VARIABLE("txt",txt);
	LOG_VARIABLE("fSize",fSize);
	assert(c.r >= 0);
	assert(c.r < 255);
	LOG_VARIABLE("c.r",c.r);
	assert(c.g >= 0);
	assert(c.g < 255);
	LOG_VARIABLE("c.g",c.g);
	assert(c.b >= 0);
	assert(c.b < 255);
	LOG_VARIABLE("c.b",c.b);
	assert(c.a >= 0);
	assert(c.a < 255);
	LOG_VARIABLE("c.a",c.a);
	LOG_VARIABLE("file",file);
	assert(x >= 0);
	LOG_VARIABLE("x",x);
	assert(y >= 0);
	LOG_VARIABLE("y",y);
	set_color(c);
	set_text(txt);
	set_style(st);
	set_font_size(fSize);
	box.x = x;
	box.y = y;
	LOG_METHOD_CLOSE("Text::Text","constructor");
}

//! A destructor.
    /*!
      This is a destructor method of Text class
    */

Text::~Text() {
	//! Iterates through all the line_array lines
	for (auto& line : line_array) {
		//! Checks if that line has texture
		if (line.texture){
			//! Destroies the line texture
			SDL_DestroyTexture(line.texture);
		}
		else{
			//do nothing
		}
	}
	LOG_METHOD_CLOSE("Text::~Text","destructor");
}


void Text::render_line_texture (Rect* clipRect, TextLine line,Vec2 clipRectEnd,
													Vec2 lineBoxEnd, int position_x, int position_y){
	SDL_Rect clip;
	SDL_Rect dest;

	if (clipRect->x > line.box.x) {
		clip.x = clipRect->x - line.box.x;
		dest.x = position_x + clipRect->x;
	}
	else {
		clip.x = 0;
		dest.x = position_x + line.box.x;
	}
	if (clipRect->y > line.box.y) {
		clip.y = clipRect->y - line.box.y;
		dest.y = position_y + clipRect->y;
	}
	else {
		clip.y = 0;
		dest.y = position_y + line.box.y;
	}
	if (clipRectEnd.x < lineBoxEnd.x) {
		clip.w = dest.w = clipRectEnd.x - line.box.x - clip.x +1;
	}
	else {
		clip.w = dest.w = lineBoxEnd.x - line.box.x - clip.x +1;
	}
	if (clipRectEnd.y < lineBoxEnd.y) {
		clip.h = dest.h = clipRectEnd.y - line.box.y - clip.y +1;
	}
	else {
		clip.h = dest.h = lineBoxEnd.y - line.box.y - clip.y +1;
	}

	SDL_RenderCopy(GAMERENDER,line.texture,&clip,&dest);
}

/*!
	@fn void Text::Render(Vec2 camera, Rect* clipRect)
	@brief Method that renders the text box and the text
	@param camera
	@brief A Vec2, that represents the camera positions
	@param clipRect
	@brief A pointer Rect, that represents rectangle of the text box
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void Text::render(Vec2 camera, Rect* clipRect) {
	LOG_METHOD_START("Text::render");
	assert(camera.x >= 0);
	assert(camera.y >= 0);
	LOG_VARIABLE("camera.x",camera.x);
	LOG_VARIABLE("camera.y",camera.y);

	//! @var pos
	//!< A Vec2 that representes the position of the text box hotspot
	Vec2 pos = box.hotspot(hotspot);
	assert(pos.x >= 0);
	assert(pos.y >= 0);

	//! @var x
	//!< A positive integer that represents the beginning of the text box
	//! rectangle in the axis x
	int position_x = pos.x - (camera.x * CAMERAZOOM);
	//! @var y
	//!< A positive integer that represents the beginning of the text box
	//! rectangle in the axis y
	int position_y = pos.y - (camera.y * CAMERAZOOM);

	//! Checks if the text box rectangle exist
	if (clipRect) {
		//! @var
		//!< A Vec2, that represents the end position of the text box rectangle
		Vec2 clipRectEnd(clipRect->x + clipRect->w - 1,
			clipRect->y + clipRect->h - 1);

		//! Iterates through all the line_array lines
		for (auto& line : line_array) {
			//! Checks if the text box rectangle end position in the axis y is lower
			//! that teh box position in the axis y
			if (clipRectEnd.y >= line.box.y) {
				//! @var lineBoxEnd
				//!< A Vec2 that recivies the end positions in the line
				Vec2 lineBoxEnd(line.box.x2()-1, line.box.y2()-1);

				//! Checks if the end position of the line is lower that the text box
				//! rectangle end position in the axis
				if (lineBoxEnd.y >= clipRect->y) {
					render_line_texture(clipRect, line, clipRectEnd, lineBoxEnd,
						position_x,position_y);
				}
				else{
					continue;
				}
			}
			else{
				break;
			}
		}
	}
	else {
		for (auto& line : line_array) {
			SDL_Rect dest;
			dest.x=position_x+line.box.x;
			dest.y=position_y+line.box.y;
			dest.w=line.box.w;
			dest.h=line.box.h;
			SDL_RenderCopy(GAMERENDER,line.texture,nullptr,&dest);
		}
	}
	LOG_METHOD_CLOSE("Text::render","void");
}

/*!
	@fn void Text::remake_texture()
	@brief Method that remakes the texture of the text box
	@return The execution of this method returns no value
*/
void Text::remake_texture() {
	LOG_METHOD_START("Text::remake_texture");
	//! Checks if the font was initialized
	if (font.get()) {
		//! @var surface
		//!< A pointer to SDL_Surface, that represents a surface
		SDL_Surface *surface = nullptr;
		box.w = box.h = 0;
		//! Iterates through all lines of the line_array
		for (auto& line : line_array) {
			//! Checks if the line has texture
			if (line.texture){
				//! Destroies the line texture
				SDL_DestroyTexture(line.texture);
			}
			else{
				// do nothing
			}
			surface = remake_surface(surface,&line);
		}
		SDL_FreeSurface(surface);

		//! Checks if the alignment is CENTERED
		if (alignment == Align::CENTERED) {
			//! Iterates through the line_array
			for (auto& line : line_array){
				//! Applies the alignment is CENTERED
				line.box.x=(box.w-line.box.w)/2;
			}

		}
		//! Checks if the alignment is RIGHT
		else if (alignment == Align::RIGHT) {
			//! Iterates through the line_array
			for (auto& line : line_array){
				//! Applies the alignment is RIGHT
				line.box.x=(box.w-line.box.w);
			}

		}
		else{
			// do nothing
		}
	}
	else{
		// do nothing
	}
	LOG_METHOD_CLOSE("Text::remake_texture","void");
}

/*!
	@fn void Text::SetPos(int x,int y)
	@brief A setter for the text box position
  @param x
  @brief A positive integer, that represents the new text box positon in the
	axis x
	@param y
  @brief A positive integer, that represents the new text box positon in the
	axis y

  @return The execution of this method returns no value
*/
void Text::set_box_position(int x,int y) {
	LOG_METHOD_START("Text::set_box_position");
	assert(x >= 0);
	LOG_VARIABLE("x",x);
	assert(y >=	 0);
	LOG_VARIABLE("y",y);
	box.x = x;
	box.y = y;
	LOG_METHOD_CLOSE("Text::set_box_position","void");
}

/*!
	@fn void Text::SetPos(Vec2 v)
	@brief A setter for the text box position
  @param v
  @brief A Vec2, that represents the new text box position
  @return The execution of this method returns no value
*/
void Text::set_box_position(Vec2 v) {
	LOG_METHOD_START("Text::set_box_position");
	assert(v.x >= 0);
	assert(v.y >= 0);
	LOG_VARIABLE("v.x",v.x);
	LOG_VARIABLE("v.y",v.y);
	set_box_position(v.x, v.y);
	LOG_METHOD_CLOSE("Text::set_box_position","void");
}

/*!
	@fn void Text::SetText(string txt)
	@brief A setter for attribute text
  @param txt
  @brief A string, that represents the new text of the text box
  @return The execution of this method returns no value
*/
void Text::set_text(string txt) {
	LOG_METHOD_START("Text::set_text");
	LOG_VARIABLE("txt",txt);
	//! Checks if the txt is empty
	if (txt == ""){
		//! Attributes a white space to txt
		txt = " ";
	}
	else{
		// do nothing
	}
	//! @var text
	stringstream text(txt); //!< A stringstream that recivies the txt
	line_array.clear();
	//! Iterates through all lines in text
	for (TextLine line;getline(text, line.text);) {
		//! Checks if the text in the line is empty
		if (line.text=="") {
			//! Attributes a white space to the line text
			line.text = " ";
		}
		else{
			// do nothing
		}
		line_array.push_back(line);
	}

	remake_texture();
	LOG_METHOD_CLOSE("Text::set_text","void");
}


/*!
	@fn void Text::SetLine(int line, string txt)
	@brief A setter for a line in the text
	@param line
	@brief A positive integer, that represents the the number of the line that
	will be replaced
  @param txt
  @brief A string, that represents the new line text
  @return The execution of this method returns no value
*/
void Text::set_line(int line, string txt) {
	LOG_METHOD_START("Text::set_line");
	LOG_VARIABLE("line",line);
	LOG_VARIABLE("txt",txt);
	//! Checks if the line number exists in the array of lines
	if (line >= 0 and line < (int)line_array.size()) {
		//! Replaces the line text for the new line text
		line_array[line].text = txt;

		remake_texture();
	}
	else{
		// do nothing
	}
	LOG_METHOD_CLOSE("Text::set_line","void");
}

void Text::set_alignment(Align al){
	alignment = al;
	remake_texture();
}

/*!
	@fn void Text::SetColor(SDL_Color c))
	@brief A setter for the text color
	@param c
	@brief A SDL_Color, that represents the new color
  @return The execution of this method returns no value
*/
void Text::set_color(SDL_Color c) {
	LOG_METHOD_START("Text::set_color");
	assert(c.r >= 0);
	assert(c.g >= 0);
	assert(c.b >= 0);
	assert(c.a >= 0);
	LOG_VARIABLE("c.r",c.r);
	LOG_VARIABLE("c.g",c.g);
	LOG_VARIABLE("c.b",c.b);
	LOG_VARIABLE("c.a",c.a);
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
	color.a = c.a;
	remake_texture();
	LOG_METHOD_CLOSE("Text::set_color","void");
}

/*!
	@fn void Text::SetStyle(Style st)
	@brief A setter for the text style
	@param st
	@brief A Style, that represents the new style
  @return The execution of this method returns no value
*/
void Text::set_style(Style st) {
	LOG_METHOD_START("Text::SetStyle");
	style = st;
	remake_texture();
	LOG_METHOD_CLOSE("Text::set_style","void");
}


/*!
	@fn void Text::SetFontSize(int fSize)
	@brief A setter for the size of the text font
	@param fSize
	@brief A positive integer, that represents the new font size
  @return The execution of this method returns no value
*/
void Text::set_font_size(int fSize) {
	LOG_METHOD_START("Text::SetFontSize");
	LOG_VARIABLE("fSize",fSize);
	font_size = fSize;
	font = Resources::game_get_font(font_name,font_size);

	remake_texture();
	LOG_METHOD_CLOSE("Text::set_font_size","void");
}


/*!
	@fn void Text::SetHotspot(Hotspot h)
	@brief A setter for the text box hotspot
	@param h
	@brief A Hotspot, that represents the new box hotspot
  @return The execution of this method returns no value
*/
void Text::set_hotspot(Hotspot h) {
	LOG_METHOD_START("Text::set_hotspot");
	LOG_VARIABLE("h",h);
	hotspot = h;
	LOG_METHOD_CLOSE("Text::set_hotspot","void");
}

/*!
	@fn Rect Text::GetBox()const
	@brief A getter of the attribute box
	@return A Rect, that represents the text box
*/
Rect Text::get_box()const {
	LOG_METHOD_START("Text::get_box");
	LOG_METHOD_CLOSE("Text::get_box",box);
	return box;
}

SDL_Surface* Text::define_surface(SDL_Surface *surface,TextLine* line){
	//! Checks if the style is SOLID
	if (style == Style::SOLID){
		//! Applies the style is SOLID
		surface = TTF_RenderText_Solid(font.get(), line->text.c_str(), color);
	}
	//! Checks if the style is SHADED
	else if (style==Style::SHADED){
		//! Applies the style is SHADED
		surface = TTF_RenderText_Shaded(font.get(), line->text.c_str(),
																			color,SDL_COLOR_BLACK);
	}
	//! Checks if the style is BLENDED
	else if (style == Style::BLENDED){
		//! Applies the style is BLENDED
		surface = TTF_RenderText_Blended(font.get(), line->text.c_str(), color);
	}
	else{
		// do nothing
	}

	return surface;
}

SDL_Surface* Text::remake_surface(SDL_Surface *surface,TextLine* line){
	surface = define_surface(surface,line);

	line->texture = SDL_CreateTextureFromSurface(GAMERENDER, surface);

	//! Resize the text box
	line->box.w = surface->w;
	line->box.h = surface->h;
	//!Checks if the width of the line is bigger than the box width
	if (line->box.w > box.w){
		box.w = line->box.w;
	}
	else{
		// do nothing
	}
	line->box.y = box.h;
	box.h += line->box.h;

	return surface;
}

Text::TextLine::TextLine() {}
