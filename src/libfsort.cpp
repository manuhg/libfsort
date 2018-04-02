#include <iostream>
#include <string>
#include <vector>
#ifndef CPU_ONLY
  #define CPU_ONLY
#endif
#include "boost/algorithm/string.hpp"
#include "google/protobuf/text_format.h"
#include "caffe/caffe.hpp"
#include "caffe/common.hpp"

#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/net.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/db.hpp"
#include "caffe/util/format.hpp"
#include "caffe/util/io.hpp"


using caffe::Blob;
using caffe::Caffe;
using caffe::Net;
using std::string;
namespace db = caffe::db;
using namespace std;

vector<vector<float>> extract_features(int num_img_files);

int main(int argc, char** argv) {
   extract_features(atoi(argv[1]));
}

vector<vector<float>> extract_features(int num_img_files) {
  int num_mini_batches = num_img_files;
  //std::clock_t start; double duration;
  vector<vector<float>> features_vec;
  
  Caffe::set_mode(Caffe::CPU);
  const char * binaryproto="ml_data/bvlc_googlenet.caffemodel";
  std::string pretrained_binary_proto(binaryproto);
  ::google::InitGoogleLogging(binaryproto);
  std::string feature_extraction_proto("ml_data/imagenet_val.prototxt");
  boost::shared_ptr<Net<float> > feature_extraction_net(new Net<float>(feature_extraction_proto, caffe::TEST));
  feature_extraction_net->CopyTrainedLayersFrom(pretrained_binary_proto);
  std::string feature_blob_name("fc7");
  
  //std::cout<<"Checking parameters";
  LOG(INFO)<< "Checking parameters";  
  CHECK(feature_extraction_net->has_blob(feature_blob_name))<< "Unknown feature name " 
  << feature_blob_name<< " in the network " << feature_extraction_proto;
  //std::cout<<"\nExtracting Features";
  LOG(ERROR)<<  "Extracting Features";
 // start=std::clock();
  int maxdims=0;//just for printing info at the end
  for (int batch_index = 0; batch_index < num_mini_batches; ++batch_index) {
    feature_extraction_net->Forward();
      const boost::shared_ptr<Blob<float> > feature_blob = feature_extraction_net->blob_by_name(feature_blob_name);
      
      int batch_size = feature_blob->num();
      int dim_features = feature_blob->count() / batch_size;
      if(dim_features>maxdims)
        maxdims=dim_features;
      const float* feature_blob_data;
      vector<float> batch_fvec;
      for (int n = 0; n < batch_size; ++n)
      {
        feature_blob_data = feature_blob->cpu_data()+feature_blob->offset(n);
        vector<float> dim_fvec {feature_blob_data,feature_blob_data+dim_features};
        batch_fvec.insert(batch_fvec.end(),dim_fvec.begin(),dim_fvec.end());

        LOG(INFO)<<" "<<batch_index<<"/"<<num_mini_batches<<" "<<n<<"/"<<batch_size<<" "<<dim_features<<" : "<<batch_fvec.size();
      }
      features_vec.push_back(batch_fvec);
  }
  //duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  int size=maxdims*features_vec.size()*sizeof(float);
  // std::cout<<"\nSuccessfully extracted the features from "<<features_vec.size()
  //  <<" files\nfeature vector size: "<<size<<" bytes "<<size/1024<<"KB "<<size/1048576
  //  <<" MB\n"<<maxdims*sizeof(float)/1024<<"KB per file"
  //  <<"\ntime duration:"<<duration<<", "<<duration/features_vec.size()<<" per file\n";
  
  LOG(ERROR)<<"\nSuccessfully extracted the features from "<<features_vec.size()
   <<" files\nfeature vector size: "<<size<<" bytes "<<size/1024<<"KB "<<size/1048576
   <<"MB, "<<maxdims*sizeof(float)/1024<<"KB per file\n";
  return features_vec;
}
