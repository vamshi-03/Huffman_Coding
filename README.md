# Huffman_Coding

## Overview

This C++ project demonstrates Huffman coding, a popular algorithm used for lossless data compression. The program reads input from a file, performs Huffman coding to compress the data, writes the compressed binary data to an output file, and then decodes the compressed data back to its original form. Additionally, it includes functionality to write and read binary data to and from files.

## Features

- **Huffman Coding**: Utilizes Huffman coding for efficient compression of data.
- **File Compression**: Reads content from a file, compresses it using Huffman coding, and writes the compressed binary data to an output file.
- **File Decompression**: Reads compressed binary data from a file, decodes it using Huffman coding, and writes the decompressed content to a separate file.
- **Binary Data Handling**: Converts binary bits to characters and vice versa, allowing manipulation of binary data.

## Getting Started

### Prerequisites

- C++ compiler (supporting C++11 or later)
- Git (optional, for cloning the repository)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/vamshi-03/huffman-coding-project.git
   ```

2. Navigate to the project directory:

   ```bash
   cd huffman-coding-project
   ```

3. Compile the code:

   ```bash
   g++ huffman_coding.cpp -o huffman_coding
   ```

4. Run the executable:

   ```bash
   ./huffman_coding
   ```

## Usage

1. **Input File**:
   - Create a text file (e.g., input.txt) with the content you want to compress.

2. **Run the Program**:
   - Execute the compiled program.
   - The compressed binary data will be written to a file named `inputfilename_compressed.bin`.
   - The decompressed content will be written to a file named `inputfilename_decompressed.txt`.

3. **Check Output**:
   - Open the `inputfilename_compressed.bin` file to view the compressed binary data.
   - Open the `inputfile_decompressed.txt` file to view the decompressed content.

## Contributing

Contributions are welcome! Please follow the [Contribution Guidelines](CONTRIBUTING.md) for details on how to contribute to this project.


Feel free to customize this README based on your specific project details and requirements. Additionally, you may want to include sections such as "Acknowledgements," "Troubleshooting," or "Future Improvements" depending on the nature and complexity of your project.
