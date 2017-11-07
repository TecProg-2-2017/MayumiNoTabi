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
		string file, int x, int y) : fontName{file} {
	LOG_METHOD_START("Text::Text");
	assert(txt != NULL);
	LOG_VARIABLE("txt",txt);
	LOG_VARIABLE("fSize",fSize);
	assert(c != NULL);
	LOG_VARIABLE("c",c);
	LOG_VARIABLE("st",st);
	assert(file != NULL);
	LOG_VARIABLE("file",file);
	assert(x >= 0);
	LOG_VARIABLE("x",x);
	assert(y >= 0);
	LOG_VARIABLE("y",y);
	SetColor(c);
	SetText(txt);
	SetStyle(st);
	SetFontSize(fSize);
	box.x = x;
	box.y = y;
	LOG_METHOD_CLOSE("Text::Text","constructor");
}

//! A destructor.
    /*!
      This is a destructor method of Text class
    */

Text::~Text() {
	LOG_METHOD_START("Text::~Text");
	//! Iterates through all the lineArray lines
	for (auto& i : lineArray) {
		//! Checks if that line has texture
		if (i.texture){
			//! Destroies the line texture
			SDL_DestroyTexture(i.texture)
		}
	}
	LOG_METHOD_CLOSE("Text::~Text","destructor");
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
void Text::Render(Vec2 camera, Rect* clipRect) {
	LOG_METHOD_START("Text::Render");
	assert(camera != NULL);
	assert(camera.x >= 0);
	assert(camera.y >= 0);
	LOG_VARIABLE("camera",camera);
	assert(clipRect != NULL);
	LOG_VARIABLE("clipRect",clipRect);
	//! @var pos
	Vec2 pos = box.hotspot(hotspot); //!< A Vec2 that representes the position of the text box hotspot

	//! @var x
	int x = pos.x - (camera.x * CAMERAZOOM); //!< A positive integer that represents the beginning of the text box rectangle in the axis x
	//! @var y
	int y = pos.y - (camera.y * CAMERAZOOM); //!< A positive integer that represents the beginning of the text box rectangle in the axis y

	//! \warning modularize decision structure
	//! Checks if the text box rectangle exist
	if (clipRect) {
		//! @var
		Vec2 clipRectEnd(clipRect->x + clipRect->w - 1,
			clipRect->y + clipRect->h - 1); //!< A Vec2, that represents the end position of the text box rectangle

		//! Iterates through all the lineArray lines
		for (auto& i : lineArray) {
			//! Checks if the text box rectangle end position in the axis y is lower
			//! that teh box position in the axis y
			if (clipRectEnd.y < i.box.y) {
				break;
			}
			//! \warning else (do nothing)

			//! @var lineBoxEnd
			Vec2 lineBoxEnd(i.box.x2()-1, i.box.y2()-1); //!< A Vec2 that recivies the end positions in the line

			//! Checks if the end position of the line is lower that the text box rectangle end position in the axis
			//! \warning: Useless decision structure
			if (lineBoxEnd.y < clipRect->y) {
				continue;
			}

			//! \warning else (do nothing)

			SDL_Rect clip;
			SDL_Rect dest;
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
			SDL_Rect dest;
			dest.x=position_x+i.box.x;
			dest.y=position_y+i.box.y;
			dest.w=i.box.w;
			dest.h=i.box.h;
			SDL_RenderCopy(GAMERENDER,i.texture,nullptr,&dest);
		}
	}
	LOG_METHOD_CLOSE("Text::Render","void");
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
void Text::SetPos(int x,int y) {
	LOG_METHOD_START("Text::SetPos");
	assert(x > 0);
	LOG_VARIABLE("x",x);
	assert(y > 0);
	LOG_VARIABLE("y",y);
	box.x = x;
	box.y = y;
	LOG_METHOD_CLOSE("Text::SetPos","void");
}

/*!
	@fn void Text::SetPos(Vec2 v)
	@brief A setter for the text box position
  @param v
  @brief A Vec2, that represents the new text box position
  @return The execution of this method returns no value
*/
void Text::SetPos(Vec2 v) {
	LOG_METHOD_START("Text::SetPos");
	assert(v != NULL);
	assert(v.x >= 0);
	assert(v.y >= 0);
	LOG_VARIABLE("v",v);
	SetPos(v.x, v.y);
	LOG_METHOD_CLOSE("Text::SetPos","void");
}

/*!
	@fn void Text::SetText(string txt)
	@brief A setter for attribute text
  @param txt
  @brief A string, that represents the new text of the text box
  @return The execution of this method returns no value
*/
void Text::SetText(string txt) {
	LOG_METHOD_START("Text::SetText");
	assert(txt != NULL);
	LOG_VARIABLE("txt",txt);
	//! Checks if the txt is empty
	if (txt == ""){
		//! Attributes a white space to txt
		txt = " ";
	}
	//! @var text
	stringstream text(txt); //!< A stringstream that recivies the txt
	lineArray.clear();
	//! Iterates through all lines in text
	for (TextLine line;getline(text, line.text);) {
		//! Checks if the text in the line is empty
		if (line.text=="") {
			//! Attributes a white space to the line text
			line.text = " ";
		}
		line_array.push_back(line);
	}

	RemakeTexture();
	LOG_METHOD_CLOSE("Text::SetText","void");
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
void Text::SetLine(int line, string txt) {
	LOG_METHOD_START("Text::SetLine");
	LOG_VARIABLE("line",line);
	assert(txt != NULL);
	LOG_VARIABLE("txt",txt);
	//! Checks if the line number exists in the array of lines
	if (line >= 0 && line < (int)lineArray.size()) {
		//! Replaces the line text for the new line text
		lineArray[line].text = txt;

		RemakeTexture();
	}
	LOG_METHOD_CLOSE("Text::SetLine","void");
}

/*!
	@fn void Text::SetColor(SDL_Color c))
	@brief A setter for the text color
	@param c
	@brief A SDL_Color, that represents the new color
  @return The execution of this method returns no value
*/
void Text::SetColor(SDL_Color c) {
	LOG_METHOD_START("Text::SetColor");
	assert(c != NULL);
	LOG_VARIABLE("c",c);
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
	color.a = c.a;
	RemakeTexture();
	LOG_METHOD_CLOSE("Text::SetColor","void");
}

/*!
	@fn void Text::SetStyle(Style st)
	@brief A setter for the text style
	@param st
	@brief A Style, that represents the new style
  @return The execution of this method returns no value
*/
void Text::SetStyle(Style st) {
	LOG_METHOD_START("Text::SetStyle");
	LOG_VARIABLE("st",st);
	style = st;
	RemakeTexture();
	LOG_METHOD_CLOSE("Text::SetStyle","void");
}


/*!
	@fn void Text::SetFontSize(int fSize)
	@brief A setter for the size of the text font
	@param fSize
	@brief A positive integer, that represents the new font size
  @return The execution of this method returns no value
*/
void Text::SetFontSize(int fSize) {
	LOG_METHOD_START("Text::SetFontSize");
	LOG_VARIABLE("fSize",fSize);
	fontSize = fSize;
	font = Resources::GetFont(fontName,fontSize);

	RemakeTexture();
	LOG_METHOD_CLOSE("Text::SetFontSize","void");
}


/*!
	@fn void Text::SetHotspot(Hotspot h)
	@brief A setter for the text box hotspot
	@param h
	@brief A Hotspot, that represents the new box hotspot
  @return The execution of this method returns no value
*/
void Text::SetHotspot(Hotspot h) {
	LOG_METHOD_START("Text::SetHotspot");
	LOG_VARIABLE("h",h);
	hotspot = h;
	LOG_METHOD_CLOSE("Text::SetHotspot","void");
}

/*!
	@fn Rect Text::GetBox()const
	@brief A getter of the attribute box
	@return A Rect, that represents the text box
*/
Rect Text::GetBox()const {
	LOG_METHOD_START("Text::GetBox");
	LOG_METHOD_CLOSE("Text::GetBox",box);
	assert(box >= NULL);
	return box;
}

/*!
	@fn void Text::RemakeTexture()
	@brief Method that remakes the texture of the text box
	@return The execution of this method returns no value
*/
void Text::RemakeTexture() {
	LOG_METHOD_START("Text::RemakeTexture");
	//! Checks if the font was initialized
	if (font.get()) {
		//! @var surface
		SDL_Surface *surface = nullptr; //!< A pointer to SDL_Surface, that represents a surface
		box.w = box.h = 0;
		//! Iterates through all lines of the lineArray
		for (auto& i : lineArray) {
			//! Checks if the line has texture
			if (i.texture){
				//! Destroies the line texture
				SDL_DestroyTexture(i.texture);
			}
			//! Checks if the style is SOLID
			if (style == Style::SOLID){
				//! Applies the style is SOLID
				surface = TTF_RenderText_Solid(font.get(), i.text.c_str(), color);
			}
			//! Checks if the style is SHADED
			else if (style==Style::SHADED){
				//! Applies the style is SHADED
				surface = TTF_RenderText_Shaded(font.get(), i.text.c_str(),
																					color,SDL_COLOR_BLACK);
			}
			//! Checks if the style is BLENDED
			else if (style == Style::BLENDED){
				//! Applies the style is BLENDED
				surface = TTF_RenderText_Blended(font.get(), i.text.c_str(), color);
			}
			i.texture = SDL_CreateTextureFromSurface(GAMERENDER, surface);

			//! Resize the text box
			i.box.w = surface->w;
			i.box.h = surface->h;
			//!Checks if the width of the line is bigger than the box width
			if (i.box.w > box.w){
				box.w = i.box.w;
			}
			i.box.y = box.h;
			box.h += i.box.h;
		}
		SDL_FreeSurface(surface);

		//! Checks if the alignment is CENTERED
		if (alignment == Align::CENTERED) {
			//! Iterates through the lineArray
			for (auto& i : lineArray){
				//! Applies the alignment is CENTERED
				i.box.x=(box.w-i.box.w)/2;
			}

		}
		//! Checks if the alignment is RIGHT
		else if (alignment == Align::RIGHT) {
			//! Iterates through the lineArray
			for (auto& i : lineArray){
				//! Applies the alignment is RIGHT
				i.box.x=(box.w-i.box.w);
			}

		}
	}
	LOG_METHOD_CLOSE("Text::RemakeTexture","void");
}

Text::TextLine::TextLine() {}
