#include "mse.h"

#include <xtensor/xrandom.hpp>

float MSE::compute(xt::xarray<float> output, xt::xarray<int> label) {
	float err = 0.0;
	int outputSize = output.size();

	for (int i = 0; i < outputSize; ++i) {
		err += ((output(i) - label(i)) * (output(i) - label(i)));
	}

	return err;
}

xt::xarray<float> MSE::prime(xt::xarray<float> output, xt::xarray<int> label) {
	int outputSize = output.size();
	xt::xarray<float> prime = xt::empty<float>({outputSize});

	for (int i = 0; i < outputSize; ++i) {
		prime(i) = 2.0 * (output(i) - label(i));
	}

	return prime;
}