//
// Created by Alexander Flohr on 12.03.2021.
//

#ifndef ALIGNMENT__READER_H
#define ALIGNMENT__READER_H

#include "../sequence.h"

using Sample = std::vector<Sequence>;

class Reader {
public:
    /**
     * Default constructor
     */
    Reader();

    /**
     * Read FASTA files (ending with .fasta or .fa).
     * Report and ignore sequences if they are not DNA or RNA
     * Use sample reference to store the results
     * @param string filename
     * @param Sample& sample
     * @throws exception if the file is inaccessible or no FASTA file
     */
    void read(std::string filename, Sample &sample);
};


#endif //ALIGNMENT__READER_H
