#include "libfsort.h"
template<class Dtype> void display_vector_(vector<vector<Dtype>> f)
{
    if(f.size()<1)
        cout<<"Empty!";
    else
        cout<<"feature vector:"<<f.size()<<"x"<<f[0].size();

    for( class vector<vector<Dtype>>::iterator i=f.begin();i!=f.end();i++)
    {
        //cout<<endl;
        for(class vector<Dtype>::iterator j=i->begin();j!=i->end();j++)
            cout<<"\t"<<*j;
    }
    cout<<endl;
}
vector<vector<double>> extract_embeddings(vector<string> image_files,int accuracy_level,bool print_tsnepts) //add option to change batch size and and crop sizes
{
    vector<vector<double>> embeddings;
    if(image_files.size()<1)
        return embeddings;

    ofstream file_list;
    tsne_wrapper tsne_obj;
    file_list.open("file_list.txt");
    for(vector<string>::iterator i=image_files.begin();i!=image_files.end();i++)
        file_list<<*i<<" 0\n";
    file_list.close();

    cout<<image_files.size()<<" input image files";
    vector<vector<float>>features = extract_features(image_files.size());
    //display_vector_<float>(features);
    if(features.size()<1)
        return embeddings;
    embeddings=tsne_obj.run(features,2,1000,4);
    if(print_tsnepts)
        display_vector_<double>(embeddings);
    return embeddings;
}
//#define _main
#ifdef _main
#include<iostream>
#include<string.h>
#include<cstring>
using namespace std;
int main(int argc, char ** argv)
{
    vector<string> files;
    for(int i=1;i<argc;i++)
    {
        string a(argv[i],strlen(argv[i]));
        files.push_back(a);
        //cout<<"\n"<<a;
    }
    vector<vector<double>> v=extract_embeddings(files,1);
    cout<<endl;
    return 0;
}


#endif
