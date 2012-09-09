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
     void add_type(type& t);
     void del_type(type& t);
     void vector_add(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b);
     void vector_sub(std::vector<std::vector<int> > &a, const std::vector <std::vector<int> > &b);
     void info();
     static int totalCluster;
private:
     int id;
     std::list<type*> types;
     std::vector<std::vector<int> > counts;
};

#endif
