#include "cluster.h"

cluster::cluster(){id = totalCluster++;};
void cluster::add_type(type& t){
     if(t.get_cluster() != NULL) throw std::domain_error("Already assigned to a cluster");
     t.set_cluster(this);
     totalTypesInClusters++;
     types.push_back(&t);
     if(counts.size() == 0) {
          init_features(t.get_counts());
     }
     else vector_add(counts, t.get_counts());
}

void cluster::init_features(const std::vector<std::vector<int> > &a){
     counts.resize(a.size());
     featureTotalCounts.resize(counts.size(),0);
     for(int i = 1 ; i < counts.size() ; i++){
          counts[i].resize(a[i].size());
          for(int j = 0 ; j < counts[i].size(); j++){
               counts[i][j] += a[i][j];
               featureTotalCounts[i] += a[i][j];
          }
     }
}

void cluster::del_type(type& t){
     if(t.get_cluster() == NULL) throw std::domain_error("Delete attempt to already not assigned to a cluster");
     t.set_cluster(NULL);
     totalTypesInClusters--;
     types.remove(&t);
     if(types.size()==0) std::cout << "Empty cluster:" << id << std::endl;
     if(counts.size() == 0) throw std::domain_error("removing from an empty cluster");
     else vector_sub(counts, t.get_counts());
}

void cluster::vector_add(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b){
     if(a.size() != b.size()) throw std::length_error("Size mismatch");   
     for(int i = 1 ; i < b.size(); i++){
          for(int j = 0 ; j < b[i].size(); j++){
               a[i][j] += b[i][j];
               featureTotalCounts[i] += b[i][j];
          }
     }
}

void cluster::vector_sub(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b){
     if(a.size() != b.size()) throw std::length_error("Size mismatch");   
     for(int i = 1 ; i < b.size(); i++){
          for(int j = 0 ; j < b[i].size(); j++){
               a[i][j] -= b[i][j];
               featureTotalCounts[i] -= b[i][j];
          }
     }
}

void cluster::info(){
     std::cout << "[cluster_info]" << std::endl;
     std::cout << "Cluster_id:" << id << " Types#:" << types.size() << " Types in all:" << totalTypesInClusters << std::endl;
     for(std::list<type*>::iterator i=types.begin(); i != types.end() ; ++i)
          (**i).info();     
     std::cout << "Feature counts:" << std::endl;
     for(int i = 1 ; i < counts.size(); i++){
          for(int j = 0 ; j < counts[i].size(); j++)
               std::cout << "[" << i << " " << j << " " << counts[i][j] << "] ";
          std::cout << " Total:" << featureTotalCounts[i] <<std::endl;
     }
}

void cluster::type_info() {
     std::cout << "Cluster_id:" << id << " Types#:" << types.size() << " Types in all:" << totalTypesInClusters << std::endl;
     for(std::list<type*>::iterator i=types.begin(); i != types.end() ; ++i)
          std::cout << (**i).get_name() << " ";
     std::cout << std::endl;
}

int cluster::totalCluster = 0;
int cluster::totalTypesInClusters = 0;
