/*!
 *  File: guiManager.cpp
 *
 *  Description: Implements gui manager
 */ 

#include <guiManager.hpp>
#include <gui.hpp>
#include <inputManager.hpp>
#include <assert.h>

/*!
 *  @fn GUIManager::GUIManager()
 *  @brief Constructor method for general user interface
 *  @return A GUIManager object
 */
GUIManager::GUIManager() {
    LOG_MSG("GUIManager constructor");
    LOG_METHOD_CLOSE("GUIManager::GUIManager()","GUIManager");
}

/*!
 *  @fn GUIManager::~GUIManager()
 *  @brief Destructor method for general user interface
 */
GUIManager::~GUIManager() {
    LOG_MSG("GUIManager destructor");
    gui_elements.clear();
    LOG_METHOD_CLOSE("GUIManager::~GUIManager()","void");
}

/*!
 *  @fn void GUIManager::update_gui_elements()
 *  @brief Updates general user interface
 *  @return The method returns no param
 */
void GUIManager::update_gui_elements() {
    LOG_METHOD_START("GUIManager::update_gui_elements");

    remove_last_gui_element_requested();

    add_stored_element_to_gui();

    //! If there's no elements in the gui, returns 
    if (gui_elements.empty()) {
         return;
    }
    else {
        // Do nothing
    }
    
    element_pop_requested = false;
    
    previous_button_state = current_button_state;

    assing_pressed_button_to_current(); 
   
    gui_elements.back()->update();  

    LOG_METHOD_CLOSE("GUIManager::update_gui_elements","void");
}

/*!
 *  @fn void GUIManager::render_gui_elements()
 *  @brief Renders general user interface
 *  @return The method returns no param
 */
void GUIManager::render_gui_elements() {
    LOG_METHOD_START("GUIManager::render_gui_elements");
    
    //! Iterates trough elements of interface to render it
    for (auto& it:gui_elements){

        //! If elements is visible renders it
        if (it->IsVisible()){
            LOG_MSG("Render gui element");
            it->render();
        }
        else {
            // Do nothing
        }
    }
    LOG_METHOD_CLOSE("GUIManager::render_gui_elements","void");
}

/*!
 *  @fn void GUIManager::remove_last_gui_element_requested()
 *  @brief Remove last element if requested
 *  @return The method returns no param
 */
void GUIManager::remove_last_gui_element_requested() {
    LOG_METHOD_START("GUIManager::remove_last_gui_element_requested");

    //! Remove last element if requested
    if (element_pop_requested) {
        selected_gui_window = nullptr;
        selected_gui_button = nullptr;
        
        LOG_MSG("Pop gui element back");
        gui_elements.pop_back();
    }
    else {
        // Do nothing
    }
    LOG_METHOD_CLOSE("GUIManager::remove_last_gui_element_requested", "void");
}

/*!
 *  @fn void GUIManager::reset_gui_button()
 *  @brief Reset the button if it is selected 
 *  @return The method returns no param
 */
void GUIManager::reset_gui_button() {
    LOG_METHOD_START("GUIManager::reset_gui_button");

    //! Reset the button if it is selected 
    if (selected_gui_button) {
        assert(selected_gui_button != NULL);

        LOG_MSG("Reset gui button");
        selected_gui_button->Reset();
        selected_gui_button = nullptr;
    }
    else {
        // Do nothing
    }
    LOG_METHOD_CLOSE("GUIManager::reset_gui_button","void");
}

/*!
 *  @fn void GUIManager::add_stored_element_to_gui()
 *  @brief If there's element stored puts it in gui elements vector
 *  @return The method returns no param
 */
void GUIManager::add_stored_element_to_gui() {
    LOG_METHOD_START("GUIManager::add_stored_element_to_gui");
    
    //! If there's element stored puts it in gui elements vector
    if (stored_gui_element) {
        assert(stored_gui_element != NULL);

        selected_gui_window = nullptr;

        reset_gui_button();

        gui_elements.emplace_back(unique_ptr<GUI_Element>(stored_gui_element));
        stored_gui_element = nullptr;
    }
    else {
        // Do nothing
    }
    LOG_METHOD_CLOSE("GUIManager::add_stored_element_to_gui","void");
}

/*!
 *  @fn void GUIManager::assing_pressed_button_to_current()
 *  @brief Check if current button is pressed and assings it to current_button_state
 *  @return The method returns no param
 */
