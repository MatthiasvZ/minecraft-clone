#ifndef POSITIONI_H
#define POSITIONI_H

class Positioni
{
    public:
        Positioni(int x, int y, int z)
            : x(x), y(y), z(z) {}
        int x;
        int y;
        int z;

        bool operator==(Positioni& b)
        {
            if (this->x == b.x && this->y == b.y && this->z == b.z)
                return true;
            return false;
        }
};

#endif // POSITIONI_H
