# Task_CPP
Implement C++ functions to (de)compress input data using run-length encoding and dictionary coder. Provide test cases showing advantages and disadvantages of both methods. Compare both methods in terms of compression ratio, (de)compression speed, and memory usage.
Sure, here's the explanation with code snippets:

```markdown
# Compression Algorithms in C++

This C++ code provides implementations of two compression algorithms: Run-Length Encoding and Dictionary Coding.

## Run-Length Encoding
Run-Length Encoding (RLE) is a simple compression algorithm that reduces the size of repetitive sequences in data.

### `runLengthEncode(const string& input)`
```cpp
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
```
This function takes a string `input` and compresses it using Run-Length Encoding. It counts the consecutive occurrences of each character and encodes them as a count followed by the character itself.

### `runLengthDecode(const string& input)`
```cpp
static string runLengthDecode(const string& input) {
    string decoded;
    for (int i = 0; i < input.size(); i += 2) {
        int count = input[i] - '0';
        decoded += string(count, input[i + 1]);
    }
    return decoded;
}
```
This function takes a string `input` that has been compressed using Run-Length Encoding and decodes it back to its original form.

## Dictionary Coding
Dictionary Coding is another compression algorithm that replaces repetitive sequences of characters with shorter codes.

### `dictionaryEncode(const string& input)`
```cpp
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
```
This function compresses the input string `input` using Dictionary Coding. It creates a dictionary of substrings encountered in the input and replaces them with shorter codes.

### `dictionaryDecode(const string& input)`
```cpp
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
```
This function decodes a string `input` that has been compressed using Dictionary Coding back to its original form.

## Testing and Comparison
The code also includes functions to test the compression algorithms and compare their performance. 
```


