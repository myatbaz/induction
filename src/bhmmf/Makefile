all: bhmmf

data.o:	data.cpp data.h
	g++ -O3 -std=gnu++0x -c -o $@ $<  -lboost_iostreams 

type.o: type.cpp type.h cluster.o
	g++ -O3 -std=gnu++0x -c -o $@  $< 

cluster.o: cluster.cpp cluster.h 
	g++ -O3 -std=gnu++0x -c -o $@ $<

bhmmf: bhmmf.cpp data.o cluster.o type.o
	g++ -O3 -std=gnu++0x -o $@ $< data.o type.o cluster.o -lboost_iostreams 

#test: learn
#	./learn ${DATA} > l.out 
#DATA=../data/enm.bigram.gz

clean:
	-rm *.o bhmmf