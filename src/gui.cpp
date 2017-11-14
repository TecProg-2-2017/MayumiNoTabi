/*
 * File: gui.cpp
 *
 * Description: Generate the elements of GUI from game.
 */

#include <gui.hpp>
#include <game.hpp>
#include <guiManager.hpp>
#include <inputManager.hpp>
#include <state.hpp>
#include <assert.h>

#define GUI GAMESTATE.gui

#define CLIP_RECT(r,m) (r).x+=(m);(r).y+=(m);(r).w-=(m)*2;(r).h-=(m)*2

#define DEFAULT_MARGIN 3
#define DEFAULT_WIDTH 24
#define DEFAULT_HEIGHT 24
#define DEFAULT_FONT_SIZE 14
#define DEFAULT_TEXTBOX_WIDTH 72
#define DIVISOR_WIDTH 5

#define BASE_COLOR 63,63,63,255
#define BOX_COLOR 255,255,255,255
#define LABEL_COLOR 191,191,191,255
#define HIGHLIGHT_COLOR 127,127,127,255
#define PRESS_COLOR 47,47,47,255
#define SHADOW_COLOR 0,0,0,95

#define ICON_X "img/editor/icon_x.png"


/**
	Prototypes from gui.cpp' methods.
*/

GUI_Element::GUI_Element(const Vec2& pos): box{pos.x,pos.y,DEFAULT_WIDTH, \
	                                               DEFAULT_HEIGHT};
GUI_Element::~GUI_Element();
void GUI_Element::SetPos(const Vec2& pos);
Rect GUI_Element::GetBox();
void GUI_Element::SetVisible(bool v);
bool GUI_Element::IsVisible();
GUI_Button::GUI_Button(uint a,const Vec2& pos):GUI_Element(pos),action{a};
void GUI_Button::Update();
void GUI_Button::render();
void GUI_Button::Reset();
bool GUI_Button::IsPressed();
bool GUI_Button::IsHovered();
GUI_CheckButton::GUI_CheckButton(bool& v,const Vec2& pos): \
                             GUI_Button(GUI_NONE,pos),value{v};
void GUI_CheckButton::Update() ;
GUI_TextButton::GUI_TextButton(uint a,const string& l,const Vec2& pos): \
                                GUI_Button(a,pos),label{l, DEFAULT_FONT_SIZE};
void GUI_TextButton::render();
GUI_IconButton::GUI_IconButton(uint a,string i,const Vec2& pos): \
                                               GUI_Button(a,pos), icon{i};
void GUI_IconButton::render();
GUI_InputBox::GUI_InputBox(const Vec2& pos,Size s): \
                     GUI_Button(GUI_NONE,pos),text{"", DEFAULT_FONT_SIZE};
GUI_InputBox::~GUI_InputBox();
void GUI_InputBox::Update();
void GUI_InputBox::render();
GUI_StringBox::GUI_StringBox(string& v,Size s,const Vec2& pos): \
                                      GUI_InputBox(pos,s),value{v};
void GUI_StringBox::SetValue();
string GUI_StringBox::GetValue();
GUI_IntBox::GUI_IntBox(int& v,int l,int h,Size s,const Vec2& pos): \
                                 GUI_InputBox(pos,s),value{v},low{l},high{h};
void GUI_IntBox::SetValue();
string GUI_IntBox::GetValue();
GUI_Label::GUI_Label(const string& t,Snap s,const Vec2& pos):GUI_Element(pos), \
                 text{t,DEFAULT_FONT_SIZE,generate_color(LABEL_COLOR)},snap{s};
void GUI_Label::update();
void GUI_Label::render();
GUI_Array::GUI_Array(vector<GUI_Element*>& v,const Vec2& pos): \
                                     GUI_Element(pos),array{v};
GUI_Array::GUI_Array(vector<GUI_Element*>& v): \
                                     GUI_Element({0,0}),array{v};
