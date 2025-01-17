#include "convolution.h"

#include <iostream>

#include "conv_op.h"
#include "tools.h"

void Convolution::forward(xt::xarray<float> input, bool training __attribute__((unused))) {
	this->input = input;

	xt::xarray<float> convolution_result;
	xt::xarray<float> tmpMat;
	xt::xarray<float> tmpFilter;

	int shape0 = this->filters.shape()[0];
	int shape1 = this->filters.shape()[1];

	for (int i = 0; i < shape0; ++i) {
		for (int j = 0; j < shape1; ++j) {
			tmpMat = xt::view(input, j);
			tmpFilter = xt::view(this->filters, i, j);
			convolution_result = matrixConvolution(tmpMat, tmpFilter, std::get<3>(this->filtersShape), std::get<4>(this->filtersShape));
		}
		xt::view(output, i) = convolution_result;
	}

	// if (this->normalize)
	// {
	// this->output = normalized(this->output);
	// }

	if (this->activation->name != "Activation") {
		this->activation->forward(this->output);
		this->output = this->activation->output;
	}
}

xt::xarray<float> Convolution::backward(xt::xarray<float> cost __attribute__((unused))) {
	std::cout << "Convolution backward" << std::endl;
	return 0;
}

void Convolution::print() const {
	std::cout << "Convolution with " << this->filters.shape()[2] << "x" << this->filters.shape()[3] << " kernel"
			  << " + " << std::get<3>(this->filtersShape) << " stride"
			  << " + " << std::get<4>(this->filtersShape) << " pad : " << this->output.shape()[1] << "x" << this->output.shape()[2] << "x" << this->output.shape()[0] << "\n          |\n          v" << std::endl;
}

void Convolution::heWeightsInit() {
	int inputHeight = std::get<1>(this->inputShape);
	int inputWidth = std::get<2>(this->inputShape);

	int filtersDepth = std::get<0>(this->filtersShape);
	int filtersHeight = std::get<1>(this->filtersShape);
	int filtersWidth = std::get<2>(this->filtersShape);

	float std = sqrt(2.0 / (static_cast<float>(filtersDepth) * this->depth * inputHeight * inputWidth));

	this->filters = xt::random::randn<float>({filtersDepth, depth,
											  filtersHeight, filtersWidth},
											 0, std);
}

void Convolution::XGWeightsInit() {
	int filtersDepth = std::get<0>(this->filtersShape);
	int filtersHeight = std::get<1>(this->filtersShape);
	int filtersWidth = std::get<2>(this->filtersShape);

	float std = sqrt(2.0 / (static_cast<float>(this->input.size()) + this->output.size()));
	
	this->filters = xt::random::randn<float>({filtersDepth, depth,
											  filtersHeight, filtersWidth},
											 0, std);
}