#pragma once

#include "Point.h"
#include "Size.h"

struct GUI_Rect;

class Rect {
public:
    Rect() { }
    Rect(int x, int y, int width, int height)
        : m_location(x, y)
        , m_size(width, height)
    {
    }
    Rect(const Point& location, const Size& size)
        : m_location(location)
        , m_size(size)
    {
    }
    Rect(const Rect& other)
        : m_location(other.m_location)
        , m_size(other.m_size)
    {
    }

    Rect(const GUI_Rect&);

    bool is_null() const
    {
        return width() == 0 && height() == 0;
    }

    bool is_empty() const
    {
        return width() <= 0 || height() <= 0;
    }

    void move_by(int dx, int dy)
    {
        m_location.move_by(dx, dy);
    }

    void move_by(const Point& delta)
    {
        m_location.move_by(delta);
    }

    Point center() const
    {
        return { x() + width() / 2, y() + height() / 2 };
    }

    void inflate(int w, int h)
    {
        set_x(x() - w / 2);
        set_width(width() + w);
        set_y(y() - h / 2);
        set_height(height() + h);
    }

    void shrink(int w, int h)
    {
        set_x(x() + w / 2);
        set_width(width() - w);
        set_y(y() + h / 2);
        set_height(height() - h);
    }

    bool contains(int x, int y) const
    {
        return x >= m_location.x() && x <= right() && y >= m_location.y() && y <= bottom();
    }

    bool contains(const Point& point) const
    {
        return contains(point.x(), point.y());
    }

    bool contains(const Rect& other) const
    {
        return left() <= other.left()
            && right() >= other.right()
            && top() <= other.top()
            && bottom() >= other.bottom();
    }

    int left() const { return x(); }
    int right() const { return x() + width() - 1; }
    int top() const { return y(); }
    int bottom() const { return y() + height() - 1; }

    void set_left(int left)
    {
        set_x(left);
    }

    void set_top(int top)
    {
        set_y(top);
    }

    void set_right(int right)
    {
        set_width(right - x() + 1);
    }

    void set_bottom(int bottom)
    {
        set_height(bottom - y() + 1);
    }

    bool intersects(const Rect& other) const
    {
        return left() <= other.right()
            && other.left() <= right()
            && top() <= other.bottom()
            && other.top() <= bottom();
    }

    int x() const { return location().x(); }
    int y() const { return location().y(); }
    int width() const { return m_size.width(); }
    int height() const { return m_size.height(); }

    void set_x(int x) { m_location.set_x(x); }
    void set_y(int y) { m_location.set_y(y); }
    void set_width(int width) { m_size.set_width(width); }
    void set_height(int height) { m_size.set_height(height); }

    Point location() const { return m_location; }
    Size size() const { return m_size; }

    operator GUI_Rect() const;

    bool operator==(const Rect& other) const
    {
        return m_location == other.m_location
            && m_size == other.m_size;
    }

    void intersect(const Rect&);

    static Rect intersection(const Rect& a, const Rect& b)
    {
        Rect r(a);
        r.intersect(b);
        return r;
    }

    Rect united(const Rect&) const;

private:
    Point m_location;
    Size m_size;
};

inline void Point::constrain(const Rect& rect)
{
    if (x() < rect.left())
        set_x(rect.left());
    else if (x() > rect.right())
        set_x(rect.right());
    if (y() < rect.top())
        set_y(rect.top());
    else if (y() > rect.bottom())
        set_y(rect.bottom());
}