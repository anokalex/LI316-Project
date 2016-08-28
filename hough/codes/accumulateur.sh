#! /bin/bash

make clean 2>/dev/null
make hough
make hough_c

if [[ $1 == "-p" ]]; then

if [[ -f $2 ]]; then

 name=`echo $2|cut -d '/' -f 3|cut -d '.' -f 1`

./contours.sh $2 $3

if [[ $name == "cerc" ]];then
if [[ $# -eq 8 ]]; then
./hough_c $3 $4 -t $5 -sx $6 -sy $7 -sr $8 > temp
else
    echo "Nb d'arguments incorrect.
        Utilisation: ./accumulateur.sh -p ../images/cerc.inr.gz cerc.cont cerc.inr Tolerance dx dy dr"
    exit 1
fi

elif [[ $name == "rotate" ]];then

./hough $3 $4 -t $5 -st $6 -sr $7 -n 8> temp

elif [[ $name == "fenetre" ]];then

./hough $3 $4 -t $5 -st $6 -sr $7 -n 15> temp
else

./hough $3 $4 -t $5 -st $6 -sr $7 > temp

fi

norma $4 |xvis -p -2 &
xvis $2 -xsh temp -p -2
rm -f hough.o hough_c.o $3

else
    echo "Image inconnue"
    exit 1
fi


elif [[ -f $1 ]]; then


./contours.sh $1 $2

name=`echo $1|cut -d '/' -f 3|cut -d '.' -f 1`
if [[ $name == "cerc" ]]; then
./hough_c $2 $3 > temp

elif [[ $name == "rotate" ]];then
./hough $2 $3 -n 8 >temp
elif [[ $name == "rotate" ]];then

./hough $2 $3 -n 15> temp
else
./hough $2 $3 >temp
fi
norma $3 |xvis -nu -p -2 &
xvis $1 -xsh temp -p -2

rm -f hough.o hough_c.o $2

else

echo "Utilisation: ./accumulateur.sh [-p] ../images/image image.cont imageres.inr [si -p est fourni [tolerance] [angle] [distance]]"
exit 1

fi

