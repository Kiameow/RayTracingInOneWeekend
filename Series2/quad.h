#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"

class quad : public hittable {
    public:
        quad(const point3& Q, const vec3& u, const vec3& v, shared_ptr<material> mat) 
            : Q(Q), u(u), v(v), mat(mat)
        {
            auto n = cross(u, v);
            normal = unit_vector(n);
            D = dot(normal, Q);
            dotuu = dot(u, u);
            dotvv = dot(v, v);
            dotuv = dot(u, v);
            det = dotuu * dotvv - dotuv * dotuv;

            set_bounding_box();
        }

        virtual void set_bounding_box() {
            aabb bbox1 = aabb(Q, Q + u + v);
            aabb bbox2 = aabb(Q + u, Q + v);
            bbox = aabb(bbox1, bbox2);
        }

        aabb bounding_box() const override { return bbox; }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            auto denom = dot(normal, r.direction());

            if (std::fabs(denom) < 1e-8) return false;

            auto t = (D - dot(normal, r.origin())) / denom;
            if (!ray_t.contains(t)) return false;

            auto intersection = r.at(t);

            vec3 planar_hitpt_vector = intersection - Q;
            auto alpha = (dot(u, planar_hitpt_vector) * dotvv - dotuv * dot(v, planar_hitpt_vector)) / det;
            auto beta  = (dot(v, planar_hitpt_vector) * dotuu - dotuv * dot(u, planar_hitpt_vector)) / det;

            if (!is_interior(alpha, beta, rec)) return false;

            rec.t = t;
            rec.p = intersection;
            rec.mat = mat;
            rec.set_face_normal(r, normal);

            return true;
        }

        virtual bool is_interior(double alpha, double beta, hit_record& rec) const {
            interval unit_interval = interval(0, 1);

            if (!unit_interval.contains(alpha) || !unit_interval.contains(beta)) 
                return false;
            
            rec.u = alpha;
            rec.v = beta;
            return true;
        }
    private:
        point3 Q;
        vec3 u, v;
        shared_ptr<material> mat;
        aabb bbox;
        vec3 normal;
        double D, det, dotuu, dotvv, dotuv;
};

#endif
