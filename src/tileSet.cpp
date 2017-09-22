/*
 *  File: tileSet.cpp
 *
 *  Description:  Implements TileSet class
 */

#include <tileSet.hpp>

// No params constructor method for TileSet
TileSet::TileSet() {

}

// Constructor method for TileSet
// Recivies the integer w, that represents the width of a tile
// Recivies the integer h, that represents the height of a tile
// Recivies the string file, that represents file path
TileSet::TileSet(int w, int h, string file) {
	Load(w, h, file);
}

// Loads the tileset from the file
// Recivies the integer w, that represents the width of a tile
// Recivies the integer h, that represents the height of a tile
// Recivies the string file, that represents file path
void TileSet::Load(int  w, int h, string file) {
	// Attributes the value of the width and height of a tile
	tileWidth = w;
	tileHeight = h;

	// Opens the file with the tileSet
	tileSet.Open(file);

	// Defines the numbers of rows and columns of the tileSet
	rows = tileSet.GetHeight()/tileHeight;
	columns = tileSet.GetWidth()/tileWidth;
}

// Render the tileSet
void TileSet::Render(unsigned int index,float x,float y, float extScale) {
	if ((int)index<(rows*columns)) {
		tileSet.SetClip(tileWidth*(index%columns),(tileHeight*(index/columns)),
											tileWidth,tileHeight);
		tileSet.Render(x,y,0,extScale);
	}
	// TODO: else (do nothing)
}

// Returns the width of the TileSet
int TileSet::GetWidth() {
	return tileWidth;
}

// Returns the height of the TileSet
int TileSet::GetHeight() {
	return tileHeight;
}

// Returns the number of tiles in the tileSet
int TileSet::GetTileCount() {
	return rows*columns;
}
