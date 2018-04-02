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

int extract_features(int num_img_files);

int main(int argc, char** argv) {
  return extract_features(atoi(argv[1]));
}

int extract_features(int num_img_files) {
 int num_mini_batches = num_img_files;
  std::vector<std::vector<float>> features_vec;
  Caffe::set_mode(Caffe::CPU);
  const char * binaryproto="ml_data/bvlc_googlenet.caffemodel";
  std::string pretrained_binary_proto(binaryproto);
  ::google::InitGoogleLogging(binaryproto);
  std::string feature_extraction_proto("ml_data/imagenet_val.prototxt");
  boost::shared_ptr<Net<float> > feature_extraction_net(new Net<float>(feature_extraction_proto, caffe::TEST));
  feature_extraction_net->CopyTrainedLayersFrom(pretrained_binary_proto);
  std::string feature_blob_name("fc7");
  
  std::cout<<"Checking parameters";
  CHECK(feature_extraction_net->has_blob(feature_blob_name))<< "Unknown feature name " 
  << feature_blob_name<< " in the network " << feature_extraction_proto;
  std::cout<<"\nExtracting Features";
  LOG(INFO)<<  "Extracting Features";  

  for (int batch_index = 0; batch_index < num_mini_batches; ++batch_index) {
    feature_extraction_net->Forward();
      const boost::shared_ptr<Blob<float> > feature_blob = feature_extraction_net->blob_by_name(feature_blob_name);
      
      int batch_size = feature_blob->num();
      int dim_features = feature_blob->count() / batch_size;
      const float* feature_blob_data;
      std::vector<float> batch_fvec;
      for (int n = 0; n < batch_size; ++n)
      {
        feature_blob_data = feature_blob->cpu_data()+feature_blob->offset(n);
        std::vector<float> dim_fvec {feature_blob_data,feature_blob_data+dim_features};
        batch_fvec.insert(batch_fvec.end(),dim_fvec.begin(),dim_fvec.end());

        LOG(INFO)<<" "<<batch_index<<"/"<<num_mini_batches<<" "<<n<<"/"<<batch_size<<" "<<dim_features<<" : "<<batch_fvec.size();
      }
      features_vec.push_back(batch_fvec);
  }
  std::cout<<"\nSuccessfully extracted the features from "<<features_vec.size()<<" files\nfeature vector size: "<<4096*features_vec.size()*sizeof(float)<<" bytes\n";
  LOG(INFO)<<  "Successfully extracted the features from "<<features_vec.size()<<" files\nfeature vector size: "<<4096*features_vec.size()*sizeof(float)<<" bytes\n";
  return 0;
}
