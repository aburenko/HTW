#!/bin/bash
cut -d " " -f 3- bibel.txt | grep -o "\<[[:upper:]][[:alpha:]]*\>" | wc -l 
