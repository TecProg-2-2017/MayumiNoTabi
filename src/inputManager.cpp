/*!
 *  File: inputManager.cpp
 *
 *  Description: Implements input manager
 */ 

#include <inputManager.hpp>
#include <assert.h>

/*!
 *  @fn InputManager::InputManager() 
 *  @brief Constructor method of Input Manager 
 *  @return An InputManager object
 */
InputManager::InputManager() {
    LOG_MSG("InputManager constructor");
    LOG_METHOD_CLOSE("InputManager::InputManager()","InputManager");
}

/*!
 *  @fn InputManager::~InputManager() 
 *  @brief Destructor method of Input Manager 
 */
InputManager::~InputManager() {
    LOG_MSG("InputManager destructor");
    LOG_METHOD_CLOSE("InputManager::~InputManager()","void");
}

/*!
 *  @fn void InputManager::update_mouse_button_state(SDL_Event event) 
 *  @brief Update mouse button current state 
 *  @param SDL_Event event
 *  @return The method returns no param
 */
void InputManager::update_mouse_button_state(SDL_Event event) {
    LOG_METHOD_START("InputManager::update_mouse_button_state");

    bool mouse_state = true; //! <Mouse button state
  

    if (event.type==SDL_MOUSEBUTTONDOWN) {
        mouse_state = true;
        LOG_VARIABLE("mouse_state","true");
    }

    else if (event.type==SDL_MOUSEBUTTONUP) {
        mouse_state = false;
        LOG_VARIABLE("mouse_state","false");
    }

    if (/*event.button.button>=0 && */event.button.button<6 && mouse_current_state[event.button.button]!=mouse_state) {
        mouse_updated_state[event.button.button]=update_counter;
        mouse_current_state[event.button.button]=mouse_state;
    }
    else {
        // Do nothing
    }

    LOG_METHOD_CLOSE("InputManager::update_mouse_button_state","void");

}

/*!
 *  @fn void InputManager::update_key_button_state(SDL_Event event) 
 *  @brief Update key button current state 
 *  @param SDL_Event event
 *  @return The method returns no param
 */
void InputManager::update_key_button_state(SDL_Event event) {
    LOG_METHOD_START("InputManager::update_key_button_state");

    bool key_state = true; //! <Key button state

    if (event.type == SDL_KEYDOWN) {
        key_state = true;

        LOG_VARIABLE("key_state","true");
    }
    else if (event.type == SDL_KEYUP) {
        key_state = false;

        LOG_VARIABLE("key_state","false");
    }
    else {
        // Do nothing 
    }

    key_current_state[event.key.keysym.sym]=key_state;
    key_updated_state[event.key.keysym.sym]=update_counter;

    LOG_METHOD_CLOSE("InputManager::update_key_button_state","void");
}

/*!
 *  @fn void InputManager::insert_text(SDL_Event event) 
 *  @brief Insert text to the text input 
 *  @param SDL_Event event
 *  @return The method returns no param
 */
void InputManager::insert_text(SDL_Event event) {
    LOG_METHOD_START("InputManager::insert_text");
    

    string input(event.text.text);
    LOG_VARIABLE("input", input);

    text->insert(text_cursor,input);
    text_cursor += input.size();

    LOG_METHOD_CLOSE("InputManager::insert_text","void");
}

/*!
 *  @fn void InputManager::erase_text(SDL_Event event) 
 *  @brief Erase text from text input 
 *  @param SDL_Event event
 *  @return The method returns no param
 */
void InputManager::erase_text(SDL_Event event) {
    LOG_METHOD_START("InputManager::erase_text");

    //! If event key is backspace and text is not empty
    if (event.key.keysym.sym == SDLK_BACKSPACE && 
            text->size() && text_cursor) {

        text->erase(--text_cursor,1);
        LOG_MSG("Text erased");

        if (text_cursor>text->size()) {
            text_cursor=text->size();
            assert(text_cursor <= text->size());
        }
        else {
            // Do nothing
        }
    }
    else {
        return;
    }
    LOG_METHOD_CLOSE("InputManager::erase_text","void");
}

/*!
 *  @fn void InputManager::input_event_handler(float time) 
 *  @brief Handle mouse and keyboard inputs  
 *  @param float time
 *  @return The method returns no param
 *  @warning Method maybe need refactoring
 */
