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
Level::Level() : background{Sprite(DEFAULT_BACKGROUND)}, 
    tileSet{TileSet(DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE, DEFAULT_TILESET)},
    tileMap{TileMap(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, &tileSet)} {

    collisionLayer.clear();
    collisionLayer.resize(DEFAULT_MAP_WIDTH*DEFAULT_MAP_HEIGHT);
    FOR(y,DEFAULT_MAP_HEIGHT) {
        FOR(x,DEFAULT_MAP_WIDTH) {
            collisionLayer[(y*DEFAULT_MAP_WIDTH)+x] = EMPTY_TILE;
        }
    }
}

/*!
 *  @fn Level::Level(string file) 
 *  @brief Constructor method of Level 
 *  @param string file
 *  @return A Level object
 */
Level::Level(string file) : tileSet{TileSet()}, tileMap{TileMap(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT, &tileSet)} { 
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
 *  @fn void Level::Load(const string& file) 
 *  @brief Load level from the level file 
 *  @param const string& file
 *  @return The method returns no param
 */
void Level::Load(const string& file) {
  ifstream in;//! <Receive input from level file
    
    in.open(LEVEL_PATH + file + ".txt");

    //! Get an error while opening the file
    //! TODO: Insert else to do nothing
    if (!in.is_open()) {
        cerr << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }
    
    string parameters; //! <Store parameters readed from level file

    //! Loading the background
    getline(in,backgroundFilename);

    //! Load background to the level if it's not empty
    //! TODO: Insert else to do nothing
    if (!backgroundFilename.empty()) { 
        background.Open(backgroundFilename);
    }
    in.ignore(1);
    background.StretchToFit(WINSIZE);
    
    int tileWidth, tileHeight; //! <Tile level width and height

    //! Loading the tileset
    getline(in, tileSetFilename);
    getline(in, parameters);
    sscanf(parameters.c_str(), " %d,%d", &tileWidth, &tileHeight);
    tileSet.Load(tileWidth, tileHeight, tileSetFilename);
    in.ignore(1);
    
    //! Loading the tilemap
    tileMap.Load(in);
    
    //! Loading the collision layer
    int mapWidth = tileMap.get_width();
    int mapHeight = tileMap.get_height();
    collisionLayer.clear();
    collisionLayer.resize(mapWidth*mapHeight);
    
    int t,g;
    collisionGroups.clear();
    collisionGroups.reserve(mapWidth*mapHeight);
    FOR(y,mapHeight) {
        FOR(x,mapWidth) {
            in >> t;
            in.ignore(1);
            collisionLayer[(y*mapWidth)+x] = t-1;
            if (t == EMPTY_TILE) {
                collisionGroups[(y*mapWidth)+x] = 0;
            }
            else {
                in >> g;
                in.ignore(1);
                collisionGroups[(y*mapWidth)+x] = g;
            }
        }
    }
    in.ignore(1);

    //! Loading the object list
    objectList.clear();

    //! Iterate through objects from the file
    for(string object;getline(in, object);) {

        //! Add not empty objects to objectList
        //! TODO: Insert else to do nothing
        if (!object.empty()) {
            objectList.push_back(object);
        }
    }

    //! <End of Loading the object list

    in.close();
}

/*!
 *  @fn string Level::Save(const string& file) 
 *  @brief Save the level on a file 
 *  @param const string& file
 *  @return string 
 */
string Level::Save(const string& file) {
    stringstream out;//! <To get the level output
    ofstream output;//! <To write level output on a file

    //! Open file with a valid name
    //! TODO: Insert else to do nothing
    if (file != "") { 
        output.open(LEVEL_PATH + file + ".txt");

        //! Get an error while opening the file
        //! TODO: Insert else to do nothing
        if (!output.is_open()) {
            cerr << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    //! Saving the background:
    out<<backgroundFilename<<endl<<endl;
    
    //! Saving the tileset:
    out<<tileSetFilename<<endl;
    out<<tileSet.get_width()<<","<<tileSet.get_height()<<endl<<endl;
    
    //! Saving the tilemap:
    tileMap.Save(out);
    
    //! Saving the collision layer:
    int mapWidth = tileMap.get_width();
    int mapHeight = tileMap.get_height();
    FOR(y,mapHeight) {
        FOR(x,mapWidth) {
            char s[200];
            sprintf(s,"%02d-%03d, ",collisionLayer[(y*mapWidth)+x]+1,collisionGroups[(y*mapWidth)+x]);
            string str(s);
            out << str;
        }
        out << endl;
    }
    out << endl;
    
    //! TODO: Insert else to do nothing
    if (file == "") {
        return out.str();
    }
    output<<out.str();
    output.close();

    return "";
}

/*!
 *  @fn void Level::LoadObjects(bool collisors) 
 *  @brief Load objects on the level 
 *  @param bool collisors 
 *  @return The method returns no param
 */
void Level::LoadObjects(bool collisors) {    
    
    char objType[50]; //! <Object type
    Vec2 objPos; //! <Object position
    int layer; //! <Level layer
    uint uid;

    //! Creating the objects
    for(auto& i:objectList) {
        
        //! Continue for empty object
        //! TODO: Insert else to do nothing
        if (i.empty()) {
             continue;
        }
        sscanf(i.c_str(), " %s %f %f %d", objType, &objPos.x, &objPos.y, &layer);
        uid = GameObject::Create(objType, objPos);
        GAMESTATE.AddObject(uid,layer);
    }
    
    //! Setting the collision boxes:
    //! TODO: Insert else to do nothing
    if (!collisors) { 
        return;
    }
    
    int tileWidth = tileSet.get_width(); //! <Tile level width
    int tileHeight = tileSet.get_height(); //! <Tile level Height
    int mapWidth = tileMap.get_width(); //! <Map width
    int mapHeight = tileMap.get height(); //! <Map height
    map<int,pair<Rect,int>> mp;

    //! TODO: Understand this paragraph
    FOR(y,mapHeight) {
        FOR(x,mapWidth) {
            int t = collisionLayer[(y*mapWidth)+x]+1;
            int g = collisionGroups[(y*mapWidth)+x];
            if (t) {
                if (!mp.count(g)) {
                    //! Default vals to make min and max work
                    mp[g]=make_pair(Rect{(float)mapWidth+1,(float)mapHeight+1,
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
        r.x*=tileWidth;
        r.w*=tileWidth;
        r.y*=tileHeight;
        r.h*=tileHeight;

        //! Instantiate a new game object 
        //! TODO: Insert else to do nothing
        if (t) {
            GameObject *tile = new GameObject{r};
            tile->AddComponent(new CompCollider{CompCollider::collType::t_ground});
            GAMESTATE.AddObject(tile->uid);
        }
    }
}

/*!
 *  @fn void Level::SaveObjects(const vector<pair<ii,ii>>& grouped) 
 *  @brief Save objects on the level 
 *  @param const vector<pair<ii,ii>>& grouped
 *  @return The method returns no param
 *  @warning Understand better this method
 */
void Level::SaveObjects(const vector<pair<ii,ii>>& grouped) {
    
    //! Saving the collision groups:
    int mapWidth = tileMap.get_width(); //! <Level map width
    int mapHeight = tileMap.get_height(); //! <Level map height 
    int id=1;
    map<ii,int> ids;
    FOR(y,mapHeight) {
        FOR(x,mapWidth) {
            if (collisionLayer[(y*mapWidth)+x]==EMPTY_TILE) {
                collisionGroups[(y*mapWidth)+x] = 0;
            }
            else{
                auto &group = grouped[(mapWidth*y)+x];
                if (group.first.first==x && group.first.second==y)ids[group.first]=id++;
                collisionGroups[(y*mapWidth)+x] = ids[group.first];
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
    
    //! TODO: Insert else to do nothing
    if (Save() == level.Save()){ 
        return true;
    }
    return false;
}
