#! /bin/bash

fmoy images/IRM.inr.gz > IRM_moy.inr
mh -n `carflo 150` IRM_moy.inr tmp1.inr
anac tmp1.inr contour1.anac

fillc contour1.anac tmp7.inr `par -x -y IRM_moy.inr` -l 1
so tmp7.inr region1.inr cav.inr
so cav.inr mg.inr lcr.inr
echo "Création de lcr.inr"

rm -f contour1.anac tmp1.inr tmp7.inr IRM_moy.inr cav.inr