void GUIManager::assing_pressed_button_to_current() {
    LOG_METHOD_START("GUIManager::assing_pressed_button_to_current");
    
    //! Check if current button is pressed and assings it to current_button_state
    if (selected_gui_button) {
        GUI_Button* selected_gui_buttonCopy = selected_gui_button;

        assert(selected_gui_buttonCopy != NULL); 

        selected_gui_button = nullptr;

        selected_gui_buttonCopy->update();
        selected_gui_button = selected_gui_buttonCopy;

        current_button_state = selected_gui_button->IsPressed();
        LOG_VARIABLE("current_button_state",current_button_state);
    }
    else {
        // Do nothing
    }
    LOG_METHOD_CLOSE("GUIManager::assing_pressed_button_to_current","void");
}

/*!
 *  @fn void GUIManager::push_gui_element(GUI_Element* element)
 *  @brief Push element to the general user interface 
 *  @param GUI_Element* element
 *  @return The method returns no param
 */
void GUIManager::push_gui_element(GUI_Element* element) {
    LOG_METHOD_START("GUIManager::push_gui_element");

    //! Checks if there's an element alredy stored, and deletes it
    if (stored_gui_element) { 
        LOG_MSG("Delete stored gui element");
        delete stored_gui_element;

        assert(stored_gui_element == NULL);
    }
    else {
        // Do nothing
    }

    stored_gui_element = element;
    LOG_METHOD_CLOSE("GUIManager::push_gui_element","void");
}

/*!
 *  @fn void GUIManager::request_gui_element_pop(GUI_Element* element)
 *  @brief Changes element_pop_requested value if requested  
 *  @param GUI_Element* element
 *  @return The method returns no param
 */
void GUIManager::request_gui_element_pop(GUI_Element* element) {
    LOG_METHOD_START("GUIManager::request_gui_element_pop");
   
    //! If last object of elements vector is equal to the param
    //! Change element_pop_requested value
    if (element == gui_elements.back().get()) {
        element_pop_requested = true;
    }
    else {
        // Do nothing
    }
    LOG_METHOD_CLOSE("GUIManager::request_gui_element_pop","void");
}

/*!
 *  @fn void GUIManager::select_gui_window(GUI_Window* window)
 *  @brief Select window in the general user interface
 *  @param GUI_Window* window
 *  @return The method returns no param
 */
void GUIManager::select_gui_window(GUI_Window* window) {
    LOG_METHOD_START("GUIManager::select_gui_window");

    assert(window != NULL);
    selected_gui_window = window;

    LOG_METHOD_CLOSE("GUIManager::select_gui_window","void");
}

/*!
 *  @fn bool GUIManager::gui_window_is_selected(GUI_Window* window)const 
 *  @brief Return if window is select 
 *  @param GUI_Window* window
 *  @return true of false 
 */
bool GUIManager::gui_window_is_selected(GUI_Window* window)const {
    LOG_METHOD_START("GUIManager::gui_window_is_selected");
    
    assert(window != NULL);
    
    bool window_selected = (window == selected_gui_window);
    assert(window_selected == true || window_selected == false);

    return window_selected; 

    LOG_METHOD_CLOSE("GUIManager::gui_window_is_selected","void");
}

/*!
 *  @fn int GUIManager::get_gui_selected_window_ID()const 
 *  @brief Get selected window ID of general user interface
 *  @return integer 
 */
int GUIManager::get_gui_selected_window_ID()const {
    LOG_METHOD_START("GUIManager::get_gui_selected_window_ID");
    
    int window_id = 0;
    //If there's a window selected, returns it ID
    if (selected_gui_window){
        window_id = selected_gui_window->id;
    }
    else if (gui_elements.size() == 1) { 
        window_id = 0;
    }
    else {
        window_id = -1;
    }

    assert(window_id >= -1);

    return window_id;
    LOG_METHOD_CLOSE("GUIManager::get_gui_selected_window_ID","void");
}

/*!
 *  @fn void GUIManager::select_gui_button(GUI_Button* button) 
 *  @brief Assing button object to selected_gui_button attribute
 *  @param GUI_Button* button
 *  @return The method returns no param
 */
void GUIManager::select_gui_button(GUI_Button* button) {
    LOG_METHOD_START("GUIManager::select_gui_button");

    assert(button!= NULL);
    selected_gui_button = button;

    LOG_METHOD_CLOSE("GUIManager::select_gui_button","void");
}

/*!
 *  @fn bool GUIManager::gui_button_is_selected(GUI_Button* button)const   
 *  @brief Avaliate if button is selected 
 *  @param GUI_Button* button
 *  @return True of False 
 */
