#include "libfsort.h"

tsne_wrapper::tsne_wrapper(int op_dims,int max_iters, double perplexity, double theta, bool normalize  )
{
  this->op_dims = op_dims;
  this->perplexity = perplexity;
  this->theta = theta;
  this->normalize = normalize;
}
vector<vector<double>> tsne_wrapper::run(vector<vector<float>> data)
{
  return run_(data, this->op_dims, this->perplexity, this->theta, this->normalize);
}

vector<vector<double>> tsne_wrapper::run_(vector<vector<float>> data,int op_dims,int max_iters, double perplexity,double theta, bool normalize)
{
  iters = 0;
  this->data = data;
  this->op_dims = op_dims;
  this->perplexity = perplexity;
  this->theta = theta;
  this->normalize = normalize;

  samples = data.size();
  input_dims = data[0].size();

  inp_data = (double *)malloc(input_dims * samples * sizeof(double));
  op_data  = (double *)malloc(op_dims * samples * sizeof(double));

  k = 0;
  for (i = 0; i < samples; i++)
    for (j = 0; j < input_dims; j++)
      inp_data[k++] = data[i][j];

  tsne.run(inp_data, samples, input_dims, op_data, op_dims, perplexity, theta,run_manually,max_iters);

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

void tsne_wrapper::finish() {
  delete (inp_data);
  delete (op_data);
}
tsne_wrapper::~tsne_wrapper()
{
    finish();
}
