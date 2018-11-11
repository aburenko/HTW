#!/bin/bash

if [ "$2" == "/" -a "$3" -eq 0 ] 
then
  echo Division by 0, cant be executed \;\)
  exit 1
fi

case $2 in 
	"+") ;;
	"-") ;;
	"/") ;;
	"*") ;;
	*) 
		echo "Kein gültiger Oparand"
		exit 1
esac

let wert="$1$2$3" 
echo $wert
