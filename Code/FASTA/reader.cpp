//
// Created by Alexander Flohr on 12.03.21.
//

#include <iostream>
#include <fstream>
#include "reader.h"

using namespace std;

// Default constructor
Reader::Reader() {
    return;
}

// read in fasta files
void Reader::read(string filename, Sample &sample) {
    // check file format
    if (filename.substr(filename.size() - 7) == ".fasta"
        || filename.substr(filename.size() - 4) == ".fa") {
        cerr << "ReadingError: Invalid input format" << endl;
        throw "Invalid input format";
    }

    // try to open the file, otherwise throw an exception
    ifstream stream(filename);
    if (stream.is_open()) {
        // store current line in one of these placeholders
        string title = "";
        string sequence = "";
        string curr = "";
        string error_report = "";

        // count lines (see specification of task 6)
        int lines = 0;
        int sequences = 0;

        // read fasta file line by line
        while (getline(stream, curr)) {
            ++lines;
            // check if there is an empty line between the different sequences
            if (!curr.empty()) {
                // if not check for sequence-header
                if (curr[0] == '>') {
                    ++sequences;
                    // for each sequence, the sequence-header is initially empty
                    // if we find a new sequence-header but already have one, we
                    // first have to store this previous sequence
                    if (title != "") {
                        try {
                            // Sequence initialization might throw an exception when
                            // the sequence contains unknown characters, so catch and
                            // report (see specification of task 6)
                            sample.push_back(Sequence(title, sequence));
                        } catch (...) {
                            error_report += "Invalid sequence:\t" + title + "\n";
                        }
                        // reset local variables for the new sequence
                        title = "";
                        sequence = "";
                    }
                    // store the current sequence-header (without '>')
                    title = curr.substr(1);
                } else {
                    // if a non empty line does not start with '>' we interpret this
                    // as sequence (if not, the sequence initialization throws an error
                    // (see above)
                    sequence += curr;
                }
            }
        }

        // store the last sequence afterwards, needed if the file does not end on newline
        if (title != "") {
            try {
                sample.push_back(Sequence(title, sequence));
            } catch (...) {
                cerr << title << endl;
            }
        }
        stream.close();

        // report (see task specification)
        // without invalid samples!
        cout << endl << "Reader report:" << endl;
        cout << "Lines:\t\t\t" << lines << endl;
        cout << "Sequences:\t\t" << sequences << endl;
        cout << error_report << endl;
    } else {
        cerr << "ReadingError: Could not FASTA open file" << endl;
        throw "Could not open file";
    }
}