GUI_Array::~GUI_Array();
void GUI_Array::Update();
void GUI_Array::render();
GUI_HBar::GUI_HBar(vector<GUI_Element*>& v,uint width,const Vec2& pos): \
                                                         GUI_Array(v,pos);
void GUI_HBar::render();
GUI_VBar::GUI_VBar(vector<GUI_Element*>& v,uint height,const Vec2& pos):
										GUI_Array(v,pos);
void GUI_VBar::render();
GUI_Window::GUI_Window(vector<GUI_Element*>& v,int i,const string& l, \
	                     const Vec2& pos):GUI_Element(pos),array{v}, \
											 label{l,DEFAULT_FONT_SIZE},closeButton{GUI_CLOSE,ICON_X},\
											       id{i};
void GUI_Window::update();
void GUI_Window::render();


//GUI_Element
GUI_Element::GUI_Element(const Vec2& pos): box{pos.x,pos.y,DEFAULT_WIDTH, \
	                                               DEFAULT_HEIGHT} {
	// Nothing to do
}

GUI_Element::~GUI_Element() {
	// Nothing to do
}

void GUI_Element::SetPos(const Vec2& pos) {
	LOG_METHOD_START("GUI_Element::SetPos");
  LOG_VARIABLE("&pos", &pos);
	box.x = pos.x;
	box.y = pos.y;
}

Rect GUI_Element::GetBox()const {
	LOG_METHOD_START("GUI_Element::GetBox");
	LOG_METHOD_CLOSE("GUI_Element::GetBox", box);
	return box;
}

void GUI_Element::SetVisible(bool v) {
	LOG_METHOD_START("GUI_Element::SetVisible");
  LOG_VARIABLE("v", v);
	visible = v;
}

bool GUI_Element::IsVisible()const {
	LOG_METHOD_START("GUI_Element::IsVisible");
	LOG_METHOD_CLOSE("GUI_Element::IsVisible", visible);
	return visible;
}

//GUI_Button
GUI_Button::GUI_Button(uint a,const Vec2& pos):GUI_Element(pos),action{a} {
	LOG_METHOD_START("GUI_Button::GUI_Button");
  LOG_VARIABLE("a", a);
	LOG_VARIABLE("pos", pos);
	// Nothing to do
}

void GUI_Button::Update() {
	LOG_METHOD_START("GUI_Button::Update");

	if (gui.gui_button_is_selected(this)) {
		return;
	}
	else if (gui.gui_button_is_down()) {
		return;
	}

	Rect button = box;
	CLIP_RECT(button, DEFAULT_MARGIN);
	hover = button.contains(INPUT.get_mouse_position());

	if (hover) {
		gui.select_gui_button(this);
		if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
			press = true;
			return;
		}
		else {
			// Nothing to do
		}
	}
	else {
		// Nothing to do
	}
	if (press && INPUT.mouse_button_released(MBUTTON_LEFT)) {
		press = false;
	}
	else {
		// Nothing to do
	}
}

void GUI_Button::render() {
	LOG_METHOD_START("GUI_Button::render");

	SDL_Rect rect = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);

	if (hover) {
		SET_COLOR(HIGHLIGHT_COLOR);
		CLIP_RECT(rect, DEFAULT_MARGIN);
		DRAW_RECT(&rect);

		if (press) {
			SET_COLOR(PRESS_COLOR);
			CLIP_RECT(rect, 1);
			FILL_RECT(&rect);
		}
		else {
			// Nothing to do
		}
	}
	else {
		// Nothing to do
	}
}

void GUI_Button::Reset() {
	LOG_METHOD_START("GUI_Button::Reset");

	press = false;
	hover = false;
}

bool GUI_Button::IsPressed()const {
	LOG_METHOD_START("GUI_Button::IsPressed");
  LOG_METHOD_CLOSE("GUI_Button::IsPressed", press);
	return press;
}

bool GUI_Button::IsHovered()const {
	LOG_METHOD_START("GUI_Button::IsHovered");
  LOG_METHOD_CLOSE("GUI_Button::IsHovered", hover);
	return hover;
}

