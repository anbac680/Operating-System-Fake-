
#include "animation.h"

float Clamp01(float value)
{
    if (value < 0.0f) return 0.0f;
    if (value > 1.0f) return 1.0f;

    return value;
}

float EaseOutCubic(float value)
{
    value = Clamp01(value);

    const float inverse = 1.0f - value;
    return 1.0f - inverse * inverse * inverse;
}

float EaseOutBack(float value)
{
    value = Clamp01(value);

    constexpr float c1 = 1.70158f;
    constexpr float c3 = c1 + 1.0f;

    const float x = value - 1.0f;

    return 1.0f + c3 * x * x * x + c1 * x * x;
}