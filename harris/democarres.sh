#! /bin/bash

cd codes/

if [[ $1 == "-o" ]]; then
    Kappa=0.1
    Sigma=1
    Seuil=0.05
    echo "Paramètres optimaux: Kappa=$Kappa, Sigma=$Sigma, Seuil=$Seuil"
    ./plotslocseuil.sh "../images/carre16.pgm" $Kappa $Sigma $Seuil
    echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter carre16 2>/dev/null
elif [[ $1 == "-m" ]]; then
    echo "Test 1: Paramètre Kappa trop bas"
    echo "Paramètres : Kappa=0.000002, Sigma=1, Seuil=0.05"
    echo "OBSERVATION: Le programme se comporte comme un détecteur de contours.Ici, comme on a une image de coins, faire baisser Kappa n'influencera pas le résultat."
       ./plotslocseuil.sh "../images/carre16.pgm" 0.000002 1 0.05 2>/dev/null
     echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter carre16 2>/dev/null
 echo "Fermez la fenêtre xvis pour obtenir le test suivant"

    echo "--------------------------------------------------------"
    echo "Test 2: Paramètre Kappa trop haut"
    echo "Paramètres : Kappa=0.25, Sigma=1, Seuil=0.05"
    echo "OBSERVATION: Kappa est trop grand, rien n'est détecté"
  ./plotslocseuil.sh "../images/carre16.pgm" 0.25 1 0.05 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
   ./filter carre16 2>/dev/null

   echo "--------------------------------------------------------"
    echo "Test 3: Paramètre Sigma trop bas"
    echo "Paramètres : Kappa=0.1, Sigma=0.5, Seuil=0.05"
    echo "OBSERVATION: Il y a beaucoup de hautes fréquences détectées.Ici, cela entraîne la détection d'un point en trop sur chaque coin (entre la croix en haut à gauche et celle en bas à gauche)"
  ./plotslocseuil.sh "../images/carre16.pgm" 0.1 0.5 0.05 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
   ./filter carre16 2>/dev/null

   echo "--------------------------------------------------------"
  echo "Test 4: Paramètre Sigma trop haut"
    echo "Paramètres : Kappa=0.1, Sigma=4, Seuil=0.05"
    echo "OBSERVATION: Plus Sigma est grand, plus les hautes fréquences sont supprimées.Ici, on obtient une seule croix au lieu de 4."
  ./plotslocseuil.sh "../images/carre16.pgm" 0.1 4 0.05 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
   ./filter carre16 2>/dev/null

   echo "--------------------------------------------------------"
    echo "Test 5: Paramètre Seuil trop bas"
    echo "Paramètres : Kappa=0.1, Sigma=1, Seuil=0.000005"
    echo "OBSERVATION: Des maxima locaux qui ne sont pas des coins apparaissent (cas général). Ici, les maxima locaux sont forcément des coins, donc la diminution du seuil ne change rien à la détection."
  ./plotslocseuil.sh "../images/carre16.pgm" 0.1 1 0.000005 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
   ./filter carre16 2>/dev/null

   echo "--------------------------------------------------------"
    echo "Test 6: Paramètre Seuil trop haut"
    echo "Paramètres : Kappa=0.1, Sigma=1, Seuil=0.5"
    echo "OBSERVATION: Si on met un seuil trop haut, la détection de coins sera trop stricte. Ici, on a la même observation que pour le test précédent: l'augmentation du seuil n'influence pas le résultat (sauf si sa valeur dépasse celle des maxima locaux qui ont ici mêmes valeurs partout) "
  ./plotslocseuil.sh "../images/carre16.pgm" 0.1 1 0.5 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
   ./filter carre16 2>/dev/null

   echo "--------------------------------------------------------"
    echo "Utilisation optimale"
    echo "Paramètres optimaux: Kappa=0.1, Sigma=1, Seuil=0.05"
    echo "OBSERVATION: la détection de Harris est bonne"
    ./plotslocseuil.sh "../images/carre16.pgm" 0.1 1 0.05 2>/dev/null
     echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter carre16 2>/dev/null


elif [[ $1 == "-p" ]]; then
    if [[ $# -eq 4 ]]; then
        echo "Paramètres: Kappa=$2, Sigma=$3, Seuil=$4"
      ./plotslocseuil.sh "../images/carre16.pgm" $2 $3 $4 2>/dev/null
       echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter carre16 2>/dev/null

    else
        echo "Nombre de paramètres incorrect. Tapez ./democarres.sh --help pour plus d'informations"
        cd ..
        exit 1
    fi
else
    echo "Utilisation: ./democarres.sh [-o (params optimaux) | -m (params nn optimaux) | -p (params fournis) ] [ [Kappa] [Sigma] [Seuil] a fournir lorsque -p utilisé]"
    cd ..
    exit 1
fi
make clean
cd ..
exit 0
