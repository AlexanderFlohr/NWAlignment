cmake_minimum_required(VERSION 3.10)
project(NWAlignment)

#set(CMAKE_CXX_STANDARD 20)

# Optionen an den Compiler
set(CXX_FLAGS
        -std=c++20               # Verwende den C++14 Standard
        -pedantic                # Achte auf genauere Einhaltung des Standards
        -Wall                    # Aktiviere alle Warnungen
        )

add_executable(nwalign
        main.cpp
        nucleotide.cpp
        nucleotide.h
        sequence.cpp
        sequence.h
        FASTA/reader.cpp
        FASTA/reader.h
        matrix.h
        alignment.cpp
        alignment.h)
