#!/bin/bash

# Argument 1: workspace name
# Argument 2: analysis name

srce="$1/$2/grafted"
tgt="$1/$2/final"
mkdir -p $tgt

#hadd -f -j 10 $tgt $srce/*/*

parallel --ungroup hadd -f -j 10 $tgt/{}.root $srce/{}/*/* ::: TOTEM20 TOTEM21 TOTEM22 TOTEM23 TOTEM24 TOTEM40 TOTEM41 TOTEM42 TOTEM43
