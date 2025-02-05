#ifndef HALIDEFUNCTIONS_H
#define HALIDEFUNCTIONS_H

#endif // HALIDEFUNCTIONS_H

#include <Halide.h>
#include <halide_image_io.h>

#include <QString>
#include <QDebug>
void makeGrayscale(const QString &t_inputPath, const QString &t_outputPath)
{
    Halide::Buffer<uint8_t> input = Halide::Tools::load_image(t_inputPath.toStdString());

    Halide::Func grayscale;
    Halide::Var x, y, c;

    // Algorithm to convert to grayscale
    grayscale(x, y) = Halide::cast<uint8_t>(
                      0.299f * Halide::cast<float>(input(x, y, 0)) +
                      0.587f * Halide::cast<float>(input(x, y, 1)) +
                      0.114f * Halide::cast<float>(input(x, y, 2)));


    //Halide::Buffer<float> output = grayscale.realize({input.width(), input.height(), input.channels()}); //likely we need to add the input channels if this doesn't work


    // try {
    //     Halide::Buffer<float> output = grayscale.realize({input.width(), input.height()});
    // } catch (const Halide::Error &e) {
    //     qDebug() << "Halide error during realization: " << e.what();
    //     return;
    // }

    Halide::Buffer<uint8_t> output = grayscale.realize({input.width(), input.height()});

    Halide::Tools::save_image(output, t_outputPath.toStdString()); //to move this out, most likely have to change this function to return
        //output type so that when save is called, it can be easy
}
