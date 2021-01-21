#ifndef RAY_H
#define RAY_H


class Ray
{
    public:
        Ray(float pitch, float yaw, float initX = 0.0f, float initY = 0.0f, float initZ = 0.0f)
        : pitch(pitch + 0.5f), yaw(yaw + 0.5f), x(initX + 0.5f), y(initY + 0.5f), z(initZ + 0.5f) {}

        void step(float amount);

        inline float getX() { return x;}
        inline float getY() { return y;}
        inline float getZ() { return z;}
    protected:

    private:
    float pitch;
    float yaw;

    float x;
    float y;
    float z;
};

#endif // RAY_H
