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
    tsne_wrapper tsne_obj(2,1000);
    file_list.open("file_list.txt");
    for(vector<string>::iterator i=image_files.begin();i!=image_files.end();i++)
        file_list<<*i<<" 0\n";
    file_list.close();
    vector<vector<float>>features=extract_features(image_files.size());
    if(features.size()<1)
        return empty;
    return tsne_obj.run(features);
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
        cout<<"\n"<<a;
    }
    cout<<"\n";
    extract_embeddings(files,1);
    return 0;
}

#endif
