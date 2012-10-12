all: eval.pl bhmmf

eval.pl: check
	test -e $@ || ln -s ../src/scripts/* .

bhmmf: check
	cd ../src/bhmmf; make
	test -e bhmmf || ln -s ../src/bhmmf/bhmmf

check:
	true

clean:
	-rm *.pl *.py *.gp bhmmf
