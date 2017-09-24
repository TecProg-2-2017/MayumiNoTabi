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
		*	\param w
		*	\brief A positive integer, that represents width of a tile
		*	\param h
		*	\brief A positive integer, that represents height of a tile
		*	\param file
		*	\brief A string, that represents path of the file with the tile set
    */
TileSet::TileSet(int w, int h, string file) {
	Load(w, h, file);
}

/*!
	@fn void TileSet::Load(int  w, int h, string file)
	@brief Method that loads the tile set from the file
	@param w
	@brief A positive integer, that represents width of a tile
	@param h
	@brief A positive integer, that represents height of a tile
	@param file
	@brief A string, that represents path of the file with the tile set
	@return The execution of this method returns no value
*/
void TileSet::Load(int  w, int h, string file) {
	//! Attributes the value of the width and height of a tile
	tileWidth = w;
	tileHeight = h;

	//! Opens the file with the tile set
	tileSet.Open(file);

	//! Defines the numbers of rows and columns of the tile set
	rows = tileSet.GetHeight() / tileHeight;
	columns = tileSet.GetWidth() / tileWidth;
}

/*!
	@fn void TileSet::Render(unsigned int index, float x, float y, float extScale)
	@brief Method that renders the tile set
	@param index
	@brief A unsigned integer
	@param x
	@brief A float
	@param y
	@brief A float
	@param extScale
	@brief A float
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void TileSet::Render(unsigned int index, float x, float y, float extScale) {
	//! Checks if the number of tiles is bigger that the index
	if ((int)index < (rows * columns)) {
		tileSet.SetClip(tileWidth * (index % columns),
										(tileHeight * (index / columns)), tileWidth, tileHeight);
		tileSet.Render(x, y, 0, extScale);
	}
	//! \warning else (do nothing)
}

/*!
	@fn int TileSet::GetWidth()
	@brief A getter of the attribute tileWidth
	@return A positive integer, that represents the width of a tile
*/
int TileSet::GetWidth() {
	return tileWidth;
}

/*!
	@fn int TileSet::GetHeight()
	@brief A getter of the attribute tileHeight
	@return A positive integer, that represents the height of a tile
*/
int TileSet::GetHeight() {
	return tileHeight;
}

/*!
	@fn int TileSet::GetTileCount()
	@brief Method that returns the number of tiles in the tile set
	@return A positive integer, that number of tiles in the tile set
*/
int TileSet::GetTileCount() {
	return rows*columns;
}
