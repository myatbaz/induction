#include "type.h"
#include "cluster.h"
type::type(): tokens(0), id(-1), clu(NULL){};
type::type(int i): tokens(0), id(-1), clu(NULL){counts.resize(i);};
type::type(std::string n, int i): tokens(0), name(n), id(-1), clu(NULL){counts.resize(i);};
type::type(int idd, std::string n, int i): tokens(0), name(n), id(idd), clu(NULL){counts.resize(i);};
void type::init_feature_vector(int i, int size){counts[i].resize(size);}
void type::set_feature_vector(int i, std::vector<int> c) {counts[i] = c;};
void type::info(){
     std::cout << "[Type info]" << std::endl;
     std::cout << "Type:" << name << " Id:" << id << "clusterId:" << (*clu).get_id() <<" Token#:" << tokens<<std::endl;
     for(int i = 0 ; i < counts.size(); i++){
          std::cout << "f:" << i << "==>\t";
          for(int j = 0 ; j < counts[i].size(); j++){               
               std::cout << counts[i][j] << " ";
          }
          std::cout << std::endl;
     }
};



