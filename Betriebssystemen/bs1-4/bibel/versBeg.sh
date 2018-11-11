#!/bin/bash
cut -d " " -f 3- bibel.txt | grep -o "^\<[[:alpha:]]* [[:alpha:]]*\>"  | sort | uniq | wc 
