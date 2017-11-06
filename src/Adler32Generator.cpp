/**
 * @file Adler32Generator.cpp
 * @brief A simple zlib wrapper implementation
 */

#include "Adler32Generator.h"
#include <zlib.h>
#include <iostream>
#include <string>

Adler32Generator::Adler32Generator()
{
}

Adler32Generator::~Adler32Generator()
{
}

unsigned long Adler32Generator::Generate(const std::string& content)
{
    // initial checksum according zlib usage manual
    unsigned long adler = adler32(0L, Z_NULL, 0);
    adler = adler32(adler, reinterpret_cast<const unsigned char *>(content.c_str()), content.length());
    return adler;
}
