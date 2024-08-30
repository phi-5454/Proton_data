#!/bin/bash

# First argument: ntuples to match protons to 
# Second argument: protons
# Third argument: target
# Fourth argument: working directory

ls -a

mkdir -p $(dirname "$3")

./combine_ntuple_proton $1 $2 $3
