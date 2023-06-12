#pragma once
#include <iostream>

class OpenTextureFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "Opening the texture failed\n";
    }
};

class OpenFontFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "Opening the font failed\n";
    }
};


class OpenFileFailed : public std::exception {
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

class FileIsInvalid : public std::exception {
public:
    const char* what() const noexcept {
        return "The file is invalid, cant read.\n";
    }
};

class OpenAudioFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "Opening the audio failed\n";
    }
};

class OpenImageFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "Opening the image failed\n";
    }
};