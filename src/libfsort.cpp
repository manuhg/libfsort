#include "libfsort.h"
#ifndef _vec_ret
vector<vector<float>> fvec;
#endif
vector<vector<double>> extract_embeddings(vector<string> image_files,int max_iters) //add option to change batch size and and crop sizes
{
    ofstream file_list;
    tsne_wrapper tsne_obj(2,max_iters);
    file_list.open("file_list.txt");
    for(vector<string>::iterator i=image_files.begin();i!=image_files.end();i++)
        file_list<<*i<<" 0\n";
    file_list.close();
    #ifndef _vec_ret
    extract_features(&fvec,image_files.size());
    #else
    extract_features(image_files.size());
    #endif
}