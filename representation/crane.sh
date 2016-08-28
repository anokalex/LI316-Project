#! /bin/bash

fmoy images/IRM.inr.gz > IRMmoy.inr
mh -n `carflo 150` IRMmoy.inr tmp.inr
anac tmp.inr contour1.anac
fillc contour1.anac region1.inr `par -x -y IRMmoy.inr` -l 1,2

echo "Création de region1.inr"
rm -f contour1.anac tmp.inr IRMmoy.inr

