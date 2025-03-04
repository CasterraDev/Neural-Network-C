#include "nn.h"
#include "dinoarray.h"
#include <assert.h>

void layerCreateInput(NN* nn, int width, int height, int depth){
    NN_ASSERT(nn->layerCnt <= 0);
    NN_Layer* l = (NN_Layer*)NN_MALLOC(sizeof(NN_Layer));

    l->width = width;
    l->height = height;
    l->depth = depth;

    l->nodeCnt = width * height * depth;

}

void layerCreateFull(NN* nn, int nodeCnt, char fillWithRand){

}

// Temp
int main(void){
    NN nn;
    nn.layers = dinoCreateReserve(3, NN_Layer);
}
