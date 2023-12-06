#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <tuple>

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>
#include <xtensor/xrandom.hpp>
#include <convolution.h>

// ILayer(xt::xarray<float> input, xt::xarray<float> output)
class ILayer {

    public:
        xt::xarray<float> input;
        xt::xarray<float> output;

        virtual void forward(xt::xarray<float> input);

        virtual void backward(xt::xarray<float> gradient);
};

// Pooling(int size, int stride, int padding, Pooling::PoolingType type)
class PoolingLayer : public ILayer   {
    
    public:
        enum PoolingType {
                NO_TYPE,
                MAX,    
                MIN,  
                AVG
        };

        int size = 1;
        int stride = 1;
        int padding = 0;
        PoolingType type = NO_TYPE;

        PoolingLayer(int size, int stride, int padding, PoolingType type)  {
            this->size = size;
            this->stride = stride;
            this->padding = padding;
            this->type = type;
        }

        ~PoolingLayer() = default;

        void forward(xt::xarray<float> input) override;

        void backward(xt::xarray<float> gradient) override;

        float pooling(xt::xarray<float> matrix);

        xt::xarray<float> poolingMatrice(xt::xarray<float> matrix);
};

// Activation()
class ActivationLayer : public ILayer   {
    
    public:
    
        void forward(xt::xarray<float> input) override;

        void backward(xt::xarray<float> gradient) override;

        virtual float activation(xt::xarray<float> matrix);
};

// ConvolutionLayer(int depth, std::tuple<int, int, int> inputShape, std::tuple<int, int, int, int, int> filtersShape, PoolingLayer pool)
class ConvolutionLayer : public ILayer   {
    
    public:
        int depth = 0;

        //Height - Width - Depth
        std::tuple<int, int, int> inputShape{0, 0, 0};
        std::tuple<int, int, int> outputShape{0, 0, 0};

        // Height - Width - Depth - Stride - Padding
        std::tuple<int, int, int, int, int> filtersShape{0, 0, 0, 0, 0};

        xt::xarray<float> filters;

        int bias = 1;

        PoolingLayer pooling{0, 0, 0, PoolingLayer::PoolingType::NO_TYPE};
        ActivationLayer activation;
    
        ConvolutionLayer(int depth, std::tuple<int, int, int> inputShape, std::tuple<int, int, int, int, int> filtersShape, ActivationLayer activation, PoolingLayer pooling)   {

            this->depth = depth;    // Nombre d'image dans la couche actuelle      
            this->inputShape = inputShape;
            this->filtersShape = filtersShape;
         
            int inputHeight = std::get<0>(inputShape);
            int inputWidth = std::get<1>(inputShape);
            int inputDepth = std::get<2>(inputShape);


            int filtersHeight = std::get<0>(filtersShape);
            int filtersWidth = std::get<1>(filtersShape);
            int filtersDepth = std::get<2>(filtersShape);

            this->outputShape = std::tuple<int, int, int>(inputHeight - filtersHeight + 1, inputWidth - filtersWidth + 1, filtersDepth * depth);

            filters = xt::random::rand<float>({depth, filtersDepth, filtersHeight, filtersWidth}, 0, 1);  

            this->pooling = pooling;
            this->activation = activation;      
        }

        ~ConvolutionLayer() = default;

        void forward(xt::xarray<float> input) override;

        void backward(xt::xarray<float> gradient) override;

};

#endif
