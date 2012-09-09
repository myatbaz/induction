#include <vector>
#include <string>


class type{
public:
     type();
     type(int i, std::vector<int> c);
     type(std::string name, int i, std::vector<int> c);
     void set_name(std::string s){name = s;}
     void set_id(int i){id=i;}
     void set_vector(std::vector<int> c) {counts = c;}
     std::vector<int> get_vector const {return counts;}
     std::string get_name const {return name;};
     int get_id const {return id}
private:
     std::string name;
     int id;//unique id of each type
     std::vector<int> counts;          
};

type::type(): id(-1){};
type::type(int i, std::vector<int> c): id(i), counts(c){};
type::type(std::string n, int i, std::vector<int> c): name(n), id(i), counts(c){};
