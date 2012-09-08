all: test

data:	data.cpp
	g++ -std=gnu++98 -o $@ $<  -lboost_iostreams 
test: data
	./data ../data/ws+f.enwsj.pairs.gz
