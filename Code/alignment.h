//
// Created by Alexander on 12.03.21.
//

#ifndef ALIGNMENT_ALIGNMENT_H
#define ALIGNMENT_ALIGNMENT_H

#include "sequence.h"
#include "matrix.h"

class Alignment {
public:
    enum Trace{
        TOP,
        DIAGONAL,
        LEFT,
        END
    };
    /**
     * Explicit constructor
     */
    Alignment();

    /**
     * Explicit constructor
     */
    Alignment(Sequence *s1, Sequence *s2);


    void set_sequence(Sequence *s, bool first);

    /**
     * Align the two sequences by either the Needleman Wunsch or Smith-Waterman algorithm
     * @param mode
     */
    void align();

    /**
     * Access the created alignment
     * @return vector<string> two sequences in alignment format
     */
    std::vector<std::string> get_alignment() const;

    /**
     * Store the alignment in the given output file
     * @param filename
     */
    void store(std::string filename);

    /**
     * Out-stream definition of the sequence (FASTA-style)
     * @param std:ostream
     * @param const Sequence
     * @return
     */
    friend std::ostream &operator<<(std::ostream &out, const Alignment &align);

    /**
     * Access the name of the first sequence
     * @return std::string
     */

    /**
     * Access the name of the first or second sequence
     * @param first
     * @return
     */
    std::string get_title(bool first) const;


private:
    /**
     * Init the first row and column according to the Needleman-Wunsch algorith
     */
    void init_mtrx();

    /**
     * Fill the matrix according to the Needleman-Wunsch algorithm
     */
    void fill_mtrx();

    /**
     * Perform the backtracking and alignment generation
     */
    void backtracking();

    // both sequences (seq1 represents rows, seq2 the columns (in the alignment matrix))
    Sequence* seq1_;
    unsigned int nrow_;
    Sequence* seq2_;
    unsigned int ncol_;

    // matrix of type int is sufficient for our scoring system, i.e. might be adjusted in case
    // of a changed internal scoring system
    Matrix<int> mtrx_;
    Matrix<Trace> track_;

    // final alignments as string representation
    std::string alignment1_;
    std::string alignment2_;
};


#endif //ALIGNMENT_ALIGNMENT_H
