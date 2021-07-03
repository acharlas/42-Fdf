#include "../include/fdf.h"

t_mat4x4 initMat4x4(void)
{
    t_mat4x4 matrix;
    int i = 0;
    int j = 0;

    while(i < 4)
    {
        while(j < 4)
        {
            matrix.m[i][j] = 0;
            j++;
        }
        i++;
    }
    return(matrix);
}

t_vec3d multiplyMatrixVector(t_vec3d vect, t_mat4x4 mat)
{
    t_vec3d ret;

    ret.x = vect.x * mat.m[0][0] + vect.y * mat.m[1][0] + vect.z * mat.m[2][0] + mat.m[3][0];
    ret.y = vect.x * mat.m[0][1] + vect.y * mat.m[1][1] + vect.z * mat.m[2][1] + mat.m[3][1];
    ret.z = vect.x * mat.m[0][2] + vect.y * mat.m[1][2] + vect.z * mat.m[2][2] + mat.m[3][2];
    float w = vect.x * mat.m[0][3] + vect.y * mat.m[1][3] + vect.z * mat.m[2][3] + mat.m[3][3];
    if(w != 0.0f)
    {
        ret.x /= w;
        ret.y /= w;
        ret.z /= w;
    }
    return ret;
}

t_mat4x4 initProjMat(void)
{
    t_mat4x4 projectMatrix = initMat4x4();

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)HEIGHT / (float)WIDTH;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

    projectMatrix.m[0][0] = fAspectRatio * fFovRad;
    projectMatrix.m[1][1] = fFovRad;
    projectMatrix.m[2][2] = fFar / (fFar - fNear);
    projectMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    projectMatrix.m[2][3] = 1.0f;
    projectMatrix.m[3][3] = 0.0f;
    return projectMatrix;
}