#ifndef POSITIONI_H
#define POSITIONI_H

#include <cmath>

class Positioni
{
    public:
        Positioni(int x, int y, int z)
            : x(x), y(y), z(z) {}
        int x;
        int y;
        int z;

        bool operator==(const Positioni& b) const
        {
            return this->x == b.x && this->y == b.y && this->z == b.z;
        }

        float distanceTo(const Positioni& b) const
        {
            return sqrt(pow(this->x - b.x, 2) + pow(this->y - b.y, 2) + pow(this->y - b.y, 2));
        }
};

#endif // POSITIONI_H
