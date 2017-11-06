#ifndef GEOMETRYHPP
#define GEOMETRYHPP

#include <common.hpp>

#define PI 3.141592653589793
#define RAD(x)     (((x)*PI)/180.0)
#define DEGREES(x) (((x)*180.0)/PI)

class Vec2;
class Rect;
class Circle;
class ConvexPolygon;

class Vec2{
public:
	float x;
	float y;

	Vec2(const float &a=0.0f,const float &b=0.0f);
	Vec2(const Vec2 &b);

	static Vec2 makeVec2(const float &len,const float &ang);

	Vec2 operator= (const Vec2& b);
	Vec2 operator+ (const Vec2& b)const;
	void operator+=(const Vec2& b);
	Vec2 operator- (const Vec2& b)const;
	void operator-=(const Vec2& b);
	Vec2 operator* (const float& r)const;
	void operator*=(const float& r);
	Vec2 operator/ (const float& r)const;
	void operator/=(const float& r);

	bool operator==(const Vec2& b)const;
	bool operator!=(const Vec2& b)const;
	bool operator< (const Vec2& b)const;

	void floor();

	float len() const; //! magnitude of the vector
	float angle() const; //! angle between this and the x-axis

	float dist(const Vec2& b) const; //! distance between this and b
	float angle(const Vec2& b) const; //! slope of the line defined by this and b

	Vec2 unit() const; // unit vector
	Vec2 renderPos() const; //! rendering position according to the camera
	Vec2 rotate(float a); //! rotates the vector in a degrees

	ConvexPolygon polygon(); //! returns the semi-vector defined by the vector and by the origin
};
std::ostream& operator<<(std::ostream& os, const Vec2& obj);

class Rect{
public:
	float x;
	float y;
	float w;
	float h;

	Rect(const float &a = 0.0f,const float &b=0.0f,const float &c = 0.0f,const float &d=0.0f);
	Rect(const Vec2 &pos,const Vec2 &sz);
	Rect(const Rect &b);

	Rect& operator= (const Rect& b);
	Rect operator+ (const Vec2& b)const;
	void operator+=(const Vec2& b);
	Rect operator- (const Vec2& b)const;
	void operator-=(const Vec2& b);

	bool operator==(const Rect& b);
	bool operator!=(const Rect& b);

	void floor();
	void setPos(const Vec2& b);
	void setCenter(const Vec2& b);

	float x2() const;
	float y2() const;

	//! returns the distance between the centers of the rectangles
	Vec2 distCenter(const Rect& b) const;

	//! returns the distance between the points closest to the rectangles
	Vec2 distEdge(const Rect& b) const;

	Vec2 hotspot(const Hotspot hs = Hotspot::TOP_LEFT);
	Vec2 corner() const; //! returns the upper left corner of the rectangle
	Vec2 corner2() const; //! returns the upper right corner of the rectangle
	Vec2 corner3() const; //! returns the bottom left corner of the rectangle
	Vec2 corner4() const; //! returns the lower right corner of the rectangle
	Vec2 center() const; //! returns the center of the rectangle
	Vec2 size() const; //! returns the size of the rectangle
	Vec2 relativePos(const Vec2 &relative,bool inverted = false) const;

	Rect relativeBox(const Rect &relative,bool inverted = false) const;
	Rect renderBox() const; //! rendering position according to the camera
	Rect sum(const Rect &other) const; //! returns the rectangle containing both

	ConvexPolygon polygon(const float &r = 0.0f) const;
	SDL_Rect sdlRect()const;

	//! returns if the point belongs to the rectangle
	bool contains(const float &i,const float &j) const;
	//! returns if the point belongs to the rectangle
	bool contains(const Vec2& b) const;
	//! returns if the rectangle intersects with b
	bool collides(const Rect& b) const;
};
ostream& operator<<(ostream& os, const Rect& obj);

class Circle {
public:
	float x;
	float y;
	float r;
	Circle(float x = 0.0f,float y = 0.0f,float r = float(1000));

	void floor();

	//! returns if the point belongs to the circle
	bool contains(const Vec2 &p)const;

	//! returns if the point belongs to the circle
	bool contains(const float &x,const float &y)const;
};

class ConvexPolygon{
	vector<Vec2> points;
	map<Vec2,float> pointsAng; //! angle point-points[0] to the origin
	Vec2 source;
	int count;
	Rect boundingRect;
public:
	ConvexPolygon();
	ConvexPolygon(vector<Vec2> v,bool all = false);

	//! doesn't work if the resulting polygon is not convex
	bool AddPoint(Vec2 p = Vec2{0.0f,0.0f});

	//! if all==true, doesnt add any if adding all wont make a convex polygon
	bool AddPoints(const vector<Vec2> &pts,bool all = false);
	bool RemovePoint(Vec2 p); //! doesn't work on non-existing points
	bool RemovePoint(int ind); //! doesn't work on non-existing points

	void SetSource(const Vec2 &p); //! changes the source and updates all points

	//! changes the source and keeps all points in the same relative position
	void MoveSource(const Vec2 &p);

	//! reorders the points with the lowest rightmost becoming the new points[0]
	void ReorderPoints();
	void ReorderPoints(vector<Vec2> &pts,map<Vec2,float> &ptsAng)const;

	vector<Vec2> GetPoints()const;
	const Vec2& GetSource()const;
	Vec2 GetCenter()const;

	int GetCount()const;
	float GetPointAng(const Vec2& p)const;
	float GetPointAng(int ind)const;

	//! tests if the polygon will remain convex if you add points pts
	bool IsConvex(const vector<Vec2> &pts)const;

	//! tests if the polygon will remain convex if you add point p
	bool IsConvex(const Vec2 &p)const;
	bool Contains(Vec2 p)const;
	bool Collides(const ConvexPolygon& other)const;

	ConvexPolygon operator+(const Vec2& p)const;
	ConvexPolygon operator* (const float &x)const;

	void Floor();

	Rect BoundingRect()const;
	ConvexPolygon AtOrigin()const;
	ConvexPolygon MinkowskySum(const ConvexPolygon& pol)const;
};
std::ostream& operator<<(std::ostream& os, const ConvexPolygon& obj);

#endif//GEOMETRYHPP
