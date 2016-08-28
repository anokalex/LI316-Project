#! /bin/bash

if [[ -f harris && -f sloc ]];then
    bool=0
else
    bool=1
fi
if [[ $bool -eq 1 ]];then
    make harris
    make sloc
fi

if [[ $# -eq 4 ]];then
name=`echo $1|cut -d "/" -f 3|cut -d "." -f 1`
./harris $1 "toto.inr" -K $2 -s $3
./sloc "toto.inr" "toto2.inr" -n $4 > tempo$name

xvis $1 -xsh tempo$name -nu -p -2
rm "toto.inr"
rm "toto2.inr"

else
    echo "Utilisation: ./plotslocseuil.sh ../images/imgin [Kappa] [Sigma] [Seuil]"

fi

make clean
exit 0
