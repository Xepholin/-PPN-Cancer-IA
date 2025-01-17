#include <iostream>

#include "relu.h"

void ReLu::forward(xt::xarray<float> input, bool training __attribute__((unused)))
{
    this->output = xt::where(input <= 0, 0.0, input);
}

xt::xarray<float> ReLu::backward(xt::xarray<float> cost __attribute__((unused)))
{
    std::cout << "ReLu backward" << std::endl;
    return 0;
}

xt::xarray<float> ReLu::prime(xt::xarray<float> input)
{

    auto ret = xt::where(input >= 0.0 , 1.0 ,0.0 );

    return ret;
}

void ReLu::print() const
{
    std::cout << "          | ReLu\n"
              << "          v" << std::endl;
}