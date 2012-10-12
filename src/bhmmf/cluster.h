#ifndef __CLUSTER_H_
#define __CLUSTER_H_
#include <vector>
#include <list>
#include <string>
#include <stdexcept>

#include "type.h"

class cluster{
public:
     cluster();
     const int get_id() const {return id;};
     const int get_typec() const {return types.size();};
     const std::vector<std::vector<int> >& get_counts() const {return counts;};
     const std::vector<int>& get_featureTotalCounts() const {return featureTotalCounts;};
     void add_type(type& t);
     void del_type(type& t);
     void vector_add(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b);
     void vector_sub(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b);
     void info();
     void type_info();
     void init_features(const std::vector<std::vector<int> > &a);
     static int totalCluster;
     static int totalTypesInClusters;
private:
     int id;
     std::list<type*> types;
     std::vector<int> featureTotalCounts;
     std::vector<std::vector<int> > counts;
};

#endif
