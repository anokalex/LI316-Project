#! /bin/bash

cd codes/
make clean
make
if [[ $1 == "-p" ]]; then
    if [[ $# -eq 5 ]]; then
        echo "Paramètres : split_thresh: $2, merge_thresh: $3, min: $4 $5"
    ./split ../images/seiche.pgm seichesplit.inr -s $2 -min $4 $5
    xvis seichesplit.inr -nu -p -2 2>/dev/null &
    ./merge ../images/seiche.pgm seichemerge.inr -s $2 -mt $3 -min $4 $5
     xvis seichemerge.inr -nu -p -2 2>/dev/null
     else
     echo "Nombre d'arguments incorrect.
     Utilisation: ./demoseiche.sh -p split_thresh merge_thresh xmin ymin"
     cd ..
     exit 1
    fi
elif [[ $1 == "-o" ]]; then
    echo "Paramètres: split_thresh: 100, merge_thresh: 100, min: 2 2"
    ./split ../images/seiche.pgm seichesplit.inr -s 100 -min 2 2
    xvis seichesplit.inr -nu -p -2 2>/dev/null &
    ./merge ../images/seiche.pgm seichemerge.inr -s 100 -mt 100 -min 2 2
     xvis seichemerge.inr -nu -p -2 2>/dev/null

 elif [[ $1 == "-m" ]]; then
     echo "Test 1: split_thresh trop haut"
     echo "Paramètres: split_thresh: 300, merge_thresh: 100, min: 2 2"
     echo "Observation: Lorsque le seuil de découpage est trop haut, les régions
     seront trop grandes"
     echo "Fermez la fenêtre xvis pour afficher le test suivant"
     echo "---------Execution-------"
    ./split ../images/seiche.pgm seichesplit.inr -s 300
    ./merge ../images/seiche.pgm seichemerge.inr -s 300 -mt 100
    xvis seichesplit.inr -nu -p -2 2>/dev/null &
    xvis seichemerge.inr -nu -p -2 2>/dev/null
    wait
     echo "-------------------------------------------------------------"
     echo "Test 2: merge_thresh trop haut"
     echo "Paramètres: split_thresh: 200, merge_thresh: 400, min: 2 2"
     echo "Observation: Lorsque le seuil de fusion est trop haut, les régions fusionneront trop, ce qui donnera une image
     illisible"
     echo "Fermez la fenêtre xvis pour afficher le test suivant"
     echo "---------Execution-------"
    ./split ../images/seiche.pgm seichesplit.inr -s 200
    ./merge ../images/seiche.pgm seichemerge.inr -s 200 -mt 400

    xvis seichesplit.inr -nu -p -2 2>/dev/null &
    xvis seichemerge.inr -nu -p -2 2>/dev/null
    wait
     echo "-------------------------------------------------------------"
     echo "Test 3: min trop haut "
     echo "Paramètres: split_thresh: 100, merge_thresh: 100, min: 6 6"
     echo "Lorsque les coordonnées fournies par min sont trop élevées, les pixels seront trop gros, et donc l'image obtenue ne
     sera pas intéressante"
     echo "Fermez la fenêtre xvis pour afficher le test suivant"
     echo "---------Execution-------"
    ./split ../images/seiche.pgm seichesplit.inr -s 100 -min 6 6
    ./merge ../images/seiche.pgm seichemerge.inr -s 100 -mt 100 -min 6 6

    xvis seichesplit.inr -nu -p -2 2>/dev/null &
    xvis seichemerge.inr -nu -p -2 2>/dev/null
    wait
    echo "---------------------------------------------------------------"
    echo "AUTRES OBSERVATIONS:
    Plus les paramètres de min sont petits, plus l'image est nette (on aura plus de pixels).
    Faire baisser split_thresh et merge_thresh ne dégrade pas le résultat.
     Pour avoir un split_thresh optimal, il faut que chaque région ait une variance assez petite. Ici, le seuil optimal a été trouvé après analyse de différentes valeurs"
    echo "--------------------------------------------------------------"
    echo "Utilisation optimale"
    echo "Paramètres: split_thresh: 100, merge_thresh:100, min: 2 2"
     echo "---------Execution-------"
    ./split ../images/seiche.pgm seichesplit.inr -s 100 -min 2 2
    ./merge ../images/seiche.pgm seichemerge.inr -s 100 -mt 100 -min 2 2

    xvis seichesplit.inr -nu -p -2 2>/dev/null &
    xvis seichemerge.inr -nu -p -2 2>/dev/null

else
   echo "Utilisation: ./demoseiche.sh [-p|-m|-o] [split_thresh merge_thresh xmin ymin : a fournir si -p utilisé]"
   cd ../
   exit 1

fi
make clean
 cd ..
 exit 0
