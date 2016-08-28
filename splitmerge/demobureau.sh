#! /bin/bash

cd codes/
make clean
make
if [[ $1 == "-p" ]]; then
    if [[ $# -eq 5 ]]; then
        echo "Paramètres : split_thresh: $2, merge_thresh: $3, min: $4 $5"
    ./split ../images/bureau.pgm bureausplit.inr -s $2 -min $4 $5
    xvis bureausplit.inr -nu -p -2 2>/dev/null &
    ./merge ../images/bureau.pgm bureaumerge.inr -s $2 -mt $3 -min $4 $5
     xvis bureaumerge.inr -nu -p -2 2>/dev/null
     else
     echo "Nombre d'arguments incorrect.
     Utilisation: ./demobureau.sh -p split_thresh merge_thresh xmin ymin"
     cd ..
     exit 1
    fi
elif [[ $1 == "-o" ]]; then
    echo "Paramètres: split_thresh: 350, merge_thresh: 350, min: 1 1"
    ./split ../images/bureau.pgm bureausplit.inr -s 350 -min 1 1
    xvis bureausplit.inr -nu -p -2 2>/dev/null &
    ./merge ../images/bureau.pgm bureaumerge.inr -s 350 -mt 350 -min 1 1
     xvis bureaumerge.inr -nu -p -2 2>/dev/null

 elif [[ $1 == "-m" ]]; then
     echo "Test 1: split_thresh trop haut"
     echo "Paramètres: split_thresh: 4000, merge_thresh: 350, min: 1 1"
     echo "Observation: Lorsque le seuil de découpage est trop haut, les régions
     seront trop grandes"
     echo "Fermez la fenêtre xvis pour afficher le test suivant"
     echo "---------Execution-------"
    ./split ../images/bureau.pgm bureausplit.inr -s 4000 -min 1 1
    ./merge ../images/bureau.pgm bureaumerge.inr -s 4000 -mt 350 -min 1 1
    xvis bureausplit.inr -nu -p -2 2>/dev/null &
    xvis bureaumerge.inr -nu -p -2 2>/dev/null
    wait
     echo "-------------------------------------------------------------"
     echo "Test 2: merge_thresh trop haut"
     echo "Paramètres: split_thresh: 350, merge_thresh: 4000, min: 1 1"
     echo "Observation: Lorsque le seuil de fusion est trop haut, les régions fusionneront trop, ce qui donnera une image
     illisible"
     echo "Fermez la fenêtre xvis pour afficher le test suivant"
     echo "---------Execution-------"
    ./split ../images/bureau.pgm bureausplit.inr -s 200 -min 1 1
    ./merge ../images/bureau.pgm bureaumerge.inr -s 200 -mt 4000 -min 1 1

    xvis bureausplit.inr -nu -p -2 2>/dev/null &
    xvis bureaumerge.inr -nu -p -2 2>/dev/null
    wait
     echo "-------------------------------------------------------------"
     echo "Test 3: min trop haut "
     echo "Paramètres: split_thresh: 350, merge_thresh: 350, min: 6 6"
     echo "Lorsque les coordonnées fournies par min sont trop élevées, les pixels seront trop gros, et donc l'image obtenue ne
     sera pas intéressante"
     echo "Fermez la fenêtre xvis pour afficher le test suivant"
     echo "---------Execution-------"
    ./split ../images/bureau.pgm bureausplit.inr -s 350 -min 6 6
    ./merge ../images/bureau.pgm bureaumerge.inr -s 350 -mt 350 -min 6 6

    xvis bureausplit.inr -nu -p -2 2>/dev/null &
    xvis bureaumerge.inr -nu -p -2 2>/dev/null
    wait
    echo "---------------------------------------------------------------"
    echo "AUTRES OBSERVATIONS:
    Plus les paramètres de min sont petits, plus l'image est nette (on aura plus de pixels).
    Faire baisser split_thresh et merge_thresh ne dégrade pas le résultat.
     Pour avoir un split_thresh optimal, il faut que chaque région ait une variance assez petite. Ici, le seuil optimal a été trouvé après analyse de différentes valeurs"
    echo "--------------------------------------------------------------"
    echo "Utilisation optimale"
    echo "Paramètres: split_thresh: 350, merge_thresh:350, min: 1 1"
     echo "---------Execution-------"
    ./split ../images/bureau.pgm bureausplit.inr -s 350 -min 1 1
    ./merge ../images/bureau.pgm bureaumerge.inr -s 350 -mt 350 -min 1 1

    xvis bureausplit.inr -nu -p -2 2>/dev/null &
    xvis bureaumerge.inr -nu -p -2 2>/dev/null

else
   echo "Utilisation: ./demobureau.sh [-p|-m|-o] [split_thresh merge_thresh xmin ymin : a fournir si -p utilisé]"
   cd ../
   exit 1

fi
make clean
 cd ..
 exit 0
