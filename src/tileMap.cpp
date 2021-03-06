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
#include <assert.h>

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

TileMap::TileMap(int width, int height, TileSet* tile_set) : tile_set{tile_set},
																														map_width{width},
																														map_height{height},
																														map_depth{1} {
	LOG_METHOD_START("TileMap::TileMap");
	assert(width >= 0);
	LOG_VARIABLE("width",width);
	assert(height >= 0);
	LOG_VARIABLE("height",height);
	tile_matrix.reserve(map_width * map_height);
  //! Iterates through tileMatrix height of tile map
	FOR(height_iterator, map_height)
	  //! Iterates through tileMatrix width of tile map
    FOR(width_iterator, map_width)
      //! Empties the first layer of the tileMatrix
			at(width_iterator, height_iterator, 0) = EMPTY_TILE;
	LOG_METHOD_CLOSE("TileMap::TileMap","constructor");
}

//! A constructor.
    /*!
    *	This is a constructor method of TileMap class
		*	\param ts
		*	\brief A pointer to TileSet, that represents the first tile set of the
    * tile map
    */
TileMap::TileMap(TileSet* tile_set) : tile_set{tile_set}{
	LOG_METHOD_START("TileMap::TileMap");
	LOG_METHOD_CLOSE("TileMap::TileMap","constructor");
}

/*!
	@fn void TileMap::Load(ifstream& in)
	@brief Method that loads the tile matrix for the in file
	@param input_file
	@brief A address to ifstream, that provides the tile map informations and
  elements
	@return The execution of this method returns no value
*/
void TileMap::load(ifstream& input_file) {
	LOG_METHOD_START("TileMap::load");
  //! @var line
	string line;//!< A string that represents the first line of the in file

	getline(input_file,line);
	sscanf(line.c_str()," %d,%d,%d",&map_width,&map_height,&map_depth);

	//! Reads a line of in and defines the map width, map height and map depth
	tile_matrix.clear();
	tile_matrix.reserve(map_width * map_height * map_depth);

  //! @var tile
	int tile;//!< a integer that represents a tile

  //! Iterates through the tile matrix depth
	FOR(depth_iterator, map_depth) {
    //! Iterates through the tile matrix height
		FOR(height_iterator, map_height) {
      //! Iterates through the tile matrix width
			FOR(width_iterator, map_width) {
        //! Loads each position from in and saves on tile matrix
        input_file >> tile;
				input_file.ignore(1);
				at(width_iterator, height_iterator, depth_iterator) = tile - 1;
			}
		}
	}
	LOG_METHOD_CLOSE("TileMap::load","void");
}

/*!
	@fn void TileMap::save(stringstream& out)
	@brief Method that saves the tile Matrix the out file
	@param out
	@brief A address to ifstream, that recives the tile matrix informations and
  elements
	@return The execution of this method returns no value
*/
void TileMap::save(stringstream& output_file) {
	LOG_METHOD_START("TileMap::save");

  //! Saves the width, height and depth of the tile matrix on out
	output_file<<map_width<<","<<map_height<<","<<map_depth<<endl<<endl;

  //! Iterates through the tile matrix depth
	FOR(depth_iterator, map_depth) {
    //! Iterates through the tile matrix width
		FOR(height_iterator, map_height) {
      //! Iterates through the tile matrix width
			FOR(width_iterator, map_width) {
        //! Saves each position of the tile matrix in the out
				output_file<<at(width_iterator,height_iterator,depth_iterator)+1<<",\t";
			}
			output_file<<endl;
		}
		output_file<<endl;
	}
	LOG_METHOD_CLOSE("TileMap::save","void");
}

