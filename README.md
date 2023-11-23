
# Encryption_Tool

This project provides a robust command-line tool for file encryption and decryption, utilizing the powerful Crypto++ library. Designed for versatility and security, it allows users to securely encrypt any type of file, ensuring data privacy and protection.


## Features

- Robust Encryption and Decryption: Utilizes the powerful Crypto++ library for secure file encryption and decryption, ensuring high-level data protection.

- Support for Various File Types: 
    - Text Files: .txt, .html, .css, .js, .json, .xml, .csv, .md
    - Document Files: jpg, .png, .gif, .bmp, .tiff, etc
    - Audio and Video Files: .mp3, .wav, .mp4, .avi, .mkv, .mov, etc
    - Executable Files: .exe, .dll, .so, .bin
    - Archvie Files: .db, .sql, .sqlite
    - Source Code: .cpp, .py, .java, .c, etc

- Command-Line Interface: Offers a straightforward command-line interface for ease of use in various operating environments, suitable for both novice and advanced users.

- High Performance: Optimized for speed and efficiency, ensuring fast encryption and decryption processes without compromising security.

- Cross-Platform Compatibility: Designed to work across different operating systems, providing a consistent user experience regardless of the platform.


## Installation

Follow these steps to install and set up the **Encryption Tool**:

1. **Clone the Repository**
   - First, clone the repository to your local machine using Git:
     ```bash
     git clone [https://github.com/Williampc1917/Encryption-Tool]
     ```
  

2. **Build the Project**
   - Navigate to the project directory:
     ```bash
     cd [Project Directory]
     ```
   

3. **Verify Installation**
   - Ensure that the `encryption_tool` executable is created in the build directory.
## Usage/Examples

After installation, you can use the **Encryption Command-Line Tool** directly from the command line. Here's how to get started:

1. **Navigate to the Build Directory**
   - Open a terminal and navigate to the build directory where the executable is located.

2. **Running the Tool**
   - To encrypt a file, use the following command:
     ```bash
     ./encryption-tool --encrypt --input-file example.txt --output-file encrypted.dat 
     ```
     or
     ```bash
      ./encryption-tool -e -i example.txt -o encrypted.dat

   - Replace `example.txt` with the path to your input file and `encrypted.dat` with your desired output file name or path to where you want the encrypted file.

   - Similarly, you can use other commands for decryption, key generation, etc., as per the features of your tool.


## License

[MIT](https://choosealicense.com/licenses/mit/)

