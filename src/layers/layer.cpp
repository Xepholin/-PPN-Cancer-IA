#include <iostream>

#include "layer.h"

void ILayer::forward(xt::xarray<float> input __attribute__((unused)), bool training __attribute__((unused)))
{
    std::cout << "forward ILayer" << std::endl;
}

xt::xarray<float> ILayer::backward(xt::xarray<float> cost __attribute__((unused)))
{
    std::cout << "backward ILayer" << std::endl;
	return 0;
}

void ILayer::print() const
{
    std::cout << "print ILayer" << std::endl; 
}