/*!
	@fn void TileMap::define_map_conner(int *lastX,int *lastY,int width,
	 																		int height)
	@brief Method that defines the map and camera corners
	@param firstX
	@brief A positive integer, that represents the beginning of the layer in the
	axis x
	@param firstY
	@brief A positive integer, that represents the beginning of the layer in the
	axis y
	@param lastX
	@brief A positive integer, that represents the end of the layer in the axis x
	@param lastY
	@brief A positive integer, that represents the end of the layer in the axis y
	@param width
	@brief A positive integer, that represents the tile set width
  @param height
  @brief A positive integer, that recives the tile set height
  @return The execution of this method returns no value
*/
void TileMap::define_corners(int *firstX, int *firstY, int *lastX, int *lastY,
															int width, int height, int position_x,
															 int position_y ){
	  //! Checks if the camera is ahead of the posX in axis x
		if (position_x < CAMERA.x){
			//! Reallocates the beginning of the layer in the axis x
			*firstX = (CAMERA.x-position_x) / width;
		}
		else{
			// do nothing
		}

		//! Checks if the camera is ahead of the posy in axis y
		if (position_y < CAMERA.y){
			//! Reallocates the beginning of the layer in the axis y
			*firstY = (CAMERA.y - position_y) / height;
		 }
		 else{
			 // do nothing
		 }
		//! @var mapCorner
		//!< a two-dimensional vector, that represents the positons of the coners
		//!< of the map
		Vec2 mapCorner = Vec2(position_x + (map_width*width),
													position_y+(map_height*height));
		//! @var cameraConer
		//!< a two-dimensional vector, that represents the positons of the coners of
		//!< the camera
	  Vec2 cameraCorner = CAMERA + (WINSIZE / CAMERAZOOM);

	  //! Checks if the coner of the map is ahead of the coner of the camera in
	  //! axis x
	  if (mapCorner.x > cameraCorner.x){
			//! Reallocates the end of the layer in the axis x
	    *lastX -= (mapCorner.x - cameraCorner.x) / width;
	  }
		else{
			// do nothing
		}
		//! Checks if the coner of the map is ahead of the coner of the camera in
	  //! axis y
	  if (mapCorner.y > cameraCorner.y){
	    //! Reallocates the end of the layer in the axis y
			*lastY -= (mapCorner.y - cameraCorner.y) / height;
	  }
	  else{
			//do nothing
		}
}

/*!
	@fn void TileMap::render_layer(int layer,int position_x ,int position_y)
	@brief Method that reders a layer of the tile map
  @param layer
	@brief A positive integer, that represents the layer that will be rendered
  @param position_x
  @brief A positive integer, that recives a position in the x axis
  @param position_Y
  @brief A positive integer, that recives a position in the y axis
  @return The execution of this method returns no value
  @warning Method that requires review of comment
*/

void TileMap::render_layer(int layer, int position_x, int position_y) {
	LOG_METHOD_START("TileMap::render_layer");
	LOG_VARIABLE("position_y",position_y);
  //! @var width
	//!< a integer that represents the tile set width
	int width = tile_set->get_width();
	assert(width >= 0);
  //! @var height
	//!< a integer that represents the tile set height
	int height=tile_set->get_height();
  //! @var tile
	assert(height >= 0);
	//! a integer that represents a tile
	int tile = 0;
  //! @var firstX
	//!< a integer that represents the beginning of the layer in the axis x
	int firstX = 0;
  //! @var firstY
	//!< a integer that represents the beginning of the layer in the axis y
  int firstY = 0;
  //! @var lastX
	//!< a integer that represents the end of the layer in the axis x
  int lastX = map_width;
  //! @var lastY
	//!< a integer that represents the end of the layer in the axis y
  int lastY = map_height;

	define_corners(&firstX ,&firstY, &lastX, &lastY, width, height, position_x,
									position_y);

  //! Iterates the height of the layer
	for (int y_iterator = firstY; y_iterator <= lastY; y_iterator++) {
		//! Iterates the width of the layer
    for (int x_iterator = firstX; x_iterator <= lastX; x_iterator++) {

			tile = at(x_iterator, y_iterator, layer);
      //! Checks if the tile is empty
			if (tile != EMPTY_TILE){
				//! Render the tile
				tile_set->render(tile, RENDERPOSX(position_x + (x_iterator * width)),
													RENDERPOSY(position_y + (y_iterator * height)),
													CAMERAZOOM);
			}
			else{
				// do nothing
			}
		}
	}
	LOG_METHOD_CLOSE("TileMap::render_layer","void");
}

