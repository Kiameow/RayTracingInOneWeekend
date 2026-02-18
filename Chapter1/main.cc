#include "rtweekend.h"

#include "hittable.h"
#include "hitttable_list.h"
#include "sphere.h"
#include "camera.h"

// hittable_list别看名字是list，其实继承了hittable,这样不论传的是一个物体还是一堆物体都适用

int main() {
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    camera cam;
    
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    cam.render(world);
}
