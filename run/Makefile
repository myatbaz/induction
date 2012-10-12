SEED=1
export PATH := ../../bin/:${PATH}

bin:
	cd ../../bin; make

%.tok.gz: %.gold.gz
	zcat $< | perl -lane '$$stc .= "$$F[0] "; if(!$$_){print $$stc; $$stc="";}'  | gzip > $@

%.pos.gz: %.gold.gz
	zcat $< | perl -lane 'print $$F[1] if /\S/' | gzip > $@

%.words.gz: %.gold.gz
	zcat $< | perl -lane 'print $$F[0] if /\S/' | gzip > $@

%.bigram.gz: %.tok.gz
	zcat $< | perl -lne 'for $$w (split) {print "$$w\t$$p" if defined $$p; $$p=$$w;}' | gzip > $@	

%.test: %.bigram.gz
	bhmmf $< > $@

%.eval: %.words.gz %.pos.gz
	toeval.pl final.ans $*.words.gz | eval.pl -m -v -g $*.pos.gz

.SECONDARY:
	*.tok.gz *.pos.gz *.words.gz *.bigram.gz *.test