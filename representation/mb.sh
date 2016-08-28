#! /bin/bash

fmoy images/IRM.inr.gz > IRM_moy.inr
mh -n `carflo 120` IRM_moy.inr tmp2.inr
anac tmp2.inr contour2.anac
fillc contour2.anac region2.inr `par -x -y IRM_moy.inr` -l 25,38
echo "Creation de region2.inr"
fillc contour2.anac region3.inr `par -x -y IRM_moy.inr` -l 27,28,40
echo "Creation de region3.inr"

rm -f contour2.anac tmp2.inr IRM_moy.inr

