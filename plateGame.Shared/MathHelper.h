#pragma once

// Dies sind einige einfache mathematische Hilfsprogramme zum Rendern eines sich drehenden Würfels. Es handelt sich nicht um eine vollständige mathematische Bibliothek.
// Sie können dies durch Ihre bevorzugte mathematische Bibliothek ersetzen, für sich für Ihre Zielplattformen eignet, z. B. DirectXMath oder GLM.

#include <math.h>

namespace MathHelper
{

struct Matrix4
{
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33)
    {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    float m[4][4];
};

inline static Matrix4 SimpleModelMatrix(float radians)
{
    float cosine = cosf(radians);
    float sine = sinf(radians);

    return Matrix4(cosine, 0.0f,  -sine, 0.0f,
                     0.0f, 1.0f,   0.0f, 0.0f,
                     sine, 0.0f, cosine, 0.0f,
                     0.0f, 0.0f,   0.0f, 1.0f);
}

inline static Matrix4 SimpleViewMatrix()
{
    // Die Kamera befindet sich im 60-Grad-Winkel zum Boden in der YZ-Ebene.
    // Der Kamerazielpunkt ist hardcodiert mit (0, 0, 0).
    // Die Aufwärtsbewegung der Kamera ist hardcodiert mit (0, 1, 0).
    const float sqrt3over2 = 0.86603f;
    const float cameraDistance = 5.0f;

    return Matrix4(1.0f,       0.0f,            0.0f, 0.0f,
                   0.0f, sqrt3over2,            0.5f, 0.0f,
                   0.0f,      -0.5f,      sqrt3over2, 0.0f,
                   0.0f,       0.0f, -cameraDistance, 1.0f);
}

inline static Matrix4 SimpleProjectionMatrix(float aspectRatio)
{
    // Die nahe Ebene liegt bei 50.0f, die ferne Ebene bei 1.0f.
    // FoV ist hardcodiert mit pi/3.
    const float cotangent = 1 / tanf(3.14159f / 6.0f);

    return Matrix4(cotangent / aspectRatio,      0.0f,                    0.0f,                             0.0f,
                                      0.0f, cotangent,                    0.0f,                             0.0f,
                                      0.0f,      0.0f, -50.0f / (50.0f - 1.0f), (-50.0f * 1.0f) / (50.0f - 1.0f),
                                      0.0f,      0.0f,                   -1.0f,                             0.0f);
}

}