#include <gui.hpp>

#include <game.hpp>
#include <guiManager.hpp>
#include <inputManager.hpp>
#include <state.hpp>

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

//GUI_Element
GUI_Element::GUI_Element(const Vec2& pos):box{pos.x,pos.y,DEFAULT_WIDTH,DEFAULT_HEIGHT}{}
GUI_Element::~GUI_Element() {}

void GUI_Element::SetPos(const Vec2& pos) {
	box.x=pos.x;
	box.y=pos.y;
}

Rect GUI_Element::GetBox()const{
	return box;
}

void GUI_Element::SetVisible(bool v) {
	visible = v;
}
bool GUI_Element::IsVisible()const{
	return visible;
}

//GUI_Button
GUI_Button::GUI_Button(uint a,const Vec2& pos):GUI_Element(pos),action{a}{
}

void GUI_Button::Update() {
	if (gui.gui_button_is_selected(this)) return;
	else if (gui.gui_button_is_down()) return;
	
	Rect button = box;
	CLIP_RECT(button, DEFAULT_MARGIN);
	hover=button.contains(INPUT.get_mouse_position());
	if (hover) {
		gui.select_gui_button(this);
		if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
			press = true;
			return;
		}
	}
	if (press && INPUT.mouse_button_released(MBUTTON_LEFT)) {
		press = false;
	}
}
void GUI_Button::render() {
	SDL_Rect rect=box.sdlRect();

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
	}
}

void GUI_Button::Reset() {
	press = false;
	hover = false;
}
bool GUI_Button::IsPressed()const{
	return press;
}
bool GUI_Button::IsHovered()const{
	return hover;
}

//GUI_CheckButton
GUI_CheckButton::GUI_CheckButton(bool& v,const Vec2& pos):GUI_Button(GUI_NONE,pos),value{v}{
}


void GUI_CheckButton::Update() {
	if (gui.gui_button_is_selected(this)) return;
	else if (gui.gui_button_is_down()) return;
	
	Rect button = box;
	CLIP_RECT(button, DEFAULT_MARGIN*2);
	hover=button.contains(INPUT.get_mouse_position());
	if (hover) {
		gui.select_gui_button(this);
		if (INPUT.mouse_button_pressed(MBUTTON_LEFT))	press = true;
	}
	if (press && INPUT.mouse_button_released(MBUTTON_LEFT)) {
		if (hover) {
			value = !value;
		}
		press = false;
	}
}
void GUI_CheckButton::render() {
	SDL_Rect rect=box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);
	SET_COLOR(BOX_COLOR);
	CLIP_RECT(rect, DEFAULT_MARGIN*2);
	DRAW_RECT(&rect);

	if (value) {
		if (press && hover) SET_COLOR(HIGHLIGHT_COLOR);
		else SET_COLOR(BOX_COLOR);
		CLIP_RECT(rect, DEFAULT_MARGIN);
		FILL_RECT(&rect);
	}
}

//GUI_TextButton
GUI_TextButton::GUI_TextButton(uint a,const string& l,const Vec2& pos):GUI_Button(a,pos),label{l, DEFAULT_FONT_SIZE}{
	label.set_hotspot();
	box.w = label.get_box().w+DEFAULT_MARGIN*4;
}

void GUI_TextButton::render() {
	GUI_Button::render();

	label.set_box_position(box.center());
	label.render();
}

//GUI_IconButton
GUI_IconButton::GUI_IconButton(uint a,string i,const Vec2& pos):GUI_Button(a,pos), icon{i}{
	icon.SetBlend(true);
	box.w = icon.GetWidth()+DEFAULT_MARGIN*4;
	box.h = icon.GetHeight()+DEFAULT_MARGIN*4;
}

void GUI_IconButton::render() {
	GUI_Button::render();
	icon.render((int)(box.x+DEFAULT_MARGIN*2), (int)(box.y+DEFAULT_MARGIN*2));
}

//GUI_InputBox
GUI_InputBox::GUI_InputBox(const Vec2& pos,Size s):GUI_Button(GUI_NONE,pos),text{"", DEFAULT_FONT_SIZE}{
	box.w = DEFAULT_TEXTBOX_WIDTH;
	if (s==SHORT_SIZE) box.w/=2;
	else if (s==LONG_SIZE) box.w*=2;
	text.set_hotspot(Hotspot::LEFT);
	text.set_alignment(Text::Align::LEFT);
}
GUI_InputBox::~GUI_InputBox() {
		INPUT.stop_text_input(&input);
}


