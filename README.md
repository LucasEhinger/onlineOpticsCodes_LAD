# onlineOpticsCodes
There's codes for H(e,e'p) and carbon sieve running. 
In the heep folder:
-plot coincidence quantities. inputs are the replayed root file and a SIMC file to overlay and compare the distributions. you will need to change the names and paths of the files as well as any cuts. output is a pdf and root file.
-plot single arm H(e,e'p) quantities. similar to the coin, you will need to change the paths and files. outputs a pdf and root file. 
In the sieve folder:
-there's plotOptics for each the HMS and SHMS folders. you need to change the input file name and path, cuts, and may need to change the cut on the central hole if you are interested to study it. this outputs a pdf and root file. 

Generally, I open the root files and integrate the counts to get a quick rate estimation when data is coming in. To prepare for the data, generate the files in SIMC that you need for the overlays. For sieve data, you generally want at least 200 events per hole per foil. If you are running multiple foils, then you will need to change the TCut in the sieve code to select which foil you are looking at to get counts. This is a quick and generic way to sanity check.  