//GUI_CheckButton
GUI_CheckButton::GUI_CheckButton(bool& v,const Vec2& pos): \
GUI_Button(GUI_NONE,pos),value{v} {

	LOG_METHOD_START("GUI_CheckButton::GUI_CheckButton");
	LOG_VARIABLE("v", &v);
	LOG_VARIABLE("pos", &pos);
		// Nothing to do
}

void GUI_CheckButton::Update() {
	LOG_METHOD_START("GUI_CheckButton::Update");
	if (gui.gui_button_is_selected(this)) {
		return;
	}
	else if (gui.gui_button_is_down()) {
		return;
	}
	else {
		// Nothing to do
	}

	Rect button = box;
	CLIP_RECT(button, DEFAULT_MARGIN*2);
	hover = button.contains(INPUT.get_mouse_position());

	if (hover) {
		gui.select_gui_button(this);
		if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
			press = true;
		}
		else {
			// Nothing to do
		}
	}
	else {
		// Nothing to do
	}
	if (press && INPUT.mouse_button_released(MBUTTON_LEFT)) {
		if (hover) {
			value = !value;
		}
		else {
			// Nothing to do
		}
		press = false;
	}
}

void GUI_CheckButton::render() {
	LOG_METHOD_START("GUI_CheckButton::render");
	SDL_Rect rect = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);
	SET_COLOR(BOX_COLOR);
	CLIP_RECT(rect, DEFAULT_MARGIN*2);
	DRAW_RECT(&rect);

	if (value) {
		if (press && hover) {
			SET_COLOR(HIGHLIGHT_COLOR);
		}
		else {
			SET_COLOR(BOX_COLOR);
		}
		CLIP_RECT(rect, DEFAULT_MARGIN);
		FILL_RECT(&rect);
	}
	else {
		// Nothing to do
	}
}

//GUI_TextButton
GUI_TextButton::GUI_TextButton(uint a, const string& l, const Vec2& pos): \
                                GUI_Button(a,pos),label{l, DEFAULT_FONT_SIZE} {
	LOG_METHOD_START("GUI_TextButton::GUI_TextButton");
	LOG_VARIABLE("a", a);
	LOG_VARIABLE("l", l);
	LOG_VARIABLE("pos", pos);

	label.set_hotspot();
	box.w = label.get_box().w + DEFAULT_MARGIN * 4;
}

void GUI_TextButton::render() {
	LOG_METHOD_START("GUI_TextButton::render");
	GUI_Button::render();

	label.set_box_position(box.center());
	label.render();
}

//GUI_IconButton
GUI_IconButton::GUI_IconButton(uint a,string i,const Vec2& pos): \
                                               GUI_Button(a,pos), icon{i} {
	LOG_METHOD_START("GUI_IconButton::GUI_IconButton");
 	LOG_VARIABLE("a", a);
 	LOG_VARIABLE("i", i);
 	LOG_VARIABLE("pos", pos);
	assert(a != NULL);
	assert(i != NULL);
	assert(pos != NULL);

	icon.SetBlend(true);
	box.w = icon.GetWidth() + DEFAULT_MARGIN * 4;
	box.h = icon.GetHeight() + DEFAULT_MARGIN * 4;
}

void GUI_IconButton::render() {
	LOG_METHOD_START("GUI_IconButton::render");
	GUI_Button::render();
	icon.render((int)(box.x + DEFAULT_MARGIN*2), \
	             (int)(box.y + DEFAULT_MARGIN * 2));
}

