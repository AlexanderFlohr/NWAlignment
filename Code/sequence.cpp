//
// Created by Alexander Flohr on 12.03.21.
//

#include "sequence.h"

#include <utility>

using namespace std;

// default constructor
Sequence::Sequence() {
    title_ = "";
    sequence_.clear();
}

// explicit constructor
Sequence::Sequence(string title, string sequence) {
    title_ = std::move(title);
    // conversion from char to Nucleotide::Base might lead to exceptions

    // reserve the required space for the sequence.
    // Runtime advantage for long sequences
    sequence_.reserve(sequence.size());
    for (char i : sequence) {
        sequence_.push_back(Nucleotide::toBase(i));
    }
}


// getter, does not allow modifications on the original object
string Sequence::get_title() const {
    return title_;
}

// Overwrite standard vector and string operations
// to allow easy access

size_t Sequence::size() const {
    return sequence_.size();
}

void Sequence::resize(size_t i) {
    sequence_.reserve(i);
}

void Sequence::reserve(size_t i) {
    sequence_.reserve(i);
}

void Sequence::push_back(Nucleotide::Base b) {
    sequence_.push_back(b);
}

void Sequence::clear() {
    sequence_.clear();
}

// Overwrite some of the standard operators to allow easy access

Nucleotide::Base &Sequence::operator[](size_t i) {
    return sequence_[i];
}

Nucleotide::Base Sequence::operator[](size_t i) const {
    return sequence_[i];
}

bool Sequence::operator==(const Sequence &seq) const {
    // equal sequences must have the same size
    if (sequence_.size() != seq.size()) {
        return false;
    } else {
        // check each Nucleotide::Base step by step
        for (unsigned i = 0; i < sequence_.size(); ++i) {
            if (sequence_[i] != seq[i]) {
                return false;
            }
        }
    }
    return true;
}

// analogue to operator==
bool Sequence::operator!=(const Sequence &seq) const {
    if (sequence_.size() != seq.size()) {
        return true;
    } else {
        for (unsigned i = 0; i < sequence_.size(); ++i) {
            if (sequence_[i] != seq[i]) {
                return true;
            }
        }
    }
    return false;
}

// write content of Sequence-object to stream
ostream &operator<<(ostream &out, const Sequence &seq) {
    // ensure fasta style
    out << '>' << seq.get_title() << endl;
    for (unsigned i = 0; i < seq.size(); ++i) {
        out << Nucleotide::toChar(seq[i]);
    }
    out << endl;
    return out;
}

vector<size_t> Sequence::occurrence() {
    vector<size_t> dist(4, 0);
    for (auto &i : sequence_) {
        switch (i) {
            case Nucleotide::Base::A :
                ++dist[0];
                break;
            case Nucleotide::Base::C :
                ++dist[1];
                break;
            case Nucleotide::Base::G :
                ++dist[2];
                break;
            case Nucleotide::Base::T :
                ++dist[3];
                break;
        }
    }
    return dist;
}

bool Sequence::is_palindrome() {
    for (unsigned i = 0; i < sequence_.size(); ++i) {
        if (sequence_[i] != sequence_[sequence_.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}
