all: test

DATA=../data/enm.bigram.gz

bigram.gz: ../data/test.bgw.tok.gz
	zcat $< | perl -lne 'for $$w (split) {print "$$w\t$$p" if defined $$p; $$p=$$w;}' | gzip > $@	

data.o:	data.cpp data.h
	g++ -O3 -std=gnu++0x -c -o $@ $<  -lboost_iostreams 

type.o: type.cpp type.h cluster.o
	g++ -O3 -std=gnu++0x -c -o $@  $< 

cluster.o: cluster.cpp cluster.h 
	g++ -O3 -std=gnu++0x -c -o $@ $<

learn: learn.cpp data.o cluster.o type.o
	g++ -O3 -std=gnu++0x -o $@ $< data.o type.o cluster.o -lboost_iostreams 

test: learn
	./learn ${DATA} > l.out 
