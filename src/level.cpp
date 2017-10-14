/*!
 *  File: level.cpp
 *
 *  Description: Implements level behavior 
 */ 

#include <level.hpp>

#include <complib.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <state.hpp>

#define DEFAULT_BACKGROUND "img/mountain_bg.jpg"
#define DEFAULT_TILE_SIZE 64
#define DEFAULT_TILESET "img/tileset.png"
#define DEFAULT_MAP_WIDTH 50
#define DEFAULT_MAP_HEIGHT 50


/*!
 *  @fn Level::Level() 
 *  @brief Constructor method of Level 
 *  @return A Level object
 */
Level::Level() : background_sprite{Sprite(DEFAULT_BACKGROUND)}, 
    level_tile_set{TileSet(DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE, DEFAULT_TILESET)},
    level_tile_map{TileMap(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, &level_tile_set)} {

    level_collision_layer.clear();
    level_collision_layer.resize(DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT);

    FOR(y,DEFAULT_MAP_HEIGHT) {
        FOR(x,DEFAULT_MAP_WIDTH) {
            level_collision_layer[(y*DEFAULT_MAP_WIDTH)+x] = EMPTY_TILE;
        }
    }
}

/*!
 *  @fn Level::Level(string file) 
 *  @brief Constructor method of Level 
 *  @param string file
 *  @return A Level object
 */
Level::Level(string file) : level_tile_set{TileSet()}, level_tile_map{TileMap(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, &level_tile_set)} { 
    Load(file);
}

/*!
 *  @fn Level::~Level() 
 *  @brief Destructor method of Level 
 *  @return The method returns no param
 */
Level::~Level() {

}

/*!
 *  @fn void Level::load_level_from_file(const string& file) 
 *  @brief Load level from the level file 
 *  @param const string& file
 *  @return The method returns no param
 */
void Level::load_level_from_file(const string& file) {
    ifstream file_input = NULL;//! <Receive input from level file
    
    file_input.open(LEVEL_PATH + file + ".txt");

    //! Get an error while opening the file
    if (!file_input.is_open()) {
        cerr << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        // Do nothing
    }
    
    string file_parameters = ""; //! <Store parameters readed from level file

    //! Loading the background
    getline(file_input,background_file_name);

    //! Load background to the level if it's not empty
    if (!background_file_name.empty()) { 
        background_sprite.Open(background_file_name);
    }
    else {
        // Do nothing
    }

    file_input.ignore(1);
    background_sprite.StretchToFit(WINSIZE);
    
    int level_tile_width = 0;//! <Tile level width 
    int level_tile_height = 0; //! <Tile level height

    //! Loading the tileset
    getline(file_input, level_tile_set_filename);
    getline(file_input, file_parameters);
    sscanf(file_parameters.c_str(), " %d,%d", &level_tile_width, &level_tile_height);
    level_tile_set.Load(level_tile_width, level_tile_height, level_tile_set_filename);
    file_input.ignore(1);
    
    //! Loading the tilemap
    level_tile_map.Load(file_input);
    
    //! Loading the collision layer
    int level_map_width = level_tile_map.get_width();
    int level_map_height = level_tile_map.get_height();

    level_collision_layer.clear();
    level_collision_layer.resize(level_map_width*level_map_height);
    
    int t = 0;
    int g = 0;

    level_collision_groups.clear();
    level_collision_groups.reserve(level_map_width*level_map_height);

    FOR(y,level_map_height) {
        FOR(x,level_map_width) {
            file_input >> t;
            file_input.ignore(1);
            level_collision_layer[(y*level_map_width)+x] = t-1;

            if (t == EMPTY_TILE) {
                level_collision_groups[(y*level_map_width)+x] = 0;
            }
            else {
                file_input >> g;
                file_input.ignore(1);
                level_collision_groups[(y*level_map_width)+x] = g;
            }
        }
    }
    file_input.ignore(1);

    //! Loading the object list
    level_object_list.clear();

    //! Iterate through objects from the file
    for(string object;getline(file_input, object);) {

        //! Add not empty objects to level_object_list
        if (!object.empty()) {
            level_object_list.push_back(object);
        }
        else {
            // Do nothing
        }
    }

    //! <End of Loading the object list

    file_input.close();
}

/*!
 *  @fn string Level::save_level_to_file(const string& file) 
 *  @brief Save the level on a file 
 *  @param const string& file
 *  @return string 
 */
