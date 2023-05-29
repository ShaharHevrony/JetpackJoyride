#pragma once
#include <iostream>

class OpenTextureFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "Opening the file failed\n";
    }
};

class OpenFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "The file is exist, but can't open this file.\n";
    }
};

class FileNotExist : public std::exception {
public:
    const char* what() const noexcept {
        return "The file is not exist.\n";
    }
};

class AlreadyOpen : public std::exception {
public:
    const char* what() const noexcept {
        return "The file is already open.\n";
    }
};
