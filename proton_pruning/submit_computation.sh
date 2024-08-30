#!/bin/bash

# First argument: name of the analysis
# Second argument: ntuple workspace directory
# Third argument: proton workspace directory

workingdir="$pwd"

#for filename in TOTEM20 TOTEM21 TOTEM22 TOTEM23 TOTEM40 TOTEM41 TOTEM42 TOTEM43; do
	#condor_submit process.sub --append "filelist=$filename" --append "ntanalysisname=$1" --append "pranalysisname=$2" --append "workspace=$3" --append "wdir=$workingdir"
#done

for filename in TestFiles.txt; do
	condor_submit process.sub --append "filelist=$filename" --append "ntanalysisname=$1" --append "pranalysisname=$2" --append "workspace=$3" --append "wdir=$workingdir"
done
