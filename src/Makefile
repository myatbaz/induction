all: test

data.o:	data.cpp data.h
	g++ -std=gnu++0x -c -o $@ $<  -lboost_iostreams 

type.o: type.cpp type.h 
	g++ -std=gnu++0x -c -o $@ $< 

cluster.o: cluster.cpp cluster.h
	g++ -std=gnu++0x -c -o $@ $<

learn: learn.cpp data.o cluster.o type.o
	g++ -std=gnu++0x -o $@ $< data.o type.o cluster.o -lboost_iostreams 

test: learn
	./learn ../data/ws+f.enwsj.pairs.gz > l.out 
