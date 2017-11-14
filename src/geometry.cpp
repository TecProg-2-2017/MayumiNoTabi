/*
 * File: geometry.cpp
 *
 * Description: Generate the geometry of game.
 */

#include <geometry.hpp>
#include <camera.hpp>

/**
	Prototypes from geometry methods.
*/

Vec2::Vec2(const float &a,const float &b):x{a},y{b};
Vec2::Vec2(const Vec2 &b):x{b.x},y{b.y};
Vec2 Vec2::makeVec2(const float &object_lenght,const float &angle);
Vec2 Vec2::operator= (const Vec2& b);
Vec2 Vec2::operator+ (const Vec2& b);
void Vec2::operator+= (const Vec2& b);
Vec2 Vec2::operator- (const Vec2& b);
void Vec2::operator-= (const Vec2& b);
Vec2 Vec2::operator* (const float& r);
void Vec2::operator*= (const float& ratio);
Vec2 Vec2::operator/ (const float& ratio);
void Vec2::operator/= (const float& r);
bool Vec2::operator== (const Vec2& b);
bool Vec2::operator!= (const Vec2& b);
bool Vec2::operator< (const Vec2& b);
void Vec2::floor();
float Vec2::std::vector_lenght();
float Vec2::angle();
float Vec2::distance(const Vec2 &b);
float Vec2::angle(const Vec2 &position);
Vec2 Vec2::unit();
Vec2 Vec2::renderPosition();
Vec2 Vec2::rotate(float angle);
ConvexPolygon Vec2::polygon();
std::ostream& operator<< (std::ostream& os, const Vec2& obj);
Rect::Rect(const float &side_a,const float &side_b,const float &side_c,
	         const float &side_d):x{a},y{b},w{c},h{d};
Rect::Rect(const Vec2 &position,const Vec2 &object_size):x{pos.x}, \
                                       y{pos.y},w{sz.x},h{sz.y};
Rect::Rect(const Rect &b):x{b.x},y{b.y},w{b.w},h{b.h};
Rect Rect::operator= (const Rect& b);
Rect Rect::operator+ (const Vec2& b);
void Rect::operator+= (const Vec2& b);
Rect Rect::operator- (const Vec2& b);
void Rect::operator-= (const Vec2& b);
bool Rect::operator== (const Rect& b);
bool Rect::operator!= (const Rect& b);
void Rect::floor();
void Rect::setPosition(const Vec2& b);
void Rect::setCenter(const Vec2& b);
float Rect::x2();
float Rect::y2();
Vec2 Rect::distCenter(const Rect& b);
Vec2 Rect::distEdge(const Rect& b);
Vec2 Rect::hotspot(Hotspot object_hotspot);
Vec2 Rect::corner();
Vec2 Rect::corner2();
Vec2 Rect::corner3();
Vec2 Rect::corner4();
Vec2 Rect::center();
Vec2 Rect::size();
Vec2 Rect::relativePosition(const Vec2 &relative, bool inverted);
Rect Rect::relativeBox(const Rect &relative,bool inverted);
Rect Rect::renderBox();
Rect Rect::sum(const Rect &other);
ConvexPolygon Rect::polygon(const float &r);
SDL_Rect Rect::sdlRect();
bool Rect::contains(const float &i,const float &j);
bool Rect::contains(const Vec2& b);
bool Rect::collides(const Rect& b);
std::ostream& operator<<(std::ostream& os, const Rect& obj);
Circle::Circle(float xx,float yy,float rr):x{xx},y{yy},r{rr};
bool Circle::contains(const Vec2 &p);
bool Circle::contains(const float &px,const float &py);
void Circle::floor();
ConvexPolygon::ConvexPolygon():count{0};
ConvexPolygon::ConvexPolygon(vector<Vec2> v,bool all):count{0};
bool ConvexPolygon::AddPoint(Vec2 p);
bool ConvexPolygon::AddPoints(const vector<Vec2> &pts,bool all);
bool ConvexPolygon::RemovePoint(Vec2 p);
bool ConvexPolygon::RemovePoint(int ind);
void ConvexPolygon::SetSource(const Vec2 &p);
void ConvexPolygon::MoveSource(const Vec2 &p);
void ConvexPolygon::ReorderPoints();
void ConvexPolygon::ReorderPoints(vector<Vec2> &pts,map<Vec2,float> &ptsAng);
vector<Vec2> ConvexPolygon::GetPoints();
const Vec2& ConvexPolygon::GetSource();
Vec2 ConvexPolygon::GetCenter();
int ConvexPolygon::GetCount();
float ConvexPolygon::GetPointAng(const Vec2& p);
float ConvexPolygon::GetPointAng(int ind);
bool ConvexPolygon::IsConvex(const Vec2 &p);
bool ConvexPolygon::IsConvex(const vector<Vec2> &pts);
bool ConvexPolygon::Contains(Vec2 p);
bool ConvexPolygon::Collides(const ConvexPolygon& other);
ConvexPolygon ConvexPolygon::operator+(const Vec2& p);
ConvexPolygon ConvexPolygon::operator*(const float& f);
void ConvexPolygon::Floor();
Rect ConvexPolygon::BoundingRect();
ConvexPolygon ConvexPolygon::AtOrigin();
ConvexPolygon ConvexPolygon::MinkowskySum(const ConvexPolygon& polygon);
std::ostream& operator<<(std::ostream& os, const ConvexPolygon& obj);


//! A constructor.
    /*!
    This is a constructor method of Vec2 class
		@param &a Dimension of angle
		@param &b Dimension of angle
		@warning Method that requires review of comment
		*/

Vec2::Vec2(const float &a,const float &b):x{a},y{b} {
	// Nothing to do
}

//! A constructor.
    /*!
    This is a constructor method of Vec2 class
		@param &b
		@warning Method that requires review of comment
		*/

Vec2::Vec2(const Vec2 &b):x{b.x},y{b.y} {
	assert(&b != NULL);
	// Nothing to do
}

/*!
	@fn Vec2 Vec2::makeVec2(const float &len,const float &ang)
	@brief Method that creates a Vector2
	@param &object_lenght - Lenght of vector
	@param &angle - Angle of polygon
	@return The execution of this method returns a Vec2 with
	@warning Method that requires review of comment
*/

Vec2 Vec2::makeVec2(const float &object_lenght,const float &angle) {
	LOG_METHOD_START("Vec2::makeVec2");
	LOG_VARIABLE("&object_lenght", &object_lenght);
	LOG_VARIABLE("&angle", &angle);
	assert(&object_lenght != NULL);
	assert(&angle != NULL);

	Vec2 vector {object_lenght,0.0f};
	LOG_METHOD_CLOSE("Vec2::makeVec2", vector.rotate(angle));
	return vector.rotate(angle);
}

