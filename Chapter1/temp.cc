#include <iostream>


int main() {
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Viewport widths less than one are ok since they are real valued.
    // 这里不使用宽高比来计算是因为image_width / image_height的计算结果可能与宽高比不同，宽高比终究还是太理想化了
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
}
