#!/bin/bash

# Check if the user provided a run number as an argument
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <runnum>"
  exit 1
fi

# Assign the input argument to runnum
runnum=$1

# Hard-coded filepath and name for runfile
runloc="/volatile/hallc/c-lad/ehingerl/ROOTfiles/CALIB/"
# Find the most recent file in the directory that contains the run number in its name
runfile=$(ls -t ${runloc}*${runnum}* 2>/dev/null | head -n 1)

# Check if a matching file was found
if [ -z "$runfile" ]; then
  echo "Error: No file found in $runloc containing run number $runnum"
  exit 1
fi

# Ask the user whether to run hms, shms, or both
echo "Do you want to run 'hms', 'shms', or 'both'? (Enter hms/shms/both)"
read -r choice

# Execute the appropriate commands based on the user's choice
case $choice in
  hms)
    hcana -q "hms/plotOptics.C(\"$runfile\", $runnum)"
    ;;
  shms)
    hcana -q "shms/plotOptics.C(\"$runfile\", $runnum)"
    ;;
  both)
    hcana -q "hms/plotOptics.C(\"$runfile\", $runnum)"
    hcana -q "shms/plotOptics.C(\"$runfile\", $runnum)"
    ;;
  *)
    echo "Invalid choice. Please enter 'hms', 'shms', or 'both'."
    exit 1
    ;;
esac