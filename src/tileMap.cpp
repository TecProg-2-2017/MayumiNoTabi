/*!
*  \file File tileMap.cpp
*  \brief Implementation of the class TileMap
*
*  Auxiliary documentation
*  \sa tileMap.hpp
*/
#include <tileMap.hpp>
#include <camera.hpp>
#include <componentCollider.hpp>
#include <componentStaticRender.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <tileSet.hpp>

/*!
	@class TileMap
	@brief This class provides the tile map to the game

*/

//! A constructor.
    /*!
    *	This is a constructor method of TileMap class
		*	\param width
		*	\brief A positive integer, that represents width of the tile map
		*	\param height
		*	\brief A positive integer, that represents height of a tile map
		*	\param ts
		*	\brief A pointer to TileSet, that represents the first tile set of the
    * tile map
    */
TileMap::TileMap(int width, int height, TileSet* ts)
 			: tileSet{ts}, mapWidth{width}, mapHeight{height}, mapDepth{1} {
	tileMatrix.reserve(mapWidth*mapHeight)
	//! Iterates through tileMatrix height of tile map
	FOR(h, mapHeight) {

    //! Iterates through tileMatrix width of tile map
		FOR(w, mapWidth) {
      //! Empties the first layer of the tileMatrix
			At(w, h, 0) = EMPTY_TILE;
		}
	}
}

//! A constructor.
    /*!
    *	This is a constructor method of TileMap class
		*	\param ts
		*	\brief A pointer to TileSet, that represents the first tile set of the
    * tile map
    */
TileMap::TileMap(TileSet* ts) : tileSet{ts} {

}

/*!
	@fn void TileMap::Load(ifstream& in)
	@brief Method that loads the tile matrix for the in file
	@param in
	@brief A address to ifstream, that provides the tile map informations and
  elements
	@return The execution of this method returns no value
*/
void TileMap::Load(ifstream& in) {
  //! @var line
  string line; //!< A string that represents the first line of the in file

	//! Reads a line of in and defines the map width, map height and map depth
	getline(in,line);
	sscanf(line.c_str(), " %d,%d,%d", &mapWidth, &mapHeight, &mapDepth);

	//! Clears the tile matrix and reserves the size matching the number of
	//! elements of the tile matrix
	tileMatrix.clear();
	tileMatrix.reserve(mapWidth*mapHeight*mapDepth);

  //! @var t
	int t; //!< a integer that represents a tile

  //! Iterates through the tile matrix depth
	FOR(d, mapDepth) {

    //! Iterates through the tile matrix height
		FOR(h, mapHeight) {

      //! Iterates through the tile matrix width
			FOR(w, mapWidth) {
        //! Loads each position from in and saves on tile matrix
				in >> t;
				in.ignore(1);
				At(w, h, d) = t-1;
			}
		}
	}
}

/*!
	@fn void TileMap::Save(stringstream& out)
	@brief Method that saves the tile Matrix the out file
	@param out
	@brief A address to ifstream, that recives the tile matrix informations and
  elements
	@return The execution of this method returns no value
*/
void TileMap::Save(stringstream& out) {
	//! Saves the width, height and depth of the tile matrix on out
	out << mapWidth << "," << mapHeight << "," << mapDepth << endl << endl;

  //! Iterates through the tile matrix depth
	FOR(d, mapDepth) {
    //! Iterates through the tile matrix height
		FOR(h, mapHeight) {
      //! Iterates through the tile matrix width
			FOR(w, mapWidth) {
        //! Saves each position of the tile matrix in the out
				out << At(w, h, d) + 1 << ",\t";
			}
			out << endl;
		}
		out << endl;
	}
}

/*!
	@fn void TileMap::SetTileSet(TileSet* ts)
	@brief A setter of the attribute tileSet
  @param ts
  @brief A pointer to TileSet, that represents the new first tile set of the
  tile map
  @return The execution of this method returns no value
*/
void TileMap::SetTileSet(TileSet* ts) {
	tileSet = ts;
}

