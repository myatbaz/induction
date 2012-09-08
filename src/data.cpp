#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/unordered/unordered_map.hpp>

typedef boost::unordered_map<std::string, int> maps2i;
#define DEBUG 1

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

class data{
public:
     data(); //Construct empty data object
     data(std::istream&); //Constructs one by reading a stream
     void read(char *); //Constructs one by reading a stream
     void info();
private:
     std::istream* inputSource;
     std::vector<std::vector<int> > instanceVector;
     maps2i hash;
};

/*method definitions*/

data::data(): inputSource(&cin) {};
void data::read(char * fname){
     std::string check = fname == NULL ? "" : fname;
     std::ifstream file;
     boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
     if (check.substr(check.find_last_of('.') + 1) == "gz"){
          using namespace boost::iostreams;
          file.open(fname, std::ios_base::in | std::ios_base::binary);
          in.push(gzip_decompressor());
          in.push(file);
          inputSource = new std::istream(&in);
     }
     else if(not check.empty()){
          file.open(fname);
          if(file.good())     inputSource = &file;
          else throw std::invalid_argument("File not found" );   
     }
     string line, subs;
     int i = 0;
     while(getline(*inputSource, line)){
          if (line.empty()) continue;
          std::istringstream iss(line);
          if(DEBUG > 0 && i++ % 1000000 == 0) std::cerr << ".";
          std::vector<int> instance;
          while(iss >> subs){
               int id = hash.size();
               hash[subs] = id;
               instance.push_back(id);
          }
          instanceVector.push_back(instance);
     }    
};
void data::info(){
     cout << "Data:" << instanceVector.size() << endl;
     if (instanceVector.size() > 0)      cout << "Token/row:" << instanceVector[0].size() << endl;
};
int main(int argc, char** argv){
     data d;
     d.read(argv[1]);
     d.info();
     cout << "looping" << endl;
     while(1);
     return 0;
}