//GUI_InputBox
GUI_InputBox::GUI_InputBox(const Vec2& pos,Size s): \
                     GUI_Button(GUI_NONE,pos),text{"", DEFAULT_FONT_SIZE} {
  LOG_METHOD_START("GUI_InputBox::GUI_InputBox");
	LOG_VARIABLE("pos", pos);
	LOG_VARIABLE("s", s);
	assert(pos != NULL);
	assert(s != NULL);

	box.w = DEFAULT_TEXTBOX_WIDTH;
	if (s == SHORT_SIZE) {
		box.w /= 2;
	}
	else if (s == LONG_SIZE) {
		box.w *= 2;
	}
	else {
		// Nothing to do
	}
	text.set_hotspot(Hotspot::LEFT);
	text.set_alignment(Text::Align::LEFT);
}


GUI_InputBox::~GUI_InputBox() {
		LOG_METHOD_START("GUI_InputBox::GUI_InputBox");
		INPUT.stop_text_input(&input);
}

void GUI_InputBox::Update() {
	LOG_METHOD_START("GUI_InputBox::GUI_InputBox");
	if (gui.gui_button_is_selected(this)) {
		return;
	}
	else if (gui.gui_button_is_down()) {
		return;
	}

	Rect button = box;
	CLIP_RECT(button, DEFAULT_MARGIN);
	hover = button.contains(INPUT.get_mouse_position());
	bool closed = false;
	if (hover) {
		gui.select_gui_button(this);
	}
	else {
		// Nothing to do
	}
	if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
		if (!press) {
			if (hover) {
				press = true;
				INPUT.start_text_input(&input);
			}
			else {
				// Nothing to do
			}
		}
		else if (!hover) {
			closed = true;
		}
		else {
			// Nothing to do
		}
	}
	else {
		// Nothing to do
	}
	if (!press) {
		return;
	}
	else {
		// Nothing to do
	}

	if (closed || INPUT.key_pressed(KEY_ENTER)) {
		press = false;
		INPUT.stop_text_input(&input);
		while (input[0] == ' ')
			input.erase(0,1);
		while (input[input.size()-1] == ' ')
			input.pop_back();
		if (!input.empty()) {
			SetValue();
		}
		else {
			// Nothing to do
		}
		input.clear();
	}
	else if (INPUT.key_pressed(KEY_ESC)) {
		press = false;
		INPUT.stop_text_input(&input);
		input.clear();
	}
}

void GUI_InputBox::render() {
	LOG_METHOD_START("GUI_InputBox::render");
	SDL_Rect rect = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);
	if (press) {
		SET_COLOR(BOX_COLOR);
	}
	else {
		SET_COLOR(HIGHLIGHT_COLOR);
	}
	CLIP_RECT(rect, DEFAULT_MARGIN);
	DRAW_RECT(&rect);

	rect.x += DEFAULT_MARGIN;
	rect.w -= DEFAULT_MARGIN*2;

	text.set_box_position({box.x+DEFAULT_MARGIN*2,box.y+box.h/2});
	if (press) {
		Rect textRect = text.get_box();
		int textEnd = (textRect.x + textRect.w) - 1 - offset;
		int rectEnd = (rect.x + rect.w) - 1;

		if ((textRect.w > rect.w) && (textEnd < rectEnd)) {
			offset -= (rectEnd - textEnd);
		}
		else {
			offset = 0;
		}

		Vec2 cursor(rect.x - offset, rect.y + 2);
		int c = INPUT.get_text_cursor_position();
		if (c > 0) {
			text.set_text(input.substr(0,c));
			cursor.x += (text.get_box().w - 1);
		}
		else {
			// Nothing to do
		}

		if (cursor.x >= (rect.x+rect.w)) {
			offset += cursor.x-(rect.x+rect.w-1);
			cursor.x = (rect.x+rect.w-1);
		}
		else if (cursor.x < rect.x) {
			offset -= rect.x-cursor.x;
			cursor.x = rect.x;
		}

		if (INPUT.text_cursor_blink()) {
			DRAW_LINE(cursor.x,cursor.y,cursor.x,cursor.y+DEFAULT_FONT_SIZE);
		}
		else {
			// Nothing to do
		}
		text.set_text(input);
		Rect textClip{(float)offset,0,(float)rect.w,DEFAULT_FONT_SIZE+2};
		text.render({(float)offset,0}, &textClip);
	}
	else {
		text.set_text(GetValue());
		Rect textClip{0,0,(float)rect.w,DEFAULT_FONT_SIZE+2};
		text.render({0,0}, &textClip);
	}
}

