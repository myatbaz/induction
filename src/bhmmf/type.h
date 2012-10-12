#ifndef __type_H_M_
#define __type_H_M_
#include <iostream>
#include <vector>
#include <string>
class cluster;

class type{
public:
     type();
     type(int i);
     type(std::string name, int i);
     type(int id, std::string name, int i);
     void set_name(std::string s){name = s;};
     void set_id(int i){id=i;};
     void set_cluster(cluster *c){clu=c;};
     void set_feature_vector(int i, std::vector<int> c);
     void init_feature_vector(int i, int size);
     void inc_feature(int f, int id){counts[f][id]++;};
     void inc_token(){tokens++;};
     void info();
     //     std::vector<int> get_vector() const {return counts;};
     const std::string& get_name() const {return name;};
     const int get_id() const {return id;};
     const std::vector<std::vector<int> >& get_counts(){return counts;};
     cluster* get_cluster()const {return clu;};
private:     
     int tokens;
     std::string name;
     int id;//unique id of each type
     std::vector<std::vector<int> > counts;
     cluster* clu;
};

#endif