bool GUIManager::gui_button_is_selected(GUI_Button* button)const{
    LOG_METHOD_START("GUIManager::gui_button_is_selected");

    assert(button!= NULL);

    LOG_METHOD_CLOSE("GUIManager::gui_button_is_selected","bool");
    bool button_selected = (button && button==selected_gui_button);

    assert(button_selected == true || button_selected == false);

    return button_selected; 
}

/*!
 *  @fn bool GUIManager::gui_button_was_pressed(uint action)const    
 *  @brief Avaliate if button was pressed 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_pressed(uint action)const{
    LOG_METHOD_START("GUIManager::gui_button_was_pressed");

    bool button_pressed;

    if(selected_button_is_empty() || is_button_action_different(action)) {
        LOG_MSG("Gui button was not pressed");
        button_pressed = false;
    }
    else {
        button_pressed = (!previous_button_state && current_button_state);
    }
    assert(button_pressed == true || button_pressed == false);

    LOG_METHOD_CLOSE("GUIManager::gui_button_was_pressed","bool");

    return button_pressed;
}

/*!
 *  @fn bool GUIManager::gui_button_was_released(uint action)const    
 *  @brief Avaliate if button was released 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_released(uint action)const{
    LOG_METHOD_START("GUIManager::gui_button_was_released");
    
    bool button_released;

    if(selected_button_is_empty() || is_button_action_different(action)) {
        LOG_MSG("Gui button was not released");

        button_released = false;
    }
    else {
        LOG_MSG("Gui button was released");

        button_released = (previous_button_state && !current_button_state);
    }
    assert(button_released == true || button_released == false);

    LOG_METHOD_CLOSE("GUIManager::gui_button_was_released","bool");
    
    return button_released;
}

/*!
 *  @fn bool GUIManager::gui_button_was_clicked(uint action)const    
 *  @brief Avaliate if button was clicked 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_clicked(uint action)const{
    LOG_METHOD_START("GUIManager::gui_button_was_clicked");

    bool button_clicked;

    if(selected_button_is_empty() || is_button_action_different(action)) {
        LOG_MSG("Gui button was not clicked");
        button_clicked = false;
    }
    else {
        LOG_MSG("Gui button was clicked");
        button_clicked = (previous_button_state && !current_button_state && selected_gui_button->IsHovered());
    }
    assert(button_clicked == true || button_clicked == false); 

    LOG_METHOD_CLOSE("GUIManager::gui_button_was_clicked","bool");

    return button_clicked;
}

/*!
 *  @fn bool GUIManager::selected_button_is_empty()
 *  @brief Avaliate if button is empty 
 *  @return True of False 
 */
bool GUIManager::selected_button_is_empty()const {
    LOG_METHOD_START("GUIManager::selected_button_is_empty");
    
    bool button_empty;
    
    //! Return false for empty selected_gui_button
    if (!selected_gui_button) {
        LOG_MSG("Selected gui button is empty");
        button_empty = true;
    }
    else {
        LOG_MSG("Selected gui button is not empty");
        button_empty = false;
    }
    
    assert(button_empty == true || button_empty == false);

    LOG_METHOD_CLOSE("GUIManager::selected_button_is_empty","bool");

    return button_empty;
}

/*!
 *  @fn bool GUIManager::selected_button_is_empty()
 *  @brief Avaliate if button action is different from the param 
 *  @param uint action
 *  @return True of False 
 */
bool GUIManager::is_button_action_different(uint action)const {
    LOG_METHOD_START("GUIManager::is_button_action_different");
    
    bool action_different;
    
    //! Return false for action different from the selected button 
    if (action && selected_gui_button->action != action) {
        LOG_MSG("Selected gui button action is different");
        action_different = true;
    }
    else {
        LOG_MSG("Selected gui button action is not different");
        action_different = false;
    }
    assert(action_different == true || action_different == false);

    LOG_METHOD_CLOSE("GUIManager::is_button_action_different","bool");
    
    return action_different;
}

/*!
 *  @fn bool GUIManager::gui_button_is_down(uint action)const    
 *  @brief Avaliate if button is down 
 *  @param unsigned int action 
 *  @return True of False 
 */
bool GUIManager::gui_button_is_down(uint action)const{
    LOG_METHOD_START("GUIManager::gui_button_is_down");
    
    bool button_down;

    if(selected_button_is_empty() || is_button_action_different(action)) {
        LOG_MSG("Gui button is not down");

        button_down = false;
    }
    else {
        LOG_MSG("Gui button is down");

        button_down = current_button_state;
    }
    assert(button_down == true || button_down == false);

    LOG_METHOD_CLOSE("GUIManager::gui_button_is_down","bool");
    
    return button_down;
}