string Level::save_level_to_file(const string& file) {
    stringstream level_stream_out = NULL;//! <To get the level output
    ofstream file_output = NULL;//! <To write level output on a file

    //! Open file with a valid name
    if (file != "") { 
        file_output.open(LEVEL_PATH + file + ".txt");

        //! Get an error while opening the file
        if (!file_output.is_open()) {
            cerr << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            // Do nothing
        }
    }
    else {
        // Do nothing
    }
    
    //! Saving the background:
    level_stream_out<<background_file_name<<endl<<endl;
    
    //! Saving the tileset:
    level_stream_out<<level_tile_set_filename<<endl;
    level_stream_out<<level_tile_set.get_width()<<","<<level_tile_set.get_height()<<endl<<endl;
    
    //! Saving the tilemap:
    level_tile_map.Save(level_stream_out);
    
    //! Saving the collision layer:
    int level_map_width = level_tile_map.get_width();
    int level_map_height = level_tile_map.get_height();

    FOR(y,level_map_height) {
        FOR(x,level_map_width) {
            char s[200] = {0};

            sprintf(s,"%02d-%03d, ",level_collision_layer[(y*level_map_width)+x]+1,level_collision_groups[(y*level_map_width)+x]);
            string str(s);

            level_stream_out << str;
        }
        level_stream_out << endl;
    }
    level_stream_out << endl;
    
    if (file == "") {
        return level_stream_out.str();
    }
    else {
        // Do nothing
    }

    file_output << out.str();
    file_output.close();

    return "";
}

/*!
 *  @fn void Level::load_level_objects(bool collisors) 
 *  @brief Load objects on the level 
 *  @param bool collisors 
 *  @return The method returns no param
 */
void Level::load_level_objects(bool collisors) {    
    
    char object_type[50] = {0}; //! <Object type
    Vec2 object_position() :x(0), y(0) {}; //! <Object position
    int layer = 0; //! <Level layer
    uint uid = 0;

    //! Creating the objects
    for(auto& i:level_object_list) {
        
        //! Continue for empty object
        if (i.empty()) {
             continue;
        }
        else {
            // Do nothing
        }

        sscanf(i.c_str(), " %s %f %f %d", object_type, &object_position.x, &objPos.y, &layer);
        uid = GameObject::Create(object_type, object_position);
        GAMESTATE.AddObject(uid,layer);
    }
    
    //! Setting the collision boxes:
    if (!collisors) { 
        return;
    }
    else {
        // Do nothing
    }

  
    int level_tile_width = level_tile_set.get_width(); //! <Tile level width
    int level_tile_height = level_tile_set.get_height(); //! <Tile level Height
    int level_map_width = level_tile_map.get_width(); //! <Map width
    int level_map_height = level_tile_map.get_height(); //! <Map height
    map<int,pair<Rect,int>> mp;

    //! TODO: Understand this paragraph
    FOR(y,level_map_height) {
        FOR(x,level_map_width) {
            int t = level_collision_layer[(y*level_map_width)+x]+1;
            int g = level_collision_groups[(y*level_map_width)+x];

            if (t) {
                if (!mp.count(g)) {
                    //! Default vals to make min and max work
                    mp[g]=make_pair(Rect{(float)level_map_width+1,(float)level_map_height+1,
                                (float)-1,(float)-1},t);
                }

                mp[g].first.x=min(mp[g].first.x,(float)x);
                mp[g].first.y=min(mp[g].first.y,(float)y);
                mp[g].first.w=max(mp[g].first.w,(float)x);
                mp[g].first.h=max(mp[g].first.h,(float)y);
            }
        }
    }
    for(auto &it:mp) {
        Rect r = it.second.first;
        int t=it.second.second;

        r.w-=r.x-1;
        r.h-=r.y-1;
        r.x*=level_tile_width;
        r.w*=level_tile_width;
        r.y*=level_tile_height;
        r.h*=level_tile_height;

        //! Instantiate a new game object 
        if (t) {
            GameObject *tile = new GameObject{r};
            tile->AddComponent(new CompCollider{CompCollider::collType::t_ground});
            GAMESTATE.AddObject(tile->uid);
        }
        else {
            // Do nothing
        }
    }
}

/*!
 *  @fn void Level::save_level_objects(const vector<pair<ii,ii>>& grouped) 
 *  @brief Save objects on the level 
 *  @param const vector<pair<ii,ii>>& grouped
 *  @return The method returns no param
 *  @warning Understand better this method
 */
void Level::save_level_objects(const vector<pair<ii,ii>>& grouped) {
    
    //! Saving the collision groups:
    int level_map_width = level_tile_map.get_width(); //! <Level map width
    int level_map_height = level_tile_map.get_height(); //! <Level map height 

    int id=1;
    map<ii,int> ids;

    FOR(y,level_map_height) {
        FOR(x,level_map_width) {
            if (level_collision_layer[(y*level_map_width)+x]==EMPTY_TILE) {
                level_collision_groups[(y*level_map_width)+x] = 0;
            }
            else{
                auto &group = grouped[(level_map_width*y)+x];
                if (group.first.first==x && group.first.second==y)ids[group.first]=id++;
                level_collision_groups[(y*level_map_width)+x] = ids[group.first];
            }
        }
    }
}

/*!
 *  @fn bool Level::operator==(Level& level) 
 *  @brief Override operator ==  
 *  @param Level& level 
 *  @return True or False 
 */
bool Level::operator==(Level& level) {
    
    if (Save() == level.save_level_to_file()){ 
        return true;
    }
    else {
        // Do nothing
    }

    return false;
}
