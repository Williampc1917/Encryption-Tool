//
// Created by william on 11/17/23.
//

#ifndef ENCRYPTIONTOOL_ENCRYPTION_H
#define ENCRYPTIONTOOL_ENCRYPTION_H

#include <string>
#include <fstream>

class Encryption{

    public:
        static void encryptFile(const std::string& inputFile, const std::string& outputFile);
        static void decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);

};




#endif //ENCRYPTIONTOOL_ENCRYPTION_H
