#ifndef CPU_ONLY
  #define CPU_ONLY
#endif

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <bhtsne/tsne.h>
using namespace std;


vector<vector<float>> extract_features(int num_img_files);
class tsne_wrapper
{
private:
    TSNE tsne;
    int iters, max_iters;
    vector<vector<double> > tsne_points;    
    vector<vector<float> > data;
    int op_dims;
    double perplexity;
    double theta;
    bool normalize;
    bool runManually=false;
    
    int input_dims,samples;
    double *inp_data, *op_data;
    vector<double> min_, max_;
    int i,j,k; 
    
    ~tsne_wrapper();
public:

    tsne_wrapper(int op_dims=3, double perplexity=30,double theta=0.5, bool normalize=true);
    vector<vector<double> > run(vector<vector<float> > & data);
    vector<vector<double> > run_(vector<vector<float> > & data, int op_dims=3, double perplexity=30,double theta=0.5,bool normalize=true);
    void finish();
};
