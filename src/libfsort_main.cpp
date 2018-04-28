#define _main
#ifdef _main
#include "libfsort.h"
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
