#include "cluster.h"

cluster::cluster(){id = totalCluster++;};
void cluster::add_type(type& t){
     types.push_back(&t);
     if(counts.size() == 0) counts = t.get_counts();//not sure about this code??
     else vector_add(counts, t.get_counts());
}

void cluster::del_type(type& t){
     types.remove(&t);
     if(counts.size() == 0) throw std::domain_error("removing from an empty cluster");
     else vector_sub(counts, t.get_counts());
}

void cluster::info(){
     std::cout << "Cluster_id:" << id << std::endl;
     for(std::list<type*>::iterator i=types.begin(); i != types.end() ; ++i)
          (**i).info();
     std::cout << "Feature counts:" << std::endl;
     for(int i = 0 ; i < counts.size(); i++){
          for(int j = 0 ; j < counts[i].size(); j++)
               std::cout << "[" << i << " " << j << " " << counts[i][j] << "] ";
          std::cout << std::endl;
     }
}

void cluster::vector_add(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b){
     if(a.size() != b.size()) throw std::length_error("Size mismatch");   
     for(int i = 0 ; i < b.size(); i++)
          for(int j = 0 ; j < b[i].size(); j++)
               a[i][j] += b[i][j];
}

void cluster::vector_sub(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b){
     if(a.size() != b.size()) throw std::length_error("Size mismatch");   
     for(int i = 0 ; i < b.size(); i++)
          for(int j = 0 ; j < b[i].size(); j++)
               a[i][j] -= b[i][j];
}

int cluster::totalCluster = 0;