/*!
	@fn void TileMap::render(Vec2 position)
	@brief Method that reders all layer of the tile map
  @param position
	@brief A Vec2, that represents a two-dimensional vector with the positons of
  to be render
  @return The execution of this method returns no value
  @warning Method that requires review of comment
*/

void TileMap::render(Vec2 position) {
	LOG_METHOD_START("TileMap::render");
	LOG_VARIABLE("position.x",position.x);
	LOG_VARIABLE("position.y",position.y);
  //! Iterates through the layer of the tile map
	FOR(depth_iterator, map_depth) {
		//! Renders the tile map layer
    render_layer(depth_iterator, position.x, position.y);
	}
	LOG_METHOD_CLOSE("TileMap::render","void");
}

/*!
	@fn int& TileMap::at(int position_x,int position_y,int position_z)
	@brief Method that returns element of the corresponding position of the tile
  matrix
	@param position_x
	@brief A positive integer, that recives the x axis position of the element
  @param position_y
  @brief A positive integer, that recives the y axis position of the element
  @param position_z
  @brief A positive integer, that recives the z axis position of the element
	@return A address to integer,that represents the tile of the tile matrix
*/
int& TileMap::at(int position_x, int position_y, int position_z) {
	LOG_METHOD_START("TileMap::at");
	LOG_VARIABLE("position_x",position_x);
	LOG_VARIABLE("position_y",position_y);
	LOG_VARIABLE("position_z",position_z);

	//! @var relative_position_x;
	//!< Represents the relative x axis position of the element;
	int relative_position_x = position_x;
	//! @var relative_position_y;
	//!< Represents the relative y axis position of the element;
	int relative_position_y = (position_y * map_width);
	//! @var relative_position_z;
	//!< Represents the relative z axis position of the element;
	int relative_position_z = (position_z * map_width * map_height);
	//! @var relative_position;
	//!< Represents the relative position of the element;
	int relative_position = relative_position_x + relative_position_y
		+ relative_position_z;
	//! @var tile
	//!< Represents the found tile

	LOG_METHOD_CLOSE("TileMap::at",tile_matrix[relative_position]);
	return tile_matrix[relative_position];
}

/*!
	@fn int TileMap::at(int position_x,int position_y,int position_z) const
	@brief Method that returns element of the corresponding position of the tile
  matrix
  @param position_x
	@brief A positive integer, that recives the x axis position of the element
  @param position_y
  @brief A positive integer, that recives the y axis position of the element
  @param position_z
  @brief A positive integer, that recives the z axis position of the element
	@return A integer,that represents the tile of the tile matrix
*/
int TileMap::at(int position_x,int position_y,int position_z) const{
	LOG_METHOD_START("TileMap::at");
	LOG_VARIABLE("position_x",position_x);
	LOG_VARIABLE("position_y",position_y);
	LOG_VARIABLE("position_z",position_z);

	//! @var relative_position_x;
	//!< Represents the relative x axis position of the element;
	int relative_position_x = position_x;
	//! @var relative_position_y;
	//!< Represents the relative y axis position of the element;
	int relative_position_y = (position_y*map_width);
	//! @var relative_position_z;
	//!< Represents the relative z axis position of the element;
	int relative_position_z = (position_z*map_width*map_height);
	//! @var relative_position;
	//!< Represents the relative position of the element;
	int relative_position = relative_position_x +relative_position_y
		+ relative_position_z;
	//! @var tile
	//!< Represents the found tile

	LOG_METHOD_CLOSE("TileMap::at",tile_matrix[relative_position]);
	return tile_matrix[relative_position];
}

