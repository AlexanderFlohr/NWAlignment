//
// Created by Alexander Flohr on 12.03.21.
//

#include "nucleotide.h"

Nucleotide::Base Nucleotide::toBase(char c) {
    // Convert the character into an integer to simplify
    // capturing non-capital characters
    unsigned int ascii = (int) c;
    if (ascii >= 97 && ascii <= 122) {
        ascii -= 32;
    }

    // translate the resulting ascii code into valid DNA bases if possible
    switch (ascii) {
        case 65:
            return Nucleotide::Base::A;
        case 67:
            return Nucleotide::Base::C;
        case 71:
            return Nucleotide::Base::G;
        case 84: // NOLINT(bugprone-branch-clone)
            return Nucleotide::Base::T;
        case 85:
            return Nucleotide::Base::T;
        default:
            throw "Invalid DNA/RNA base";
    }
}

char Nucleotide::toChar(Nucleotide::Base b) {
    switch (b) {
        case Nucleotide::A:
            return 'A';
        case Nucleotide::C:
            return 'C';
        case Nucleotide::G:
            return 'G';
        case Nucleotide::T:
            return 'T';
        // other cases should never be reached
    }
}