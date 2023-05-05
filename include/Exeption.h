#pragma once
#include <iostream>

class OpenTextureFailed : public std::exception {
public:
    const char* what() const noexcept {
        return "Opening the texture failed\n";
    }
};
