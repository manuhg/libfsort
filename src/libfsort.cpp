#include "libfsort.h"
#ifndef _vec_ret
vector<vector<float>> fvec;
#endif
vector<vector<double>> extract_embeddings(vector<string> image_files,int accuracy_level) //add option to change batch size and and crop sizes
{
    ofstream file_list;
    tsne_wrapper tsne_obj(2,1000);
    file_list.open("file_list.txt");
    for(vector<string>::iterator i=image_files.begin();i!=image_files.end();i++)
        file_list<<*i<<" 0\n";
    file_list.close();
    return tsne_obj.run(extract_features(image_files.size()));
}