void InputManager::input_event_handler(float time) {
    LOG_METHOD_START("InputManager::input_event_handler");

    int x_position = 0; //! <Horizontal axis position
    int y_position = 0; //! <Vertical axis position

    //! Get mouse position 
    SDL_GetMouseState(&x_position,&y_position);
    LOG_VARIABLE("x_position",x_position);
    LOG_VARIABLE("y_position",y_position);

    mouse_motion = (mouse_position.x!=x_position || mouse_position.y!=y_position);

    mouse_position.x = (float)x_position;
    mouse_position.y = (float)y_position;
    LOG_VARIABLE("mouse_position.x",mouse_position.x);
    LOG_VARIABLE("mouse_position.y",mouse_position.y);
    
    quit_requested=false;
    
    text_cursor_blinker.add_time(time);

    SDL_Event event;
    
    //! Iterate through SDL events
    while(SDL_PollEvent(&event)) {

        //! Event is quit
        if (event.type==SDL_QUIT) {
            LOG_MSG("Quit game event");
            quit_requested=true;
            LOG_VARIABLE("quit_requested",quit_requested);
        }

        //! Event is Mouse button down
        else if (event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP) {
            LOG_MSG("Mouse button down or up event");
            update_mouse_button_state(event);
        }
    
        //! Event is Key down 
        else if (event.type==SDL_KEYDOWN) {
            LOG_MSG("Key down event");

            if (!event.key.repeat) {
                update_key_button_state(event);
            }
            else {
                // Do nothing
            }
        }


        //! Event is Key up 
        else if (event.type==SDL_KEYUP) {
            LOG_MSG("Key up event");
            update_key_button_state(event);
        }
        
        //! If text is not empty    
        if (text != nullptr) {

            //! Event is text input
            if (event.type==SDL_TEXTINPUT) {
                LOG_MSG("Text input event");
                insert_text(event);
            }

           //! Event is key down when text is not empty 
            else if (event.type==SDL_KEYDOWN) {
                LOG_MSG("Key down event when handling text");
                text_cursor_blinker.Restart();

                erase_text(event);
                

                //! Move cursor to the left if left key is pressed 
                if (event.key.keysym.sym == SDLK_LEFT && text_cursor > 0) {
                    LOG_MSG("Move text cursor to the left");
                    text_cursor--;
                }

                //! Move cursor to the right if right key is pressed 
                else if (event.key.keysym.sym == SDLK_RIGHT && text_cursor < text->size()) {
                    LOG_MSG("Move text cursor to the right");
                    text_cursor++;
                }
            }//! <End of if which event is key down
        } //! <End of if which text is not empty
        else {
            // Do nothing
        }
    } //! <End of while which iteration through sdl events
    update_counter++;

    LOG_METHOD_CLOSE("InputManager::input_event_handler","void");
}

/*!
 *  @fn bool InputManager::key_pressed(int key) 
 *  @brief Check if the key was pressed 
 *  @param int key 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::key_pressed(int key) {
    LOG_METHOD_START("InputManager::key_pressed");
    LOG_METHOD_CLOSE("InputManager::key_pressed","bool");

    return (key_current_state[key] && key_updated_state[key]==update_counter-1);
}

/*!
 *  @fn bool InputManager::key_released(int key) 
 *  @brief Check if the key was released 
 *  @param int key 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::key_released(int key) {
    LOG_METHOD_START("InputManager::key_released");
    LOG_METHOD_CLOSE("InputManager::key_released","bool");

    return ((!key_current_state[key]) && key_updated_state[key]==update_counter-1);
}

/*!
 *  @fn bool InputManager::key_is_down(int key) 
 *  @brief Check if the key is down 
 *  @param int key 
 *  @return True of False 
 */
bool InputManager::key_is_down(int key) {
    LOG_METHOD_START("InputManager::key_is_down");
    LOG_METHOD_CLOSE("InputManager::key_is_down","bool");

    return (key_current_state[key]);
}

/*!
 *  @fn bool InputManager::mouse_button_pressed(int key) 
 *  @brief Check if the mouse button was pressed 
 *  @param int button 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::mouse_button_pressed(int button) {
    LOG_METHOD_START("InputManager::mouse_button_pressed");
    LOG_METHOD_CLOSE("InputManager::mouse_button_pressed","bool");

    return (mouse_current_state[button] && mouse_updated_state[button]==update_counter-1);
}

/*!
 *  @fn bool InputManager::mouse_button_released(int button) 
 *  @brief Check if the mouse button was released 
 *  @param int button 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::mouse_button_released(int button) {
    LOG_METHOD_START("InputManager::mouse_button_released");
    LOG_METHOD_CLOSE("InputManager::mouse_button_released","bool");

    return ((!mouse_current_state[button]) && mouse_updated_state[button]==update_counter-1);
}

/*!
 *  @fn bool InputManager::mouse_button_is_down(int button) 
 *  @brief Check if the mouse button is down 
 *  @param int button 
 *  @return True of False 
 */