void GUI_InputBox::Update() {
	if (gui.gui_button_is_selected(this)) return;
	else if (gui.gui_button_is_down()) return;
	
	Rect button = box;
	CLIP_RECT(button, DEFAULT_MARGIN);
	hover=button.contains(INPUT.get_mouse_position());
	bool closed = false;
	if (hover)
		gui.select_gui_button(this);
		
	if (INPUT.mouse_button_pressed(MBUTTON_LEFT)) {
		if (!press) {
			if (hover) {
				press = true;
				INPUT.start_text_input(&input);
			}
		}
		else if (!hover) {
			closed =true;
		}
	}
	if (!press) return;
	
	if (closed || INPUT.key_pressed(KEY_ENTER)) {
		press = false;
		INPUT.stop_text_input(&input);
		while (input[0] == ' ')
			input.erase(0,1);
		while (input[input.size()-1] == ' ')
			input.pop_back();
		if (!input.empty())
			SetValue();
		input.clear();
	}
	else if (INPUT.key_pressed(KEY_ESC)) {
		press = false;
		INPUT.stop_text_input(&input);
		input.clear();
	}
}
void GUI_InputBox::render() {
	SDL_Rect rect=box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);
	if (press) {
		SET_COLOR(BOX_COLOR);
	}
	else{
		SET_COLOR(HIGHLIGHT_COLOR);
	}
	CLIP_RECT(rect, DEFAULT_MARGIN);
	DRAW_RECT(&rect);

	rect.x+=DEFAULT_MARGIN;
	rect.w-=DEFAULT_MARGIN*2;

	text.set_box_position({box.x+DEFAULT_MARGIN*2,box.y+box.h/2});
	if (press) {
		Rect textRect = text.get_box();
		int textEnd = (textRect.x+textRect.w)-1-offset;
		int rectEnd = (rect.x+rect.w)-1;

		if ((textRect.w > rect.w) && (textEnd < rectEnd)) {
			offset -= (rectEnd - textEnd);
		}
		else offset = 0;

		Vec2 cursor(rect.x-offset,rect.y+2);
		int c = INPUT.get_text_cursor_position();
		if (c>0) {
			text.set_text(input.substr(0,c));
			cursor.x+=(text.get_box().w-1);
		}

		if (cursor.x >= (rect.x+rect.w)) {
			offset += cursor.x-(rect.x+rect.w-1);
			cursor.x = (rect.x+rect.w-1);
		}
		else if (cursor.x < rect.x) {
			offset -= rect.x-cursor.x;
			cursor.x = rect.x;
		}
		
		if (INPUT.text_cursor_blink())
			DRAW_LINE(cursor.x,cursor.y,cursor.x,cursor.y+DEFAULT_FONT_SIZE);

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
GUI_StringBox::GUI_StringBox(string& v,Size s,const Vec2& pos):GUI_InputBox(pos,s),value{v}{}

void GUI_StringBox::SetValue() {
	value = input;
}
string GUI_StringBox::GetValue()const{
	return value;
}

//GUI_IntBox
GUI_IntBox::GUI_IntBox(int& v,int l,int h,Size s,const Vec2& pos):GUI_InputBox(pos,s),value{v},low{l},high{h}{}

void GUI_IntBox::SetValue() {
	while (!input.empty() && (input[0]<'0' || input[0] >'9'))
		input.erase(0,1);
	if (input.empty()) return;
	value = stoi(input);
	value = min(max(low,value),high);
}
string GUI_IntBox::GetValue()const{
	return to_string(value);
}

//GUI_Label
GUI_Label::GUI_Label(const string& t,Snap s,const Vec2& pos):GUI_Element(pos),text{t,DEFAULT_FONT_SIZE,generate_color(LABEL_COLOR)},snap{s}{
	text.set_hotspot();
	box.w = text.get_box().w;
	if (snap==SNAP_LEFT || snap==SNAP_RIGHT)
		box.w+=DEFAULT_MARGIN;
	else
		box.w+=DEFAULT_MARGIN*2;
}

void GUI_Label::update() {}
void GUI_Label::render() {
	SDL_Rect rect=box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&rect);

	if (snap==SNAP_LEFT)
		text.set_box_position(box.center()-Vec2(DEFAULT_MARGIN,0));
	else if (snap==SNAP_RIGHT)
		text.set_box_position(box.center()+Vec2(DEFAULT_MARGIN,0));
	else
		text.set_box_position(box.center());
	text.render();
}

//GUI_Array
GUI_Array::GUI_Array(vector<GUI_Element*>& v,const Vec2& pos):GUI_Element(pos),array{v}{}
GUI_Array::GUI_Array(vector<GUI_Element*>& v):GUI_Element({0,0}),array{v}{}
GUI_Array::~GUI_Array() {
	for (auto& it:array)
		delete it;
}


void GUI_Array::Update() {
	Vec2 mouse = INPUT.get_mouse_position();
	for (auto it=array.rbegin();it!=array.rend();it++) {
		GUI_Element& element = **it;
		if (&element && element.GetBox().contains(mouse) && element.IsVisible()) {
			element.update();
			return;
		}
	}
}
void GUI_Array::render() {
	for (auto& it:array)
		if (it->IsVisible())
			it->render();
}

