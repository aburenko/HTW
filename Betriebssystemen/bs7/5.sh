#!/bin/bash

wget -P $1 -r --no-glob -nd -e robots=off -A bs1-prak??.pdf https://www2.htw-dresden.de/~robge/bs1/prak
#wget -r --no-glob -nd -e robots=off -A bs1-prak??.pdf  https://www2.htw-dresden.de/~robge/bs1/prak