//GUI_StringBox
GUI_StringBox::GUI_StringBox(string& v,Size s,const Vec2& pos): \
                                      GUI_InputBox(pos,s),value{v} {
	LOG_METHOD_START("GUI_StringBox::GUI_StringBox");
  LOG_VARIABLE("v", &v);
  LOG_VARIABLE("pos", &pos);
	assert(v != NULL);
	assert(&pos != NULL);
	// Nothing to do
}

void GUI_StringBox::SetValue() {
	LOG_METHOD_START("GUI_StringBox::SetValue");
	value = input;
}

string GUI_StringBox::GetValue()const {
	LOG_METHOD_START("GUI_StringBox::GUI_StringBox");
	LOG_METHOD_CLOSE("GUI_StringBox::GUI_StringBox", value);
	return value;
}

//GUI_IntBox
GUI_IntBox::GUI_IntBox(int& v,int l,int h,Size s,const Vec2& pos): \
                                 GUI_InputBox(pos,s),value{v},low{l},high{h} {
	LOG_METHOD_START("GUI_IntBox::GUI_IntBox");
	LOG_VARIABLE("v", &v);
	LOG_VARIABLE("l", l);
	LOG_VARIABLE("h", &h);
	LOG_VARIABLE("s", &s);
	assert(v != NULL);
	assert(l != NULL);
	assert(h != NULL);
	assert(s != NULL);
	// Nothing to do
}

void GUI_IntBox::SetValue() {
	LOG_METHOD_START("GUI_IntBox::SetValue");

	while (!input.empty() && (input[0] < '0' || input[0] >'9'))
		input.erase(0,1);
	if (input.empty()) {
		return;
	}
	else {
		// Nothing to do
	}
	value = stoi(input);
	value = min(max(low,value), high);
}

string GUI_IntBox::GetValue()const {
	return to_string(value);
}

//GUI_Label
GUI_Label::GUI_Label(const string& t,Snap s,const Vec2& pos):GUI_Element(pos), \
                 text{t,DEFAULT_FONT_SIZE,generate_color(LABEL_COLOR)},snap{s} {

	LOG_METHOD_START("GUI_Label::GUI_Label");
 	LOG_VARIABLE("t", &t);
 	LOG_VARIABLE("s", s);
 	LOG_VARIABLE("pos", &pos);
	assert(&t != NULL);
	assert(s != NULL);
	assert(&pos != NULL);

	text.set_hotspot();
	box.w = text.get_box().w;

	if (snap == SNAP_LEFT || snap == SNAP_RIGHT) {
		box.w += DEFAULT_MARGIN;
	}
	else {
		box.w += DEFAULT_MARGIN * 2;
	}
}

void GUI_Label::update() {
	LOG_METHOD_START("GUI_Label::update");
	// Nothing to do
}

void GUI_Label::render() {
	LOG_METHOD_START("GUI_Label::render");
	SDL_Rect rect = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);

	if (snap == SNAP_LEFT) {
		text.set_box_position(box.center() - Vec2(DEFAULT_MARGIN,0));
	}
	else if (snap == SNAP_RIGHT) {
		text.set_box_position(box.center() + Vec2(DEFAULT_MARGIN,0));
	}
	else {
		text.set_box_position(box.center());
	}
	text.render();
}

//GUI_Array
GUI_Array::GUI_Array(vector<GUI_Element*>& v,const Vec2& pos): \
                                     GUI_Element(pos),array{v} {
		LOG_METHOD_START("GUI_Array::GUI_Array");
 	 	LOG_VARIABLE("v", &v);
 	 	LOG_VARIABLE("pos", &pos);
		assert(v != NULL);
		assert(pos != NULL);
		// Nothing to do
}

