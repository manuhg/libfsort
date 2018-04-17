#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "libfsort.h"
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

bool exists(const char *f)
{
    struct stat s;
    return(stat(f,&s)==0);
}
vector<vector<float>> extract_features(int num_img_files)
{
    int num_mini_batches = num_img_files;
    vector<vector<float>> features_vec;

    const char * binaryproto="ml_data/bvlc_googlenet.caffemodel";
    string feature_extraction_proto("ml_data/imagenet_val.prototxt");

    if(num_img_files<1)
    {
        cout<<"Too few files!\n";
        return features_vec;
    }
    if(!exists("file_list.txt"))
    {
        cout<<"file_list.txt not found!\n";
        return features_vec;
    }
    if(!exists(binaryproto))
    {
        cout<<"File "<<binaryproto<<" not found!\n";
        return features_vec;
    }
    cout <<"Found "<<binaryproto<<endl;
    if(!exists(feature_extraction_proto.c_str()))
    {
        cout <<"File "<<feature_extraction_proto<<" not found!\n";
        return features_vec;
    }
    cout<<"Found "<<feature_extraction_proto;

    Caffe::set_mode(Caffe::CPU);
    std::string pretrained_binary_proto(binaryproto);
    ::google::InitGoogleLogging(binaryproto);

    boost::shared_ptr<Net<float> > feature_extraction_net(new Net<float>(feature_extraction_proto, caffe::TEST));
    feature_extraction_net->CopyTrainedLayersFrom(pretrained_binary_proto);
    std::string feature_blob_name("fc7");

    if(!feature_extraction_net->has_blob(feature_blob_name))
    {
        cout<< "Unknown feature name "<< feature_blob_name;
        return features_vec;
    }

    for (int batch_index = 0; batch_index < num_mini_batches; ++batch_index) {
        feature_extraction_net->Forward();
        const boost::shared_ptr<Blob<float> > feature_blob = feature_extraction_net->blob_by_name(feature_blob_name);

        int batch_size = feature_blob->num();
        int dim_features = feature_blob->count() / batch_size;

        const float* feature_blob_data;
        vector<float> batch_fvec;
        for (int n = 0; n < batch_size; ++n)
        {
            feature_blob_data = feature_blob->cpu_data()+feature_blob->offset(n);
            vector<float> dim_fvec {feature_blob_data,feature_blob_data+dim_features};
            batch_fvec.insert(batch_fvec.end(),dim_fvec.begin(),dim_fvec.end());
        }
        features_vec.push_back(batch_fvec);
    }
    return features_vec;
}
