#!/bin/bash
echo "To count your files in directory X ==>"
read -p "Write your directory: " dirc
echo $dirc
cd
ls -l $dirc | wc
for (( i=1; i<=5; i++ ))
do  
   echo $i
done
