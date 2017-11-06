#ifndef INPUTMANAGERHPP
#define INPUTMANAGERHPP

#include <common.hpp>

#include <geometry.hpp>
#include <timer.hpp>

#define KEY_LEFT        SDLK_LEFT
#define KEY_RIGHT       SDLK_RIGHT
#define KEY_UP          SDLK_UP
#define KEY_DOWN        SDLK_DOWN
#define KEY_ESC         SDLK_ESCAPE
#define KEY_SPACE       SDLK_SPACE
#define KEY_ENTER       SDLK_RETURN

#define KEY_F(x)        SDLK_F ## x
#define KEY(x)          SDLK_ ## x

#define MBUTTON_LEFT    SDL_BUTTON_LEFT
#define MBUTTON_RIGHT   SDL_BUTTON_RIGHT
#define MBUTTON_MIDDLE  SDL_BUTTON_MIDDLE

#define INPUT InputManager::get_input_manager_instance()
#define MOUSE INPUT.get_mouse_position()

class InputManager{
    bitset<6> mouse_current_state;//vetor de 6 booleanos //bitset ocupa o menor numero de bytes possivel(char para < 8 bits)
    array<int,6> mouse_updated_state;
    unordered_map<int,bool> key_current_state;
    unordered_map<int,int>  key_updated_state;
    int update_counter=0;
    Vec2 mouse_position;
    bool mouse_motion;

    string* text=nullptr;
    uint text_cursor;
    Timer text_cursor_blinker;
    //uint selection_len; //unused

    bool quit_requested=false;

    InputManager();
    ~InputManager();
public:

    void input_event_handler(float time);

    bool key_pressed(int key);
    bool key_released(int key);
    bool key_is_down(int key);

    bool mouse_button_pressed(int button);
    bool mouse_button_released(int button);
    bool mouse_button_is_down(int button);
    bool mouse_is_moving();

    Vec2 get_mouse_position();
    int get_mouse_x_position();
    int get_mouse_y_position();

    void update_mouse_button_state(SDL_Event event);
    void update_key_button_state(SDL_Event event);
    void insert_text(SDL_Event event);
    void erase_text(SDL_Event event);

    void start_text_input(string* t);
    void stop_text_input(string* t);
    uint get_text_cursor_position();
    bool text_cursor_blink();


    bool get_quit_requested();

    static InputManager& get_input_manager_instance();

};

#endif//INPUTMANAGERHPP