/*!
	@fn Vec2 Vec2::operator=(const Vec2& b)
	@brief Method that changes the items form vector2
	@param b
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::operator= (const Vec2& b) {
	LOG_METHOD_START("Vec2::operator=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);

	x_axis = b.x_axis; // x_axis is the axis x in cordinates.
	y_axis = b.y_axis; // y_axis is the axis y in cordinates.
	LOG_METHOD_CLOSE("Vec2::operator=", *this);
	return *this;
}

/*!
	@fn Vec2 Vec2::operator=(const Vec2& b)
	@brief Method that changes the items form vector2
	@param b A vector2
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::operator+ (const Vec2& b)const {
	LOG_METHOD_START("Vec2::operator+");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Vec2::operator+", {x_axis + b.x_axis, y_axis + b.y_axis});
	return {x_axis + b.x_axis, y_axis + b.y_axis};
}

/*!
	@fn Vec2 Vec2::operator+=(const Vec2& b)
	@brief Method that increments the items form vector2
	@param b A Vector 2
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

void Vec2::operator+= (const Vec2& b) {
	LOG_METHOD_START("Vec2::operator+=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);

	x_axis += b.x_axis; // x_axis is the axis x in cordinates.
	y_axis += b.y_axis; // y_axis is the axis y in cordinates.
}

/*!
	@fn Vec2 Vec2::operator - (const Vec2& b)
	@brief Method that changes the items from vector2 with operator -
	@param b
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::operator- (const Vec2& b)const {
	LOG_METHOD_START("Vec2::operator-");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Vec2::operator-", {x_axis - b.x_axis, y_axis - b.y_axis});
	return {x_axis - b.x_axis, y_axis - b.y_axis};
}

/*!
	@fn Vec2 Vec2::operator - (const Vec2& b)
	@brief Method that changes the items from vector2 with operator -=
	@param b
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Vec2::operator-= (const Vec2& b) {
	LOG_METHOD_START("Vec2::operator-=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	x_axis -= b.x_axis; // x_axis is the axis x in cordinates.
	y_axis -= b.y_axis; // y_axis is the axis y in cordinates.
}

/*!
	@fn Vec2 Vec2::operator - (const Vec2& b)
	@brief Method that changes the items form vector2
	@param r - rotation of object or a radio of a circle polygon
	@return The execution of this method returns Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::operator* (const float& r)const{
	LOG_METHOD_START("Vec2::operator*");
	LOG_VARIABLE("&b", &b);
	assert(&r != NULL);
	LOG_METHOD_CLOSE("Vec2::operator*", {x_axis*r, y_axis*r});
	return {x_axis*r, y_axis*r};
}

/*!
	@fn Vec2 Vec2::operator - (const Vec2& b)
	@brief Method that changes the items form vector2
	@param r - rotation of object or a radio of a circle polygon
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Vec2::operator*= (const float& ratio) {
	LOG_METHOD_START("Vec2::operator*=");
	LOG_VARIABLE("&ratio", &ratio);
	assert(&pos != NULL);
	x_axis *= ratio; // x_axis is the axis x in cordinates. r is rotation from object
	y_axis *= ratio; // y_axis is the axis y in cordinates. r is rotation from object
}

/*!
	@fn Vec2 Vec2::operator/ (const float& r)
	@brief Method that changes the items form vector2
	@param r - ratio of a circle object
	@return The execution of this method returns Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::operator/ (const float& ratio)const {
	LOG_METHOD_START("Vec2::operator/");
	LOG_VARIABLE("&ratio", &ratio);
	assert(&ratio != NULL);
	LOG_METHOD_CLOSE("Vec2::operator/", {x_axis / ratio, y_axis / ratio});
	return {x_axis / ratio, y_axis / ratio};
}

/*!
	@fn void Vec2::operator/=(const float& r)
	@brief Method that changes the items form vector2
	@param r - rotation of object
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Vec2::operator/= (const float& r) {
	LOG_METHOD_START("Vec2::operator/=");
	LOG_VARIABLE("&r", &r);
	assert(&r != NULL);
	x_axis /= r; // x_axis is the axis x in cordinates. r is rotation from object
	y_axis /= r; // y_axis is the axis y in cordinates. r is rotation from object
}

/*!
	@fn bool Vec2::operator==(const Vec2& b)
	@brief Method that compairs the items from vector2
	@param b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Vec2::operator== (const Vec2& b) const {
	LOG_METHOD_START("Vec2::operator==");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Vec2::operator==", (equals(x_axis, b.x_axis) &&
																	equals(y_axis, b.y_axis)));
	return (equals(x_axis, b.x_axis) && equals(y_axis, b.y_axis));
}

/*!
	@fn Vec2::operator!=(const Vec2& b)
	@brief Method that compairs the items from vector2
	@param b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Vec2::operator!= (const Vec2& b) const {
	LOG_METHOD_START("Vec2::operator!=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Vec2::operator!=", !((*this) == b));

	return !((*this) == b);
}

/*!
	@fn Vec2::operator < (const Vec2& b)
	@brief Method that compairs the items from vector2
	@param b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Vec2::operator< (const Vec2& b) const {
	LOG_METHOD_START("Vec2::operator<");
	LOG_VARIABLE("&b", &rb);
	assert(&pos != NULL);

	if (x_axis == b.x_axis) {
		return (y_axis < b.y_axis);
	}
	else {
		// Nothing to do
	}
	LOG_METHOD_CLOSE("Vec2::operator<", x_axis < b.x_axis);

	return x_axis < b.x_axis;
}

/*!
	@fn Vec2::floor()
	@brief Method that stores the position in axis x and y in cartesian plan on
	game interface. It represents the floor of gui game.
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Vec2::floor() {
	LOG_METHOD_START("Vec2::floor");

	x_axis = std::floor(x_axis); // x_axis is axis x in cartesian plan
	y_axis = std::floor(y_axis); // y_axis is axis y in cartesian plan
}

/*!
	@fn Vec2::vector_lenght()
	@brief Method that calculate the lenght of vector between two points in
	plan, x and y.
	@return The execution of this method returns the hypotenuse in float
	@warning Method that requires review of comment
*/

float Vec2::std::vector_lenght() const {
	LOG_METHOD_START("Vec2::std::vector_lenght");
	LOG_METHOD_CLOSE("Vec2::std::vector_lenght", hypot(x,y));
	return hypot(x,y); // x and y are two points in vector
}

/*!
	@fn Vec2::angle()
	@brief Method that calculate the angle between the object this and axis x in
	plan.
	@return The execution of this method returns the angle in float
	@warning Method that requires review of comment
*/

float Vec2::angle() const {
	LOG_METHOD_START("Vec2::angle");

	float f = DEGREES(atan(y / x) + (x < 0 ? PI : 0));
	LOG_METHOD_CLOSE("Vec2::angle", ((f < 0) ? (360 + f) : (f)));

	return ((f < 0) ? (360 + f) : (f));
}

/*!
	@fn Vec2::distance(const Vec2 &b)
	@brief Method that calculate the lenght between the object this and point b in
	plan.
	@param b Point b in plan
	@return The execution of this method returns the angle in float
	@warning Method that requires review of comment
*/

float Vec2::distance(const Vec2 &b) const {
	LOG_METHOD_START("Vec2::distance");
	LOG_VARIABLE("b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Vec2::distance", ((*this) - b).lenght());
	return ((*this) - b).lenght();
}

