#ifndef NN_H
#define NN_H

#include <xtensor/xarray.hpp>

xt::xarray<float> CNN(xt::xarray<float> input);

xt::xarray<float> ANN(xt::xarray<float> input);

#endif