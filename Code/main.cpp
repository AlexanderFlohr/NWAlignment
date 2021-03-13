#include <iostream>
#include "cstring"
#include "sequence.h"
#include "FASTA/reader.h"
#include "alignment.h"

using namespace std;

// global variables that store the user input
string input;
string output;
bool help = false;

/**
 * Provide some usage-information, i.e. show the help message
 */
void show_help() {
    cout << "This tool is intended to create pairwise sequence alignments." << endl;
    cout << "using the Needleman-Wunsch  algorithm." << endl << endl;
    cout << "Usage:" << endl;
    cout << " -i or --input  [string]\t\tDefine the path to a FASTA file with two or more sequences" << endl;
    cout << "                        \t\tNote: only the first two are considered for alignment." << endl;
    cout << " -o or --output [string]\t\tdefine the name of the output alignment file" << endl;
    cout << " -h or --help           \t\tShow this help-message" << endl;
    cout << " Note:" << endl;
    cout << "  1. There is no protection against overwriting existing files" << endl;
    cout << "  2. Input FASTA files must end with .fa or .fasta" << endl << endl;
}

/**
 * Read in the arguments passed by the user. Redefines the global user input variables.
 * @param argc The number of input arguments
 * @param argv The actual arguments
 */
void read_args(int argc, char **argv) {
    // assume either fully defined input and output arguments or the demand for help
    if (argc == 5 || argc == 2) {
        for (int i = 1; i < argc; ++i) {

            // check for input information, increment i if possible
            if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                if (i + 1 < argc) {
                    ++i;
                    input = argv[i];
                    continue;
                } else {
                    cout << "No input file defined, see --help" << endl;
                    exit(0);
                }

                // check for output information, increment i if possible
            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if (i + 1 < argc) {
                    ++i;
                    output = argv[i];
                    continue;
                } else {
                    cout << "No output file defined, see --help" << endl;
                    exit(0);
                }

                //  check if help is demanded
            } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                help = true;
                continue;

                // only reached if parameters are wrongly ordered or mis-spelled
            } else {
                cout << "Unknown argument \"" << argv[i] << "\", see --help" << endl;
                exit(-1);
            }
        }
    } else {
        cout << "Invalid number of arguments given, see --help" << endl;
        exit(0);
    }
}

/**
 * Main, functional process pipeline control
 * @param argc Number of input arguments
 * @param argv The actual input arguments
 * @return exit status
 */
int main(int argc, char **argv) {
    // read in user arguments
    read_args(argc, argv);
    if (help) {
        show_help();
        // demand for help is considered as stand-alone argument
        exit(0);
    }

    // report user arguments to ensure the reading process was successful
    cout << "Input parameters:" << endl;
    cout << " Input file:\t\t" << input << endl;
    cout << " Output file:\t\t" << output << endl;

    // read in the input sequences
    Reader reader = Reader();
    vector<Sequence> sequences;

    // read in the given FASTA sequences
    try {
        reader.read(input, sequences);
    } catch (...) {
        cout << "Could not read the input file" << endl;
        exit(0);
    }

    // consider only the first two sequences for alignment
    if (sequences.size() >= 2) {
        // create an alignment based on the information of the first two sequences
        Alignment model = Alignment(&sequences[0], &sequences[1]);
        model.align();
        model.store(output);
    } else {
        cout << "Too few input sequences, see --help" << endl;
        exit(0);
    }

    cout << "Alignment created successfully" << endl;
    return 0;
}
