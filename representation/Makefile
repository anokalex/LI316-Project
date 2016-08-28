all: lcr.inr exo4

exo4: statsreg regions
	./exo4.4.sh

statsreg:
	gcc -o statsreg statsreg.c -linrimage

regions: region1.inr region2.inr region3.inr region4.inr region5.inr

region1.inr:
	./crane.sh

region2.inr region3.inr:
	./mb.sh

region4.inr region5.inr:
	./mg.sh

lcr.inr:
	./lcr.sh

clean:
	rm -f statsreg
	rm -f mg.inr		region1.inr	region2.inr	\
		region3.inr 	region4.inr	region5.inr	\
		crane.inr	mbg.inr		mbd.inr		\
		mgg.inr		mgd.inr		lcr.inr
