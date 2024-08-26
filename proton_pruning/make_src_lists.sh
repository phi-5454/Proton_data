#!/bin/bash

# Function to create files for each subdirectory containing .root file list
create_subdir_files() {
    local hostname="$1"
    local base_directory="$2"
    
    # List all items in the base directory
    xrdfs "$hostname" ls "$base_directory" | while read -r item; do
        # Check if the item is a directory
        if xrdfs "$hostname" stat "$item" | grep -q 'IsDir'; then
            # Get the directory name (last part of the path)
            subdir_name=$(basename "$item")
            
            # Create a file with the directory name in the current directory
            local output_file="${subdir_name}.txt"
            : > "$output_file"
            
	    # List .root files recursively in the subdirectory and write to the file (filter out prefixes)
	    xrdfs "$hostname" ls -R "$item" | grep '.root$' |  awk -v prefix="$base_directory" '{sub(prefix, "", $0); print}' > "$output_file"

	    #xrdfs "$hostname" ls -R "$item" | grep '.root$' |  while read -r FILE; do
		    #echo "$FILE" | sed "s|^$base_directory||" >> "$output_file"
	    #done > "$output_file"

        fi
    done
}

# Parse arguments
hostname="root://eostotem/"
base_directory="/eos/totem/data/cmstotem/2018/90m/RECO_copy/"

# Call the function
create_subdir_files "$hostname" "$base_directory"
