#!/bin/bash

# First argument: ntuple analysis name
# Second argument: proton anlaysis name
# Third argument: analysis workspace

for filelist in TOTEM20 TOTEM21 TOTEM22 TOTEM23 TOTEM40 TOTEM41 TOTEM42 TOTEM43; do 
	# Unfortunately, this cannot be run in parallel due to temporary memory files.
	#parallel --ungroup ./run.sh $3/$1/ntuplized/{} $3/$2/intermediate_prot/{} $3/$1/combined_indiv/{} :::: "$filelist.txt"
	while IFS= read -r line; do
	./run.sh $3/$1/ntuplized/$line $3/$2/intermediate_prot/$line $3/$1/combined_indiv/$line
done < "$filelist.txt"
done
