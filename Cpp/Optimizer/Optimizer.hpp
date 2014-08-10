// Free for non-commercial, non-military, and non-critical 
// use unless incorporated in OpenCV. 
// Inherits OpenCV Licence if in OpenCV.


#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "CostVolume/CostVolume.hpp"

class Optimizer
{
public:
    CostVolume cv;//The cost volume we are attached to
    
    Optimizer(CostVolume cv);

    void attach(CostVolume cv);
    void initOptimization();
    bool optimizeA();
    bool optimizeQD();
    const cv::Mat depthMap();
    
    void setDefaultParams();

    //public parameters
    float thetaStart,thetaStep,thetaMin,epsilon,lambda;

    //buffers
    cv::gpu::GpuMat _qx,_qy,_d,_a,_g,_g1,_gx,_gy,_gbig;
    cv::gpu::GpuMat stableDepth;

private:
    void allocate();
    void initA();
    void initQD();
    void computeSigmas();
    void cacheGValues();

    //internal parameter values
    float theta,sigma_d,sigma_q;

    //flags
    bool cachedG, haveStableDepth;
    
    //
    int stableDepthEnqueued;
    cv::Ptr<char> stableDepthReady;//really a void*
public:
    cv::gpu::Stream cvStream;

    
};

#endif // OPTIMIZER_H