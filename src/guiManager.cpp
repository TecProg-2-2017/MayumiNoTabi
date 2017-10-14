/*!
 *  File: guiManager.cpp
 *
 *  Description: Implements gui manager
 */ 

#include <guiManager.hpp>
#include <gui.hpp>
#include <inputManager.hpp>

/*!
 *  @fn GUIManager::GUIManager()
 *  @brief Constructor method for general user interface
 *  @return A GUIManager object
 */
GUIManager::GUIManager() {

}

/*!
 *  @fn GUIManager::~GUIManager()
 *  @brief Destructor method for general user interface
 */
GUIManager::~GUIManager() {
    gui_elements.clear();
}

/*!
 *  @fn void GUIManager::remove_last_gui_element_requested()
 *  @brief Remove last element if requested
 *  @return The method returns no param
 */
void GUIManager::remove_last_gui_element_requested() {

    //! Remove last element if requested
    if (element_pop_requested) {
        selected_gui_window = nullptr;
        selected_gui_button = nullptr;

        gui_elements.pop_back();
    }
    else {
        // Do nothing
    }
}
/*!
 *  @fn void GUIManager::reset_gui_button()
 *  @brief Reset the button if it is selected 
 *  @return The method returns no param
 */
void GUIManager::reset_gui_button() {
    
    //! Reset the button if it is selected 
    if (selected_gui_button) {
        selected_gui_button->Reset();
        selected_gui_button = nullptr;
    }
    else {
        // Do nothing
    }
}

/*!
 *  @fn void GUIManager::add_stored_element_to_gui()
 *  @brief If there's element stored puts it in gui elements vector
 *  @return The method returns no param
 */
void GUIManager::add_stored_element_to_gui() {
    
    //! If there's element stored puts it in gui elements vector
    if (stored_gui_element) {
        selected_gui_window = nullptr;

        reset_gui_button();

        gui_elements.emplace_back(unique_ptr<GUI_Element>(stored_gui_element));
        stored_gui_element = nullptr;
    }
    else {
        // Do nothing
    }
}

/*!
 *  @fn void GUIManager::assing_pressed_button_to_current()
 *  @brief Check if current button is pressed and assings it to current_button_state
 *  @return The method returns no param
 */
void GUIManager::assing_pressed_button_to_current() {
    
    //! Check if current button is pressed and assings it to current_button_state
    if (selected_gui_button) {
        GUI_Button* selected_gui_buttonCopy = selected_gui_button;

        selected_gui_button = nullptr;

        selected_gui_buttonCopy->Update();
        selected_gui_button = selected_gui_buttonCopy;
        current_button_state = selected_gui_button->IsPressed();
    }
    else {
        // Do nothing
    }
}

/*!
 *  @fn void GUIManager::update_gui_elements()
 *  @brief Updates general user interface
 *  @return The method returns no param
 */
void GUIManager::update_gui_elements() {

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
   
    gui_elements.back()->Update();  
}

/*!
 *  @fn void GUIManager::render_gui_elements()
 *  @brief Renders general user interface
 *  @return The method returns no param
 */
void GUIManager::render_gui_elements() {
    
    //! Iterates trough elements of interface to render it
    for (auto& it:gui_elements){

        //! If elements is visible renders it
        if (it->IsVisible()){
            it->Render();
        }
        else {
            // Do nothing
        }
    }
}
 
/*!
 *  @fn void GUIManager::push_gui_element(GUI_Element* element)
 *  @brief Push element to the general user interface 
 *  @param GUI_Element* element
 *  @return The method returns no param
 */
void GUIManager::push_gui_element(GUI_Element* element) {

    //! Checks if there's an element alredy stored, and deletes it
    if (stored_gui_element) { 
        delete stored_gui_element;
    }
    else {
        // Do nothing
    }

    stored_gui_element = element;
}

/*!
 *  @fn void GUIManager::request_gui_element_pop(GUI_Element* element)
 *  @brief Changes element_pop_requested value if requested  
 *  @param GUI_Element* element
 *  @return The method returns no param
 */
