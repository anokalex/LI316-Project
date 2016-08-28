#! /bin/sh

if [ $# -eq 1 ]; then
    detc -sob $1 |mh -n 0.2|aff|cco -f |xvis &
elif [ $# -eq 2 ]; then
    detc -sob $1 |mh -n 0.2|aff|cco -f >$2
else
    echo "Utilisation: ./contours.sh imgin [imgout]\n"
    exit 1
fi

exit 0
