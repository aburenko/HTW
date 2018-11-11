#!/bin/sh
echo "Schlange:"
grep "Schlange" bibel.txt | wc
echo "Lo'we":
grep "Löwe" bibel.txt | wc
echo "Maus":
grep "Maus" bibel.txt | wc