/*!
	@fn void TileMap::change_size(int new_width,int new_height)
	@brief Method that changes the size of the tile map
  @param new_width
	@brief A positive integer, that represents the new width of the tile map
  @param new_height
  @brief A positive integer, that represents the new height of the tile map
  @return The execution of this method returns no value
*/
void TileMap::change_size(int new_width,int new_height) {
	LOG_METHOD_START("TileMap::change_size");
	assert(map_width >= 0);
	LOG_VARIABLE("new_width",new_width);
	assert(map_height >= 0);
	LOG_VARIABLE("new_height",new_height);
	//! @var new_matrix
	//!<  A integer vector, that represents the tile map with the new size
  vector<int> new_matrix(new_width*new_height*map_depth, EMPTY_TILE);
	//! @var max_x
	//!< A integer, that represents the lower value between newWidth and mapWidth
	int max_x = min(new_width, map_width);
	assert(max_x >= 0);
	//! @var max_y
	//!< A integer, that represents the lower value between newHeight and
	//! mapHeight
  int max_y = min(new_height, map_height);
	assert(max_y >= 0);

  //! Iterates z from 0 to the tile map depth
	FOR(depth_iterator, map_depth){
    //! Iterates y from 0 to maxY
		FOR(height_iterator, max_y){
			//! Iterates x to 0 to maxX
      FOR(width_iterator, max_x){
				int relative_position_x = width_iterator;
				//! @var relative_position_y;
				//!< Represents the relative y axis position of the element;
				int relative_position_y = (height_iterator * new_width);
				//! @var relative_position_z;
				//!< Represents the relative z axis position of the element;
				int relative_position_z = (depth_iterator * new_width * new_height);
				//! @var relative_position;
				//!< Represents the relative position of the element;
				int relative_position = relative_position_x + relative_position_y
					+ relative_position_z;

				//! Copies the elements of the tile matrix to the newMatrix
				new_matrix[relative_position] = at(width_iterator, height_iterator,
					depth_iterator);
			}
		}
	}
  //! Replaces the tileMatrix with the new matrix
	map_width = new_width;
	map_height = new_height;
	tile_matrix.clear();
	tile_matrix = new_matrix;
	LOG_METHOD_CLOSE("TileMap::change_size","void");
}

/*!
	@fn void TileMap::set_tile_set(Tile_set* ts)
	@brief A setter of the attribute tile_set
  @param ts
  @brief A pointer to TileSet, that represents the new first tile set of the
  tile map
  @return The execution of this method returns no value
*/
void TileMap::set_tile_set(TileSet* tile_set) {
	LOG_METHOD_START("TileMap::set_tile_set");
	this->tile_set = tile_set;
	LOG_METHOD_CLOSE("TileMap::set_tile_set","void");
}


/*!
	@fn int TileMap::get_width() const
	@brief A getter of the attribute mapWidth
	@return A positive integer, that represents the width of a tile map
*/
int TileMap::get_width() const{
	LOG_METHOD_START("TileMap::get_width");
	assert(map_width >= 0);
	LOG_METHOD_CLOSE("TileMap::get_width",map_width);
	return map_width;
}


/*!
	@fn int TileMap::get_height() const
	@brief A getter of the attribute mapHeight
	@return A positive integer, that represents the height of a tile map
*/
int TileMap::get_height() const{
	LOG_METHOD_START("TileMap::get_height");
	assert(map_height >= 0);
	LOG_METHOD_CLOSE("TileMap::get_height",map_height);
	return map_height;
}

/*!
	@fn int TileMap::get_depth() const
	@brief A getter of the attribute mapDepth
	@return A positive integer, that represents the depth of a tile map
*/
int TileMap::get_depth() const{
	LOG_METHOD_START("TileMap::get_depth");
	assert(map_depth >= 0);
	LOG_METHOD_CLOSE("TileMap::get_depth",map_depth);
	return map_depth;
}
