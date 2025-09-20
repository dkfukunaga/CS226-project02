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

using namespace std;

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

    try {
        // Collect arguments into vector for easier handling
        file_names = parse_args(argc, argv);

        // Open input file
        std::ifstream in(file_names.input_file);
        if (!in) {
            std::cerr << "Error: could not open input file: " << file_names.input_file << "\n";
            return 1;
        }

        // Setup output streams
        // Only write to file if output file provided
        std::ofstream out;
        bool write_to_file = false;
        if (!file_names.output_file.empty()) {
            out.open(file_names.output_file);
            if (!out) {
                std::cerr << "Error: could not open output file: " << file_names.output_file << "\n";
                return 1;
            }
            write_to_file = true;
        }

        //put your main program here!

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