#ifndef HALIDEFUNCTIONS_H
#define HALIDEFUNCTIONS_H

#endif // HALIDEFUNCTIONS_H

#include <Halide.h>
#include <halide_image_io.h>

#include <QString>
#include <QDebug>


bool isImageGrayscale(const QString &t_inputPath){
    Halide::Buffer<uint8_t> input = Halide::Tools::load_image(t_inputPath.toStdString());

    int w = input.width();
    int h = input.height();
    int c = input.channels();

    if(c < 3)return true;

    // Iterate over the pixels
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            uint8_t r = input(x, y, 0);
            uint8_t g = input(x, y, 1);
            uint8_t b = input(x, y, 2);

            // Check if R, G, and B values are equal
            if (r != g || r != b) {
                // Found a pixel with differing values
                return false;
            }
        }
    }

    return true;
}

void makeGrayscale(const QString &t_inputPath, const QString &t_outputPath)
{
    Halide::Buffer<uint8_t> input = Halide::Tools::load_image(t_inputPath.toStdString());

    Halide::Func grayscale;
    Halide::Var x, y, c;

    if(!isImageGrayscale(t_inputPath)){
        // Algorithm to convert to grayscale
        grayscale(x, y) = Halide::cast<uint8_t>(
            0.299f * Halide::cast<float>(input(x, y, 0)) +
            0.587f * Halide::cast<float>(input(x, y, 1)) +
            0.114f * Halide::cast<float>(input(x, y, 2)));

        Halide::Buffer<uint8_t> output = grayscale.realize({input.width(), input.height()});

        Halide::Tools::save_image(output, t_outputPath.toStdString()); //to move this out, most likely have to change this function to return
            //output type so that when save is called, it can be easy
    }
}

void brighten(const QString &t_inputPath, const QString &t_outputPath)
{
    Halide::Buffer<uint8_t> input = Halide::Tools::load_image(t_inputPath.toStdString());

    Halide::Func brighter;
    Halide::Var x, y, c;

    Halide::Expr value = input(x, y, c);
    value = Halide::cast<float>(value);

    value *= 1.5f;

    value = Halide::min(value, 255.0f);

    value = Halide::cast<uint8_t>(value);

    brighter(x, y, c) = value;

    Halide::Buffer<uint8_t> output = brighter.realize({input.width(), input.height(), input.channels()});
    Halide::Tools::save_image(output, t_outputPath.toStdString());
}

void blur(const QString &t_inputPath, const QString &t_outputPath)
{
    // Load the input image using Halide Tools
    Halide::Buffer<uint8_t> input = Halide::Tools::load_image(t_inputPath.toStdString());

    // Define Halide variables
    Halide::Func blur_func;
    Halide::Var x, y, c;

    //////////////////////////////////////////////////////////////////////////////////////
    // Apply boundary conditions to handle edges                                        //
    Halide::Func clamped;                                                               //
    clamped(x, y, c) = Halide::BoundaryConditions::repeat_edge(input)(x, y, c);         //
                                                                                        //
    // Define the blur kernel radius                                                    //
    int radius = 1; // You can adjust this value to change the blur strength            //
                                                                                        //
    // Define the reduction domain over the kernel                                      // The solution was partly deduced using A.I.
    Halide::RDom r(-radius, 2 * radius + 1, -radius, 2 * radius + 1);                   //
                                                                                        //
    // Compute the average of the neighboring pixels                                    //
    Halide::Expr sum = Halide::sum(clamped(x + r.x, y + r.y, c));                       //
    Halide::Expr count = (2 * radius + 1) * (2 * radius + 1);                           //
    blur_func(x, y, c) = Halide::cast<uint8_t>(sum / count);                            //
    //////////////////////////////////////////////////////////////////////////////////////

    Halide::Buffer<uint8_t> output = blur_func.realize({input.width(), input.height(), input.channels()});
    Halide::Tools::save_image(output, t_outputPath.toStdString());
}
