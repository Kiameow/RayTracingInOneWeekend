#ifndef PERLIN_H
#define PERLIN_H

#include "rtweekend.h"

class perlin {
    public:
        perlin() {
            for (int i = 0; i < point_count; i++) {
                randfloat[i] = random_double();
            }

            perlin_generate_perm(perm_x);
            perlin_generate_perm(perm_y);
            perlin_generate_perm(perm_z);
        }

        double noise(const point3& p, double inv_scale) const {
            auto i = int(inv_scale*p.x()) & 255;
            auto j = int(inv_scale*p.y()) & 255;
            auto k = int(inv_scale*p.z()) & 255;

            return randfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
        }

        double simple_noise(const point3& p, double inv_scale) const {
            auto i = int(inv_scale*p.x()) & 255;
            auto j = int(inv_scale*p.y()) & 255;
            auto k = int(inv_scale*p.z()) & 255;

            return randfloat[(i + j + k) % 256];
        }

    private:
        static const int point_count = 256;
        double randfloat[point_count];
        int perm_x[point_count];
        int perm_y[point_count];
        int perm_z[point_count];

        static void perlin_generate_perm(int* p) {
            for (int i = 0; i < point_count; i++) {
                p[i] = i;
            }

            random_permute(p, point_count);
        }

        static void random_permute(int*p, int n) {
            for (int i = n-1; i > 0; i--) {
                int target = random_int(0, i);
                int tmp = p[i];
                p[i] = target;
                p[target] = tmp;
            }
        }
};

#endif
