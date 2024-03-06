#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "class.h" // Include the file containing compression functions

using namespace std;

// Function to read content from a file
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
size_t estimateMemoryUsage(const string& data) {
    // Assuming each character takes 1 byte of memory
    return data.size();
}
// Function to perform comparisons and print results in a table format
// Function to perform comparisons and print results in a table format
void printComparisonTable(const string& input) {
    // Perform comparisons for run-length encoding
    auto start_rle_comp = chrono::steady_clock::now();
    string rle_encoded = Compression::runLengthEncode(input);
    auto end_rle_comp = chrono::steady_clock::now();
    auto rle_comp_duration = chrono::duration_cast<chrono::microseconds>(end_rle_comp - start_rle_comp).count();
    double rle_comp_ratio = (double)rle_encoded.size() / input.size();
    size_t rle_comp_memory = estimateMemoryUsage(rle_encoded);

    auto start_rle_decomp = chrono::steady_clock::now();
    string rle_decoded = Compression::runLengthDecode(rle_encoded);
    auto end_rle_decomp = chrono::steady_clock::now();
    auto rle_decomp_duration = chrono::duration_cast<chrono::microseconds>(end_rle_decomp - start_rle_decomp).count();

    // Perform comparisons for dictionary coding
    auto start_dict_comp = chrono::steady_clock::now();
    string dict_encoded = Compression::dictionaryEncode(input);
    auto end_dict_comp = chrono::steady_clock::now();
    auto dict_comp_duration = chrono::duration_cast<chrono::microseconds>(end_dict_comp - start_dict_comp).count();
    double dict_comp_ratio = (double)dict_encoded.size() / input.size();
    size_t dict_comp_memory = estimateMemoryUsage(dict_encoded);

    auto start_dict_decomp = chrono::steady_clock::now();
    string dict_decoded = Compression::dictionaryDecode(dict_encoded);
    auto end_dict_decomp = chrono::steady_clock::now();
    auto dict_decomp_duration = chrono::duration_cast<chrono::microseconds>(end_dict_decomp - start_dict_decomp).count();

    // Print comparison table
    cout << "Compression and Decompression Comparison Table:" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    cout << "| Method            | Compression Ratio | Compression Time (µs) | Decompression Time (µs) | Memory Usage |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    cout << "| Run-Length Encoding | " << rle_comp_ratio << " | " << rle_comp_duration << " | " << rle_decomp_duration << " | " << rle_comp_memory << " bytes |" << endl;
    cout << "| Dictionary Coding   | " << dict_comp_ratio << " | " << dict_comp_duration << " | " << dict_decomp_duration << " | " << dict_comp_memory << " bytes |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
}

int main() {
    // Read the content of the text file
    string filename = "text.txt";
    string input = readFile(filename);
    if (input.empty()) {
        return 1; // Error occurred while reading the file
    }

    // Print the content of the file
    cout << "Content of the text file:" << endl;
    cout << input << endl;

    // Print comparisons in a table format
    printComparisonTable(input);

    return 0;
}