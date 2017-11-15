/*!
 *  File: guiManager.cpp
 *
 *  Description: Implements gui manager
 */

#include <guiManager.hpp>
#include <gui.hpp>
#include <inputManager.hpp>
#include <assert.h>

/**
  Prototypes from guiManeger's methods.
*/

GUIManager::GUIManager();
GUIManager::~GUIManager();
void GUIManager::update_gui_elements();
void GUIManager::render_gui_elements();
void GUIManager::push_gui_element(GUI_Element* element);
void GUIManager::request_gui_element_pop(GUI_Element* element);
void GUIManager::select_gui_window(GUI_Window* window);
bool GUIManager::gui_window_is_selected(GUI_Window* window);
int GUIManager::get_gui_selected_window_ID();
void GUIManager::select_gui_button(GUI_Button* button);
bool GUIManager::gui_button_is_selected(GUI_Button* button);
bool GUIManager::gui_button_was_pressed(uint action);
bool GUIManager::gui_button_was_released(uint action);
bool GUIManager::gui_button_was_clicked(uint action);
bool GUIManager::gui_button_is_down(uint action);


/*!
 *  @fn GUIManager::GUIManager()
 *  @brief Constructor method for general user interface
 *  @return A GUIManager object
 */
GUIManager::GUIManager() {
  LOG_METHOD_START("GUIManager::GUIManager");
    // Nothing to do
}

/*!
 *  @fn GUIManager::~GUIManager()
 *  @brief Destructor method for general user interface
 */
GUIManager::~GUIManager() {
    LOG_METHOD_START("GUIManager::~GUIManager");
    gui_elements.clear();
}

/*!
 *  @fn void GUIManager::update_gui_elements()
 *  @brief Updates general user interface
 *  @return The method returns no param
 */
