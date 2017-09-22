/*
 *  File: tileMap.cpp
 *
 *  Description:  Implements TileMap class
 */

#include <tileMap.hpp>
#include <camera.hpp>
#include <componentCollider.hpp>
#include <componentStaticRender.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <tileSet.hpp>

// Constructor method for TileSet
// Recivies a integer width, a integer height, a pointer to TileSet  ts
TileMap::TileMap(int width, // Represents the width of the tileMap
                  int height, // Represents the height of the tileMap
                   TileSet* ts // Represents the the tileSet)
 			: tileSet{ts}, mapWidth{width}, mapHeight{height}, mapDepth{1} {
	tileMatrix.reserve(mapWidth*mapHeight)
	// Iterates through tileMatrix height of tileMap
	for(h, mapHeight) {

    // Iterates through tileMatrix width of tileMap
		for(w, mapWidth) {
      // Empties the first layer of the tileMatrix
			At(w, h, 0) = EMPTY_TILE;
		}
	}
}

// Constructor method for TileMap
// Recieves a pointer to TileSet ts, that represents the tileSet
TileMap::TileMap(TileSet* ts) : tileSet{ts} {

}

// Loads the tileMatrix
// Recieves the param in that provides the tileMatrix informations and elements
void TileMap::Load(ifstream& in) {
	string line;

	// Reads a line of in and defines the mapWidth, mapHeight and mapDepth
	getline(in,line);
	sscanf(line.c_str(), " %d,%d,%d", &mapWidth, &mapHeight, &mapDepth);

	// Clears the tileMatrix and reserves the size matching the nuber of elements
	// of the tileMatrix
	tileMatrix.clear();
	tileMatrix.reserve(mapWidth*mapHeight*mapDepth);

	int t;
  //Iterates through the tileMatrix depth
	FOR(d, mapDepth) {

    //Iterates through the tileMatrix height
		FOR(h, mapHeight) {

      //Iterates through the tileMatrix width
			FOR(w, mapWidth) {
        // Loads each position from in and saves on tileMatrix
				in >> t;
				in.ignore(1);
				At(w, h, d) = t-1;
			}
		}
	}
}

// Savess the tileMatrix
// The param in that recives the tileMatrix informations and elements
void TileMap::Save(stringstream& out) {
	// Saves the width, height and depth of the tileMatrix on out
	out << mapWidth << "," << mapHeight << "," << mapDepth << endl << endl;

	// Saves each position of the tileMatrix in the out
	FOR(d, mapDepth) {
		FOR(h, mapHeight) {
			FOR(w, mapWidth) {
				out << At(w, h, d) + 1 << ",\t";
			}
			out << endl;
		}
		out << endl;
	}
}

// Sets the tileSet
void TileMap::SetTileSet(TileSet* ts) {
	tileSet = ts;
}

// Returns the corresponding position of the tileMatrix as a integer address
int& TileMap::At(int x,int y,int z) {
	return tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

// Returns the corresponding position of the tileMatrix as a integer
int TileMap::At(int x, int y, int z) const {
	return tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

// Reder a layer of TileMap
void TileMap::RenderLayer(int layer, int posX , int posY) {
	int w = tileSet->GetWidth();
	int h = tileSet->GetHeight();
	int tile;
	// TODO: separate variable declarations
	int firstX = 0,firstY = 0,lastX = mapWidth,lastY = mapHeight;

	if (posX < CAMERA.x){
		firstX = (CAMERA.x - posX) / w;
	}
	// TODO: else (do nothing)

	if (posY < CAMERA.y){
		firstY = (CAMERA.y - posY) / h;
	}
  // TODO: else (do nothing)

  // Defines the map coners
	Vec2 mapCorner = Vec2(posX + (mapWidth * w),posY + (mapHeight * h));
	Vec2 cameraCorner = CAMERA + (WINSIZE / CAMERAZOOM);

  if (mapCorner.x > cameraCorner.x){
		lastX -= (mapCorner.x - cameraCorner.x) / w;
	}
  // TODO: else (do nothing)

  if (mapCorner.y > cameraCorner.y){
		lastY -= (mapCorner.y - cameraCorner.y) / h;
	}
  // TODO: else (do nothing)

  // Iterates the height of the layer
	for (int y=firstY;y<=lastY;y++) {

    // Iterates the width of the layer
		for (int x=firstX;x<=lastX;x++) {
			tile = At(x, y, layer);

      // Checks if the tile is empty
			if (tile != EMPTY_TILE){
        // Render the layer
				tileSet->Render(tile, RENDERPOSX(posX + (x * w)),
					RENDERPOSY(posY + (y * h)), CAMERAZOOM);
			}
		}
	}
}

// Reder all layer of TileMap
void TileMap::Render(Vec2 pos) {
	FOR(i, mapDepth) {
		RenderLayer(i,pos.x, pos.y);
	}
}

// Gets TileMap width as a integer
int TileMap::GetWidth() const{
	return mapWidth;
}

// Gets TileMap height as a integer
int TileMap::GetHeight() const{
	return mapHeight;
}

// Gets TileMap depth as a integer
int TileMap::GetDepth() const{
	return mapDepth;
}

// Changes the size of the TileMap
// Recieves newWidth, a integer, that represents the new width of the TileMap
// Recieves newHeight, a integer, that represents the new height of the TileMap
void TileMap::SetSize(int newWidth,int newHeight) {
	// Creates a new matrix full of empty tiles
	vector<int> newMatrix(newWidth*newHeight*mapDepth, EMPTY_TILE);
	int maxX = min(newWidth, mapWidth);
	int maxY = min(newHeight, mapHeight);

  // Iterates through tileMatrix depth
	FOR(z,mapDepth){

    // Iterates through tileMatrix height
		FOR(y,maxY){

      // Iterates through tileMatrix width
			FOR(x,maxX){
        // Copies the elements of the tile matrix to the newMatrix
				newMatrix[x+(y*newWidth)+(z*newWidth*newHeight)] = At(x, y, z);
			}
		}
	}

	// Replaces the tileMatrix with the newMatrix
	mapWidth = newWidth;
	mapHeight = newHeight;
	tileMatrix.clear();
	tileMatrix = newMatrix;
}