/*!
	@fn  Vec2::angle(const Vec2 &b)
	@brief Method that calculate the angle between the object this and point b in
	plan.
	@param b Point b in plan
	@return The execution of this method returns the angle in float
	@warning Method that requires review of comment
*/

float Vec2::angle(const Vec2 &position) const {
	LOG_METHOD_START("Vec2::angle");
	LOG_VARIABLE("&position", &position);
	assert(&positon != NULL);

	if (*this == position) {
		return 0.0f;
	}
	else {
		// Nothing to do
	}
	LOG_METHOD_CLOSE("Vec2::angle", (position - (*this)).angle());

	return (position - (*this)).angle();
}

/*!
	@fn Vec2 Vec2::unit()
	@brief Method that get the unitary vector
	@return The execution of this method returns a vector Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::unit() const {
	LOG_METHOD_START("Vec2::unit");
	LOG_METHOD_CLOSE("Vec2::unit", (*this)/lenght());

	return (*this)/lenght(); // lenght of vector
}

/*!
	@fn Vec2 Vec2::renderPos()
	@brief Method that render the position like the camera
	@return The execution of this method returns a vector Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::renderPosition() const {
	LOG_METHOD_START("Vec2::renderPosition");
	LOG_METHOD_CLOSE("Vec2::renderPosition", RENDERPOS(*this));
	return RENDERPOS(*this);
}

/*!
	@fn Vec2 Vec2::rotate(float a)
	@brief Method that rotates the vector in a degrees
	@param angle Dimension of angle in degrees
	@return The execution of this method returns a vector Vec2
	@warning Method that requires review of comment
*/

Vec2 Vec2::rotate(float angle) {
	LOG_METHOD_START("Vec2::rotate");
	LOG_VARIABLE("angle", &angle);
	assert(angle != NULL);

	Vec2 vector = null; // Initializing the variable vector
	// Converts the angle to radianus. It's used by functions sin and cos
	angle = RAD(angle);

	vector.x_axis = x_axis*cos(angle) - y_axis*sin(angle);
	vector.y_axis = y_axis*cos(angle) + x_axis*sin(angle);

	LOG_METHOD_CLOSE("Vec2::rotate", vector);
	return vector;
}

/*!
	@fn ConvexPolygon Vec2::polygon()
	@brief Method that returns a semi straight defined by vector and origin
	@return The execution of this method returns a ConvexPolygon
	@warning Method that requires review of comment
*/

ConvexPolygon Vec2::polygon() {
	LOG_METHOD_START("Vec2::polygon");

	ConvexPolygon polygon = new ConvexPolygon(); // Initializing the polygon
	polygon.AddPoint({});
	polygon.AddPoint(*this);
	LOG_METHOD_CLOSE("Vec2::polygon", polygon);
	return polygon;
}

/*!
	@fn std::ostream& operator<< (std::ostream& os, const Vec2& obj)
	@brief Method that returns a semi straight defined by vector and origin
	@param os
	@param obj The object
	@return The execution of this method returns a Ostream
	@warning Method that requires review of comment
*/

std::ostream& operator<< (std::ostream& os, const Vec2& obj) {
	os << "(" << obj.x << "," << obj.y << ")";
	LOG_METHOD_START("std::ostream& operator");
	assert(&os != NULL);
	assert(&obj != NULL);
	LOG_METHOD_CLOSE("operator", os);
	return os;
}

//! A constructor.
    /*!
    This is a constructor method of Vec2 class
		@param &side_a Dimension of a rectangule side
		@param &side_b Dimension of a rectangule side
		@param &side_c Dimension of a rectangule side
		@param &side_d Dimension of a rectangule side
		@warning Method that requires review of comment
		*/

Rect::Rect(const float &side_a,const float &side_b,const float &side_c,
	         const float &side_d):x{a},y{b},w{c},h{d} {
	LOG_METHOD_START("Rect::Rect");
	LOG_VARIABLE("&side_a", &side_a);
  LOG_VARIABLE("&side_b", &side_b);
	LOG_VARIABLE("&side_c", &side_c);
	LOG_VARIABLE("&side_d", &side_d);
	assert(&side_a != NULL);
	assert(&side_b != NULL);
	assert(&side_c != NULL);
	assert(&side_d != NULL);
	// Nothing to do
}

//! A constructor.
     /*!
		    This is a constructor method of Vec2 class
				@param &position Dimension of a rectangule side
				@param &object_size Dimension of a rectangule side
				@warning Method that requires review of comment
			*/

Rect::Rect(const Vec2 &position, const Vec2 &object_size):x{pos.x}, \
                                       y{pos.y}, w{sz.x}, h{sz.y} {

		 LOG_METHOD_START("Rect::Rect");
	 	 LOG_VARIABLE("&position", &position);
	   LOG_VARIABLE("&object_size", &object_size);
		 LOG_VARIABLE("x{pos.x}", x{pos.x});
		 LOG_VARIABLE("y{pos.y}", y{pos.y});
		 LOG_VARIABLE("w{sz.x}", w{sz.x});
		 LOG_VARIABLE("h{sz.y}", h{sz.y});
		 assert(&position != NULL);
		 assert(&object_size != NULL);

		 //Nothing to do
}

Rect::Rect(const Rect &b):x{b.x},y{b.y},w{b.w},h{b.h} {
	LOG_METHOD_START("Rect::Rect");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_VARIABLE("x{b.x}", x{b.x});
	LOG_VARIABLE("y{b.y}", y{b.y});
	LOG_VARIABLE("w{b.w}", w{b.w});
	LOG_VARIABLE("h{b.h}", h{b.h});
	// Nothing to do
}

/*!
	@fn Rect Rect::operator= (const Rect& b)
	@brief Method that changes the items form vector2
	@param b A Rect
	@return The execution of this method returns a Rect
	@warning Method that requires review of comment
*/