void GUIManager::update_gui_elements() {
    LOG_METHOD_START("GUIManager::update_gui_elements");

    //! Remove last element if requested
    //! TODO Error Handling
    if (element_pop_requested) {
        selected_gui_window = nullptr;
        selected_gui_button = nullptr;

        gui_elements.pop_back();
    }
    else {
      // Nothing to do
    }


    //! If there's element stored puts it in gui elements vector
    if (stored_gui_element) {
        selected_gui_window = nullptr;


        //! Reset the button if it is selected
        //! TODO Error Handling
        if (selected_gui_button) {
            selected_gui_button->Reset();
            selected_gui_button = nullptr;
        }
        else {
          // Nothing to do
        }

        gui_elements.emplace_back(unique_ptr<GUI_Element>(stored_gui_element));
        stored_gui_element = nullptr;
    }
    else {
      // Nothing to do
    }


    //! If there's no elements in the gui, returns
    //! TODO Error Handling
    if (gui_elements.empty()) {
         return;
    }
    else {
      // Nothing to do
    }

    element_pop_requested = false;

    previous_button_state = current_button_state;

    //! Check if current button is pressed and assings it to current_button_state
    //! TODO Error Handling
    if (selected_gui_button) {
        GUI_Button* selected_gui_buttonCopy = selected_gui_button;

        selected_gui_button = nullptr;
        selected_gui_buttonCopy->Update();
        selected_gui_button = selected_gui_buttonCopy;
        current_button_state = selected_gui_button->IsPressed();
    }
    else {
      // Nothing to do
    }

    gui_elements.back()->Update();
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
        //! TODO Error Handling
        if (it->IsVisible()){
            it->Render();
        }
        else {
          // Nothing to do
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
    LOG_METHOD_START("GUIManager::render_gui_elements");
    LOG_VARIABLE("element", element);
    assert(*element != NULL);

    //! Checks if there's an element alredy stored, and deletes it
    //! TODO Error Handling
    if (stored_gui_element) {
        delete stored_gui_element;
    }
    else {
      // Nothing to do
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

    LOG_METHOD_START("GUIManager::request_gui_element_pop");
    LOG_VARIABLE("element", element);
    assert(*element != NULL);
    //! If last object of elements vector is equal to the param
    //! Change element_pop_requested value
    //! TODO Error Handling
    if (element == gui_elements.back().get()) {
        element_pop_requested = true;
    }
    else {
      // Nothing to do
    }
}

/*!
 *  @fn void GUIManager::select_gui_window(GUI_Window* window)
 *  @brief Select window in the general user interface
 *  @param GUI_Window* window
 *  @return The method returns no param
 */
void GUIManager::select_gui_window(GUI_Window* window) {
    LOG_METHOD_START("GUIManager::select_gui_window");
    LOG_VARIABLE("window", window);
    assert(*window != NULL);
    selected_gui_window = window;
}

/*!
 *  @fn bool GUIManager::gui_window_is_selected(GUI_Window* window)const
 *  @brief Return if window is select
 *  @param GUI_Window* window
 *  @return true of false
 */
bool GUIManager::gui_window_is_selected(GUI_Window* window)const {
   LOG_METHOD_START("GUIManager::gui_window_is_selected");
   LOG_VARIABLE("window", window);
   assert(*window != NULL);
   LOG_METHOD_CLOSE("GUIManager::gui_window_is_selected", \
                            window == selected_gui_window);

    return window == selected_gui_window;
}

/*!
 *  @fn int GUIManager::get_gui_selected_window_ID()const
 *  @brief Get selected window ID of general user interface
 *  @return integer
 */
int GUIManager::get_gui_selected_window_ID()const {
    LOG_METHOD_START("GUIManager::get_gui_selected_window_ID");
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
    // LOG_METHOD_CLOSE("GUIManager::gui_window_is_selected", \
    //                          window == selected_gui_window);
}

/*!
 *  @fn void GUIManager::select_gui_button(GUI_Button* button)
 *  @brief Assing button object to selected_gui_button attribute
 *  @param GUI_Button* button
 *  @return The method returns no param
 */
void GUIManager::select_gui_button(GUI_Button* button) {
    LOG_METHOD_START("GUIManager::select_gui_button");
    LOG_VARIABLE("button", button);
    assert(*button != NULL);
    selected_gui_button = button;
}

/*!
 *  @fn bool GUIManager::gui_button_is_selected(GUI_Button* button)const
 *  @brief Avaliate if button is selected
 *  @param GUI_Button* button
 *  @return True of False
 */
bool GUIManager::gui_button_is_selected(GUI_Button* button)const {
    LOG_METHOD_START("GUIManager::gui_button_is_selected");
    LOG_VARIABLE("button", button);
    assert(*button != NULL);
    LOG_METHOD_CLOSE("GUIManager::gui_button_is_selected", \
                     button && button == selected_gui_button);
    return button && button == selected_gui_button;
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
    LOG_VARIABLE("action", &action);
    assert(&action != NULL);
    //! Return false for empty selected_gui_button
    //! TODO Error Handling
    if (!selected_gui_button) {
        return false;
    }
    else {
      // Nothing to do
    }

    //! Return false for action different from the selected button
    if (action && selected_gui_button->action != action) {
        return false;
    }
    else {
      // Nothing to do
    }
    LOG_METHOD_CLOSE("GUIManager::gui_button_was_pressed", \
                    (!previous_button_state && current_button_state));
    return (!previous_button_state && current_button_state);
}

/*!
 *  @fn bool GUIManager::gui_button_was_released(uint action)const
 *  @brief Avaliate if button was released
 *  @param unsigned int action
 *  @return True of False
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_released(uint action)const {
    LOG_METHOD_START("GUIManager::gui_button_was_released");
    LOG_VARIABLE("action", action);
    assert(action != NULL);

    //! TODO Error Handling
    if (!selected_gui_button) {
        return false;
    }
    else {
      // Nothing to do
    }
    //! TODO Error Handling
    if (action && selected_gui_button->action != action) {
        return false;
    }
    else {
      // Nothing to do
    }
    LOG_METHOD_CLOSE("GUIManager::gui_button_was_released", \
                    (previous_button_state && !current_button_state));

    return (previous_button_state && !current_button_state);
}

/*!
 *  @fn bool GUIManager::gui_button_was_clicked(uint action)const
 *  @brief Avaliate if button was clicked
 *  @param unsigned int action
 *  @return True of False
 *  @warning Simplify return of the method
 */
bool GUIManager::gui_button_was_clicked(uint action)const {
    LOG_METHOD_START("GUIManager::gui_button_was_clicked");
    LOG_VARIABLE("action", action);
    assert(action != NULL);

    //! TODO Error Handling
    if (!selected_gui_button) {
        return false;
    }
    else {
      // Nothing to do
    }
    //! TODO Error Handling
    if (action && selected_gui_button->action != action) {
        return false;
    }
    else {
      // Nothing to do
    }
    LOG_METHOD_CLOSE("GUIManager::gui_button_was_clicked", \
                    (previous_button_state && !current_button_state &&
                     selected_gui_button->IsHovered()));
    return (previous_button_state && !current_button_state &&
            selected_gui_button->IsHovered());
}

/*!
 *  @fn bool GUIManager::gui_button_is_down(uint action)const
 *  @brief Avaliate if button is down
 *  @param unsigned int action
 *  @return True of False
 */
bool GUIManager::gui_button_is_down(uint action) const {
  LOG_METHOD_START("GUIManager::gui_button_is_down");
  LOG_VARIABLE("action", action);
  assert(action != NULL);

    //! TODO Error Handling
    if (!selected_gui_button) {
        return false;
    }
    else {
      // Nothing to do
    }
    //! TODO Error Handling
    if (action && selected_gui_button->action != action) {
        return false;
    }
    else {
      // Nothing to do
    }

    LOG_METHOD_CLOSE("GUIManager::gui_button_is_down", current_button_state);
    return current_button_state;
}
