#include <iostream>
using namespace std;

class Vector2D
{
public:
    Vector2D();
    Vector2D(int newx, int newy);
    void SetXY(int newx, int newy);
    int GetX();
    int GetY();
    int operator*(const Vector2D &v2);

private:
    int x;
    int y;
};
// Vector2D::Vector2D
// Default constructor
Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

// Vector2D::Vector2D
// Constructor with parameters
Vector2D::Vector2D(int newx, int newy)
{
    x = newx;
    y = newy;
}

// Vector2D::SetXY
// Set the x and y values of the vector
void Vector2D::SetXY(int newx, int newy)
{
    x = newx;
    y = newy;
}

// Vector2D::GetX
// Return the x value of the vector
int Vector2D::GetX()
{
    return x;
}

// Vector2D::GetY
// Return the y value of the vector
int Vector2D::GetY()
{
    return y;
}

// Vector2D::operator *
// Overrides the * operator to return the dot product of two vectors
int Vector2D::operator*(const Vector2D &v2)
{
    return x * v2.x + y * v2.y;
}

int main()
{
    // Some test vectors
    Vector2D v1(10, 0), v2(0, 10), v3(10, 10), v4(5, 4);
    cout << "(" << v1.GetX() << "," << v1.GetY() << ") * (" << v2.GetX()
         << "," << v2.GetY() << ") = " << v1 * v2 << endl;
    cout << "(" << v2.GetX() << "," << v2.GetY() << ") * (" << v3.GetX()
         << "," << v3.GetY() << ") = " << v2 * v3 << endl;
    cout << "(" << v3.GetX() << "," << v3.GetY() << ") * (" << v4.GetX()
         << "," << v4.GetY() << ") = " << v3 * v4 << endl;

    return 0;
}

