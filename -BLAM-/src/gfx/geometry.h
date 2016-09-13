/*
 *  geometry.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/5/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifndef COORD_TYPE
typedef float Coordinate;
#else
typedef COORD_TYPE Coordinate;
#endif

struct Vector2D
{
    Coordinate x, y;
    
    Vector2D(void)
    {}
    
    Vector2D(Coordinate x, Coordinate y)
    : x(x), y(y)
    {}
    
    Vector2D(Coordinate coords[2])
    : x(coords[0]), y(coords[1])
    {}
    
    Vector2D operator+(const Vector2D &rhs) const
    {
        return Vector2D(x + rhs.x, y + rhs.y);
    }
    
    Vector2D operator-(const Vector2D &rhs) const
    {
        return Vector2D(x - rhs.x, y - rhs.y);
    }
    
    const Vector2D & operator+=(const Vector2D &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        
        return *this;
    }
    
    const Vector2D & operator-=(const Vector2D &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        
        return *this;
    }
    
    operator Coordinate * (void)
    {
        return &x;
    }
    
    operator const Coordinate * (void) const
    {
        return &x;
    }
};

typedef Vector2D Point2D;

struct Vector3D
{
    Coordinate x, y, z;
    
    Vector3D(void)
    : x(0), y(0), z(0)
    {}
    
    Vector3D(Coordinate x, Coordinate y, Coordinate z)
    : x(x), y(y), z(z)
    {}
    
    Vector3D(Coordinate coords[3])
    : x(coords[0]), y(coords[1]), z(coords[2])
    {}
    
    Vector3D(const Vector2D &rhs)
    : x(rhs.x), y(rhs.y), z(0)
    {}
    
    Vector3D(const Vector2D &xy, Coordinate z)
    : x(xy.x), y(xy.y), z(z)
    {}
    
    Vector3D operator+(const Vector3D &rhs) const
    {
        return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    
    Vector3D operator+(const Vector2D &rhs) const
    {
        return Vector3D(x + rhs.x, y + rhs.y, z);
    }
    
    Vector3D operator-(const Vector3D &rhs) const
    {
        return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    
    Vector3D operator-(const Vector2D &rhs) const
    {
        return Vector3D(x - rhs.x, y - rhs.y, z);
    }
    
    const Vector3D & operator+=(const Vector3D &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        
        return *this;
    }
    
    const Vector3D & operator+=(const Vector2D &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        
        return *this;
    }
    
    const Vector3D & operator-=(const Vector3D &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        
        return *this;
    }
    
    const Vector3D & operator-=(const Vector2D &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        
        return *this;
    }
    
    operator Coordinate * (void)
    {
        return &x;
    }
    
    operator const Coordinate * (void) const
    {
        return &x;
    }
};

typedef Vector3D Point3D;

struct Rect2D
{
    Point2D pos;
    Vector2D size;

    Rect2D(const Point2D &pos, const Vector2D &size)
    : pos(pos), size(size)
    {}
    
    Rect2D(Coordinate x, Coordinate y, Coordinate width, Coordinate height)
    : pos(Point2D(x, y)), size(Vector2D(width, height))
    {}
    
    Rect2D(void)
    : pos(Point2D(0, 0)), size(Point2D(0, 0))
    {}
    
    bool pointInside(const Point2D &p) const
    {
        const Coordinate right = pos.x + size.x;
        const Coordinate top   = pos.y + size.y;
        
        return (((p.x >= pos.x) & (p.x <= right)) &
                ((p.y >= pos.y) & (p.y <= top)));
    }
    
};

struct ColorRGB
{
    float r, g, b;
    
    ColorRGB(void)
    : r(1.0), g(1.0), b(1.0)
    {}
    
    ColorRGB(float r, float g, float b)
    : r(r), g(g), b(b)
    {}
    
    ColorRGB(float *rgb)
    : r(rgb[0]), g(rgb[1]), b(rgb[2])
    {}
    
    void set(const ColorRGB &rgb)
    {
        *this = rgb;
    }
    
    void set(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
};

struct ColorRGBA
{
    float r, g, b, a;
    
    ColorRGBA(void)
    : r(1.0), g(1.0), b(1.0), a(1.0)
    {}
    
    ColorRGBA(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
    {}
    
    ColorRGBA(float *rgba)
    : r(rgba[0]), g(rgba[1]), b(rgba[2]), a(rgba[3])
    {}
    
    ColorRGBA(const ColorRGB &rhs)
    : r(rhs.r), g(rhs.g), b(rhs.b), a(1.0)
    {}
    
    void set(const ColorRGB &rgb)
    {
        r = rgb.r;
        g = rgb.g;
        b = rgb.b;
    }
    
    void set(const ColorRGBA &rgba)
    {
        *this = rgba;
    }
    
    void set(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    void set(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

struct Graphics_Point
{
    // The texture coordinate.
    Point2D t;
    
    // The RGBA color.
    ColorRGBA c;
    
    // The normal vector.
    Vector3D n;
    
    // The physical coordinates.
    Point3D v;
    
    Graphics_Point(Point2D t, ColorRGBA c, Vector3D n, Point3D v)
    : t(t), c(c), n(n), v(v)
    {}
    
    Graphics_Point(Point2D t, ColorRGBA c, Point3D v)
    : t(t), c(c), v(v)
    {}
    
    Graphics_Point(Point2D t, Point3D v)
    : t(t), v(v)
    {}
    
    Graphics_Point(void)
    {}
};
    

#endif // GEOMETRY_H
