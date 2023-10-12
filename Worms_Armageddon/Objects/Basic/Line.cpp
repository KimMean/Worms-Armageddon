#include "Framework.h"

Line::Line(Vector2 start, Vector2 end)
    : GameObject(start), end(end)
{
}

void Line::Render(HDC hdc)
{
    MoveToEx(hdc, pos.x, pos.y, nullptr);
    LineTo(hdc, end.x, end.y);
}

bool Line::IsCollision(const Vector2& point) const
{
    return false;
}

bool Line::IsRectCollision(const Rect* rect) const
{
    return false;
}

bool Line::IsCircleCollision(const Circle* circle) const
{
    Vector2 e1 = end - pos;
    Vector2 e2 = circle->pos - pos;


    return false;
}

bool Line::IsLineCollision(const Line* line) const
{
    return IsBetweenLine(line) && line->IsBetweenLine(this);
}

bool Line::IsLineCollision(const Line* line, Vector2& crossPoint)
{    

    return false;
}

bool Line::IsCircleCollision(const Circle* circle, Vector2& closestPoint)
{


    return false;
}

bool Line::IsBetweenLine(const Line* line) const
{
    Vector2 e1 = line->pos - pos;
    Vector2 e2 = line->end - pos;
    Vector2 e3 = end - pos;

    return Cross(e1, e3) * Cross(e2, e3) < 0;
}
