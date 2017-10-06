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
    elements.clear();
}

/*!
 *  @fn void GUIManager::Update()
 *  @brief Updates general user interface
 *  @return The method returns no param
 */
void GUIManage::update() {

    //! TODO: Insert else to do nothing
    //! Remove last element if requested
    if (popRequested) {
        selectedWindow = nullptr;
        selectedButton = nullptr;

        elements.pop_back();
    }

    //! TODO: Insert else to do nothing
    //! If there's element stored puts it in gui elements vector
    if (storedElement) {
        selectedWindow = nullptr;

        //! TODO: Insert else to do nothing
        //! Reset the button if it is selected 
        if (selectedButton) {
            selectedButton->Reset();
            selectedButton = nullptr;
        }

        elements.emplace_back(unique_ptr<GUI_Element>(storedElement));
        storedElement = nullptr;
    }

    //! TODO: Insert else to do nothing
    //! If there's no elements in the gui, returns 
    if (elements.empty()) {
         return;
    }
    
    popRequested = false;
    
    previousButtonState = currentButtonState;
    
    //! TODO: Insert else to do nothing
    //! Check if current button is pressed and assings it to currentButtonState
    if (selectedButton) {
        GUI_Button* selectedButtonCopy = selectedButton;

        selectedButton = nullptr;

        selectedButtonCopy->update();
        selectedButton = selectedButtonCopy;
        currentButtonState = selectedButton->IsPressed();
    }
    
    elements.back()->update();  
}

/*!
 *  @fn void GUIManager::render()
 *  @brief Renders general user interface
 *  @return The method returns no param
 */
void GUIManager::render() {
    
    //! Iterates trough elements of interface to render it
    for (auto& it:elements){

        //! TODO: Insert else to do nothing
        //! If elements is visible renders it
        if (it->IsVisible()){
            it->Render();
        }
    }
}
 
/*!
 *  @fn void GUIManager::PushElement(GUI_Element* element)
 *  @brief Push element to the general user interface 
 *  @param GUI_Element* element
 *  @return The method returns no param
 */
void GUIManager::PushElement(GUI_Element* element) {

    //! TODO: Insert else to do nothing
    //! Checks if there's an element alredy stored, and deletes it
    if (storedElement) { 
        delete storedElement;
    }

    storedElement = element;
}

/*!
 *  @fn void GUIManager::RequestPop(GUI_Element* element)
 *  @brief Changes popRequested value if requested  
 *  @param GUI_Element* element
 *  @return The method returns no param
 */
void GUIManager::RequestPop(GUI_Element* element) {
   
    //! TODO: Insert else to do nothing
    //! If last object of elements vector is equal to the param
    //! Change popRequested value
    if (element == elements.back().get()) {
        popRequested = true;
    }
}

/*!
 *  @fn void GUIManager::SelectWindow(GUI_Window* window)
 *  @brief Select window in the general user interface
 *  @param GUI_Window* window
 *  @return The method returns no param
 */
void GUIManager::SelectWindow(GUI_Window* window) {
    selectedWindow = window;
}

/*!
 *  @fn bool GUIManager::IsWindowSelected(GUI_Window* window)const 
 *  @brief Return if window is select 
 *  @param GUI_Window* window
 *  @return true of false 
 */
bool GUIManager::IsWindowSelected(GUI_Window* window)const {
    return window==selectedWindow;
}

/*!
 *  @fn int GUIManager::GetSelectedWindowID()const 
 *  @brief Get selected window ID of general user interface
 *  @return integer 
 */
int GUIManager::GetSelectedWindowID()const {

    //If there's a window selected, returns it ID
    if (selectedWindow){
        return selectedWindow->id;
    }
    else if (elements.size() == 1) { 
        return 0;
    }
    else {
        return -1;
    }
}

/*!
 *  @fn void GUIManager::SelectButton(GUI_Button* button) 
 *  @brief Assing button object to selectedButton attribute
 *  @param GUI_Button* button
 *  @return The method returns no param
 */
void GUIManager::SelectButton(GUI_Button* button) {
    selectedButton = button;
}

/*!
 *  @fn bool GUIManager::IsButtonSelected(GUI_Button* button)const   
 *  @brief Avaliate if button is selected 
 *  @param GUI_Button* button
 *  @return True of False 
 */
bool GUIManager::IsButtonSelected(GUI_Button* button)const{
    return button && button==selectedButton;
}

/*!
 *  @fn bool GUIManager::ButtonPress(uint action)const    
 *  @brief Avaliate if button was pressed 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::ButtonPress(uint action)const{

    //! TODO: Insert else to do nothing
    //! Return false for empty selectedButton
    if (!selectedButton) {
        return false;
    }
    
    //! TODO: Insert else to do nothing
    //! Return false for action different from the selected button 
    if (action && selectedButton->action != action) {
        return false;
    }
    return (!previousButtonState && currentButtonState);
}

/*!
 *  @fn bool GUIManager::ButtonPress(uint action)const    
 *  @brief Avaliate if button was released 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::ButtonRelease(uint action)const{

    //! TODO: Insert else to do nothing
    if (!selectedButton) { 
        return false;
    }
    
    //! TODO: Insert else to do nothing
    if (action && selectedButton->action != action) {
        return false;
    }
    return (previousButtonState && !currentButtonState);
}

/*!
 *  @fn bool GUIManager::ButtonClick(uint action)const    
 *  @brief Avaliate if button was clicked 
 *  @param unsigned int action 
 *  @return True of False 
 *  @warning Simplify return of the method
 */
bool GUIManager::ButtonClick(uint action)const{

    //! TODO: Insert else to do nothing
    if (!selectedButton) {
        return false;
    }

    //! TODO: Insert else to do nothing
    if (action && selectedButton->action != action) { 
        return false;
    }

    return (previousButtonState && !currentButtonState && selectedButton->IsHovered());
}

/*!
 *  @fn bool GUIManager::IsButtonDown(uint action)const    
 *  @brief Avaliate if button is down 
 *  @param unsigned int action 
 *  @return True of False 
 */
bool GUIManager::IsButtonDown(uint action)const{

    //! TODO: Insert else to do nothing
    if (!selectedButton) {
        return false;
    }

    //! TODO: Insert else to do nothing
    if (action && selectedButton->action != action) { 
        return false;
    }

    return currentButtonState;
}
