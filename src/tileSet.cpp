/*!
*  \file File tileSet.cpp
*  \brief Implementation of the class TileSet
*
*  Auxiliary documentation
*  \sa tileSet.hpp
*/
#include <tileSet.hpp>
#include <assert.h>


/*!
	@class TileSet
	@brief This class provides the tile sets to the game
*/

//! A constructor.
/*!
*	This is a constructor method of TileSet class
*	\param width
*	\brief A positive integer, that represents width of a tile
*	\param height
*	\brief A positive integer, that represents height of a tile
*	\param file_path
*	\brief A string, that represents path of the file with the tile set
*/
TileSet::TileSet(int width, int height, string file_path) {
	LOG_METHOD_START("TileSet::TileSet");
	assert(width > 0);
	LOG_VARIABLE("width",width);
	assert(height > 0);
	LOG_VARIABLE("height",height);
	assert(file_path != "");
	LOG_VARIABLE("file_path",file_path);
	load(width, height, file_path);
	LOG_METHOD_CLOSE("TileSet::TileSet","constructor");
}

//! A constructor.
    /*!
    This is a empty constructor method of TileSet class
    */
TileSet::TileSet() {
	LOG_METHOD_START("TileSet::TileSet");
	LOG_METHOD_CLOSE("TileSet::TileSet","constructor");
}

/*!
	@fn void TileSet::render(unsigned int index,float position_x,float position_y, float extended_scale)
	@brief Method that renders the tile set
	@param index
	@brief A unsigned integer
	@param position_x
	@brief A float
	@param position_y
	@brief A float
	@param extended_scale
	@brief A float
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void TileSet::render(unsigned int index, float position_x, float position_y,
											float extended_scale) {
	LOG_METHOD_START("TileSet::render");
	LOG_VARIABLE("index",index);
	LOG_VARIABLE("position_x",position_x);
	LOG_VARIABLE("position_y",position_y);
	LOG_VARIABLE("extended_scale",extended_scale);
	//! Checks if the number of tiles is bigger that the index
	if ((int)index < (rows * columns)) {
		//! var sprite_start_x
		//!< A positive integer that represents the start of the sprite in x
		int setclip_start_x = tile_width * (index % columns);
		//! var sprite_start_y
		//!< A positive integer that represents the start of the sprite in y
		int setclip_start_y = tile_height*(index/columns);
		tileSet.SetClip(setclip_start_x, setclip_start_y,tile_width, tile_height);
		tileSet.render(position_x, position_y, 0, extended_scale);
	}
	else{
		// do nothing
	}
	LOG_METHOD_CLOSE("TileSet::render","void");
}

/*!
	@fn void TileSet::load(int  width, int height, string file_path)
	@brief Method that loads the tile set from the file
	@param width
	@brief A positive integer, that represents width of a tile
	@param height
	@brief A positive integer, that represents height of a tile
	@param file_path
	@brief A string, that represents path of the file with the tile set
	@return The execution of this method returns no value
*/
void TileSet::load(int  width, int height, string file_path) {
	LOG_METHOD_START("TileSet::load");
	assert(width > 0);
	LOG_VARIABLE("width",width);
	assert(height > 0);
	LOG_VARIABLE("height",height);
	LOG_VARIABLE("file_path",file_path);
  //! Attributes the value of the width and height of a tile
	tile_width = width;
	tile_height = height;

	//! Opens the file with the tile set
  tileSet.Open(file_path);

  //! Defines the numbers of rows and columns of the tile set
  rows = tileSet.GetHeight() / tile_height;
	assert(rows >= 0);
	columns = tileSet.GetWidth() / tile_width;
	assert(columns >= 0);
	LOG_METHOD_CLOSE("TileSet::load","void");
}

/*!
	@fn int TileSet::get_width()
	@brief A getter of the attribute tileWidth
	@return A positive integer, that represents the width of a tile
*/
int TileSet::get_width() {
	LOG_METHOD_START("TileSet::get_width");
	LOG_METHOD_CLOSE("TileSet::get_width",tile_width);
	assert(tile_width >= 0);
	return tile_width;
}

/*!
	@fn int TileSet::get_height()
	@brief A getter of the attribute tileHeight
	@return A positive integer, that represents the height of a tile
*/
int TileSet::get_height() {
	LOG_METHOD_START("TileSet::get_height");
	LOG_METHOD_CLOSE("TileSet::get_height",tile_height);
	assert(tile_height >= 0);
	return tile_height;
}

/*!
	@fn int TileSet::get_tile_count()
	@brief Method that returns the number of tiles in the tile set
	@return A positive integer, that number of tiles in the tile set
*/
int TileSet::get_tile_count() {
	LOG_METHOD_START("TileSet::get_tile_count");
	LOG_METHOD_CLOSE("TileSet::get_tile_count",rows*columns);
	assert(rows * columns >= 0);
	return rows * columns;
}
