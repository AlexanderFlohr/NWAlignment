//
// Created by Alexander Flohr on 12.03.21.
//

#ifndef ALIGNMENT__NUCLEOTIDE_H
#define ALIGNMENT__NUCLEOTIDE_H

class Nucleotide {
public:

    /**
     * Encodes the 4 common DNA bases
     */
    enum Base {
        A, // Adenine
        C, // Cytosine
        G, // Guanine
        T, // Thymine
    };

    /**
     * Convert a character into a DNA base object
     * RNA base Uracil is automatically translated into Thymine
     * @param char c
     * @return Base b
     */
    static Base toBase(char c);

    /**
     * Convert a DNA base object into a character
     * @param Base b
     * @return char b
     */
    static char toChar(Base b);
};


#endif //ALIGNMENT__NUCLEOTIDE_H
