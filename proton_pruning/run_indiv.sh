#!/bin/bash

# First argument: ntuples to match (prune) protons to
# Second argument: Protons to prune
# Third argument: Target directory
# Fourth argument: working directory

#cd /afs/cern.ch/user/y/yelberke/scratch1/proton_pruning
cd $4

echo $1

#mkdir -p /eos/user/y/yelberke/intermediate_prot_reduced/$(dirname "$1")
mkdir -p $(dirname "$3")

./build/proton_pruning $1 $2 $3
