#! /bin/bash

cd codes/

if [[ $1 == "-o" ]]; then
    Kappa=0.1
    Sigma=2
    Seuil=0.05
    echo "Paramètres optimaux: Kappa=$Kappa, Sigma=$Sigma, Seuil=$Seuil"
    ./plotslocseuil.sh "../images/cameraman.inr.gz" $Kappa $Sigma $Seuil
    echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

elif [[ $1 == "-m" ]]; then
    echo "Test 1: Paramètre Kappa trop bas"
    echo "Paramètres : Kappa=0.002, Sigma=2, Seuil=0.05"
    echo "OBSERVATION: Le programme se comporte comme un détecteur de contours"
        ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.002 2 0.05 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

echo "Fermez la fenêtre xvis pour obtenir le test suivant"

    echo "--------------------------------------------------------"
    echo "Test 2: Paramètre Kappa trop haut"
    echo "Paramètres : Kappa=0.25, Sigma=2, Seuil=0.05"
    echo "OBSERVATION: Kappa est trop grand, rien n'est détecté"
  ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.25 2 0.05 2>/dev/null
     echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
  echo "--------------------------------------------------------"
    echo "Test 3: Paramètre Sigma trop bas"
    echo "Paramètres : Kappa=0.1, Sigma=0.5, Seuil=0.05"
    echo "OBSERVATION: Il y a beaucoup de hautes fréquences détectées"
  ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.1 0.5 0.05 2>/dev/null
     echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
  echo "--------------------------------------------------------"
  echo "Test 4: Paramètre Sigma trop haut"
    echo "Paramètres : Kappa=0.1, Sigma=4, Seuil=0.05"
    echo "OBSERVATION: Plus Sigma est grand, plus les hautes fréquences sont supprimées"
  ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.1 4 0.05 2>/dev/null
    echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
  echo "--------------------------------------------------------"
    echo "Test 5: Paramètre Seuil trop bas"
    echo "Paramètres : Kappa=0.1, Sigma=2, Seuil=0.005"
    echo "OBSERVATION: Des maxima locaux qui ne sont pas des coins apparaissent"
  ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.1 2 0.005 2>/dev/null
    echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
  echo "--------------------------------------------------------"
    echo "Test 6: Paramètre Seuil trop haut"
    echo "Paramètres : Kappa=0.1, Sigma=2, Seuil=0.5"
    echo "OBSERVATION: Si on met un seuil trop haut, la détection de coins sera trop stricte"
  ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.1 2 0.5 2>/dev/null
    echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

    echo "Fermez la fenêtre xvis pour obtenir le test suivant"
  echo "--------------------------------------------------------"
    echo "Utilisation optimale"
    echo "Paramètres optimaux: Kappa=0.1, Sigma=2, Seuil=0.05"
    echo "OBSERVATION: la détection de Harris est bonne"
    ./plotslocseuil.sh "../images/cameraman.inr.gz" 0.1 2 0.05 2>/dev/null
   echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
    ./filter cameraman 2>/dev/null

elif [[ $1 == "-p" ]]; then
    if [[ $# -eq 4 ]]; then
        echo "Paramètres: Kappa=$2, Sigma=$3, Seuil=$4"
      ./plotslocseuil.sh "../images/cameraman.inr.gz" $2 $3 $4 2>/dev/null
         echo "Comparaison avec l'application du filtre de l'Exercice 7 suivie d'un seuillage"
        ./filter cameraman 2>/dev/null
  else
        echo "Nombre de paramètres incorrect. Tapez ./democamera.sh --help pour plus d'informations"
        cd ..
        exit 1
    fi
else
    echo "Utilisation: ./democamera.sh [-o (params optimaux) | -m (params nn optimaux) | -p (params fournis) ] [ [Kappa] [Sigma] [Seuil] a fournir lorsque -p utilisé]"
    cd ..
    exit 1
fi
make clean
cd ..
exit 0