bool InputManager::mouse_button_is_down(int button) {
    LOG_METHOD_START("InputManager::mouse_button_is_down");
    LOG_METHOD_CLOSE("InputManager::mouse_button_is_down","bool");

    return (mouse_current_state[button]);
}

/*!
 *  @fn bool InputManager::mouse_is_moving() 
 *  @brief Check if the mouse button is moving 
 *  @return True of False 
 */
bool InputManager::mouse_is_moving() {
    LOG_METHOD_START("InputManager::mouse_is_moving");
    LOG_METHOD_CLOSE("InputManager::mouse_is_moving","bool");

    return mouse_is_moving;
}

/*!
 *  @fn Vec2 InputManager::get_mouse_position() 
 *  @brief Get X and Y position of player's mouse 
 *  @return Vec2 
 */
Vec2 InputManager::get_mouse_position() {
    LOG_METHOD_START("InputManager::get_mouse_position");
    LOG_METHOD_CLOSE("InputManager::get_mouse_position","Vec2");

    return mouse_position;
}

/*!
 *  @fn int InputManager::get_mouse_x_position() 
 *  @brief Get horizontal position of player's mouse 
 *  @return integer 
 */
int InputManager::get_mouse_x_position() {
    LOG_METHOD_START("InputManager::get_mouse_x_position");
    LOG_METHOD_CLOSE("InputManager::get_mouse_x_position","int");

    return mouse_position.x;
}

/*!
 *  @fn int InputManager::get_mouse_y_position() 
 *  @brief Get vertical position of player's mouse 
 *  @return integer 
 */
int InputManager::get_mouse_y_position() {
    LOG_METHOD_START("InputManager::get_mouse_y_position");
    LOG_METHOD_CLOSE("InputManager::get_mouse_y_position","int");

    return mouse_position.y;
}

/*!
 *  @fn void InputManager::start_text_input(string* t) 
 *  @brief Start text input for player 
 *  @param string* t
 *  @return The method returns no param
 */
void InputManager::start_text_input(string* t) {
    LOG_METHOD_START("InputManager::start_text_input");

    //! If param is empty, returns
    if (t == nullptr) { 
        return;
    }
    else {
        // Do nothing
    }

    SDL_StartTextInput();
    text = t;
    text_cursor = text->size();
    text_cursor_blinker.restart_time();

    LOG_METHOD_CLOSE("InputManager::start_text_input","void");
}

/*!
 *  @fn void InputManager::stop_text_input(string* t) 
 *  @brief Stop text input for player 
 *  @param string* t
 *  @return The method returns no param
 */
void InputManager::stop_text_input(string* t) {
    LOG_METHOD_START("InputManager::stop_text_input");
    
    //! If class attribute text is different from param, returns
    if (text != t) {
        return;
    }
    else {
        // Do nothing
    }
    
    text = nullptr;
    SDL_StopTextInput();

    LOG_METHOD_CLOSE("InputManager::stop_text_input","void");
}

/*!
 *  @fn unsigned int InputManager::get_text_cursor_position()
 *  @brief Get text cursor position 
 *  @return unsigned integer 
 */
uint InputManager::get_text_cursor_position() {
    LOG_METHOD_START("InputManager::get_text_cursor_position");
    LOG_METHOD_CLOSE("InputManager::get_text_cursor_position","uint");

    return text_cursor;
}

/*!
 *  @fn bool InputManager::text_cursor_blink()
 *  @brief Make text cursor blink 
 *  @return True or false 
 *  @warning Simplify method return
 */
bool InputManager::text_cursor_blink() {
    LOG_METHOD_START("InputManager::text_cursor_blink");
    LOG_METHOD_CLOSE("InputManager::text_cursor_blink","bool");

    return !((int)(text_cursor_blinker.get_time()/0.5)%2);
}

/*!
 *  @fn bool InputManager::get_quit_requested()
 *  @brief Get quit_requested value  
 *  @return True or false 
 */
bool InputManager::get_quit_requested() {
    LOG_METHOD_START("InputManager::get_quit_requested");
    LOG_METHOD_CLOSE("InputManager::get_quit_requested","bool");

    return quit_requested;
}

/*!
 *  @fn InputManager& InputManager::get_input_manager_instance() 
 *  @brief Get InputManager instance 
 *  @return InputManager 
 */
InputManager& InputManager::get_input_manager_instance() {
    LOG_METHOD_START("InputManager& InputManager::get_input_manager_instance");

    static InputManager uniqueInst;

    LOG_METHOD_CLOSE("InputManager& InputManager::get_input_manager_instance", "InputManager");
    return uniqueInst;
}
