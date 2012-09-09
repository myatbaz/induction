all: test

data.o:	data.cpp
	g++ -std=gnu++0x -c -o $@ $<  -lboost_iostreams 

type.o: type.cpp
	g++ -std=gnu++0x -c -o $@ $<

learn: learn.cpp data.o type.h
	g++ -std=gnu++0x -o $@ $< data.o -lboost_iostreams 

test: learn
	./learn ../data/ws+f.enwsj.pairs.gz > l.out 
