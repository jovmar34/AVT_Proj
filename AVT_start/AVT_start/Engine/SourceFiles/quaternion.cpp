#include "..\HeaderFiles\quaternion.h"

Quaternion::Quaternion() : t(0), x(0), y(0), z(0)
{
}

Quaternion::Quaternion(double _t, double _x, double _y, double _z) : t(_t), x(_x), y(_y), z(_z)
{
}

// from angle and axis
Quaternion::Quaternion(double theta, Vector4D axis)
{
    Vector4D axisn = axis;
    axisn.normalize();

    Quaternion q;
    double a = theta * M_PI / 180.0f;
    q.t = cos(a / 2.0f);
    double s = sin(a / 2.0f);
    q.x = axisn.x * s;
    q.y = axisn.y * s;
    q.z = axisn.z * s;
}

Vector4D Quaternion::toAngleAxis(float& theta)
{

    return Vector4D();
}

double Quaternion::quadrance()
{
    return t*t + x*x + y*y + z*z;
}

double Quaternion::norm()
{
    return sqrt(quadrance());
}

Quaternion& Quaternion::normalize()
{
    double norm = this->norm();
    if (norm == 0) throw "cant normalize a 0 quaternion";

    this->t /= norm;
    this->x /= norm;
    this->y /= norm;
    this->z /= norm;

    return *this;
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(t, -x, -y, -z);
}

Quaternion Quaternion::inverse()
{
    return conjugate()/quadrance();
}

Quaternion Quaternion::operator=(const Quaternion& q1)
{
    return Quaternion(q1.t, q1.x, q1.y, q1.z);
}

Quaternion Quaternion::operator+(const Quaternion& q1)
{
    return Quaternion(t + q1.t, x + q1.x, y + q1.y, z + q1.z);
}

Quaternion Quaternion::operator*(const double s)
{
    return Quaternion(t * s, x * s, y * s, z * s);
}

Quaternion Quaternion::operator*(const Quaternion& q1)
{
    return Quaternion(
        t * q1.t - x * q1.x - y * q1.y - z * q1.z,
        t * q1.x + x * q1.t + y * q1.z - z * q1.y,
        t * q1.y + y * q1.t + z * q1.x - x * q1.z,
        t * q1.z + z * q1.t + x * q1.y - y * q1.x
    );
}

Quaternion Quaternion::operator/(const double s)
{
    if (s == 0) {
        throw "division by 0";
    }
    return Quaternion(t/s, x/s, y/s, z/s);
}

GLfloat* Quaternion::toOpenGLRot()
{
    Quaternion qn = *this;
    double xx = x * x;
    double xy = x * y;
    double xz = x * z;
    double xt = x * t;
    double yy = y * y;
    double yz = y * z;
    double yt = y * t;
    double zz = z * z;
    double zt = z * t;

    Matrix4 res(
        1.0f - 2.0f * (yy + zz), 2.0f * (xy - zt), 2.0f * (xz + yt), 0.0f,
        2.0f * (xy + zt), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xt), 0.0f,
        2.0f * (xz - yt), 2.0f * (yz + xt), 1.0f - 2.0f * (xx + yy), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );


    return res.toOpenGl();
}

Quaternion Quaternion::Lerp(Quaternion& q1, double k)
{
    double cos_angle = x * q1.x + y * q1.y + z * q1.z + t * q1.t;
    double k0 = 1.0f - k;
    double k1 = (cos_angle > 0) ? k : -k;
    Quaternion res = (*this * k0) + (q1 * k1);
    res.normalize();
    return res;
}

Quaternion Quaternion::Slerp(Quaternion& q1, float k)
{
    double angle = acos(x * q1.x + y * q1.y + z * q1.z + t * q1.t);
    double k0 = sin((1 - k) * angle) / sin(angle);
    double k1 = sin(k * angle) / sin(angle);
    Quaternion res = (*this * k0) + (q1 * k1);
    res.normalize();
    return res;
}

bool Quaternion::operator==(const Quaternion& q1)
{
    return false;
}

void Quaternion::print()
{
    std::cout << "(" << t << ", " << x << ", " << y << ", " << z << ")" << std::endl;
}

void Quaternion::printAngleAxis()
{
}
