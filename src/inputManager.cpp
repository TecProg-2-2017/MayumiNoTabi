/*!
 *  File: inputManager.cpp
 *
 *  Description: Implements input manager
 */ 

#include <inputManager.hpp>

/*!
 *  @fn InputManager::InputManager() 
 *  @brief Constructor method of Input Manager 
 *  @return An InputManager object
 */
InputManager::InputManager() {

}

/*!
 *  @fn InputManager::~InputManager() 
 *  @brief Destructor method of Input Manager 
 */
InputManager::~InputManager() {

}

/*!
 *  @fn void InputManager::Update(float time) 
 *  @brief Handle mouse and keyboard inputs  
 *  @param float time
 *  @return The method returns no param
 *  @warning Method maybe need refactoring
 */
void InputManager::update(float time) {
    int x,y; //! <Horizontal axis position, Vertical axis position

    //! Get mouse position 
    SDL_GetMouseState(&x,&y);
    mouseMotion = (mouse.x!=x || mouse.y!=y);
    mouse.x = (float)x;
    mouse.y = (float)y;
    quitRequested=false;
    
    cursorBlinker.add_time(time);

    SDL_Event event;
    
    //! Iterate through SDL events
    while(SDL_PollEvent(&event)) {

        //! Event is quit
        if (event.type==SDL_QUIT) {
            quitRequested=true;
        }

        //! Event is Mouse button down
        else if (event.type==SDL_MOUSEBUTTONDOWN) {

            //! TODO: Insert else to do nothing
            if (/*event.button.button>=0 && */event.button.button<6 && mouseState[event.button.button]!=true) {
                mouseUpdate[event.button.button]=updateCounter;
                mouseState[event.button.button]=true;
            }
        }
        
        //! Event is Mouse button up 
        else if (event.type==SDL_MOUSEBUTTONUP) {

            //! TODO: Insert else to do nothing
            if (/*event.button.button>=0 && */event.button.button<6 && mouseState[event.button.button]!=false) {
                mouseUpdate[event.button.button]=updateCounter;
                mouseState[event.button.button]=false;
            }
        }
    
        //! Event is Key down 
        else if (event.type==SDL_KEYDOWN) {

            //! TODO: Insert else to do nothing
            if (!event.key.repeat) {
                keyState[event.key.keysym.sym]=true;
                keyUpdate[event.key.keysym.sym]=updateCounter;
            }
        }


        //! Event is Key up 
        else if (event.type==SDL_KEYUP) {
            keyState[event.key.keysym.sym]=false;
            keyUpdate[event.key.keysym.sym]=updateCounter;
        }
        
        //! If text is not empty    
        //! TODO: Insert else to do nothing
        if (text != nullptr) {

            //! Event is text input
            if (event.type==SDL_TEXTINPUT) {
                string input(event.text.text);
                text->insert(cursor,input);
                cursor += input.size();
            }

           //! Event is key down 
            else if (event.type==SDL_KEYDOWN) {
                cursorBlinker.Restart();

                //! If event key is backspace and text is not empty
                if (event.key.keysym.sym == SDLK_BACKSPACE && 
                        text->size() && cursor) {

                    text->erase(--cursor,1);

                    //! TODO: Insert else to do nothing
                    if (cursor>text->size()) {
                        cursor=text->size();
                    }
                }

                //! Move cursor to the left if left key is pressed 
                else if (event.key.keysym.sym == SDLK_LEFT && cursor > 0) {
                    cursor--;
                }

                //! Move cursor to the right if right key is pressed 
                else if (event.key.keysym.sym == SDLK_RIGHT && cursor < text->size()) {
                    cursor++;
                }
            }//! <End of if which event is key down
        } //! <End of if which text is not empty
    } //! <End of while which iteration through sdl events
    updateCounter++;
}

