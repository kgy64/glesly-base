/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Camera movement
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "camera.h"

using namespace Glesly;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                                       *
 *     class CameraMatrix:                                                               *
 *                                                                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

CameraMatrix::CameraMatrix(void):
    Glesly::Matrix<float,4,4>(1.0f)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

CameraMatrix::~CameraMatrix()
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

void CameraMatrix::Update(void)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 float r_xy_factor = fminf(myWidth, myHeight) / fov;
 float r_x = r_xy_factor/myWidth;
 float r_y = r_xy_factor/myHeight;
 float r_zw_factor = far - near;
 float r_z = (near + far) / r_zw_factor;
 float r_w = -2.0f*near*far / r_zw_factor;

 static_cast<Matrix<float,4,4>&>(*this) = {
    r_x,    0.0f,   0.0f,   0.0f,
    0.0f,   r_y,    0.0f,   0.0f,
    0.0f,   0.0f,   r_z,    1.0f,
    0.0f,   0.0f,   r_w,    0.0f
 };
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                                       *
 *     class Transformation:                                                             *
 *                                                                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Transformation::Transformation(void):
    Glesly::Matrix<float, 4, 4>(1.0f),
    xAngle(0.0f),
    yAngle(0.0f),
    zAngle(0.0f)
{
}


void Transformation::RotateX(float angle, float scale)
{
 xAngle = angle;

 float s = sinf(angle) * scale;
 float c = cosf(angle) * scale;

 (*this)[0][0] = scale;
 (*this)[0][1] = 0.0f;
 (*this)[0][2] = 0.0f;
 (*this)[1][0] = 0.0f;
 (*this)[1][1] = c;
 (*this)[1][2] = s;
 (*this)[2][0] = 0.0f;
 (*this)[2][1] = -s;
 (*this)[2][2] = c;
}

void Transformation::RotateY(float angle, float scale)
{
 yAngle = angle;

 float s = sinf(angle) * scale;
 float c = cosf(angle) * scale;

 (*this)[0][0] = c;
 (*this)[0][1] = 0.0f;
 (*this)[0][2] = s;
 (*this)[1][0] = 0.0f;
 (*this)[1][1] = scale;
 (*this)[1][2] = 0.0f;
 (*this)[2][0] = -s;
 (*this)[2][1] = 0.0f;
 (*this)[2][2] = c;
}

void Transformation::RotateZ(float angle, float scale)
{
 zAngle = angle;

 float s = sinf(angle) * scale;
 float c = cosf(angle) * scale;

 (*this)[0][0] = c;
 (*this)[0][1] = s;
 (*this)[0][2] = 0.0f;
 (*this)[1][0] = -s;
 (*this)[1][1] = c;
 (*this)[1][2] = 0.0f;
 (*this)[2][0] = 0.0f;
 (*this)[2][1] = 0.0f;
 (*this)[2][2] = scale;
}

void Transformation::RotateZ(float angle, float scale, float aspect)
{
 zAngle = angle;

 float s = sinf(angle) * scale;
 float c = cosf(angle) * scale;

 (*this)[0][0] = c * aspect;
 (*this)[0][1] = s * aspect;
 (*this)[0][2] = 0.0f;
 (*this)[1][0] = -s;
 (*this)[1][1] = c;
 (*this)[1][2] = 0.0f;
 (*this)[2][0] = 0.0f;
 (*this)[2][1] = 0.0f;
 (*this)[2][2] = scale;
}

void Transformation::Move(float x, float y, float z)
{
 (*this)[3][0] = x;
 (*this)[3][1] = y;
 (*this)[3][2] = z;
}

bool Transformation::ConvertMouseCoordinates(float & x, float & y) const
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 SYS_DEBUG(DL_INFO3, "Got raw coordinates: " << x << ":" << y);

 ASSERT((*this)[0][0] != 0.0f && (*this)[1][1] != 0.0f, "Matrix is not invertible");

 x = (x - (*this)[3][0]) * (1.0f/(*this)[0][0]);
 y = (y - (*this)[3][1]) * (1.0f/(*this)[1][1]);

 if (x < -1.0f || x > 1.0f || y < -1.0f || y > 1.0f) {
    SYS_DEBUG(DL_INFO3, "Position " << x << ":" << y << " is out of bounds");
    return false;
 }

 SYS_DEBUG(DL_INFO3, "Position " << x << ":" << y << " is accepted");

 return true;
}

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
