#include "mxfactory.h"

Matrix2 MxFactory::identity2()
{
    return Matrix2(1.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MxFactory::identity3()
{
    return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MxFactory::dual(float ax, float ay, float az)
{
    return Matrix3(
        0.0f, -az, ay, 
        az, 0.0f, -ax, 
        -ay, ax, 0.0f);
}

Matrix3 MxFactory::squaredual(float ax, float ay, float az)
{
    return Matrix3(
        -ay*ay-az*az , ax*ay        , ax*(az), 
        ax*ay        , -ax*ax-az*az , ay*az, 
        ax*az        , ay*az        , -ax*ax-ay*ay);
}

Matrix4 MxFactory::identity4()
{
    return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 
                   0.0f, 1.0f, 0.0f, 0.0f, 
                   0.0f, 0.0f, 1.0f, 0.0f, 
                   0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MxFactory::scaling4(float sx, float sy, float sz)
{
    return Matrix4( sx  , 0.0f, 0.0f, 0.0f,
                    0.0f, sy  , 0.0f, 0.0f,
                    0.0f, 0.0f, sz  , 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MxFactory::translation4(float tx, float ty, float tz)
{
    return Matrix4( 1.0f, 0.0f, 0.0f, tx  ,
                    0.0f, 1.0f, 0.0f, ty  ,
                    0.0f, 0.0f, 1.0f, tz  ,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MxFactory::rotation4(float rx, float ry, float rz, float theta)
{
    Vector3D axis = Vector3D(rx, ry, rz);
    axis.normalize();
    float angle = theta * M_PI / 180.0f;

    Matrix3 mat3 = identity3();
    mat3 += dual(axis.x, axis.y, axis.z) * sin(angle);
    mat3 += squaredual(axis.x, axis.y, axis.z) * (1 - cos(angle));
    return mat3.increase();
}

Matrix4 MxFactory::invscaling4(float sx, float sy, float sz)
{
    float invx = (sx != 0.0f) ? 1 / sx : 0.0f,
        invy = (sy != 0.0f) ? 1 / sy : 0.0f,
        invz = (sz != 0.0f) ? 1 / sz : 0.0f;

    return scaling4(invx, invy, invz);
}

Matrix4 MxFactory::invtranslation4(float tx, float ty, float tz)
{
    return translation4(-tx, -ty, -tz);
}

Matrix4 MxFactory::invrotation4(float rx, float ry, float rz, float theta)
{
    return rotation4(rx, ry, rz, -theta);
}

