#NWAlignment

This tool is designed to perform pairwise sequence alignments based on the [Needleman-Wunsch algorithm](https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm). The current program version uses a simple scoring system, where gaps and mismatches have a score of -1, matches are defined as +1.

###Requirements:
* [cmake](https://cmake.org/) >= Version 3.10
* C++20 standard

### Compile:
1. Navigate into the 'Code' directory  
`cd Code`
2. Create a folder called 'build'  
`mkdir build`
3. Navigate into the newly generated folder  
`cd build`
4. Compile the project using cmake  
`cmake ..`
5. Build the executables  
`make`
6. Run the program as shown below

###Usage:
Allowed parameters:

Short | Long     | Type   | Description
----- | -------- | ------ | ----------
-i    | --input  | string | Path to the input seuqnece file (FASTA format, ending: .fa or .fasta
-o    | --output | string | Path to the output file (any fileformat)
-h    | --help   | -      | Show some helping text and usage-information

Note:
* To perform an alignment, input and output files must be defines
* The help request is considered as single argument
* Example runs:  
  perform the alignment  
  `./nwalign -i ../../Data/input.fa -o ../../Data/output.align`  
  or demand help  
  `./nealign --help`


###Note:
* This tool comes without any warranty
* This tool is updated infrequently
* Have fun using it
