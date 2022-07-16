#pragma once
#include <cmath>

#define rad_degrees(x)      x * 180 / 3.14159265
#define degrees_rad(x)      x * 3.14159265 / 180

#define sfml_vec2f(vec)      Vec2f(vec.x, vec.y)
#define vec2f_sfml(vec)      sf::Vector2f((vec).x,  (vec).y)
#define inv_vec2f_sfml(vec)  sf::Vector2f((vec).x, -(vec).y)


///////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct Vec2
{
    T x, y;

    Vec2(): x(0), y(0) {}
    template <typename U> Vec2(U _x, U _y): x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}
    template <typename U> Vec2(const Vec2<U> &vec): x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y)) {}
     
    float  mag       () const;
    float  angle     () const;
    void   norm      ();
    void   set_angle (float angle);
    void   set_mag   (float new_mag);
    void   rotate    (float d_angle);
    void   constrain (float max_mag);

    static Vec2<T>  polar     (float r, float angle);
    static Vec2<T>  norm      (const Vec2<T> &vec);
    static Vec2<T>  set_angle (const Vec2<T> &vec, float angle);
    static Vec2<T>  set_mag   (const Vec2<T> &vec, float new_mag);
    static Vec2<T>  rotate    (const Vec2<T> &vec, float d_angle);
    static Vec2<T>  constrain (const Vec2<T> &vec, float max_mag);
    
    static float  dot           (const Vec2<T> &a, const Vec2<T> &b);
    static float  dist          (const Vec2<T> &a, const Vec2<T> &b);
    static float  angle_between (const Vec2<T> &a, const Vec2<T> &b);
};


///////////////////////////////////////////////////////////////////////////////////
template <typename T> inline Vec2<T> operator+(const Vec2<T> &a, const Vec2<T> &b)
{
    return Vec2<T>(a.x + b.x, a.y + b.y);
}

template <typename T, typename U> inline Vec2<T> operator+(U scalar, const Vec2<T> &vec)
{
    return Vec2<T>(vec.x + scalar, vec.y + scalar);
}

template <typename T, typename U> inline Vec2<T> operator+(const Vec2<T> &vec, U scalar)
{
    return Vec2<T>(vec.x + scalar, vec.y + scalar);
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T> inline Vec2<T> operator-(const Vec2<T> &a, const Vec2<T> &b)
{
    return Vec2<T>(a.x - b.x, a.y - b.y);
}

template <typename T, typename U> inline Vec2<T> operator-(U scalar, const Vec2<T> &vec)
{
    return Vec2<T>(scalar - vec.x, scalar - vec.y);
}

template <typename T, typename U> inline Vec2<T> operator-(const Vec2<T> &vec, U scalar)
{
    return Vec2<T>(vec.x - scalar, vec.y - scalar);
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U> inline Vec2<T> operator*(const Vec2<T> &vec, U scalar)
{
    return Vec2<T>(vec.x * scalar, vec.y * scalar);
}

template <typename T, typename U> inline Vec2<T> operator*(U scalar, const Vec2<T> &vec)
{
    return Vec2<T>(vec.x * scalar, vec.y * scalar);
}

template <typename T, typename U> inline Vec2<T> operator/(const Vec2<T> &vec, U scalar)
{
    return Vec2<T>(vec.x / scalar, vec.y / scalar);
}

template <typename T, typename U> inline Vec2<T> operator/(U scalar, const Vec2<T> &vec)
{
    return Vec2<T>(scalar / vec.x, scalar / vec.y);
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T> inline Vec2<T> operator-(const Vec2<T> &vec)
{
    return Vec2<T>(-vec.x, -vec.y);
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T> inline Vec2<T>& operator+=(Vec2<T>& left, const Vec2<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T, typename U> inline Vec2<T>& operator+=(Vec2<T>& left, U right)
{
    left.x += right;
    left.y += right;
    return left;
}

template <typename T> inline Vec2<T>& operator-=(Vec2<T>& left, const Vec2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template <typename T, typename U> inline Vec2<T>& operator-=(Vec2<T>& left, U right)
{
    left.x -= right;
    left.y -= right;
    return left;
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U> inline Vec2<T>& operator*=(Vec2<T>& left, U right)
{
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T, typename U> inline Vec2<T>& operator/=(Vec2<T>& left, U right)
{
    left.x /= right;
    left.y /= right;
    return left;
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T> float Vec2<T>::mag() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

template <typename T> float Vec2<T>::angle() const
{
    return atan2(y, x);
}

template <typename T> void Vec2<T>::norm()
{
    float current_mag = mag();
    x /= current_mag;
    y /= current_mag;
}

template <typename T> void Vec2<T>::set_angle(float angle)
{
    float current_mag = mag();
    x = cos(angle) * current_mag;
    y = sin(angle) * current_mag;
}

template <typename T> void Vec2<T>::set_mag(float new_mag)
{
    float ratio = new_mag / mag();
    x *= ratio;
    y *= ratio;
}

template <typename T> void Vec2<T>::rotate(float d_angle)
{
    set_angle(angle() + d_angle);
}

template <typename T> void Vec2<T>::constrain(float max_mag)
{
    float current_mag = mag();
    if (current_mag <= max_mag)
        return;
    x *= max_mag / current_mag; 
    y *= max_mag / current_mag; 
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T> inline Vec2<T> Vec2<T>::polar(float r, float angle)
{
    return Vec2<T>(cos(angle) * r, sin(angle) * r);
}

template <typename T> inline Vec2<T> Vec2<T>::norm(const Vec2<T> &vec)
{
    return vec / vec.mag();
}

template <typename T> inline Vec2<T> Vec2<T>::set_angle(const Vec2<T> &vec, float angle)
{
    return Vec2<T>::polar(vec.mag(), angle);
}

template <typename T> inline Vec2<T> Vec2<T>::set_mag(const Vec2<T> &vec, float new_mag)
{
    return vec * (new_mag / vec.mag());
}

template <typename T> inline Vec2<T> Vec2<T>::rotate(const Vec2<T> &vec, float d_angle)
{
    return set_angle(vec, vec.angle() + d_angle);
}

template <typename T> inline Vec2<T> Vec2<T>::constrain(const Vec2<T> &vec, float max_mag)
{
    float current_mag = vec.mag();
    if (current_mag <= max_mag)
        return vec;
    return vec * (max_mag / current_mag); 
}


///////////////////////////////////////////////////////////////////////////////////
template <typename T> inline float Vec2<T>::dot(const Vec2<T> &a, const Vec2<T> &b)
{
    return a.x * b.x + a.y * b.y;
}

template <typename T> inline float Vec2<T>::dist(const Vec2<T> &a, const Vec2<T> &b)
{
    return (a - b).mag();
}

template <typename T> inline float Vec2<T>::angle_between(const Vec2<T> &a, const Vec2<T> &b)
{
    return acos(Vec2::dot(a, b) / (a.mag() * b.mag));
}


///////////////////////////////////////////////////////////////////////////////////
typedef Vec2<float>        Vec2f;
typedef Vec2<double>       Vec2d;
typedef Vec2<int>          Vec2i;
typedef Vec2<unsigned int> Vec2u;

