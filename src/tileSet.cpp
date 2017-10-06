/*!
*  \file File tileSet.cpp
*  \brief Implementation of the class TileSet
*
*  Auxiliary documentation
*  \sa tileSet.hpp
*/
#include <tileSet.hpp>

/*!
	@class TileSet
	@brief This class provides the tile sets to the game
*/

//! A constructor.
    /*!
    This is a empty constructor method of TileSet class
    */
TileSet::TileSet() {

}

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
	load(width, height, file_path);
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
  //! Attributes the value of the width and height of a tile
	tile_width = width;
	tile_height = height;
  
	//! Opens the file with the tile set
  tileSet.Open(file_path);
	
  //! Defines the numbers of rows and columns of the tile set
  rows = tileSet.GetHeight()/tile_height;
	columns = tileSet.GetWidth()/tile_width;
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
void TileSet::render(unsigned int index,float position_x,float position_y, float extended_scale) {
  //! Checks if the number of tiles is bigger that the index
	if ((int)index<(rows*columns)) {
		tileSet.SetClip(tile_width*(index%columns),(tile_height*(index/columns)),tile_width,tile_height);
		tileSet.render(position_x,position_y,0,extended_scale);
	}
	//! \warning else (do nothing)
}

/*!
	@fn int TileSet::get_width()
	@brief A getter of the attribute tileWidth
	@return A positive integer, that represents the width of a tile
*/
int TileSet::get_width() {
	return tile_width;
}

/*!
	@fn int TileSet::get_height()
	@brief A getter of the attribute tileHeight
	@return A positive integer, that represents the height of a tile
*/
int TileSet::get_height() {
	return tile_height;
}

/*!
	@fn int TileSet::get_tile_count()
	@brief Method that returns the number of tiles in the tile set
	@return A positive integer, that number of tiles in the tile set
*/
int TileSet::get_tile_count() {
	return rows*columns;
}
