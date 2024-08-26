#!/bin/bash
cd /afs/cern.ch/user/y/yelberke/scratch1/proton_pruning

echo $1

mkdir -p /eos/user/y/yelberke/intermediate_prot_reduced_loose/$(dirname "$1")

build/proton_pruning /eos/user/y/yelberke/TOTEM_2018_ADDEDVARS_OUT/loosecuts/$(echo "$1" | cut -d '/' -f1).root /eos/user/y/yelberke/intermediate_prot/$1 /eos/user/y/yelberke/intermediate_prot_reduced_loose/$1
