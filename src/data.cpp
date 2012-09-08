#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/unordered_set.hpp>

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
  //  string get_inputSource() const {return inputSource;}  
  int get_rows() const {return rows;}
  int get_cols() const {return cols;}
  
private:
  std::istream* inputSource;
  int rows;
  int cols;
  int debug;
};

/*method definitions*/

data::data(): inputSource(&cin), rows(0), cols(0), debug(0) {};
//data::data(std::istream& is):inputSource(&is),rows(0), cols(0), debug(0){};
void data::read(char * fname)
{
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
  string line;
  boost::unordered_map<std::string, int> map;
  while(getline(*inputSource, line)){
    if (debug > 10)cout << line << endl;
    std::istringstream iss(line);
    while(iss){ 
      string subs; 
      iss >> subs;
      //      cout << subs << "["<< id <<"] ";
    }
    cout << endl;
    rows++;
  }    
}

void data::info()
{
  cout << "r:" << get_rows() << " c" << get_cols() << endl;  
}
int main(int argc, char** argv){
  data d;
  d.read(argv[1]);
  d.info();
//   //  cout << argv[1] << endl;
//   //  data d(argv[1]);
//   //  d.info();
//   using namespace std;
//   using namespace boost::iostreams;
//   using namespace std;
   return 1;
 }
