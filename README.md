PROJET LI316

L3 PIMA - PATEL M.TAYYIB


Le projet est subdivisé en 4 parties : harris, hough, representation et splitmerge.

Pour chaque partie, 3 démonstrateurs sont présents, testant le code sur 3 images différentes (pour la partie hough, il y en a 1 en plus pour tester la détection de cercle).

Pour afficher l'aide de chaque démonstrateur, tapez ./[nom du démonstrateur] --help

Chaque démonstrateur prend plusieurs options. (Voir ci-dessous)

PARTIE HARRIS:

Démonstrateurs : demolena.sh democamera.sh democarres.sh
Application du détecteur de Harris sur lena.inr, cameraman.inr ou carre16.pgm. 3 possibilités sont données pour chaque démonstrateur:
    -o: Le détecteur sera exécuté avec des paramètres optimaux, et ensuite comparé à l'image RESFILTER obtenue par l'application du filtre de l'Exercice 7 à l'image suivie d'un seuillage (par le seuil optimal).
    -m: Le détecteur sera exécuté avec plusieurs séries de paramètres non optimaux, et chaque résultat sera comparé à RESFILTER.
    -p: Le détecteur sera exécuté avec les paramètres fournis par l'utilisateur: Kappa, Sigma et Seuil.

Scripts utilisés par les démonstrateurs:

    plotslocseuil.sh:
    Utilisation: ./plotslocseuil.sh ../images/imgin [Kappa] [Sigma] [Seuil]

    Application du détecteur sur imgin avec les paramètres Kappa,Sigma et Seuil

    filter:
    Utilisation: ./filter [lena|carre16|cameraman]

    Crée le filtre de l'Exercice 7, et compare les croix obtenues à l'aide du détecteur (donc en appliquant plotslocseuil.sh) à ce filtre.


Codes:
    harris.c sloc.c

    Utilisation:
    ./harris imgin imgout -K kappa -s sigma
    ./sloc imgin imgout -n seuil

PARTIE HOUGH:

Démonstrateurs: demorectangle.sh demofenetre.sh demorotate.sh democircle.sh
Application de la transformée de Hough et :
    1)test de la détection de droites sur rectangle.inr, fenetre.inr, rotate.inr.
    2)test de la détection de cercles sur cerc.inr

Utilisation pour demorectangle,demorotate et demofenetre: ./[nom du démonstrateur] [-p $Tolerance $dtheta $drho]

Si -p est spécifié, l'utilisateur doit fournir les paramètres Tolerance,dtheta et drho.

Utilisation pour democircle: ./[nom du démonstrateur] [-p $Tolerance $dx $dy $dr]

Si -p est spécifié, l'utilisateur doit fournir les paramètres Tolerance,dx, dy et dr.

Le démonstrateur affiche l'accumulateur obtenu et superpose les droites détectées à l'image analysée.

Remarque: Pour l'image fenetre.inr, l'éxecution dure environ 25 minutes.

Scripts utilisés par les démonstrateurs:

    accumulateur.sh:
    Utilisation: ./accumulateur.sh [-p] ../images/imgin img.cont img.inr [a fournir si -p spécifié: tolerance [dtheta drho|dx dy dr]]

    Affiche l'accumulateur et les figures détectées par l'algorithme.

    contours.sh (utilisé par accumulateur.sh):
    Utilisation: ./contours.sh imgin [imgout|sortie standard]

    Détecte les contours d'une image en utilisant le filtre de Sobel.

Codes:
    hough.c hough_c.c

    Utilisation:
        ./hough imgin imgout [-t tolerance -st dtheta -sr drho -n nombre de maxima locaux à garder dans findmax]
        ./hough_c imgin imgout [ -t tolerance -sx dx -sy dy -sr dr ]


PARTIE SPLIT/MERGE:

Démonstrateurs : demomuscle.sh demoseiche.sh demobureau.sh
Application de l'algorithme de split/merge sur muscle.pgm, seiche.pgm  ou bureau.pgm. 3 possibilités sont données pour chaque démonstrateur:
    -o: Le programme sera exécuté avec des paramètres optimaux.
    -m: Le programme sera exécuté avec plusieurs séries de paramètres non optimaux.
    -p: Le détecteur sera exécuté avec les paramètres fournis par l'utilisateur: Split_thresh, Merge_thresh, xmin et ymin.


Codes (main):
    mainsplit.c mainmerge.c


    Utilisation:
    ./split imgin imgout -s split_thresh -min xmin ymin
    ./merge imgin imgout -s split_thresh -mt merge_thresh -min xmin ymin


PARTIE REPRESENTATION:

Codes et fichiers: ./crane.sh exo4.4.sh ./lcr.sh ./mb.sh ./mg.sh atlas.txt statsreg.c Makefile

 atlas.txt: fichier prérempli, contenant des informations sur les
	       regions de l'atlas sous la forme:
       	       	 nom_de_la_region niveau_de_gris
            ce fichier est utilisé par exo4.4.sh pour determiner les différentes
            régions de l'atlas.
 Makefile:
	 make: génère tous les fichiers demandés dans le TME
	       (execute tous les scripts dans le bon ordre)
	 make exo4: génère les résultats de l'exercice 4
	       (execute tous les scripts sauf lcr.inr)
	 make statsreg: genere l'executable statsreg
	 make regions: genere les fichiers regions 1 à 5
	       (execute crane.sh mb.sh mg.sg)
	 make lcr.inr: (execute lcr.sh)
	 make clean: efface tous les fichiers créés


