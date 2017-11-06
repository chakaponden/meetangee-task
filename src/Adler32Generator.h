/**
 * @file Adler32Generator.h
 * @brief A simple zlib wrapper for the adler32 hash generation
 */

#ifndef ADLER32GENERATOR_H
#define ADLER32GENERATOR_H

#include <string>

/**
 * @brief Generate adler32 hash using zlib realization
 * @version 1.0.0
 * @author chakaponden (itransition.com)
 * @date 4 November 2017
 * @copyright MIT License
 * @details A simple zlib wrapper for the adler32 hash generation
 */
class Adler32Generator
{
public:
    Adler32Generator();
    ~Adler32Generator();
    /**
     * @brief Generate adler32 hash from data stored in std::string
     * @param[in] content Data from which hash to be generated
     * @return Adler32 Hash
     */
    static unsigned long Generate(const std::string& content);
};

#endif  /* ADLER32GENERATOR_H */
