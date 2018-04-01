#include <string>
#include <vector>
#define CPU_ONLY
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

int extract_features();

int main(int argc, char** argv) {
  return extract_features();
}

int extract_features() {
  int num_mini_batches = 10;
  std::vector<std::vector<float>> features_vec;
  Caffe::set_mode(Caffe::CPU);
  const char * binaryproto="ml_data/bvlc_googlenet.caffemodel";
  std::string pretrained_binary_proto(binaryproto);
  ::google::InitGoogleLogging(binaryproto);
  std::string feature_extraction_proto("ml_data/imagenet_val.prototxt");
  boost::shared_ptr<Net<float> > feature_extraction_net(new Net<float>(feature_extraction_proto, caffe::TEST));
  feature_extraction_net->CopyTrainedLayersFrom(pretrained_binary_proto);
  std::string feature_blob_name("fc7");
  
  CHECK(feature_extraction_net->has_blob(feature_blob_name))<< "Unknown feature name " 
  << feature_blob_name<< " in the network " << feature_extraction_proto;
  LOG(ERROR)<< "Extracting Features";

  for (int batch_index = 0; batch_index < num_mini_batches; ++batch_index) {
    feature_extraction_net->Forward();
      const boost::shared_ptr<Blob<float> > feature_blob =
        feature_extraction_net->blob_by_name(feature_blob_name);
      int batch_size = feature_blob->num();
      int dim_features = feature_blob->count() / batch_size;
      const float* feature_blob_data;
      for (int n = 0; n < batch_size; ++n)
      {
        feature_blob_data = feature_blob->cpu_data()+feature_blob->offset(n);
        std::vector<float> fvec;
        for (int d = 0; d < dim_features; ++d)
          fvec.push_back(feature_blob_data[d]);
        features_vec.push_back(fvec);
      }
  }
  LOG(ERROR)<< "Successfully extracted the features!"<<features_vec.size();
  return 0;
}
