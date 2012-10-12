#include <iostream>
#include <cstdlib> 
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
#define myrand() rand()*1.0 / RAND_MAX
#define LOGZERO 0
class learn{
public:
     learn();
     learn(std::vector<std::string> r, int cc);
     void set_cluster(int cc){numberClusters = cc;};
     void preprocess_data();
     void assign_id(maps2i& m);
     void counts();
     void info();
     double cluster_prior(cluster &c) const;
     double cluster_posterior(type &t, cluster &c) const;
     double log_cluster_prior(cluster &c) const;
     double log_cluster_posterior(type &t, cluster &c) const;
     void random_init();
     void sample_type();
     double log_sum(double a, double b)const {return a+b;}
          //                   if (a == LOGZERO) return b;
          //          else if(b == LOGZERO) return a;
          //         else return a > b ? a + log(1 + std::exp (b - a)) : b + log(1 + std::exp(a - b)); };
     int multi(std::vector<double>& probs) const;
     int multi(std::vector<double>& probs, double normalize) const;
     void write_answer(std::string s);
private:
     int threshold;
     int numberClusters;
     double hyperBeta;
     double hyperAlpha;
     std::vector<std::string> rows;
     maps2i typeMap;
     std::vector<maps2i> typeHash;
     std::vector<type> typeObjects;
     std::vector<cluster> clusters;
     
};

learn::learn():threshold(100),numberClusters(45),hyperAlpha(1),hyperBeta(1){clusters.resize(numberClusters);srand(1);}
learn::learn(std::vector<std::string> r, int cluster):threshold(100),numberClusters(cluster),hyperAlpha(0.05),hyperBeta(1){rows = r; clusters.resize(numberClusters);srand(1);};
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

double learn::cluster_prior(cluster &c) const{
     return (c.get_typec() + hyperAlpha) / (c.totalTypesInClusters + c.totalCluster * hyperAlpha);
}

double learn::cluster_posterior(type &t, cluster &c) const{
     std::vector<std::vector<int> > typeCounts = t.get_counts();
     std::vector<std::vector<int> > counts = c.get_counts();
     std::vector<int> allCounts = c.get_featureTotalCounts();
     double post = 1;
     for(int i = 1 ; i < typeCounts.size() ; i++){
          double postNum = 1, postDen = 1;
          int allTypeCounts = 0;//better design should be made
          for(int j = 0 ; j < typeCounts[i].size(); j++){
               allTypeCounts += typeCounts[i][j];
               for(int k = 0 ; k < typeCounts[i][j] - 1; k++){
                    postNum *= (counts[i][j] + k + hyperBeta);
               }
          }
          for(int k = 0 ; k < allTypeCounts - 1; k++)
               postDen *= (allCounts[i] + k + typeHash[i].size() * hyperBeta); //ad          
          post *= postNum / postDen;
          //          std::cout << i << "typeHash" << typeHash[i].size() <<" Num" << postNum << "Den" << postDen << " post" << post << std::endl;
     }          
     return post;
}

double learn::log_cluster_prior(cluster &c) const{
     return log(c.get_typec() + hyperAlpha) - log(c.totalTypesInClusters + c.totalCluster * hyperAlpha);
}

double learn::log_cluster_posterior(type &t, cluster &c) const{
     std::vector<std::vector<int> > typeCounts = t.get_counts();
     std::vector<std::vector<int> > counts = c.get_counts();
     std::vector<int> allCounts = c.get_featureTotalCounts();
     double post = LOGZERO;
     for(int i = 1 ; i < typeCounts.size() ; i++){
          double postNum = LOGZERO, postDen = LOGZERO;
          int allTypeCounts = 0;//better design should be made
          for(int j = 0 ; j < typeCounts[i].size(); j++){
               allTypeCounts += typeCounts[i][j];
               for(int k = 0 ; k < typeCounts[i][j] - 1; k++){
                    postNum = log_sum(postNum, log(counts[i][j] + k + hyperBeta));
               }
          }
          for(int k = 0 ; k < allTypeCounts - 1; k++)
               postDen = log_sum(postDen,  log(allCounts[i] + k + typeHash[i].size() * hyperBeta)); //add only once 
          //std::cout << "postNum:" << std::exp(postNum) << " postDen:" << std::exp(postDen) << std:endl;          
          double diff = log_sum(postNum, -postDen);
          post = log_sum(post, diff);
          //std::cout << i << "typeHash" << typeHash[i].size() <<" Num" << postNum << "Den" << postDen << " post" << post << std::endl;
     }
     return post;
}

