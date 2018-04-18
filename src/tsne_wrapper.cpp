#include "libfsort.h"
#include <bhtsne/tsne.h>


vector<vector<double>> tsne_wrapper::run(vector<vector<float>> data,int op_dims,int max_iters, int num_threads,double perplexity,double theta, bool normalize)
{
  iters = 0;
  perplexity=30;
  this->data = data;
  this->op_dims = op_dims;
  this->perplexity = perplexity;
  this->theta = theta;
  this->normalize = normalize;

  samples = data.size();
  input_dims = data[0].size();
  cout<<"\n\ntsne wrapper:Received Feature vector of size "<<samples<<"x"<<input_dims<<"\n";
  if(samples-1<3*perplexity)
  {
      cout<<"Warning: too few samples for expected accuracy";
      perplexity=(samples-1)/3;
  }

  inp_data = (double *)malloc(input_dims * samples * sizeof(double));
  op_data  = (double *)malloc(op_dims * samples * sizeof(double));

  k = 0;
  for (i = 0; i < samples; i++)
    for (j = 0; j < input_dims; j++)
      inp_data[k++] = data[i][j];
  tsne_run_double(inp_data, samples, input_dims, op_data, op_dims, perplexity, theta, 4, max_iters);
  
  
  if (min_.size() != op_dims)
    min_.resize(op_dims);
  if (max_.size() != op_dims)
    max_.resize(op_dims);
  for (i = 0; i < op_dims; i++) {
    min_[i] = numeric_limits<double>::max();
    max_[i] = numeric_limits<double>::min();
  }

  tsne_embeddings.clear();
  k = 0;
  for (i = 0; i < samples; i++) {
    vector<double> tsne_points;
    tsne_points.resize(op_dims);
    for (j = 0; j < op_dims; j++) {
      tsne_points[j] = op_data[k++];
      if (normalize) {
        if (tsne_points[j] < min_[j])
          min_[j] = tsne_points[j];
        if (tsne_points[j] > max_[j])
          max_[j] = tsne_points[j];
      }
    }
    tsne_embeddings.push_back(tsne_points);
  }

  // normalize if requested
  if (normalize) {
    for (i = 0; i < tsne_embeddings.size(); i++) {
      for (j = 0; j < op_dims; j++) {
        tsne_embeddings[i][j] = (tsne_embeddings[i][j] - min_[j]) / (max_[j] - min_[j]);
      }
    }
  }

  return tsne_embeddings;
}
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
vector<vector<double>> tsne_wrapper::run(vector<string> image_files,int op_dims,int max_iters, double perplexity,int num_threads,double theta, bool normalize)
{
    Mat image; vector<vector<double>> points;
    for(vector<string>::iterator i=image_files.begin();i!=image_files.end();i++)
    {
        image=imread(i->c_str(),IMREAD_COLOR);
        if(! image.data )                              // Check for invalid input
        {
            cout <<  "Could not open or find the image" <<endl ;
            return points;
        }

        namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
        imshow( "Display window", image );
    }
    return points;
}
void tsne_wrapper::finish() {
  delete (inp_data);
  delete (op_data);
}
tsne_wrapper::~tsne_wrapper()
{
    finish();
}
