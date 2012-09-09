#ifndef __data_h_M_
#define __data_h_M_
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#define DEBUG 1

class data{
public:
     data(); 
     ~data();
     void read(char *);
     void info();
     std::vector<std::string> get_rows() const {return rows;};
private:
     std::istream* inputSource;
     std::vector<std::string> rows;
     //     std::vector<std::vector<int> > instanceVector;

};
#endif
