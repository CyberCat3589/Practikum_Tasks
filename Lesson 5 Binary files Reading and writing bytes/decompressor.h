#pragma once

#include <string>
#include <fstream>

// напишите эту функцию
inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name)
{
    ifstream src(src_name, std::ios::in | std::ios::binary);
    if (!src) {
        return false;
    }
    ofstream dest(dst_name, std::ios::out | std::ios::binary);
    do {
        unsigned char header = src.get();
        bool series_flag = (header & 1);
        size_t data_size = static_cast<size_t>(header >> 1) + 1;
        if (!series_flag && !src.eof()) {
            char buff[128];
            src.read(buff, data_size);
            size_t readed = src.gcount();
            dest.write(buff, readed);
        }
        else if (!src.eof()){
            unsigned char symbol = src.get();
            string str(data_size, symbol);
            dest.write(str.data(), data_size);
        }
    } while (src);
    return true;
}