/*!
 *  @fn bool InputManager::KeyPress(int key) 
 *  @brief Check if the key was pressed 
 *  @param int key 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::KeyPress(int key) {
    return (keyState[key] && keyUpdate[key]==updateCounter-1);
}

/*!
 *  @fn bool InputManager::KeyRelease(int key) 
 *  @brief Check if the key was released 
 *  @param int key 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::KeyRelease(int key) {
    return ((!keyState[key]) && keyUpdate[key]==updateCounter-1);
}

/*!
 *  @fn bool InputManager::IsKeyDown(int key) 
 *  @brief Check if the key is down 
 *  @param int key 
 *  @return True of False 
 */
bool InputManager::IsKeyDown(int key) {
    return (keyState[key]);
}

/*!
 *  @fn bool InputManager::KeyRelease(int key) 
 *  @brief Check if the key was released 
 *  @param int key 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::MousePress(int button) {
    return (mouseState[button] && mouseUpdate[button]==updateCounter-1);
}

/*!
 *  @fn bool InputManager::MouseRelease(int button) 
 *  @brief Check if the mouse button was released 
 *  @param int button 
 *  @return True of False 
 *  @warning Simplify return 
 */
bool InputManager::MouseRelease(int button) {
    return ((!mouseState[button]) && mouseUpdate[button]==updateCounter-1);
}

/*!
 *  @fn bool InputManager::IsMouseDown(int button) 
 *  @brief Check if the mouse button is down 
 *  @param int button 
 *  @return True of False 
 */
bool InputManager::IsMouseDown(int button) {
    return (mouseState[button]);
}

/*!
 *  @fn bool InputManager::IsMouseMoving() 
 *  @brief Check if the mouse button is moving 
 *  @return True of False 
 */
bool InputManager::IsMouseMoving() {
    return mouseMotion;
}

/*!
 *  @fn Vec2 InputManager::GetMouse() 
 *  @brief Get X and Y position of player's mouse 
 *  @return Vec2 
 */
Vec2 InputManager::GetMouse() {
    return mouse;
}

/*!
 *  @fn int InputManager::GetMouseX() 
 *  @brief Get horizontal position of player's mouse 
 *  @return integer 
 */
int InputManager::GetMouseX() {
    return mouse.x;
}

/*!
 *  @fn int InputManager::GetMouseY() 
 *  @brief Get vertical position of player's mouse 
 *  @return integer 
 */
int InputManager::GetMouseY() {
    return mouse.y;
}

/*!
 *  @fn void InputManager::StartTextInput(string* t) 
 *  @brief Start text input for player 
 *  @param string* t
 *  @return The method returns no param
 */
void InputManager::StartTextInput(string* t) {

    //! If param is empty, returns
    //! TODO: Insert else to do nothing
    if (t == nullptr) { 
        return;
    }

    SDL_StartTextInput();
    text = t;
    cursor = text->size();
    cursorBlinker.restart_time();
}

/*!
 *  @fn void InputManager::StopTextInput(string* t) 
 *  @brief Stop text input for player 
 *  @param string* t
 *  @return The method returns no param
 */
void InputManager::StopTextInput(string* t) {
    
    //! If class attribute text is different from param, returns
    //! TODO: Insert else to do nothing
    if (text != t) {
        return;
    }
    text = nullptr;
    SDL_StopTextInput();
}

/*!
 *  @fn unsigned int InputManager::GetTextCursor()
 *  @brief Get text cursor position 
 *  @return unsigned integer 
 */
uint InputManager::GetTextCursor() {
    return cursor;
}

/*!
 *  @fn bool InputManager::TextCursorBlink()
 *  @brief Make text cursor blink 
 *  @return True or false 
 *  @warning Simplify method return
 */
bool InputManager::TextCursorBlink() {
    return !((int)(cursorBlinker.get_time()/0.5)%2);
}

/*!
 *  @fn bool InputManager::QuitRequested()
 *  @brief Get quitRequested value  
 *  @return True or false 
 */
bool InputManager::QuitRequested() {
    return quitRequested;
}

/*!
 *  @fn InputManager& InputManager::GetInstance() 
 *  @brief Get InputManager instance 
 *  @return InputManager 
 */
InputManager& InputManager::GetInstance() {
    static InputManager uniqueInst;
    return uniqueInst;
}
