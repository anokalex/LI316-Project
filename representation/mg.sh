#! /bin/bash

fmoy images/IRM.inr.gz > IRM_moy.inr
mh -n `carflo 60` IRM_moy.inr tmp4.inr
mh -n `carflo 86` IRM_moy.inr tmp5.inr
anac tmp4.inr contour4.anac
anac tmp5.inr contour5.anac
fillc contour4.anac mg.inr `par -x -y IRM_moy.inr` -l 3
echo "Création de mg.inr"
fillc contour5.anac region4.inr `par -x -y IRM_moy.inr` -l 3,6,7,17
echo "Création de region4.inr"
fillc contour5.anac region5.inr `par -x -y IRM_moy.inr` -l 4,5
echo "Création de region5.inr"

rm -f contour4.anac contour5.anac tmp4.inr tmp5.inr IRM_moy.inr

#contour    10(   2), lgr=    14, S=        12
#contour    12(   2), lgr=    20, S=        32
#contour    14(   2), lgr=     4, S=         2
#contour    16(   2), lgr=    12, S=        23
#contour    11(   2), lgr=     2, S=         1
#contour    18(   2), lgr=    12, S=        14
#contour    21(   2), lgr=    10, S=        14
#contour    24(   2), lgr=    36, S=        75
#contour    32(   2), lgr=     4, S=         2
#contour    30(   2), lgr=     6, S=         8
#contour    33(   2), lgr=     8, S=        10
#contour    28(   2), lgr=     2, S=         1
#contour    34(   2), lgr=     6, S=        12
#contour    26(   2), lgr=     2, S=         2
#contour    36(   2), lgr=     4, S=         3
#contour    38(   2), lgr=     6, S=         8
#contour    45(   2), lgr=     6, S=         6
#contour    47(   2), lgr=     4, S=         2
#contour    29(   2), lgr=     6, S=         5
#contour    51(   2), lgr=     4, S=         3
#contour    54(   2), lgr=     4, S=         6
#contour    55(   2), lgr=     6, S=         5
#contour    56(   2), lgr=    16, S=        49
#contour    58(   2), lgr=    24, S=        23
#contour    62(   2), lgr=    16, S=        33
#contour    63(   2), lgr=     2, S=         1
#contour    64(   2), lgr=     2, S=         1
#contour    67(   2), lgr=    12, S=        16
#contour    65(   2), lgr=     4, S=         2
#contour    69(   2), lgr=     2, S=         2
#contour    73(   2), lgr=     4, S=         3
#contour    71(   2), lgr=     2, S=         2
#contour    92(   2), lgr=    10, S=        15
