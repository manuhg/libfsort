#ifndef CPU_ONLY
 #define CPU_ONLY
#endif
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
#include <iostream>

using caffe::Blob;
using caffe::Caffe;
using caffe::Net;
using std::string;
namespace db = caffe::db;
using namespace std;

bool exists(const char *f)
{
    struct stat s;
    return(stat(f,&s)==0);
}

vector<vector<float>> extract_features(int num_img_files)
{
    int num_mini_batches = num_img_files;
    vector<vector<float>> features_vec;

    const char * binaryproto="ml_data/models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel";
    string feature_extraction_proto("ml_data/imagenet_val.prototxt");
    std::string pretrained_binary_proto(binaryproto);
    ::google::InitGoogleLogging(binaryproto);

    if(num_img_files<1)
    {
        LOG(ERROR)<<"oo few files!"<<endl;
        return features_vec;
    }
    if(!exists("file_list.txt"))
    {
        LOG(ERROR)<<"\nfile_list.txt not found!"<<endl;
        return features_vec;
    }
    if(!exists(binaryproto))
    {
        LOG(ERROR)<<"File "<<binaryproto<<" not found!"<<endl;
        return features_vec;
    }
    LOG(ERROR)<<"Found "<<binaryproto<<endl;
    if(!exists(feature_extraction_proto.c_str()))
    {
        LOG(ERROR) <<"File "<<feature_extraction_proto<<" not found!"<<endl;
        return features_vec;
    }
    LOG(ERROR)<<"Found "<<feature_extraction_proto<<endl;

    Caffe::set_mode(Caffe::CPU);

    LOG(ERROR)<<"Extracting features"<<endl;

    boost::shared_ptr<Net<float> > feature_extraction_net(new Net<float>(feature_extraction_proto, caffe::TEST));
    feature_extraction_net->CopyTrainedLayersFrom(pretrained_binary_proto);
    std::string feature_blob_name("fc7");

    if(!feature_extraction_net->has_blob(feature_blob_name))
    {
        LOG(ERROR)<< "Unknown feature name "<< feature_blob_name<<endl;
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
    LOG(ERROR)<<"Done extracting features :"<<features_vec.size()<<"x"<<features_vec[0].size()<<endl<<endl;
    return features_vec;
}
// int main(int argc,char **argv)
// {
//     cout<<"hello!"<<endl;
//     vector<vector<float>>f=extract_features(atoi(argv[1]));
//     if(f.size()<1)
//         cout<<"mpty!";
//     else
//         cout<<""<<f.size()<<" files"<<"<<f[0].size()<<" features";
//     int hh=0;
//     for( vector<vector<float>>::iterator i=f.begin();i!=f.end();i++)
//     {
//         cout<<endl;
//         for(vector<float>::iterator j=i->begin();j!=i->end();j++)
//         	// if(*j)
//         		cout<<*j;
//     }
//     cout<<endl;
// }