/*!
	@fn int& TileMap::At(int x,int y,int z)
	@brief Method that returns element of the corresponding position of the tile
  matrix
	@param x
	@brief A positive integer, that recives the x axis position of the element
  @param y
  @brief A positive integer, that recives the y axis position of the element
  @param z
  @brief A positive integer, that recives the z axis position of the element
	@return A address to integer,that represents the tile of the tile matrix
*/
int& TileMap::At(int x,int y,int z) {
	return tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

/*!
	@fn int TileMap::At(int x, int y, int z) const
	@brief Method that returns element of the corresponding position of the tile
  matrix
  @param x
	@brief A positive integer, that recives the x axis position of the element
  @param y
  @brief A positive integer, that recives the y axis position of the element
  @param z
  @brief A positive integer, that recives the z axis position of the element
	@return A integer,that represents the tile of the tile matrix
*/
int TileMap::At(int x, int y, int z) const {
	return tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

/*!
	@fn void TileMap::RenderLayer(int layer, int posX , int posY)
	@brief Method that reders a layer of the tile map
  @param layer
	@brief A positive integer, that represents the layer that will be rendered
  @param posX
  @brief A positive integer, that recives a position in the x axis
  @param posY
  @brief A positive integer, that recives a position in the y axis
  @return The execution of this method returns no value
  @warning Method that requires review of comment
*/
void TileMap::RenderLayer(int layer, int posX , int posY) {
  //! @var w
	int w = tileSet->GetWidth(); //!< a integer that represents the tile set width
  //! @var h
	int h = tileSet->GetHeight(); //!< a integer that represents the tile set height
  //! @var tile
  int tile; //! a integer that represents a tile
	//! @var firstX
  int firstX = 0; //!< a integer that represents the beginning of the layer in the axis x
  //! @var firstY
  int firstY = 0; //!< a integer that represents the beginning of the layer in the axis y
  //! @var lastX
  int lastX = mapWidth; //!< a integer that represents the end of the layer in the axis x
  //! @var lastY
  int lastY = mapHeight; //!< a integer that represents the end of the layer in the axis y

  //! Checks if the camera is ahead of the posX in axis x
	if (posX < CAMERA.x){
    //! Reallocates the beginning of the layer in the axis x
		firstX = (CAMERA.x - posX) / w;
	}
	//! \warning else (do nothing)

  //! Checks if the camera is ahead of the posy in axis y
	if (posY < CAMERA.y){
    //! Reallocates the beginning of the layer in the axis y
		firstY = (CAMERA.y - posY) / h;
	}
  // \warning else (do nothing)

  //! Defines the map and camera corners
  //! @var mapCorner
	Vec2 mapCorner = Vec2(posX + (mapWidth * w),posY + (mapHeight * h)); //!< a two-dimensional vector, that represents the positons of the coners of the map
  //! @var cameraCorner
  Vec2 cameraCorner = CAMERA + (WINSIZE / CAMERAZOOM); //!< a two-dimensional vector, that represents the positons of the coners of the camera

  //! Checks if the coner of the map is ahead of the coner of the camera in axis
  //! x
  if (mapCorner.x > cameraCorner.x){
    //! Reallocates the end of the layer in the axis x
		lastX -= (mapCorner.x - cameraCorner.x) / w;
	}
  //! \warning else (do nothing)

  //! Checks if the coner of the map is ahead of the coner of the camera in axis
  //! y
  if (mapCorner.y > cameraCorner.y){
    //! Reallocates the end of the layer in the axis y
		lastY -= (mapCorner.y - cameraCorner.y) / h;
	}
  //! \warning else (do nothing)

  //! Iterates the height of the layer
	for (int y = firstY; y <= lastY; y++) {

    //! Iterates the width of the layer
		for (int x = firstX; x <= lastX; x++) {
			tile = At(x, y, layer);

      //! Checks if the tile is empty
			if (tile != EMPTY_TILE){
        //! Render the tile
				tileSet->Render(tile, RENDERPOSX(posX + (x * w)),
					RENDERPOSY(posY + (y * h)), CAMERAZOOM);
			}
		}
	}
}

/*!
	@fn void TileMap::Render(Vec2 pos)
	@brief Method that reders all layer of the tile map
  @param pos
	@brief A Vec2, that represents a two-dimensional vector with the positons of
  to be render
  @return The execution of this method returns no value
  @warning Method that requires review of comment
*/
void TileMap::Render(Vec2 pos) {
  //! Iterates through the layer of the tile map
	FOR(i, mapDepth) {
    //! Renders the tile map layer
		RenderLayer(i,pos.x, pos.y);
	}
}

/*!
	@fn int TileMap::GetWidth() const
	@brief A getter of the attribute mapWidth
	@return A positive integer, that represents the width of a tile map
*/
int TileMap::GetWidth() const{
	return mapWidth;
}

/*!
	@fn int TileMap::GetHeight() const
	@brief A getter of the attribute mapHeight
	@return A positive integer, that represents the height of a tile map
*/
int TileMap::GetHeight() const{
	return mapHeight;
}

/*!
	@fn int TileMap::GetDepth() const
	@brief A getter of the attribute mapDepth
	@return A positive integer, that represents the depth of a tile map
*/
int TileMap::GetDepth() const{
	return mapDepth;
}

/*!
	@fn void TileMap::SetSize(int newWidth,int newHeight)
	@brief Method that changes the size of the tile map
  @param newWidth
	@brief A positive integer, that represents the new width of the tile map
  @param newHeight
  @brief A positive integer, that represents the new height of the tile map
  @return The execution of this method returns no value
*/
void TileMap::SetSize(int newWidth,int newHeight) {
	//! @var newMatrix
	vector<int> newMatrix(newWidth*newHeight*mapDepth, EMPTY_TILE);//!<  A integer vector, that represents the tile map with the new size
  //! @var maxX
  int maxX = min(newWidth, mapWidth); //!< A integer, that represents the lower value between newWidth and mapWidth
  //! @var maxY
	int maxY = min(newHeight, mapHeight); //!< A integer, that represents the lower value between newHeight and mapHeight

  //! Iterates z from 0 to the tile map depth
	FOR(z,mapDepth){

    //! Iterates y from 0 to maxY
		FOR(y,maxY){

      //! Iterates x to 0 to maxX
			FOR(x,maxX){
        //! Copies the elements of the tile matrix to the newMatrix
				newMatrix[x+(y*newWidth)+(z*newWidth*newHeight)] = At(x, y, z);
			}
		}
	}

	//! Replaces the tileMatrix with the newMatrix
	mapWidth = newWidth;
	mapHeight = newHeight;
	tileMatrix.clear();
	tileMatrix = newMatrix;
}
