//
// Created by s9alfloh on 11.11.17.
//

#ifndef ALIGNMENT_WRITER_H
#define ALIGNMENT_WRITER_H

#include "../sequence.h"

class FASTAWriter {
public:
    /**
     * Default constructor
     */
    FASTAWriter();

    /**
     * Write a set of Sequence-objects into a fasta file
     * @param string filename
     * @param vector<Sequence>& sample
     */
    void write(std::string filename, std::vector<Sequence> &sample);
};


#endif //ALIGNMENT_WRITER_H
