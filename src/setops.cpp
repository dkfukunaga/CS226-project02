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
#include "value_types.h"
#include "set_ops.h"
#include "set_ops_io.h"

using namespace std;
using namespace setops;

/* TYPES */

struct FileNames {
    std::string input_file;
    std::string output_file;
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

        getline(in_file, line);
        set_a = parseSet(line);
        
        getline(in_file, line);
        set_b = parseSet(line);

        cout << "Set A: ";
        cout << set_a << endl;

        cout << "Set B: ";
        cout << set_b << "\n" << endl;

        ValueSet a_b_union = set_union(set_a, set_b);
        cout << "A union B = " << a_b_union << endl;

        ValueSet a_b_intersect = set_intersection(set_a, set_b);
        cout << "A intersection B = " << a_b_intersect << endl;

        ValueSet a_b_diff = set_difference(set_a, set_b);
        cout << "A difference B = " << a_b_diff << endl;

        ValueSet a_b_xor = set_symmetric_difference(set_a, set_b);
        cout << "A xor B = " << a_b_xor << endl;

        ValuePairVec a_b_cross = set_cartesian_product(set_a, set_b);
        cout << "A X B = " << a_b_cross << endl;

        ValueSetVec a_power = power_set(set_a);
        cout << "P(A) = " << a_power << endl;

	    return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << "Usage: " << argv[0] << " [-i file] [-o file]\n";
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
 * @throws std::runtime_error if an option is malformed, duplicated, or unknown.
 */
FileNames parse_args(int argc, char* argv[]) {
    FileNames opts;
    // if (argc == 1) {
    //     opts.input_file = DEFAULT_INPUT_FILE;
    //     return opts;
    // }

    std::vector<std::string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "-i") {
            if (i + 1 < args.size()) {
                if (!opts.input_file.empty()) throw std::runtime_error("-i specified more than once");
                opts.input_file = args[++i];
            } else throw std::runtime_error("-i requires a filename");
        } else if (args[i] == "-o") {
            if (i + 1 < args.size()) {
                if (!opts.output_file.empty()) throw std::runtime_error("-o specified more than once");
                opts.output_file = args[++i];
            } else throw std::runtime_error("-o requires a filename");
        } else if (args[i] == "-h" || args[i] == "--help") {
            std::cout << "Usage: " << argv[0] << " [-i file] [-o file]\n";
            std::exit(0);
        } else {
            throw std::runtime_error("Unknown option: " + args[i]);
        }
    }

    if (opts.input_file.empty()) {
        opts.input_file = DEFAULT_INPUT_FILE; // default
    }

    return opts;
}