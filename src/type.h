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
     void init_feature_vector(int i, int size);
     void inc_feature(int f, int id){counts[f][id]++;};
     void set_feature_vector(int i, std::vector<int> c);
     void info();
     //     std::vector<int> get_vector() const {return counts;};
     std::string get_name() const {return name;};
     int get_id() const {return id;};
private:
     std::string name;
     int id;//unique id of each type
     std::vector<std::vector<int> > counts;
};

type::type(): id(-1){};
type::type(int i): id(-1){counts.resize(i);};
type::type(std::string n, int i): name(n), id(-1){counts.resize(i);};
type::type(int idd, std::string n, int i): name(n), id(idd){counts.resize(i);};
void type::init_feature_vector(int i, int size){counts[i].resize(size);}
void type::set_feature_vector(int i, std::vector<int> c) {counts[i] = c;};
void type::info(){
     std::cout << "Type:" << name << " Id:" << id << std::endl;
     for(int i = 0 ; i < counts.size(); i++){
          std::cout << "f:" << i << "==>\t";
          for(int j = 0 ; j < counts[i].size(); j++){               
               std::cout << counts[i][j] << " ";
          }
          std::cout << std::endl;
     }
};
