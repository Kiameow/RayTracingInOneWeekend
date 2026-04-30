#ifndef AABB_H
#define AABB_H

#include "interval.h"
#include "cmath"

class aabb {
    public:
        interval x, y, z;

        aabb() {}

        aabb(const interval& x, const interval& y, const interval& z) 
            : x(x), y(y), z(z) 
        {
            pad_to_minimums();
        }

        aabb(const point3& a, const point3& b) {
            x = interval(a.x(), b.x());
            y = interval(a.y(), b.y());
            z = interval(a.z(), b.z());

            pad_to_minimums();
        }

        aabb(const aabb& box1, const aabb& box2) {
            x = interval(box1.x, box2.x);
            y = interval(box1.y, box2.y);
            z = interval(box1.z, box2.z);
        }

        const interval& axis_interval(int axis) const {
            if (axis == 1) return y;
            else if (axis == 2) return z;
            else return x;
        }

        bool hit(const ray& r, interval ray_t) const {
            const point3& ray_orig = r.origin();
            const vec3&   ray_dir  = r.direction();

            for (int axis = 0; axis < 3; axis++) {
                // 在const标记的函数体内也只能调用带有const标记的函数，否则有改变类内变量的可能性
                const interval& i = axis_interval(axis);
                const double adinv = 1.0 / ray_dir[axis]; // axis direction inverse 
                double t0 = (i.min - ray_orig[axis]) * adinv;
                double t1 = (i.max - ray_orig[axis]) * adinv;
                
                if (t0 < t1) {
                    if (t0 > ray_t.min) ray_t.min = t0;
                    if (t1 < ray_t.max) ray_t.max = t1;
                } else {
                    if (t1 > ray_t.min) ray_t.min = t1;
                    if (t0 < ray_t.max) ray_t.max = t0;
                }

                if (ray_t.max <= ray_t.min) return false;
            }
            return true;
        }

        int longest_axis() const {
            if (x.size() > y.size()) {
                return x.size() > z.size() ? 0 : 2;
            } else {
                return y.size() > y.size() ? 1 : 2;
            }
        }

        static const aabb empty, universe;

    private:
        void pad_to_minimums() {
            double delta = 0.0001;
            if (x.size() < delta) x = x.expand(delta);
            if (y.size() < delta) y = y.expand(delta);
            if (z.size() < delta) z = z.expand(delta);
        }
};

const aabb aabb::empty    = aabb(interval::empty,    interval::empty,    interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);

#endif
