#!/bin/bash

#for arg in TOTEM20 TOTEM22 TOTEM23 TOTEM40 TOTEM41 TOTEM42 TOTEM43 TOTEM21; do
	#./run.sh /home/younes/totemdata/v1.2/"$arg".root /home/younes/totemdata/improved_protons_v1/"$arg".root  /home/younes/totemdata/combined/"$arg".root
#done


for arg in TOTEM21; do
	./run.sh /home/younes/totemdata/v1.2/"$arg".root /home/younes/totemdata/improved_protons_v1/"$arg".root  /home/younes/totemdata/combined/"$arg".root
done

