#include "generator.h"

Generator::Generator(float frequency, int depth, int seed) 
:
_frequency(frequency),
_depth(depth),
 _seed(seed)
{

}

Generator::~Generator()
{

}

float Generator::at(int x, int y)
{
    float xa = x*_frequency;
    float ya = y*_frequency;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    for(int i= 0; i < _depth; i++)
    {
        div += 256 * amp;
        fin += _noise_2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}

/* ---------------------------------------------| info |--------------------------------------------- */

int Generator::_noise_sample(int x, int y)
{
    int tmp = hash_table[(y + _seed) % 256];
    return hash_table[(tmp + x) % 256];
}

float Generator::_interpolation_linear(float x, float y, float s)
{
    return x + s * (y-x);
}

float Generator::_interpolation_smooth(float x, float y, float s)
{
    return _interpolation_linear(x, y, s * s * (3-2*s));
}

float Generator::_noise_2d(float x, float y)
{
    int x_int = x;
    int y_int = y;

    float x_frac = x - x_int;
    float y_frac = y - y_int;

    int s = _noise_sample(x_int, y_int);
    int t = _noise_sample(x_int+1, y_int);
    int u = _noise_sample(x_int, y_int+1);
    int v = _noise_sample(x_int+1, y_int+1);

    float low = _interpolation_smooth(s, t, x_frac);
    float high = _interpolation_smooth(u, v, x_frac);

    return _interpolation_smooth(low, high, y_frac);
}