void GUIManager::request_gui_element_pop(GUI_Element* element) {
   
    //! If last object of elements vector is equal to the param
    //! Change element_pop_requested value
    if (element == gui_elements.back().get()) {
        element_pop_requested = true;
    }
    else {
        // Do nothing
    }
}

/*!
 *  @fn void GUIManager::select_gui_window(GUI_Window* window)
 *  @brief Select window in the general user interface
 *  @param GUI_Window* window
 *  @return The method returns no param
 */
void GUIManager::select_gui_window(GUI_Window* window) {
    selected_gui_window = window;
}

/*!
 *  @fn bool GUIManager::gui_window_is_selected(GUI_Window* window)const 
 *  @brief Return if window is select 
 *  @param GUI_Window* window
 *  @return true of false 
 */
bool GUIManager::gui_window_is_selected(GUI_Window* window)const {
    return window==selected_gui_window;
}

/*!
 *  @fn int GUIManager::get_gui_selected_window_ID()const 
 *  @brief Get selected window ID of general user interface
 *  @return integer 
 */
int GUIManager::get_gui_selected_window_ID()const {

    //If there's a window selected, returns it ID
    if (selected_gui_window){
        return selected_gui_window->id;
    }
    else if (gui_elements.size() == 1) { 
        return 0;
    }
    else {
        return -1;
    }
}

/*!
 *  @fn void GUIManager::select_gui_button(GUI_Button* button) 
 *  @brief Assing button object to selected_gui_button attribute
 *  @param GUI_Button* button
 *  @return The method returns no param
 */
void GUIManager::select_gui_button(GUI_Button* button) {
    selected_gui_button = button;
}

/*!
 *  @fn bool GUIManager::gui_button_is_selected(GUI_Button* button)const   
 *  @brief Avaliate if button is selected 
 *  @param GUI_Button* button
 *  @return True of False 
 */
bool GUIManager::gui_button_is_selected(GUI_Button* button)const{
    return button && button==selected_gui_button;
}

/*!
 *  @fn bool GUIManager::selected_button_is_empty()
 *  @brief Avaliate if button is empty 
 *  @return True of False 
 */
bool GUIManager::selected_button_is_empty() {
    
    //! Return false for empty selected_gui_button
    if (!selected_gui_button) {
        return true;
    }
    else {
        return false;
    }
}

/*!
 *  @fn bool GUIManager::selected_button_is_empty()
 *  @brief Avaliate if button action is different from the param 
 *  @param uint action
 *  @return True of False 
 */
bool GUIManager::is_button_action_different(uint action) {
    
    //! Return false for action different from the selected button 
    if (action && selected_gui_button->action != action) {
        return true;
    }
    else {
        return false;
    }
}

/*!
 *  @fn bool GUIManager::gui_button_was_pressed(uint action)const    
 *  @brief Avaliate if button was pressed 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_pressed(uint action)const{

    if(selected_button_is_empty() || is_button_action_different(action)) {
        return false
    }
    else {
        return (!previous_button_state && current_button_state);
    }
}

/*!
 *  @fn bool GUIManager::gui_button_was_released(uint action)const    
 *  @brief Avaliate if button was released 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_released(uint action)const{

    if(selected_button_is_empty() || is_button_action_different(action)) {
        return false
    }
    else {
        return (previous_button_state && !current_button_state);
    }
}

/*!
 *  @fn bool GUIManager::gui_button_was_clicked(uint action)const    
 *  @brief Avaliate if button was clicked 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_clicked(uint action)const{

    if(selected_button_is_empty() || is_button_action_different(action)) {
        return false
    }
    else {
        return (previous_button_state && !current_button_state && selected_gui_button->IsHovered());
    }
}

/*!
 *  @fn bool GUIManager::gui_button_is_down(uint action)const    
 *  @brief Avaliate if button is down 
 *  @param unsigned int action 
 *  @return True of False 
 */
bool GUIManager::gui_button_is_down(uint action)const{

    if(selected_button_is_empty() || is_button_action_different(action)) {
        return false
    }
    else {
        return current_button_state;
    }
}
