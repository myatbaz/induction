#include "data.h"
data::data(): inputSource(&std::cin) {};
data::~data(){rows.clear();}
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
     std::string line, subs;
     int i = 0;
     while(getline(*inputSource, line)){
          if (line.empty()) continue;
          rows.push_back(line);
     }    
};
void data::info(){
     std::cout << "Data:" << rows.size() << std::endl;
     //     for(int i = 0 ; i < rows.size(); i++)
     //std::cout << rows[i] << std::endl;
};