void learn::random_init(){
     for(std::vector<type>::iterator iter = typeObjects.begin(); iter != typeObjects.end() ; iter++){
          int cid = rand() % numberClusters;
          clusters[cid].add_type(*iter);
     }     
}

void learn::sample_type(){
     std::vector<double> probs(clusters.size(),0);
     for(int it = 0 ; it < 5 ;it++){
          std::cout << "iter:" << it << std::endl;
          std::stringstream out;
          out << it << ".out";
          write_answer(out.str());
          for(std::vector<type>::iterator iter = typeObjects.begin(); iter != typeObjects.end() ; iter++){
               cluster* cur = (*iter).get_cluster();
               //               std::cout << "type:" << (*iter).get_name() << " Deleted from:" << (*cur).get_id() << " ";
               (*cur).del_type(*iter);
               double maxProb = -99999999;
               for(int i = 0 ; i < clusters.size(); i++){
                    double pri = log_cluster_prior(clusters[i]);
                    double pos = log_cluster_posterior(*iter, clusters[i]);
                    //std::cout << i << " pri:" << std::exp(pri) << " pos:" << std::exp(pos) << std::endl;
                    //std::cout << i << " pri:" << pri << " pos:" << pos << std::endl;
                    probs[i] = log_sum(pri, pos);
                    if (probs[i] > maxProb) maxProb = probs[i];
                    //                    probs[i] = pri * pos;
               }
               int ncid =  multi(probs, maxProb);
               //               std::cout << "Added to:" << ncid << std::endl;
               clusters[ncid].add_type(*iter);
          }
     }
}

int learn::multi(std::vector<double>& probs)const {
     double sum = 0,min = INT_MAX, r = myrand();
     int ret = -1;
     for(int i = 0 ; i < probs.size();i++)
          min = min < -probs[i] ? min : -probs[i];
     //     std::cout << "min:" << min << std::endl;
     for(int i = 0 ; i < probs.size();i++){
          //          std::cout << probs[i] << " ";
          probs[i] = std::exp(probs[i]+min);
          //          std::cout << "[" <<probs[i] << "] ";
          sum += probs[i];
     }
     //     std::cout << "random:" << r << " sum:" << sum << std::endl;
     for(int i = 0 ; i < probs.size();i++){
          probs[i] /= sum;
          if (i > 0) probs[i] += probs[i-1];
          //          std::cout << probs[i] << " ";
          if(r < probs[i]) {ret = i; break;}
     }     
     //     std::cout << std::endl;
     return ret;
}

int learn::multi(std::vector<double> & probs, double normalizer)const{
     int ret = 0;
     double sum = exp(probs[0] - normalizer), r = -1;
     //     std::cout << "norm:" << normalizer << std::endl;
     for(int i = 1 ; i < probs.size() ; i++){
          r = myrand();
          //          std::cout << "probsbef: " << probs[i] << std::endl;
          probs[i] = std::exp(probs[i] - normalizer);
          sum += probs[i];
          if (r < probs[i] / sum) ret = i;
          //   std::cout <<  "r:" << r << " probs:" << probs[i] << " pr:" << probs[i]/sum << " sum:" << sum << " ret:" << ret << std::endl;
     }
     //     std::exit(1);
     return ret;
}

void learn::info(){
     for(int i = 0 ; i < clusters.size(); i++)
          //          clusters[i].info();
          clusters[i].type_info();
}

void learn::write_answer(std::string s){
     std::ofstream out;
     std::cout << "writing to " << s << std::endl;
     out.open(s);
     for(std::vector<type>::iterator iter = typeObjects.begin(); iter != typeObjects.end() ; iter++){
          out << (*iter).get_name() << "\t" << (*(*iter).get_cluster()).get_id() << std::endl;
     }
     out.close();
}

int main(int argc, char ** argv){
     std::cout << "learn:ok" << std::endl;
     data d;
     d.read(argv[1]);
     d.info();
     learn l(d.get_rows(),45);
     l.preprocess_data();
     l.counts();
     l.random_init();
     //     l.info();
     l.sample_type();
     //l.info();
     l.write_answer("final.ans");
     return 0;
}
