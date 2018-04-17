#include "libfsort.h"
#ifndef _vec_ret
vector<vector<float>> fvec;
#endif
vector<vector<double>> extract_embeddings(vector<string> image_files,int accuracy_level) //add option to change batch size and and crop sizes
{
    vector<vector<double>> empty;
    if(image_files.size()<1)
        return empty;

    ofstream file_list;
    tsne_wrapper tsne_obj;
    file_list.open("file_list.txt");
    for(vector<string>::iterator i=image_files.begin();i!=image_files.end();i++)
        file_list<<*i<<" 0\n";
    file_list.close();
    vector<vector<float>>features;
    for (int j=1;j<=100;j++)
    {
        vector<float>a;
        for(int i=1;i<=512;i++)
            a.push_back(i*j);
        features.push_back(a);
    }
    //extract_features(image_files.size());
    if(features.size()<1)
        return empty;
    cout<<"\nFeature Vector: "<<features.size()<<"x"<<features[0].size();
    return tsne_obj.run(features,2,1000);
}
#define _main
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
    cout<<"\n"<<v.size()<<" files "<<v[0].size()<<" dims";
    cout<<endl;
    return 0;
}

#endif
