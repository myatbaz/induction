#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <boost/unordered/unordered_map.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include "data.h"
#include "type.h"
#include "cluster.h"
typedef boost::unordered_map<std::string, int> maps2i;
#define isexsist(h,v) h.find(v) != h.end()
class learn{
public:
     learn();
     learn(std::vector<std::string> r);
     void preprocess_data();
     void assign_id(maps2i& m);
     void counts();
     void info();
private:
     int threshold;
     int numberClusters;
     std::vector<std::string> rows;
     maps2i typeMap;
     std::vector<maps2i> typeHash;
     std::vector<type> typeObjects;
     std::vector<cluster> clusters;
};

learn::learn():threshold(100),numberClusters(45){clusters.resize(numberClusters);}
learn::learn(std::vector<std::string> r):threshold(100),numberClusters(45){rows = r; clusters.resize(numberClusters);};
void learn::preprocess_data(){
     if (rows.empty()) {std::cerr << "No row data" << std::endl; return;}
     for(int i = 0 ; i < rows.size(); i++){
          std::istringstream iss(rows[i]);
          std::string subs;
          for(int i = 0 ; iss >> subs ; i++){
               if (i == typeHash.size()) typeHash.push_back(*(new maps2i));
               if(isexsist(typeHash[i],subs)) typeHash[i][subs]++;               
               else typeHash[i][subs] = 0;
          }          
     }
     //std::cout << "feat size:" << typeHash.size() << std::endl;     
     for(int i = 1 ; i< typeHash.size() ; i++){
     //      std::cout << "i:"<< i << " Before feat_types:" << typeHash[i].size() << std::endl;
          assign_id(typeHash[i]);
     //      std::cout << "i:"<< i << " After feat_types:" << typeHash[i].size() << std::endl;
     }     
}

struct compare_second{
     template<class Pair>
          bool operator()(Pair* lhs, Pair* rhs) const{
          return lhs->second > rhs->second;
     }
};

template<class T>
     struct make_pointer{
     typedef T* result_type;
     T* operator()(T& v) const{ return &v; }
};

void learn::assign_id(maps2i& m){
     using namespace boost::adaptors;
     typedef maps2i::value_type pair_type;
     auto p = m | transformed(make_pointer<pair_type>());
     std::set<pair_type*, compare_second> value_ordered(p.begin(), p.end());
     maps2i id_map;
     int i = 0;
     for(auto x : value_ordered | indirected | map_keys){
          int id = id_map.size();
          if(i++ < threshold) id_map[x] = id;
          //          std::cout << "[" <<x << " " << id << "] ";
     }
     m.clear();
     m = id_map;
}

void learn::counts(){
     if (rows.empty()) {std::cerr << "No row data" << std::endl; return;}     
     for(int i = 0 ; i < rows.size(); i++){
          std::istringstream iss(rows[i]);
          std::string subs;
          int curObjId = -1;
          for(int i = 0 ; iss >> subs ; i++){
               if (i == 0 &&  not (isexsist(typeMap,subs))){
                    curObjId = typeMap.size();
                    typeMap[subs] = curObjId;
                    type t(curObjId, subs, typeHash.size());
                    t.inc_token();
                    for(int j = 1 ; j < typeHash.size(); j++)
                         t.init_feature_vector(j,typeHash[j].size());
                    typeObjects.push_back(t);
               }
               else if (i == 0) {curObjId = typeMap.at(subs); typeObjects[curObjId].inc_token();}
               if(i > 0 && isexsist(typeHash[i],subs)){
                    int fid = typeHash[i].at(subs);                    
                    //                    std::cerr << "types#:" << typeObjects.size() << " fid:" << fid << std::endl;
                    typeObjects[curObjId].inc_feature(i,fid);
               }
          }          
     }
}

void learn::info(){
     // clusters[2].add_type(typeObjects[0]);
     // clusters[2].info();
     // std::exit(1);
     for(int i = 0 ; i < typeObjects.size(); i++)
          typeObjects[i].info();
}

int main(int argc, char ** argv){
     std::cout << "learn:ok" << std::endl;
     data d;
     d.read(argv[1]);
     d.info();
     learn l(d.get_rows());
     l.preprocess_data();
     l.counts();
     l.info();
     while(1);
     return 0;
}
