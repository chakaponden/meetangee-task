/**
 * Adler32Generalor.h
 *
 * A simple C++ wrapper for the ZLib adler32 hash generation.
 */
#ifndef ADLER32GENERATOR_H
#define ADLER32GENERATOR_H
#include <string>
/**
 * A simple ZLib adler32 hash generator
 */
class Adler32Generator
{
public:
    Adler32Generator();
    ~Adler32Generator();
    /**
     * Generate adler32 hash from data stored in std::string using Zlib
     * @param content The input data content
     * @return The hash result
     */
    static unsigned long Generate(const std::string& content);
};
#endif  /* ADLER32GENERATOR_H */