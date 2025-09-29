/*
  Class: CS226
  Project Name: Programming Project 02
   
  Author: Dani Fukunaga
   
  Description: Write a program that takes as input two sets, A and B, and
    outputs the following: A ∪ B, A ∩ B, A × B, A ⊕ B, 𝒫(A).

    I want the program to take file input and output to both the console and a
    file.

  (style guide based on https://google.github.io/styleguide/cppguide.html)
*/

/* INCLUDES and NAMESPACE */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "value_types.h"    // aliases for variants, sets, pairs, vectors, etc
#include "set_ops.h"        // set operations union, intersection, difference, xor, cartesian product, power set
#include "set_ops_io.h"     // helper functions for parsing and outputing sets

using namespace std;
using namespace setops;

/* TYPES */

struct FileNames {
    string input_file;
    string output_file;
};

/* CONSTANTS */

constexpr const char* DEFAULT_INPUT_FILE = "input.txt";

/* FUNCTION PROTOTYPES */

FileNames parse_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    FileNames file_names;
    ifstream in_file;
    ofstream out_file;

    try {
        // Collect arguments into vector for easier handling
        file_names = parse_args(argc, argv);

        // Open input file
        in_file.open(file_names.input_file);
        if (!in_file) {
            cerr << "Error: could not open input file: " << file_names.input_file << "\n";
            return 1;
        }

        // Setup output streams
        // Only write to file if output file provided
        out_file;
        bool write_to_file = false;
        if (!file_names.output_file.empty()) {
            out_file.open(file_names.output_file);
            if (!out_file) {
                cerr << "Error: could not open output file: " << file_names.output_file << "\n";
                return 1;
            }
            write_to_file = true;
        }

        ValueSet set_a;
        ValueSet set_b;
        string line;

        // read sets from input file
        getline(in_file, line);
        set_a = parseSet(line);
        getline(in_file, line);
        set_b = parseSet(line);

        // apply set operations
        ValueSet a_b_union = set_union(set_a, set_b);
        ValueSet a_b_intersect = set_intersection(set_a, set_b);
        ValueSet a_b_diff = set_difference(set_a, set_b);
        ValueSet a_b_xor = set_symmetric_difference(set_a, set_b);
        ValuePairVec a_b_cross = set_cartesian_product(set_a, set_b);
        ValueSetVec a_power = power_set(set_a);

        // output original sets
        cout << "Set A: " << set_a << endl;
        cout << "Set B: " << set_b << endl;
        
        // output results of set operations
        cout << "A union B = " << a_b_union << endl;
        cout << "A intersection B = " << a_b_intersect << endl;
        cout << "A difference B = " << a_b_diff << endl;
        cout << "A xor B = " << a_b_xor << endl;
        cout << "A X B = " << a_b_cross << endl;
        cout << "P(A) = " << a_power << endl;

        // output to text file
        if (out_file.is_open()) {
            out_file << "Set A: " << set_a << endl;
            out_file << "Set B: " << set_b << endl;
            
            out_file << "A union B = " << a_b_union << endl;
            out_file << "A intersection B = " << a_b_intersect << endl;
            out_file << "A difference B = " << a_b_diff << endl;
            out_file << "A xor B = " << a_b_xor << endl;
            out_file << "A X B = " << a_b_cross << endl;
            out_file << "P(A) = " << a_power << endl;
        }

	    return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        cerr << "Usage: " << argv[0] << " [-i file] [-o file]\n";
        return 1;
    }

    

}

/* FUNCTION DEFINITIONS */

/**
 * @brief Parses command-line arguments for input and output files.
 *
 * Recognized options:
 *   - `-i <file>` : optional input file (defaults to "input.txt" if omitted).
 *   - `-o <file>` : optional output file (if omitted, results are written only to console).
 *
 * @param argc Number of arguments (from main).
 * @param argv Array of argument strings (from main).
 * @return FileNames Structure containing resolved input and output file names.
 *
 * @throws runtime_error if an option is malformed, duplicated, or unknown.
 */
FileNames parse_args(int argc, char* argv[]) {
    FileNames opts;
    // if (argc == 1) {
    //     opts.input_file = DEFAULT_INPUT_FILE;
    //     return opts;
    // }

    vector<string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "-i") {
            if (i + 1 < args.size()) {
                if (!opts.input_file.empty()) throw runtime_error("-i specified more than once");
                opts.input_file = args[++i];
            } else throw runtime_error("-i requires a filename");
        } else if (args[i] == "-o") {
            if (i + 1 < args.size()) {
                if (!opts.output_file.empty()) throw runtime_error("-o specified more than once");
                opts.output_file = args[++i];
            } else throw runtime_error("-o requires a filename");
        } else if (args[i] == "-h" || args[i] == "--help") {
            cout << "Usage: " << argv[0] << " [-i file] [-o file]\n";
            exit(0);
        } else {
            throw runtime_error("Unknown option: " + args[i]);
        }
    }

    if (opts.input_file.empty()) {
        opts.input_file = DEFAULT_INPUT_FILE; // default
    }

    return opts;
}