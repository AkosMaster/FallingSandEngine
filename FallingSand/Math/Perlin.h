#pragma once
#include <vector>
#include <numeric>
#include <random>
#include <cmath>

class Perlin {
public:
    std::vector<int> p;
    float scale;

    Perlin(float scale=1) : scale(scale) {
        p.resize(256);
        std::iota(p.begin(), p.end(), 0);

        std::default_random_engine engine(std::random_device{}());
        std::shuffle(p.begin(), p.end(), engine);

        p.insert(p.end(), p.begin(), p.end());
    }

    double noise(double x, double y) {
        x /= scale; y /= scale;

        int X = (int)floor(x) & 255;
        int Y = (int)floor(y) & 255;

        x -= floor(x);
        y -= floor(y);

        double u = fade(x);
        double v = fade(y);

        int A = p[X] + Y;
        int B = p[X + 1] + Y;

        return lerp(v,
            lerp(u, grad(p[A], x, y), grad(p[B], x - 1, y)),
            lerp(u, grad(p[A + 1], x, y - 1), grad(p[B + 1], x - 1, y - 1))
        );
    }

private:
    static double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    static double grad(int hash, double x, double y) {
        int h = hash & 7;
        double u = h < 4 ? x : y;
        double v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
    }
};