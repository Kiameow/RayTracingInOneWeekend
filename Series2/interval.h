#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

class interval {
    public:
        double min, max;

        interval() : min(+infinity), max(-infinity) {} 

        interval(double min, double max) {
            if (min > max) {
                this->min = max;
                this->max = min;
            } else {
                this->min = min;
                this->max = max;
            }
        }

        interval(const interval& a, const interval& b) {
            min = a.min <= b.min ? a.min : b.min;
            max = a.max >= b.max ? a.max : b.max;
        }

        double size() const {
            return max - min;
        }

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const {
            return min < x && x < max;
        }

        double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        interval expand(double delta) const {
            auto padding = delta / 2;
            return interval(min - padding, max + padding);
        }

        static const interval empty, universe;
};

// 复杂静态类型的初始化需要放在类外部
const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity); 

#endif
