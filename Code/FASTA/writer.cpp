//
// Created by s9alfloh on 11.11.17.
//

#include "writer.h"
#include <fstream>

using namespace std;

FASTAWriter::FASTAWriter() {
    return;
}

void FASTAWriter::write(string filename, vector<Sequence> &sample) {
    ofstream stream(filename);
    if (stream.is_open()) {
        for (unsigned i = 0; i < sample.size(); ++i) {
            stream << sample[i];
        }
    }
    stream.close();
}
