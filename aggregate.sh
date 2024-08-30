#!/bin/bash

# Argument 1: analysis name
# Argument 2: workspace directory

srce="$2/$1/combined_indiv"
tgt="$2/$1/final"
mkdir -p $tgt

#hadd -f -j 10 $tgt $srce/*/*

parallel --ungroup hadd -f -j 10 $tgt/{}.root $srce/{}/*/* ::: TOTEM20 TOTEM21 TOTEM22 TOTEM23 TOTEM24 TOTEM40 TOTEM41 TOTEM42 TOTEM43