GUI_Array::GUI_Array(vector<GUI_Element*>& v): \
                                     GUI_Element({0,0}),array{v} {
	 LOG_METHOD_START("GUI_Array::GUI_Array");
	 LOG_VARIABLE("v", &v);
	 assert(v != NULL);
	 // Nothing to do
}

GUI_Array::~GUI_Array() {
	LOG_METHOD_START("GUI_Array::~GUI_Array");
	for (auto& it:array) {
		delete it;
	}
}

void GUI_Array::Update() {
	LOG_METHOD_START("GUI_Array::Update");

	Vec2 mouse = INPUT.get_mouse_position();
	for (auto it=array.rbegin(); it != array.rend(); it++) {
		GUI_Element& element = **it;
		if (&element && element.GetBox().contains(mouse) && element.IsVisible()) {
			element.update();
			return;
		}
		else {
			// Nothing to do
		}
	}
}

void GUI_Array::render() {
	LOG_METHOD_START("GUI_Array::render");

	for (auto& it:array) {
		if (it->IsVisible()) {
			it->render();
		}
		else {
			// Nothing to do
		}
	}
}

//GUI_HBar
GUI_HBar::GUI_HBar(vector<GUI_Element*>& v,uint width,const Vec2& pos): \
                                                         GUI_Array(v,pos) {
	LOG_METHOD_START("GUI_HBar::GUI_HBar");
	LOG_VARIABLE("v", &v);
	LOG_VARIABLE("width", width);
	LOG_VARIABLE("&pos", &pos);
	assert(v != NULL);
	assert(width != NULL);
	assert(&pos != NULL);

	if (width) {
		box.w = width;
	}
	else {
		box.w = 0;
		for (auto& it:array) {
			if (it) {
				box.w += it->GetBox().w;
			}
			else {
				box.w += DIVISOR_WIDTH;
			}
		}
	}

	int h = 0;

	for (auto& it:array) {
		if (it) {
			h = it->GetBox().h;
			if (h > box.h) {
				box.h = h;
			}
			else {
				// Nothing to do
			}
		}
		else {
			// Nothing to do
		}
	}
}

void GUI_HBar::render() {
	LOG_METHOD_START("GUI_HBar::render");

	Vec2 pos(box.x, box.y);
	int divX = 0;
	int divY = pos.y + DEFAULT_MARGIN;
	int divLen = box.h - (DEFAULT_MARGIN*2);
	bool empty = false;
	SDL_Rect bg = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&bg);
	for (auto& it:array) {
		if (it) {
			if (it->IsVisible()) {
				it->SetPos(pos);
				it->render();
				pos.x += it->GetBox().w;
				empty = false;
			}
			else {
				// Nothing to do
			}
		}
		else if (!empty) {
			divX = pos.x + (DIVISOR_WIDTH / 2);

			SET_COLOR(HIGHLIGHT_COLOR);
			DRAW_LINE(divX,divY,divX,divY + divLen);

			pos.x += DIVISOR_WIDTH;
			empty = true;
		}
		else {
			// Nothing to do
		}
	}
}

//GUI_VBar
GUI_VBar::GUI_VBar(vector<GUI_Element*>& v,uint height,const Vec2& pos):
										GUI_Array(v,pos) {
	LOG_METHOD_START("GUI_VBar::GUI_VBar");
  LOG_VARIABLE("v", &v);
	LOG_VARIABLE("height", height);
	LOG_VARIABLE("&pos", &pos);
	assert(v != NULL);
	assert(height != NULL);
	assert(&pos != NULL);

	if (height) {
		box.h = height;
	}
	else {

		box.h = 0;

		for (auto& it:array) {
			if (it) {
				box.h += it->GetBox().h;
			}
			else {
				 box.h += DIVISOR_WIDTH;
			}
		}
	}

	int w = 0;

	for (auto& it:array) {
		if (it) {
			w = it->GetBox().w;
			if (w > box.w) {
				box.w = w;
			}
			else {
				// Nothing to do
			}
		}
	}
}

