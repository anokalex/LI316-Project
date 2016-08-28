#! /bin/bash

cd codes/
if [[ $1 == "-p" ]];then
    if [[ $# -eq 5 ]];then
    Tolerance=$2
    dx=$3
    dy=$4
    dr=$5
    echo "Paramètres fournis: Tolerance: $Tolerance, dx: $dx, dy: $dy, dr: $dr"
    echo "Affichage de l'accumulateur et des cercles détectés"
    echo "Temps d'éxecution: Environ 4 minutes"
    ./accumulateur.sh ../images/cerc.inr.gz cerc.cont cerc.inr $Tolerance $dx $dy $dr
    else
        echo "Nombre d'arguments incorrect.
        Utilisation: ./democircle.sh -p tolerance dx dy dr"
        cd ../
        exit 1
    fi
elif [[ -z $1 ]]; then
    echo "Paramètres: Tolerance: 0.05, dx: 1, dy: 1,dr: 0.5"
    echo "Affichage de l'accumulateur et des cercles détectés"
   echo "Temps d'éxecution: Environ 4 minutes"
    ./accumulateur.sh ../images/cerc.inr.gz cerc.cont cerc.inr
elif [[ $1 == "--help" ]]; then
    echo "Utilisation: ./democircle.sh [-p tolerance dx dy dr]"
    cd ../
    exit 1

fi

cd ../
exit 0
