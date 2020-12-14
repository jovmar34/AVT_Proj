#include "../HeaderFiles/mxfactory.h"

Matrix2 MxFactory::identity2()
{
    return Matrix2(1.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MxFactory::identity3()
{
    return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3 MxFactory::dual(double ax, double ay, double az)
{
    return Matrix3(
        0.0f, -az, ay, 
        az, 0.0f, -ax, 
        -ay, ax, 0.0f);
}

Matrix3 MxFactory::squaredual(double ax, double ay, double az)
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

Matrix4 MxFactory::scaling4(Vector3D scaleVec)
{
    return Matrix4( scaleVec.x  , 0.0f, 0.0f, 0.0f,
                    0.0f, scaleVec.y, 0.0f, 0.0f,
                    0.0f, 0.0f, scaleVec.z, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MxFactory::translation4(Vector3D translateVec)
{
    return Matrix4( 1.0f, 0.0f, 0.0f, translateVec.x  ,
                    0.0f, 1.0f, 0.0f, translateVec.y  ,
                    0.0f, 0.0f, 1.0f, translateVec.z  ,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 MxFactory::rotation4(Vector3D axis, double theta)
{
    Matrix3 mat3 = rotation3(axis, theta);
    return mat3.increase();
}

Matrix3 MxFactory::rotation3(Vector3D axis, double theta)
{
    Vector3D axis_c = axis; // assume axis may not be normalized
    axis_c.normalize();
    double angle = theta * M_PI / 180.0f; // degree to radian

    Matrix3 mat3 = identity3();
    mat3 += dual(axis_c.x, axis_c.y, axis_c.z) * sin(angle);
    mat3 += squaredual(axis_c.x, axis_c.y, axis_c.z) * (1 - cos(angle));
    return mat3;
}

Matrix4 MxFactory::invscaling4(Vector3D scaleVec)
{
    double invx = (scaleVec.x != 0.0f) ? 1 / scaleVec.x : 0.0f,
        invy = (scaleVec.y != 0.0f) ? 1 / scaleVec.y : 0.0f,
        invz = (scaleVec.z != 0.0f) ? 1 / scaleVec.z : 0.0f;

    return scaling4(Vector3D(invx, invy, invz));
}

Matrix4 MxFactory::invtranslation4(Vector3D tranlateVec)
{
    return translation4(tranlateVec * (-1));
}

Matrix4 MxFactory::invrotation4(Vector3D axis, double theta)
{
    return rotation4(axis, -theta);
}

Matrix3 MxFactory::invrotation3(Vector3D axis, double theta)
{
    return rotation3(axis, -theta);
}