void GUI_VBar::render() {
	LOG_METHOD_START("GUI_VBar::render");

	Vec2 pos(box.x,box.y);
	int divX = pos.x + DEFAULT_MARGIN;
	int divY = 0;
	int divLen = box.w - (DEFAULT_MARGIN*2);
	bool empty = false;
	SDL_Rect bg = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&bg);

	for (auto& it:array) {
		if (it) {
			if (it->IsVisible()) {
				it->SetPos(pos);
				it->render();
				pos.y += it->GetBox().h;
				empty = false;
			}
			else {
				// Nothing to do
			}
		}
		else if (!empty) {
			divY = pos.y + (DIVISOR_WIDTH / 2);
			SET_COLOR(HIGHLIGHT_COLOR);
			DRAW_LINE(divX,divY,divX + divLen,divY);
			pos.y += DIVISOR_WIDTH;
			empty = true;
		}
		else {
			// Nothing to do
		}
	}
}

//GUI_Window
GUI_Window::GUI_Window(vector<GUI_Element*>& v,int i,const string& l, \
	                     const Vec2& pos):GUI_Element(pos),array{v}, \
											 label{l,DEFAULT_FONT_SIZE},closeButton{GUI_CLOSE,ICON_X},\
											       id{i} {

	LOG_METHOD_START("GUI_Window::GUI_Window");
	LOG_VARIABLE("v", &v);
	LOG_VARIABLE("i", i);
	LOG_VARIABLE("&l", &l);
	assert(v != NULL);
	assert(i != NULL);
	assert(&l != NULL);

	box.w = array.GetBox().w;
	box.h = array.GetBox().h + DEFAULT_HEIGHT;

	if (pos == Vec2(-1,-1)) {
		box.x = (WINSIZE.x-box.w) / 2;
		box.y = (WINSIZE.y-box.h) / 2;
	}
	else {
		// Nothing to do
	}

	label.set_hotspot(LEFT);
  GUI.select_gui_window(this);
}

void GUI_Window::update() {
	LOG_METHOD_START("GUI_Window::update");

	if (pop) {
		GUI.request_gui_element_pop(this);
		return;
	}
	else {
		// Nothing to do
	}

	bool hover = box.contains(INPUT.get_mouse_position());

	if (!hover) {
		if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
			GUI.select_gui_window(nullptr);
		}
		else {
			// Nothing to do
		}
		return;
	}
	else {
		// Nothing to do
	}

	if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
		GUI.select_gui_window(this);
	}
	else {
		// Nothing to do
	}
	closeButton.update();
	if (GUI.gui_button_was_clicked(GUI_CLOSE)|| GUI.gui_button_was_clicked(GUI_CONFIRM)|| \
		 				                            GUI.gui_button_was_clicked(GUI_DENY)) {
		 pop = true;
	}

	array.update();
}

void GUI_Window::render() {
	LOG_METHOD_START("GUI_Window::render");

	SDL_Rect rect = box.sdlRect();

	SET_COLOR(SHADOW_COLOR);
	CLIP_RECT(rect,-1);
	DRAW_RECT(&rect);

	SET_COLOR(BASE_COLOR);
	CLIP_RECT(rect,1);
	rect.h = DEFAULT_HEIGHT;
	FILL_RECT(&rect);
	label.set_box_position({box.x + DEFAULT_MARGIN,box.y + (DEFAULT_HEIGHT / 2)});
	Rect textClip{0,0,box.w -(DEFAULT_WIDTH+DEFAULT_MARGIN),DEFAULT_FONT_SIZE+2};
	label.render({0,0}, &textClip);
	closeButton.SetPos({box.x + box.w - DEFAULT_WIDTH - 1, box.y});
	closeButton.render();

	array.SetPos({box.x,box.y + DEFAULT_HEIGHT});
	array.render();
}
