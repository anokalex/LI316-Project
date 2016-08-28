CFLAGS = `inrinfo --cflags` `pkg-config glib-2.0 --cflags` -I. -g
LDLIBS = `inrinfo --libs` `pkg-config glib-2.0 --libs` -lm

all: split merge

# TME 8
#rajouter segment.o dans split et en dessous
split: split.o utils.o mainsplit.o predicats.o segment.o
split.o utils.o mainsplit.o predicats.o segment.o: splitmerge.h

# TME 9
merge: mainmerge.o split.o utils.o predicats.o merge.o segment.o
mainmerge.o merge.o: splitmerge.h

clean:
	$(RM) split.o creer_region.o utils. mainsplit.o predicats.o segment.o
	$(RM) merge.o mainmerge.o voisins.o
	$(RM) *.inr split merge



