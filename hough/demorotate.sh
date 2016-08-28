#! /bin/bash

cd codes/
if [[ $1 == "-p" ]];then
    if [[ $# -eq 4 ]];then
    Tolerance=$2
    dtheta=$3
    drho=$4
    echo "Paramètres fournis: Tolerance: $Tolerance, dtheta: $dtheta, drho: $drho"
    echo "Affichage de l'accumulateur et des droites détectées"
    ./accumulateur.sh ../images/rotate.inr.gz rot.cont rot.inr $Tolerance $dtheta $drho
    else
        echo "Nombre d'arguments incorrects.
        Utilisation: ./demorotate.sh -p tolerance dtheta drho"
        cd ../
        exit 1
    fi
elif [[ -z $1 ]]; then
    echo "Paramètres: Tolerance: 0.05, dtheta: 0.01, drho: 1"
    echo "Affichage de l'accumulateur et des droites détectées"
    ./accumulateur.sh ../images/rotate.inr.gz rot.cont rot.inr
elif [[ $1 == "--help" ]]; then
    echo "Utilisation: ./demorotate.sh [-p tolerance dtheta drho]"
    cd ../
    exit 1

fi
make clean
cd ../
exit 0
