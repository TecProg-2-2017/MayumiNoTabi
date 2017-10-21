#ifndef GUIMANAGERHPP
#define GUIMANAGERHPP

#include <common.hpp>

#include <geometry.hpp>

class GUI_Element;
class GUI_Button;
class GUI_Window;

class GUIManager{
	vector<unique_ptr<GUI_Element>> gui_elements;
	GUI_Element* stored_gui_element=nullptr;

	bool element_pop_requested=false;
	bool mouse_hover = false;
	
	vector<GUI_Window*> gui_windows;
	GUI_Window* selected_gui_window=nullptr;
	
	GUI_Button* selected_gui_button=nullptr;
	bool current_button_state=false;
	bool previous_button_state=false;
public:
	GUIManager();
	~GUIManager();
	
    void remove_last_gui_element_requested();
    void reset_gui_button();
    void add_stored_element_to_gui();
    void assing_pressed_button_to_current();

    bool selected_button_is_empty()const;
    bool is_button_action_different(uint action)const;

	void update_gui_elements();
	void render_gui_elements();

	
	void push_gui_element(GUI_Element* element);
	void request_gui_element_pop(GUI_Element* element);
	
	void select_gui_window(GUI_Window* window);
	bool gui_window_is_selected(GUI_Window* window)const;
	int get_gui_selected_window_ID()const;

	void select_gui_button(GUI_Button* button);
	bool gui_button_is_selected(GUI_Button* button)const;
    
    /*! These functions return true if a button with the same action:
    *   - was pressed in the current frame;
    *   - was released in the current frame;
    *   - was released with the cursor over it in the current frame;
    *   - is being pressed
    */
	bool gui_button_was_pressed(uint action=0)const;	
	bool gui_button_was_released(uint action=0)const;
	bool gui_button_was_clicked(uint action=0)const;
	bool gui_button_is_down(uint action=0)const;
};

#endif//GUIMANAGERHPP