Rect Rect::operator= (const Rect& b) {
	LOG_METHOD_START("Rect::operator=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	x_axis = b.x_axis;
	y_axis = b.y_axis;
	w_axis = b.w_axis;
	h_axis = b.h_axis;

	LOG_METHOD_CLOSE("Rect::operator=", *this);
	return *this;
}

/*!
	@fn Rect Rect::operator+ (const Vec2& b)
	@brief Method that changes the items form vector2
	@param b
	@return The execution of this method returns a Rect
	@warning Method that requires review of comment
*/

Rect Rect::operator+ (const Vec2& b) const {
	LOG_METHOD_START("Rect::operator+");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Rect::operator+", {x_axis + b.x_axis, y_axis + b.y_axis, \
		               w, h});

	return {x_axis + b.x_axis, y_axis + b.y_axis, w, h};
}

/*!
	@fn Rect::operator+= (const Vec2& b)
	@brief Method that changes the items from vector2
	@param b
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Rect::operator+= (const Vec2& b) {
	LOG_METHOD_START("Rect::operator+=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);

	x_axis += b.x_axis;
	y_axis += b.y_axis;
}

/*!
	@fn Rect::operator- (const Vec2& b)
	@brief Method that changes the items form vector2
	@param b
	@return The execution of this method returns a Rect
	@warning Method that requires review of comment
*/

Rect Rect::operator- (const Vec2& b) const {
	LOG_METHOD_START("Rect::operator-");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Rect::operator-", \
	                 Rect(x_axis - b.x_axis, y_axis - b.y_axis, w, h));

	return Rect(x_axis - b.x_axis, y_axis - b.y_axis, w, h);
}

/*!
	@fn Rect::operator-= (const Vec2& b)
	@brief Method that changes the items from vector2
	@param b
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Rect::operator-= (const Vec2& b) {
	LOG_METHOD_START("Rect::operator-=");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);

	x_axis -= b.x_axis;
	y_axis-= b.y_axis;
}

/*!
	@fn bool Rect::operator== (const Rect& b)
	@brief Method that changes the items from Rect
	@param b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Rect::operator== (const Rect& b) {
	LOG_METHOD_START("Rect::operator==");
	LOG_VARIABLE("&b", &b);
	assert(&b != NULL);

	LOG_METHOD_CLOSE("Rect::operator==", (equals(x,b.x) && equals(y,b.y) &&
	                                      equals(w,b.w) && equals(h,b.h)));


	return (equals(x,b.x) && equals(y,b.y) && equals(w,b.w) && equals(h,b.h));
}

/*!
	@fn bool Rect::operator!= (const Rect& b)
	@brief Method that changes the items from Rect
	@param b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Rect::operator!= (const Rect& b) {
	LOG_METHOD_START("Rect::operator!=");
  LOG_VARIABLE("b", &b);
	assert(&b != NULL);
  LOG_METHOD_CLOSE("Rect::operator!=", !((*this) == b));

	return !((*this) == b);
}

/*!
	@fn bool Rect::operator== (const Rect& b)
	@brief Method that take the less value from x_axis, y_axis and weight and
	height
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Rect::floor() {
	LOG_METHOD_START("Rect::floor");

	x_axis = std::floor(x_axis);
	y_axis = std::floor(y_axis);
	w_axis = std::floor(w_axis);
	h_axis = std::floor(h_axis);
}

/*!
	@fn void Rect::setPos(const Vec2& b)
	@brief Method that sets the position from vector
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Rect::setPosition(const Vec2& b) {
	LOG_METHOD_START("Rect::setPosition");
	assert(&b != NULL);
	x_axis = b.x_axis;
	y_axis = b.y_axis;
}

/*!
	@fn void Rect::setCenter(const Vec2& b)
	@brief Method that sets the center position from vector
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Rect::setCenter(const Vec2& b) {
	LOG_METHOD_START("Rect::setCenter");
	assert(&b != NULL);
	x_axis = b.x_axis - (w/2);
	y_axis = b.y_axis - (h/2);
}

/*!
	@fn float Rect::x2()
	@brief Method that calculate a second x_axis position in plan
	@return The execution of this method returns a second x_axis position in float
	@warning Method that requires review of comment
*/

float Rect::x2() const {
	LOG_METHOD_START("Rect::x2");
	LOG_METHOD_CLOSE("Rect::x2", x_axis + weight);
	return x_axis + weight;
}

/*!
	@fn float Rect::y2()
	@brief Method that calculate a second y_axis position in plan
	@param b
	@return The execution of this method returns a second y_axis position in float
	@warning Method that requires review of comment
*/

float Rect::y2() const {
	LOG_METHOD_START("Rect::y2");
	LOG_METHOD_CLOSE("Rect::y2", y_axis + height);
	return y_axis + height;
}

/*!
	@fn Vec2 Rect::distCenter(const Rect& b)
	@brief Method that calculate the distance between the centers of rectangles
	@param b
	@return The execution of this method returns a Vec2 with the distance
	@warning Method that requires review of comment
*/

Vec2 Rect::distCenter(const Rect& b) const {
	LOG_METHOD_START("Rect::distCenter");
	assert(&b != NULL);
	LOG_METHOD_CLOSE("Rect::distCenter", center() - b.center());
	return center() - b.center();
}

/*!
	@fn Vec2 Rect::distCenter(const Rect& b)
	@brief Method that calculate the distance between the points closers from rectangles
	@param b
	@return The execution of this method returns a Vec2 with the distance
	@warning Method that requires review of comment
*/

Vec2 Rect::distEdge(const Rect& b) const {
	LOG_METHOD_START("Rect::distEdge");
  LOG_VARIABLE("b", &b);
	assert(&b != NULL);

	Vec2 rectangle;

	if (!collides(b)) {
		if (!BETWEEN(x_axis,b.x_axis,b.x2()) && !BETWEEN(b.x_axis,x_axis,x2())) {
					rectangle.x_axis = min(abs(x_axis-(b.x2())),abs((x2())-b.x_axis));
		}
		else {
			//! Nothing to do
		}
		if (!BETWEEN(y_axis,b.y_axis,b.y2()) && !BETWEEN(b.y_axis,y_axis,y2())) {
			rectangle.y_axis = min(abs(y_axis-(b.y2())),abs((y2())-b.y_axis));
		}
		else {
			//! Nothing to do
		}
	}
	else {
		//! Nothing to do
	}
	LOG_METHOD_CLOSE("Rect::distEdge", rectangle);

	return rectangle;
}

/*!
	@fn Rect::hotspot(Hotspot object_hotspot)
	@brief Method that generate an other vector with a object_hotspot
	@param object_hotspot
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::hotspot(Hotspot object_hotspot) {
	LOG_METHOD_START("Rect::hotspot");
  LOG_VARIABLE("b", &b);
	assert(&b != NULL);

	Vec2 object_vector{x_axis, y_axis};
	auto &add = HotspotPos[object_hotspot];
	object_vector.x_axis -= weight * add.first;
	object_vector.y_axis -= height * add.second;

	LOG_METHOD_CLOSE("Rect::hotspot", object_vector);
	return object_vector;
}

/*!
	@fn Rect::corner()
	@brief Method that calculate the point left superior from rectangle
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::corner() const {
	LOG_METHOD_START("Rect::corner");
  LOG_METHOD_CLOSE("Rect::corner", {x_axis, y_axis});

	return {x_axis, y_axis};
}

/*!
	@fn Rect::corner2()
	@brief Method that calculate the point right superior from rectangle
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::corner2() const {
	LOG_METHOD_START("Rect::corner2");
  LOG_METHOD_CLOSE("Rect::corner2", {x2(),y_axis});

	return {x2(),y_axis};
}

/*!
	@fn Rect::corner3()
	@brief Method that calculate the point left inferior from rectangle
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::corner3() const {
	LOG_METHOD_START("Rect::corner3");
  LOG_METHOD_CLOSE("Rect::corner3", {x_axis,y2()});
	return {x_axis,y2()};
}

/*!
	@fn Rect::corner3()
	@brief Method that calculate the point right inferior from rectangle
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::corner4() const {
	LOG_METHOD_START("Rect::corner4");
  LOG_METHOD_CLOSE("Rect::corner4", {x2(),y2()});

	return {x2(),y2()};
}

/*!
	@fn Rect::center()
	@brief Method that calculate the center point from rectangle
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::center() const {
	LOG_METHOD_START("Rect::center");
  LOG_METHOD_CLOSE("Rect::center", {x_axis + (weight/2), y_axis + (height/2)});

	return {x_axis + (weight/2), y_axis + (height/2)};
}

/*!
	@fn Rect::size()
	@brief Method that calculate the rectangle size
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::size() const {
	LOG_METHOD_START("Rect::size");
  LOG_METHOD_CLOSE("Rect::size", {weight, height});
	return {weight, height};
}

/*!
	@fn Rect::relativePosition(const Vec2 &relative,bool inverted)
	@brief Method that calculate the relative posit ion of rectangle in the displayd
	@param &relative Relative position
	@param inverted The status of rectangle, inverted or not
	@return The execution of this method returns a Vec2
	@warning Method that requires review of comment
*/

Vec2 Rect::relativePosition(const Vec2 &relative, bool inverted) const {
	LOG_METHOD_START("Rect::relativePosition");
  LOG_VARIABLE("&relative", &relative);
	LOG_VARIABLE("inverted", inverted);
	assert(&relative != NULL);
	assert(&inverted != NULL);

	Vec2 positon {x_axis, y_axis};
	if (inverted) {
		position.x_axis +=  relative.x_axis  * weight;
	}
	else {
		 position.x_axis += (1-relative.x_axis) * weight;
	}
	position.y_axis += relative.y_axis * height;

  LOG_METHOD_CLOSE("Rect::relativePosition", position);

	return position;
}

/*!
	@fn Rect::relativeBox(const Rect &relative,bool inverted)
	@brief Method that calculate the relative position from rectangle according
	 camera
	@param &relative Relative position
	@param inverted The status of rectangle, inverted or not
	@return The execution of this method returns a Rect
	@warning Method that requires review of comment
*/

Rect Rect::relativeBox(const Rect &relative, bool inverted) const {
	LOG_METHOD_START("Rect::relativeBox");
  LOG_VARIABLE("&relative", &relative);
	LOG_VARIABLE("inverted", inverted);
	assert(&relative != NULL);
	assert(&inverted != NULL);

	Rect box{x_axis, y_axis, weight, height};
	if (inverted) {
		box.x_axis +=    relative.x_axis  * weight;
	}
	else {
		box.x_axis += (1-relative.x_axis) * weight;
	}
	box.y_axis += relative.y_axis * height;
	box.weight *= relative.weight;
	box.height *= relative.height;

	LOG_METHOD_CLOSE("Rect::relativeBox", box);
	return box;
}

/*!
	@fn Rect::renderBox()
	@brief Method that calculate the render position from rectangle according
	camera
	@return The execution of this method returns a Rect
	@warning Method that requires review of comment
*/

Rect Rect::renderBox() const {
	LOG_METHOD_START("Rect::renderBox");
  LOG_METHOD_CLOSE("Rect::renderBox", {RENDERPOSX(x), RENDERPOSY(y), \
		                                 w * CAMERAZOOM, h * CAMERAZOOM});

	return {RENDERPOSX(x), RENDERPOSY(y), w * CAMERAZOOM, h * CAMERAZOOM};
}

/*!
	@fn Rect::sum(const Rect &other)
	@brief Method that calculate the render position from rectangle according
	camera
	@return The execution of this method returns a Rect
	@warning Method that requires review of comment
*/

Rect Rect::sum(const Rect &other) const {
	LOG_METHOD_START("Rect::sum");
  LOG_VARIABLE("other", &other);
	assert(&other != NULL);

	float x_axis = min(min(x,x2()),min(other.x,other.x2()));
	float y_axis = min(min(y,y2()),min(other.y,other.y2()));
	float xx = max(max(x,x2()),max(other.x,other.x2()));
	float yy = max(max(y,y2()),max(other.y,other.y2()));

	LOG_METHOD_CLOSE("Rect::sum", Rect{x,y,xx - x,yy - y});
	return Rect{x,y,xx - x,yy - y};
}

/*!
	@fn ConvexPolygon Rect::polygon(const float &r)
	@param &r The indices of radio, distance between center and board of polygon
	@brief Method that generate a polygon rectangle
	@return The execution of this method returns a ConvexPolygon
	@warning Method that requires review of comment
*/

ConvexPolygon Rect::polygon(const float &r) const {
	LOG_METHOD_START("Rect::polygon");
  LOG_VARIABLE("r", &r);
	assert(&r != NULL);

	ConvexPolygon polygon = new ConvexPolygon(); // Initializing a convex polygon
	polygon.AddPoint(Vec2{});
	polygon.AddPoint(Vec2{w,0.0f}.rotate(r));
	polygon.AddPoint(Vec2{0.0f,h}.rotate(r));
	polygon.AddPoint(Vec2{w,h}.rotate(r));
	polygon.MoveSource(corner());

	LOG_METHOD_CLOSE("Rect::polygon", polygon);
	return polygon;
}

/*!
	@fn SDL_Rect Rect::sdlRect()
	@brief Method that generate a rectangle
	@return The execution of this method returns a SDL_Rect
	@warning Method that requires review of comment
*/

SDL_Rect Rect::sdlRect()const {
	LOG_METHOD_START("Rect::sdlRect");

	SDL_Rect rect = new SDL_Rect();
	rect.x_axis = x_axis;
	rect.y_axis = y_axis;
	rect.w = w;
	rect.h = h;

	LOG_METHOD_CLOSE("Rect::sdlRect", rect);
	return rect;
}

/*!
	@fn Rect::contains(const float &i,const float &j)
	@brief Method that verifies the contains of the rectangle
	@param &i
	@param &j
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Rect::contains(const float &i,const float &j) const {
	LOG_METHOD_START("Rect::contains");
  LOG_VARIABLE("&i", &i);
  LOG_VARIABLE("&j", &j);
	assert(&i != NULL);
	assert(&j != NULL);

		if (i < x) {
		return false;
	}
	else {
		//! Nothing to do
	}

	if (i > x2()) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (j < y) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (j > y2()) {
		return false;
	}
	else {
		// Nothing to do
	}

	// LOG_METHOD_CLOSE("Rect::sdlRect", rect);
	return true;
}

/*!
	@fn ConvexPolygon Rect::polygon(const float &r)
	@brief Method that verifies the contains of the rectangle
	@param &b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Rect::contains(const Vec2& b) const {
	LOG_METHOD_START("Rect::contains");
  LOG_VARIABLE("b", &b);
	assert(&b != NULL);

	if (b.x < x) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (b.x > x2()) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (b.y < y) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (b.y > y2()) {
		return false;
	}
	else {
		// Nothing to do
	}

	LOG_METHOD_CLOSE("Rect::contains", ((*this) - b).lenght());
	return true;
}

/*!
	@fn Rect::collides(const Rect& b)
	@brief Method that verifies if there's a collision with rectangle
	@param &b
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool Rect::collides(const Rect& b) const{
	// if (BETWEEN(x,b.x,b.x2()))return true;
	// if (BETWEEN(b.x,x,x2()))return true;
	// if (BETWEEN(y,b.y,b.y2()))return true;
	// if (BETWEEN(b.y,y,y2()))return true;
	// return false;
	LOG_METHOD_START("Rect::collides");
  LOG_VARIABLE("b", &b);
	assert(&b != NULL);

	if (x > (b.x2())) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (y > (b.y2())) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (b.x > (x2())) {
		return false;
	}
	else {
		// Nothing to do
	}

	if (b.y > (y2())) {
		return false;
	}
	else {
		// Nothing to do
	}

	//LOG_METHOD_CLOSE("Rect::collides", ((*this) - b).lenght());
	return true;
}

std::ostream& operator<<(std::ostream& os, const Rect& obj) {
	os << "(" << obj.x << "," << obj.y << "," << obj.w << "," << obj.h << ")";
	assert(&os != NULL);
	assert(&obj != NULL);

	return os;
}

//! A constructor.
    /*!
    This is a constructor method of Circle class
		@param xx
		@param yy
		@param rr The radio from circle
		@warning Method that requires review of comment
		*/

Circle::Circle(float xx,float yy,float rr):x{xx},y{yy},r{rr} {
	LOG_METHOD_START("Circle::Circle");
	LOG_VARIABLE("xx", xx);
	LOG_VARIABLE("yy", yy);
	LOG_VARIABLE("rr", rr);
	assert(xx != NULL);
	assert(yy != NULL);
	assert(rr != NULL);
	// Nothing to do
}

/*!
	@fn Circle::contains(const Vec2 &p)
	@brief Method that verifies if the circle contains the point
	@param &p The point to be verified
	@return The execution of this method returns a bool, if the point belows from
	circle
	@warning Method that requires review of comment
*/

bool Circle::contains(const Vec2 &p)const {
	LOG_METHOD_START("Circle::contains");
  LOG_VARIABLE("&p", &p);
	assert(&p != NULL);

	Vec2 center(x,y) = new Vec2(); // Initializing the vector

	LOG_METHOD_CLOSE("Circle::contains", (center - p).len() <= r);
	return (center - p).len() <= r;
}

/*!
	@fn Circle::contains(const float &px,const float &py)
	@brief Method that verifies if the circle contains the point
	@param &px The point in x_axis to be verified
	@param &py The point in y_axis to be verified
	@return The execution of this method returns a bool, if the point belows from
	circle
	@warning Method that requires review of comment
*/

bool Circle::contains(const float &px,const float &py)const {
	LOG_METHOD_START("Circle::contains");
  LOG_VARIABLE("&px", &px);
	LOG_VARIABLE("&py", &py);
	assert(&px != NULL);
	assert(&py != NULL);

	Vec2 center(x,y);
	Vec2 p(px,py);

	LOG_METHOD_CLOSE("Circle::contains", (center - p).len() <= r);
	return (center-p).len() <= r;
}

/*!
	@fn Circle::floor()
	@brief Method that assignes the points from circle on the floor
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Circle::floor() {
	LOG_METHOD_START("Circle::floor");

	x_axis = std::floor(x);
	y_axis = std::floor(y);
	r = std::floor(r);
}

/*!
	@fn ConvexPolygon::ConvexPolygon():count{0}
	@brief Method that starts the counter fromo polygons
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

ConvexPolygon::ConvexPolygon():count{0} {
	LOG_METHOD_START("ConvexPolygon::ConvexPolygon");

	// Nothing to do
}

/*!
	@fn ConvexPolygon::ConvexPolygon(vector<Vec2> v,bool all):count{0}
	@brief Method that adds points to polygon matched by points v and all
	@param v It's a point in vector
	@param all
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

ConvexPolygon::ConvexPolygon(vector<Vec2> v,bool all):count{0} {
	LOG_METHOD_START("ConvexPolygon::ConvexPolygon");
	LOG_VARIABLE("v", v);
	LOG_VARIABLE("all", all);
	assert(v != NULL);
	assert(all != NULL);

	AddPoints(v,all);
}

/*!
	@fn bool ConvexPolygon::AddPoint(Vec2 p)
	@brief Method that searchs points from the polygon
	@param p It's a vector2
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool ConvexPolygon::AddPoint(Vec2 p) {
	LOG_METHOD_START("ConvexPolygon::AddPoint");
  LOG_VARIABLE("p", p);
	assert(p != NULL);

	p -= GetSource();

	if (!count) {
		boundingRect += p;
	} else {
		if (boundingRect.x > p.x)boundingRect.x = p.x;
		else if (boundingRect.x2() < p.x) {
			boundingRect.w = p.x - boundingRect.x;
		}
		if (boundingRect.y > p.y) {
			boundingRect.y = p.y;
		}
		else if (boundingRect.y2() < p.y) {
			boundingRect.h = p.y-boundingRect.y;
		}
		else {
				// Nothing to do
		}
	}

	if (find(points.begin(), points.end(), p-GetSource()) != points.end()) {
		return false;
	}
	else if (!IsConvex(p)) {
		return false;
	}
	points.push_back(p);
	ReorderPoints();
	pointsAng[p] = points[0].angle(p);
	count++;

	//LOG_METHOD_CLOSE("ConvexPolygon::AddPoint", ((*this) - b).lenght());

	return true;
}

/*!
	@fn bool ConvexPolygon::AddPoints(const vector<Vec2> &pts,bool all)
	@brief Method that fix points from the polygon
	@param &pts It's a vector2
	@return The execution of this method returns a bool, false if no added points.
	@warning Method that requires review of comment
*/

bool ConvexPolygon::AddPoints(const vector<Vec2> &pts,bool all) {
	LOG_METHOD_START("ConvexPolygon::AddPoints");
  LOG_VARIABLE("&pts", &pts);
	LOG_VARIABLE("all", all);
	assert(&pts != NULL);
	assert(all != NULL);

	if (all) {
		ConvexPolygon polygon =* this;
		if (!polygon.AddPoints(pts)) {
			return false;
		}
		*this = polygon;
	}
	else {
		for (auto p:pts) {
			p -= GetSource();
			AddPoint(p);
		}
	}

  LOG_METHOD_CLOSE("ConvexPolygon::AddPoints", ((*this) - b).lenght());
	return true;
}

/*!
	@fn bool ConvexPolygon::RemovePoint(Vec2 p)
	@brief Method that removes points from the polygon
	@param p It's a vector2
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool ConvexPolygon::RemovePoint(Vec2 p) {
	LOG_METHOD_START("ConvexPolygon::RemovePoint");
  LOG_VARIABLE("p", p);
	assert(p != NULL);

	auto it = find(points.begin(), points.end(), p);

	LOG_METHOD_CLOSE("ConvexPolygon::RemovePoint", \
	                  RemovePoint(it - points.begin()));
	return RemovePoint(it - points.begin());
}

/*!
	@fn bool ConvexPolygon::RemovePoint(int ind)
	@brief Method that removes points from the polygon
	@param ind It's a indices from vector's polygon
	@return The execution of this method returns a bool
	@warning Method that requires review of comment
*/

bool ConvexPolygon::RemovePoint(int ind) {
	LOG_METHOD_START("ConvexPolygon::RemovePoint");
  LOG_VARIABLE("ind", ind);
	assert(ind != NULL);

	if (ind < 0 || ind >= count) {
		return false;
	}
	else {
		// Nothing to do
	}

	pointsAng.erase(points[ind]);
	points.erase(points.begin() + ind);

	if (ind == 0) {
		ReorderPoints();
	}
	else {
		// Nothing to do
	}

	float x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	for (auto &p:points) {
		x1 = min(x1,p.x);
		x2 = max(x2,p.x);
		y1 = min(y1,p.y);
		y2 = max(y2,p.y);
	}

	boundingRect = Rect{x1,y1,x2-x1,y2-y1};

	// LOG_METHOD_CLOSE("ConvexPolygon::RemovePoint", RemovePoint(it - points.begin()));

	return true;
}

/*!
	@fn void ConvexPolygon::SetSource(const Vec2 &p)
	@brief Method that sets source points from polygon
	@param &p It's a reference to Vec2
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void ConvexPolygon::SetSource(const Vec2 &p) {
	LOG_METHOD_START("ConvexPolygon::SetSource");
  LOG_VARIABLE("p", p);
	assert(&p != NULL);

	Vec2 move = GetSource()-p;
	for (auto &i:points)i += move;
	source = p;
}

void ConvexPolygon::MoveSource(const Vec2 &p) {
	LOG_METHOD_START("ConvexPolygon::MoveSource");
  LOG_VARIABLE("p", p);
	assert(&p != NULL);
	source = p;
}

void ConvexPolygon::ReorderPoints() {
	LOG_METHOD_START("ConvexPolygon::ReorderPoints");
	ReorderPoints(points,pointsAng);
}

void ConvexPolygon::ReorderPoints(vector<Vec2> &pts, \
	   map<Vec2,float> &ptsAng)const {

		LOG_METHOD_START("ConvexPolygon::ReorderPoints");
	  LOG_VARIABLE("pts", &pts);
		LOG_VARIABLE("ptsAng", &ptsAng);
		assert(&pts != NULL);
		assert(&ptsAng != NULL);

	const auto &it = min_element(pts.begin(), pts.end(), \
	                    [](const Vec2& a,const Vec2& b) {
		if (equals(a.y,b.y)) {
			return a.x > b.x;
		}
		else {
			// Nothing to do
		}
		return a.y > b.y;
	});
	std::swap(*pts.begin(),*it);
	ptsAng.clear();
	for (auto &p:pts)ptsAng[p] = pts[0].angle(p);
	ptsAng[pts[0]] = 400;
	sort(pts.begin(), pts.end(), [&pts,&ptsAng](const Vec2 &a,const Vec2 &b) {
		return ptsAng[a] > ptsAng[b];
	});
	ptsAng[pts[0]] = 0;
}

vector<Vec2> ConvexPolygon::GetPoints()const {

	vector<Vec2> v;

	for (auto p:points) {
		v.push_back(p + GetSource());
	}

	return v;
}

const Vec2& ConvexPolygon::GetSource()const {
	LOG_METHOD_START("ConvexPolygon::GetSource");
  LOG_METHOD_CLOSE("ConvexPolygon::GetSource", source);
	return source;
}

Vec2 ConvexPolygon::GetCenter()const {
	LOG_METHOD_START("ConvexPolygon::GetSource");
  LOG_METHOD_CLOSE("ConvexPolygon::GetSource", source);
	Vec2 sum;

	for (auto p:points) {
		sum += p;
	}
	sum /= points.size();

	return sum + GetSource();
}

int ConvexPolygon::GetCount()const {
	LOG_METHOD_START("ConvexPolygon::GetCount");
  LOG_METHOD_CLOSE("ConvexPolygon::GetCount", count);
	return count;
}

float ConvexPolygon::GetPointAng(const Vec2& p)const {
	LOG_METHOD_START("ConvexPolygon::GetPointAng");
  LOG_VARIABLE("p", &p);
	assert(&p != NULL);

	if (pointsAng.count(p)) {
		return pointsAng.at(p);
	}
	else {
		// Nothing to do
	}
	LOG_METHOD_CLOSE("ConvexPolygon::GetPointAng", ((*this) - b).lenght());
	return 0.0f;
}

float ConvexPolygon::GetPointAng(int ind)const {
	LOG_METHOD_START("ConvexPolygon::GetPointAng");
  LOG_VARIABLE("ind", ind);
	assert(ind != NULL);
	LOG_METHOD_CLOSE("ConvexPolygon::GetPointAng", pointsAng.at(points[ind]));
	return pointsAng.at(points[ind]);
}

bool ConvexPolygon::IsConvex(const Vec2 &p) const {
	LOG_METHOD_START("ConvexPolygon::IsConvex");
  LOG_VARIABLE("&p", &p);
	assert(&p != NULL);

	if (count < 3) {
		return true;
	}
	else {
		// Nothing to do
	}
	vector<Vec2> v = points;
	map<Vec2,float> vAng = pointsAng;
	v.push_back(p - GetSource());
	ReorderPoints(v,vAng);
	v.push_back(v[0]);

	float prevAng = v[0].angle(v[1]), ang;
	for (int i = 1; i <= count; i++) {
		ang = v[i].angle(v[i + 1]);
		if (ang > prevAng) {
			return false;
		}
		else {
			// Nothing to do
		}
		prevAng = ang;
	}
	//LOG_METHOD_CLOSE("ConvexPolygon::IsConvex", pointsAng.at(points[ind]));

	return true;
}

bool ConvexPolygon::IsConvex(const vector<Vec2> &pts) const {
	LOG_METHOD_START("ConvexPolygon::IsConvex");
  LOG_VARIABLE("&pts", &pts);
	assert(&pts != NULL);

	vector<Vec2> v = points;
	map<Vec2,float> vAng = pointsAng;

	for (auto p:pts) {
		v.push_back(p - GetSource());
	}
	ReorderPoints(v,vAng);
	v.push_back(v[0]);

	float prevAng=v[1].angle(v[0]),ang;
	for (int i = 1; i <= count; i++) {
		ang = v[i+1].angle(v[i]);
		if (ang < prevAng) {
			return false;
		}
		else {
			// Nothing to do
		}
		prevAng = ang;
	}
	//LOG_METHOD_CLOSE("ConvexPolygon::IsConvex", pointsAng.at(points[ind]));
	return true;
}

bool ConvexPolygon::Contains(Vec2 p) const {
	LOG_METHOD_START("ConvexPolygon::Contains");
  LOG_VARIABLE("p", p);
	assert(p != NULL);

	if (count < 3) {
		return false;
	}
	else {
		// Nothing to do
	}
	p -= GetSource();
	float ang = 0.0f;
	vector<Vec2> v = points;
	v.push_back(v[0]);
	FOR(i,v.size()-1) {
		ang += p.angle(v[i+1]);
		ang -= p.angle(v[i]);
	}
	//LOG_METHOD_CLOSE("ConvexPolygon::IsConvex", pointsAng.at(points[ind]));
	return equals(ang,360.0f) || equals(ang,0.0f);
}

bool ConvexPolygon::Collides(const ConvexPolygon& other) const {
	LOG_METHOD_START("ConvexPolygon::Collides");
  LOG_VARIABLE("other", other);
	assert(&other != NULL);

	if (count < 3 || other.GetCount() < 3) {
		return false;//degenerated polygons dont collide
	}
	else {
		// Nothing to do
	}
	Rect a = BoundingRect();
	Rect b = other.BoundingRect();
	if ((a.x2() <= b.x) || (b.x2()<=a.x)) {
		return false;//if bounding boxes dont collide, no need
	}
	else {
		// Nothing to do
	}
	if ((a.y2() <= b.y) || (b.y2()<=a.y)) {
		return false;// to do more complex collision check
	}
	else {
		// Nothing to do
	}

	ConvexPolygon ms = (AtOrigin()*-1.0f).MinkowskySum(other);

	//if (ms.Contains(GetSource()))cout << *this << " collides with " << other << endl;
	//LOG_METHOD_CLOSE("ConvexPolygon::IsConvex", pointsAng.at(points[ind]));
	return ms.Contains(GetSource());
}

ConvexPolygon ConvexPolygon::operator+(const Vec2& p) const {
	LOG_METHOD_START("ConvexPolygon::operator+");
  LOG_VARIABLE("p", &p);
	assert(&p != NULL);

	ConvexPolygon polygon =* this;
	polygon.AddPoint(p);

	LOG_METHOD_CLOSE("ConvexPolygon::operator+", polygon);
	return polygon;
}

ConvexPolygon ConvexPolygon::operator*(const float& f) const {
	LOG_METHOD_START("ConvexPolygon::operator*");
  LOG_VARIABLE("&f", &f);
	assert(&f != NULL);

	ConvexPolygon polygon =  null;
	for (auto p:points) {
		pol.AddPoint(p*-f);
	}
	pol.MoveSource(GetSource());

	LOG_METHOD_CLOSE("ConvexPolygon::operator*", polygon);
	return polygon;
}

void ConvexPolygon::Floor() {
	LOG_METHOD_START("ConvexPolygon::Floor");

	for (auto &p:points) {
		p.floor();
	}
	source.floor();
}

Rect ConvexPolygon::BoundingRect() const {
	LOG_METHOD_START("ConvexPolygon::BoundingRect");
	LOG_METHOD_CLOSE("ConvexPolygon::BoundingRect", boundingRect + GetSource());
	return boundingRect + GetSource();
}

ConvexPolygon ConvexPolygon::AtOrigin() const {
	LOG_METHOD_START("ConvexPolygon::AtOrigin");

	ConvexPolygon polygon =* this;
	pol.MoveSource(Vec2{});

	LOG_METHOD_CLOSE("ConvexPolygon::AtOrigin", polygon);
	return polygon;
}

ConvexPolygon ConvexPolygon::MinkowskySum(const ConvexPolygon& polygon) const {
	LOG_METHOD_START("ConvexPolygon::MinkowskySum");
	LOG_VARIABLE("polygon", polygon);
	assert(&polygon != NULL);

	if (count <= 0 || polygon.count <= 0) {
		return ConvexPolygon();
	}
	else {
		// Nothing to do
	}
	if (count == 1) {
		return polygon + GetPoints()[0];
	}
	else {
		// Nothing to do
	}
	if (pol.GetCount() == 1) {
		return (*this) + polygon.GetPoints()[0];
	}
	else {
		// Nothing to do
	}
	vector<Vec2> vPol1 = GetPoints();
	vector<Vec2> vPol2 = pol.GetPoints();
	vPol1.push_back(vPol1[0]);
	vPol2.push_back(vPol2[0]);

	vector<Vec2> vPol3;
	vPol3.push_back(vPol1[0]+vPol2[0]);

	auto it1 = vPol1.begin();
	auto it2 = vPol2.begin();
	float ang1,ang2;

	while (next(it1) != vPol1.end() && next(it2) != vPol2.end()) {
		ang1 = it1->angle(*next(it1));
		ang2 = it2->angle(*next(it2));

		if (ang1 == ang2) {//if both are lined up, add them both together
			Vec2 v = (*next(it1))-(*it1) + (*next(it2))-(*it2);
			vPol3.push_back(vPol3.back() + v);
			it1++;
			it2++;
		}
		else if (ang1 > ang2) {
			Vec2 v = (*next(it1))-(*it1);
			vPol3.push_back(vPol3.back() + v);
			it1++;
		}
		else {
			Vec2 v = (*next(it2)) - (*it2);
			vPol3.push_back(vPol3.back() + v);
			it2++;
		}
	}

	while (next(it1) != vPol1.end()) {
		Vec2 v = (*next(it1)) - (*it1);
		vPol3.push_back(vPol3.back() + v);
		it1++;
	}
	while (next(it2) != vPol2.end()) {
		Vec2 v = (*next(it2))-(*it2);
		vPol3.push_back(vPol3.back() + v);
		it2++;
	}

	ConvexPolygon minkSum;
	for (auto &p:vPol3)minkSum.AddPoint(p);

	//cout << *this << " + " << pol << " = " << minkSum << endl;
	LOG_METHOD_CLOSE("ConvexPolygon::MinkowskySum", minkSum);
	return minkSum;
}

std::ostream& operator<<(std::ostream& os, const ConvexPolygon& obj) {
	LOG_METHOD_START("std::ostream& operator<<");
	LOG_VARIABLE("os", os);
	LOG_VARIABLE("obj", obj);
	assert(&os != NULL);
	assert(&obj != NULL);
	// auto pts=obj.GetPoints();
	// if (pts.size()==0)return os << "{}";
	// os << "{(" << (int)pts[0].x << "," << (int)pts[0].y << ")";
	// FOR2(i,1,pts.size())os << ",(" << (int)pts[i].x << "," << (int)pts[i].y << ")";
	// os << "}";
	// return os;

	auto pts = obj.GetPoints();
	if (pts.size() == 0) {
		return os << "{}";
	}
	else {
		// Nothing to do
	}
	os << "{" << pts[0];
	FOR2(i,1,pts.size()) {
		os << "," << pts[i];
	}
	os << "}";

	LOG_METHOD_CLOSE("std::ostream& operator<<", os);
	return os;

	// auto pts=obj.GetPoints();
	// if (pts.size()==0) {
	// 	os << "{}";
	// 	return os;
	// }
	// os << "{" << pts[0] << "[" << obj.GetPointAng(pts[0]) << "]";
	// FOR2(i,1,pts.size())os << "," << pts[i] << "[" << obj.GetPointAng(pts[i]) << "]";
	// os << "} -> " << obj.GetSource();
	// return os;
}