//GUI_HBar
GUI_HBar::GUI_HBar(vector<GUI_Element*>& v,uint width,const Vec2& pos):GUI_Array(v,pos) {
	if (width)
		box.w=width;
	else{
		box.w=0;
		for (auto& it:array) {
			if (it) box.w += it->GetBox().w;
			else box.w += DIVISOR_WIDTH;
		}
	}
	int h;
	for (auto& it:array) {
		if (it) {
			h = it->GetBox().h;
			if (h>box.h)
				box.h=h;
		}
	}
}

void GUI_HBar::render() {
	Vec2 pos(box.x,box.y);
	int divX;
	int divY=pos.y+DEFAULT_MARGIN;
	int divLen=box.h-(DEFAULT_MARGIN*2);
	bool empty = false;
	SDL_Rect bg = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&bg);
	for (auto& it:array) {
		if (it) {
			if (it->IsVisible()) {
				it->SetPos(pos);
				it->render();
				pos.x+=it->GetBox().w;
				empty = false;
			}
		}
		else if (!empty) {
			divX=pos.x+(DIVISOR_WIDTH/2);
			SET_COLOR(HIGHLIGHT_COLOR);
			DRAW_LINE(divX,divY,divX,divY+divLen);
			pos.x+=DIVISOR_WIDTH;
			empty = true;
		}
	}
}

//GUI_VBar
GUI_VBar::GUI_VBar(vector<GUI_Element*>& v,uint height,const Vec2& pos):GUI_Array(v,pos) {
	if (height)
		box.h=height;
	else{
		box.h=0;
		for (auto& it:array) {
			if (it) box.h += it->GetBox().h;
			else box.h+=DIVISOR_WIDTH;
		}
	}

	int w;
	for (auto& it:array) {
		if (it) {
			w = it->GetBox().w;
			if (w>box.w)
				box.w=w;
		}
	}
}

void GUI_VBar::render() {
	Vec2 pos(box.x,box.y);
	int divX=pos.x+DEFAULT_MARGIN;
	int divY;
	int divLen=box.w-(DEFAULT_MARGIN*2);
	bool empty = false;
	SDL_Rect bg = box.sdlRect();

	SET_COLOR(BASE_COLOR);
	FILL_RECT(&bg);
	for (auto& it:array) {
		if (it) {
			if (it->IsVisible()) {
				it->SetPos(pos);
				it->render();
				pos.y+=it->GetBox().h;
				empty = false;
			}
		}
		else if (!empty) {
			divY=pos.y+(DIVISOR_WIDTH/2);
			SET_COLOR(HIGHLIGHT_COLOR);
			DRAW_LINE(divX,divY,divX+divLen,divY);
			pos.y+=DIVISOR_WIDTH;
			empty = true;
		}
	}
}

//GUI_Window
GUI_Window::GUI_Window(vector<GUI_Element*>& v,int i,const string& l,const Vec2& pos):GUI_Element(pos),array{v},label{l,DEFAULT_FONT_SIZE},closeButton{GUI_CLOSE,ICON_X},id{i}{
	box.w = array.GetBox().w;
	box.h = array.GetBox().h + DEFAULT_HEIGHT;
	if (pos == Vec2(-1,-1)) {
		box.x = (WINSIZE.x-box.w)/2;
		box.y = (WINSIZE.y-box.h)/2;
	}

	label.set_hotspot(LEFT);
  GUI.select_gui_window(this);

}

void GUI_Window::update() {
	if (pop) {
		GUI.request_gui_element_pop(this);
		return;
	}
	
	bool hover=box.contains(INPUT.get_mouse_position());
	if (!hover) { 
		if (INPUT.mouse_button_pressed(MBUTTON_LEFT))
			GUI.select_gui_window(nullptr);
		return;
	}
	
	if (INPUT.mouse_button_pressed(MBUTTON_LEFT))
		GUI.select_gui_window(this);
	closeButton.update();
	if (GUI.gui_button_was_clicked(GUI_CLOSE)||GUI.gui_button_was_clicked(GUI_CONFIRM)||GUI.gui_button_was_clicked(GUI_DENY))
		pop = true;
	array.update();
}
void GUI_Window::render() {
	SDL_Rect rect = box.sdlRect();

	SET_COLOR(SHADOW_COLOR);
	CLIP_RECT(rect,-1);
	DRAW_RECT(&rect);

	SET_COLOR(BASE_COLOR);
	CLIP_RECT(rect,1);
	rect.h = DEFAULT_HEIGHT;
	FILL_RECT(&rect);
	label.set_box_position({box.x+DEFAULT_MARGIN,box.y+(DEFAULT_HEIGHT/2)});
	Rect textClip{0,0,box.w-(DEFAULT_WIDTH+DEFAULT_MARGIN),DEFAULT_FONT_SIZE+2};
	label.render({0,0}, &textClip);
	closeButton.SetPos({box.x+box.w-DEFAULT_WIDTH-1,box.y});
	closeButton.render();

	array.SetPos({box.x,box.y+DEFAULT_HEIGHT});
	array.render();
}
