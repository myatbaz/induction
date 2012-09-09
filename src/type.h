#ifndef __type_H_M_
#define __type_H_M_
#include <iostream>
#include <vector>
#include <string>
class type{
public:
     type();
     type(int i);
     type(std::string name, int i);
     type(int id, std::string name, int i);
     void set_name(std::string s){name = s;};
     void set_id(int i){id=i;};
     const std::vector<std::vector<int>>& get_counts() {return counts;};
     void init_feature_vector(int i, int size);
     void inc_feature(int f, int id){counts[f][id]++;};
     void inc_token(){tokens++;};
     void set_feature_vector(int i, std::vector<int> c);
     void info();
     //     std::vector<int> get_vector() const {return counts;};
     std::string get_name() const {return name;};
     int get_id() const {return id;};
private:
     int tokens;
     std::string name;
     int id;//unique id of each type
     std::vector<std::vector<int> > counts;
};

#endif
