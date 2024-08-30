#!/bin/bash

# Second argument: ntuple analysis name
# Third argument: proton analysis name
# Third argument: workspace directory


#for filename in TOTEM20 TOTEM21 TOTEM22 TOTEM23 TOTEM40 TOTEM41 TOTEM42 TOTEM43; do
	#condor_submit process.sub --append "filelist=$filename" --append "ntanalysisname=$1" --append "pranalysisname=$2" --append "workspace=$3" --append "wdir=$workingdir"
#done

./make_src_lists.sh

#workingdir="$(pwd)"

for filename in TOTEM20 TOTEM21 TOTEM22 TOTEM23 TOTEM40 TOTEM41 TOTEM42 TOTEM43; do
#for filename in TOTEM43; do
	condor_submit -append "filelist=$filename.txt" -append "ntanalysisname=$1" -append "pranalysisname=$2" -append "workspace=$3" process.sub 
done
