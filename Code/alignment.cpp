//
// Created by s9alfloh on 12.03.21.
//

#include "alignment.h"
#include <iostream>
#include <fstream>

using namespace std;
Alignment::Alignment() {
    seq1_->clear();
    nrow_ = 0;
    seq2_->clear();
    ncol_ = 0;
    mtrx_ = Matrix<int>();
}

Alignment::Alignment(Sequence *s1, Sequence *s2){
    seq1_ = s1;
    nrow_ = seq1_->size() + 1;
    seq2_ = s2;
    ncol_ = seq2_->size() + 1;
    mtrx_ = Matrix<int>(nrow_, ncol_);
    track_ = Matrix<Trace>(nrow_, ncol_);
}

void Alignment::set_sequence(Sequence *s, bool first) {
    if (first){
        seq1_ = s;
    } else {
        seq2_ = s;
    }
    mtrx_ = Matrix<int>(seq1_->size() + 1, seq2_->size() + 1);
    track_ = Matrix<Trace>(seq1_->size() + 1, seq2_->size() + 1);
}

void Alignment::align() {
    init_mtrx();
    fill_mtrx();
    backtracking();
}

void Alignment::store(std::string filename) {
    ofstream outfile;
    outfile.open(filename);
    if (outfile.is_open()){
        outfile << *this;
        outfile.close();
        cout << "Final alignment was stored in \"" << filename << "\"" << endl;
    } else {
        cout << "Could not write output file" << endl;
        throw "Could not write file";
    }
}

std::vector<std::string> Alignment::get_alignment() const {
    vector<std::string> texts;
    texts.push_back(alignment1_);
    texts.push_back(alignment2_);
    return texts;
}

std::string Alignment::get_title(bool first) const {
    if (first){
        return (seq1_->get_title());
    } else {
        return (seq2_->get_title());
    }
}

// write content of Sequence-object to stream
ostream &operator<<(ostream &out, const Alignment &align) {
    std::string id1 = align.get_title(true);
    std::string id2 = align.get_title(false);

    while(id1.length() < id2.length()){
        id1 += " ";
    }
    while(id2.length() < id1.length()){
        id2 += " ";
    }

    // ensure fasta style
    out << id1 << "\t" << align.get_alignment()[0] << endl;
    out << id2 << "\t" << align.get_alignment()[1] << endl;
    return out;
}


void Alignment::init_mtrx() {
    // top left corner
    track_(0,0) = END;
    mtrx_(0,0) = 0;

    // first column
    for (int i = 1; i < nrow_; ++i) {
        mtrx_(i, 0) = mtrx_(i - 1, 0) - 1;
        track_(i, 0) = TOP;

    }

    // first row
    for (int i = 1; i < ncol_; ++i) {
        mtrx_(0, i) = mtrx_(0, i-1)-1;
        track_(0, i) = LEFT;
    }
}

void Alignment::fill_mtrx() {
    for (unsigned r = 1; r < nrow_; ++r) {
        for (unsigned c = 1; c < ncol_; ++c) {
            int left = mtrx_(r,c-1) - 1;
            int top = mtrx_(r-1, c) - 1;
            int diagonal = mtrx_(r-1, c-1);
            if ((*seq1_)[r-1] == (*seq2_)[c-1]){
                diagonal += 1;
            } else {
                diagonal -= 1;
            }
            if (diagonal >= left && diagonal >= top){
                mtrx_(r, c) = diagonal;
                track_(r, c) = DIAGONAL;
            } else if (left >= diagonal && left >= top){
                mtrx_(r, c) = left;
                track_(r, c) = LEFT;
            } else {
                mtrx_(r, c) = top;
                track_(r, c) = TOP;
            }
        }
    }
    cout << "Alignment score:\t\t" << mtrx_(nrow_-1, ncol_-1) << endl;
    cout << "Best possible score:\t";
    cout << min(nrow_, ncol_) - (max(nrow_,ncol_) - min(nrow_, ncol_)) - 1 << endl;
}

void Alignment::backtracking() {
    int r = nrow_-1;
    int c = ncol_-1;
    while (track_(r,c) != END){
        switch (track_(r,c)) {
            case LEFT:
                alignment2_ = Nucleotide::toChar((*seq2_)[c-1]) + alignment2_;
                alignment1_ = "-" + alignment1_;
                c -= 1;
                continue;
            case TOP:
                alignment2_ = "-" + alignment2_;
                alignment1_ = Nucleotide::toChar((*seq1_)[r-1]) + alignment1_;
                r -= 1;
                continue;
            default:
                alignment1_ = Nucleotide::toChar((*seq1_)[r-1]) + alignment1_;
                alignment2_ = Nucleotide::toChar((*seq2_)[c-1]) + alignment2_;
                r -= 1;
                c -= 1;
                continue;
        }
    }
}