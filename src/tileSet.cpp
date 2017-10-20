#include <tileSet.hpp>

TileSet::TileSet() {
}

TileSet::TileSet(int width, int height, string file_path) {
	load(width, height, file_path);
}

void TileSet::load(int  width, int height, string file_path) {
	tile_width = width;
	tile_height = height;

	tileSet.Open(file_path);

	rows = tileSet.GetHeight()/tile_height;
	columns = tileSet.GetWidth()/tile_width;
}

void TileSet::render(unsigned int index,float position_x,float position_y, float extended_scale) {
	if ((int)index<(rows*columns)) {
		tileSet.SetClip(tile_width*(index%columns),(tile_height*(index/columns)),tile_width,tile_height);
		tileSet.render(position_x,position_y,0,extended_scale);
	}
}

int TileSet::get_width() {
	return tile_width;
}

int TileSet::get_height() {
	return tile_height;
}

int TileSet::get_tile_count() {
	return rows*columns;
}
