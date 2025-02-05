#ifndef HALIDEFUNCTIONS_H
#define HALIDEFUNCTIONS_H

#endif // HALIDEFUNCTIONS_H

#include <Halide.h>
#include <halide_image_io.h>

#include <QString>

void makeGrayscale(const QString &t_inputPath, const QString &t_outputPath)
{
     Halide::Buffer<uint8_t> input = Halide::Tools::load_image(t_inputPath.toStdString());

    Halide::Func grayscale;
    Halide::Var x, y, c;

    // Algorithm to convert to grayscale
    grayscale(x, y) = 0.299f * input(x, y, 0) +
                      0.587f * input(x, y, 1) +
                      0.114f * input(x, y, 2);

    Halide::Buffer<uint8_t> output = grayscale.realize({input.width(), input.height()}); //likely we need to add the input channels if this doesn't work

    Halide::Tools::save_image(output, t_outputPath.toStdString()); //to move this out, most likely have to change this function to return
        //output type so that when save is called, it can be easy
}
