#!/bin/bash

NAME[0]="Zara"
NAME[1]="Qadir"
NAME[2]="Mahnaz"
NAME[3]="Ayan"
NAME[4]="Daisy"
echo "First Index: ${NAME[0]}"
echo "Second Index: ${NAME[1]}"

for a in NAME
do
	if test a="Ayan"
	then
		echo "Ayan gefunden" 
	fi
done

exit 0
