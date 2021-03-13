//
// Created by Alexander Flohr on 12.03.21.
//

#ifndef ALIGNMENT_SEQUENCE_H
#define ALIGNMENT_SEQUENCE_H

#include <iostream>
#include <vector>
#include "nucleotide.h"

// Increase readability by type renaming
using Seq = std::vector<Nucleotide::Base>;

/**
 * DNA/RNA sequence object, implemented to maintain information of FASTA files
 */
class Sequence {
public:
    /**
     * Default constructor
     */
    Sequence();

    /**
     * Explicit constructor
     * @param string title
     * @param string sequence
     * @throws BaseException if a given base is not known
     */
    Sequence(std::string title, std::string sequence);

    /**
     * Getter for title
     * @return std::string
     */
    std::string get_title() const;

    /**
     * Returns the number of DNA/RNA-bases in the sequence
     * @return size_t
     */
    size_t size() const;

    // definition of functions to make it usable like strings or vectors

    /**
     * Resize the sequence
     * @param size_t i
     */
    void resize(size_t i);

    /**
     * Reserve some space for the sequence, allows a faster initialization
     * @param size_t i
     */
    void reserve(size_t i);

    /**
     * Add one DNA base to the sequence
     * @param Nucleotide::Base b
     */
    void push_back(Nucleotide::Base b);

    /**
     * Clear sequence, i.e. removes title and sequence
     */
    void clear();

    // Overwrite operators to allow a fast and easy access / usage
    /**
     * Returns true if two sequences are equal
     * @return bool
     */
    bool operator==(const Sequence &seq) const;

    /**
     * Returns true if two sequences are unequal
     * @return bool
     */
    bool operator!=(const Sequence &seq) const;

    /**
     * Get access to the DNA-base at position i
     * @param size_t i
     * @return Nucleotide::Base
     */
    Nucleotide::Base &operator[](size_t i);

    /**
     * Get access to the DNA-base at position i
     * @param size_t i
     * @return Nucleotide::Base
     */
    Nucleotide::Base operator[](size_t i) const;

    /**
     * Out-stream definition of the sequence (FASTA-style)
     * @param std:ostream
     * @param const Sequence
     * @return
     */
    friend std::ostream &operator<<(std::ostream &out, const Sequence &seq);


    /**
     * Returns the occurrence-count of A, C, G, T in the sequence as vector (A, C, G, T).
     * Represented with absolute numbers.
     * @return vector<size_T>
     */
    std::vector<size_t> occurrence();

    /**
     * Check if a given sequence is a palindrome, i.e. reading it backwards results
     * in the same sequence
     * @return bool
     */
    bool is_palindrome();

private:
    // local variables that encode the name and base-vector of the sequence
    std::string title_;
    Seq sequence_;
};


#endif //ALIGNMENT_SEQUENCE_H
