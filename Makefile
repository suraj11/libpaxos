all:
	(cd src ; make)
	(cd sample ; make)
clean:
	(cd src ; make clean)
	(cd sample ; make clean)
