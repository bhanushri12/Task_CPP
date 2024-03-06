#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>

using namespace std;

class Compression {
public:
    // Run-Length Encoding
    static string runLengthEncode(const string& input) {
        string encoded;
        int count = 1;
        for (int i = 0; i < input.size(); ++i) {
            if (i + 1 < input.size() && input[i] == input[i + 1]) {
                count++;
            } else {
                encoded += to_string(count) + input[i];
                count = 1;
            }
        }
        return encoded;
    }

    static string runLengthDecode(const string& input) {
        string decoded;
        for (int i = 0; i < input.size(); i += 2) {
            int count = input[i] - '0';
            decoded += string(count, input[i + 1]);
        }
        return decoded;
    }

    // Dictionary Coding
    static string dictionaryEncode(const string& input) {
        unordered_map<string, int> dictionary;
        string encoded;
        int index = 1;
        for (int i = 0; i < input.size();) {
            string current;
            while (dictionary[current] && i < input.size()) {
                current += input[i];
                i++;
            }
            if (i < input.size()) {
                dictionary[current] = index++;
                encoded += to_string(dictionary[current]);
            }
        }
        return encoded;
    }

    static string dictionaryDecode(const string& input) {
        unordered_map<int, string> dictionary;
        string decoded;
        int index = 1;
        for (int i = 0; i < input.size();) {
            int code = input[i] - '0';
            if (dictionary[code] == "") {
                string newEntry = dictionary[index++] = dictionary[0] + input[i + 1];
                decoded += newEntry;
            } else {
                decoded += dictionary[code];
            }
            i++;
        }
        return decoded;
    }
};

void testRunLengthEncoding(const string& input) {
    auto start = chrono::steady_clock::now();
    string encoded = Compression::runLengthEncode(input);
    auto end = chrono::steady_clock::now();
    cout << "Run-Length Encoding: " << encoded << endl;
    cout << "Encoded Size: " << encoded.size() << " bytes" << endl;
    cout << "Compression Ratio: " << (double)encoded.size() / input.size() << endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Compression Time: " << duration << " microseconds" << endl;

    start = chrono::steady_clock::now();
    string decoded = Compression::runLengthDecode(encoded);
    end = chrono::steady_clock::now();
    cout << "Decoded String: " << decoded << endl;
    cout << "Decompression Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    cout << endl;
}

void testDictionaryCoding(const string& input) {
    auto start = chrono::steady_clock::now();
    string encoded = Compression::dictionaryEncode(input);
    auto end = chrono::steady_clock::now();
    cout << "Dictionary Encoding: " << encoded << endl;
    cout << "Encoded Size: " << encoded.size() << " bytes" << endl;
    cout << "Compression Ratio: " << (double)encoded.size() / input.size() << endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Compression Time: " << duration << " microseconds" << endl;

    start = chrono::steady_clock::now();
    string decoded = Compression::dictionaryDecode(encoded);
    end = chrono::steady_clock::now();
    cout << "Decoded String: " << decoded << endl;
    cout << "Decompression Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    cout << endl;
}
void visualizeCompressionRatio(const std::string& input1, const std::string& input2) {
    double rle_ratio = (double)Compression::runLengthEncode(input1).size() / input1.size();
    double dict_ratio = (double)Compression::dictionaryEncode(input2).size() / input2.size();

    std::cout << "Compression Ratio Comparison:" << std::endl;
    std::cout << "Run-Length Encoding: " << rle_ratio << std::endl;
    std::cout << "Dictionary Coding: " << dict_ratio << std::endl;
    std::cout << std::endl;
}

void compareSpeed(const std::string& input1, const std::string& input2) {
    auto start = std::chrono::steady_clock::now();
    std::string rle_encoded = Compression::runLengthEncode(input1);
    std::string rle_decoded = Compression::runLengthDecode(rle_encoded);
    auto end = std::chrono::steady_clock::now();
    auto rle_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    std::string dict_encoded = Compression::dictionaryEncode(input2);
    std::string dict_decoded = Compression::dictionaryDecode(dict_encoded);
    end = std::chrono::steady_clock::now();
    auto dict_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Compression and Decompression Speed Comparison:" << std::endl;
    std::cout << "Run-Length Encoding: " << rle_duration << " microseconds" << std::endl;
    std::cout << "Dictionary Coding: " << dict_duration << " microseconds" << std::endl;
    std::cout << std::endl;
}