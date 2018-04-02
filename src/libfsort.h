#ifndef _LIBFSORT_H

#define _LIBFSORT_H
#ifndef CPU_ONLY
  #define CPU_ONLY
#endif
#define _vec_ret
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <bhtsne/tsne.h>
using namespace std;

#ifdef _vec_ret
vector<vector<float>> extract_features(int num_img_files);
#else
void extract_features(vector<vector<float>> &features_vec,int num_img_files);
#endif
class tsne_wrapper
{
private:
    TSNE tsne;
    int iters, max_iters;
    vector<vector<double> > tsne_embeddings;    
    vector<vector<float> > data;
    int op_dims;
    double perplexity;
    double theta;
    bool normalize;
    bool run_manually=false;
    
    int input_dims,samples;
    double *inp_data, *op_data;
    vector<double> min_, max_;
    int i,j,k; 
    
public:

    tsne_wrapper(int op_dims=3, int max_iters=1000, double perplexity=30,double theta=0.5, bool normalize=true);
    vector<vector<double> > run(vector<vector<float> > & data);
    vector<vector<double> > run_(vector<vector<float> > & data, int op_dims=3,int max_iters=1000, double perplexity=30,double theta=0.5,bool normalize=true);
    void finish();
    ~tsne_wrapper();
};
vector<vector<double>> extract_embeddings(vector<string> image_files,int max_iters=1000); //add option to change batch size and and crop sizes

#endif