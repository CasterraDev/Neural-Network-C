#define MATRIX_IMPLEMENTATION
#include "matrix.h"
#define DINO_IMPLEMENTATION
#include "dinoarray.h"

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif // NN_MALLOC

#ifndef NN_FREE
#include <stdlib.h>
#define NN_FREE free
#endif // NN_FREE

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif // NN_ASSERT

typedef enum LAYER_TYPE {
    LAYER_TYPE_INPUT,
    LAYER_TYPE_OUTPUT,
    LAYER_TYPE_HIDDEN,
} LAYER_TYPE;

typedef struct NN_Layer {
    LAYER_TYPE layerType;
    struct NN_Layer* prev;
    struct NN_Layer* next;

    int depth;
    int width;
    int height;

    int nodeCnt;
    Matrix* output;
    Matrix* gs; // The gradients

    Matrix* ws;
    Matrix* bs;

    // The updates to weights/bias
    Matrix* wsu;
    Matrix* bsu;

    union {
        struct {

        } full;

        struct {
            int kernelSize;
            int paddingSize;
            int stride;
        } conv;
    };
} NN_Layer;

typedef struct NN {
    NN_Layer* layers;
    int layerCnt;
} NN;

void layerCreateInput(NN* nn, int width, int height, int depth);
void layerCreateFull(NN* nn, int nodeCnt, char fillWithRand);

/*#define NN_INPUT(nn) (nn).as[0]*/
/*#define NN_OUTPUT(nn) (nn).as[(nn).count]*/
/**/
/*NN nnAlloc(size_t* arch, size_t archCount);*/
/*void nnFill(NN nn, size_t val);*/
/*void nnPrint(NN nn, const char* name);*/
/*#define NN_PRINT(nn) nnPrint(nn, #nn);*/
/*void nnRand(NN nn, float low, float high);*/
/*void nnForward(NN nn);*/
/*float nnCost(NN nn, Matrix ti, Matrix to);*/
/*void nnFiniteDiff(NN nn, NN g, float eps, Matrix ti, Matrix to);*/
/*void nnBackprop(NN nn, NN g, Matrix ti, Matrix to);*/
/*void nnLearn(NN nn, NN g, float rate);*/
