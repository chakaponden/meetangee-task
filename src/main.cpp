/**
 * @file main.cpp
 * @brief A program entry point
 */

#include <iostream>
#include <string>

#include "Controller.h"
#include "URI.h"
#include "TextColor.h"
#include "TextColorCode.h"

int main(int argc, char *argv[])
{
    /// Input args count validation
    if(argc < 2)
    {
        std::cerr << "You must specify:" << std::endl
                  << "source HTML file URL as first cmd argument." << std::endl
                  << "Example: ./itransition-task http://www.meetangee.com" << std::endl;
        return 1;
    }
    /// Source HTML file URL validation
    URI rootURI;
    rootURI.SetURL(std::string(argv[1]));
    if(!rootURI.IsValid())
    {
        std::cerr << "Error! Source HTML file URL is invalid." << std::endl
                  << "Specify valid HTML file URL as first cmd argument." << std::endl
                  << "Example: ./itransition-task http://www.meetangee.com" << std::endl;
        return 2;
    }
    Controller facade(rootURI.GetURL());
    try
    {
        facade.Execute();
    }
    catch(std::invalid_argument exception)
    {
        std::cerr << exception.what() << std::endl;
        return 3;
    }
    catch(std::runtime_error exception)
    {
        std::cerr << exception.what() << std::endl;
        return 4;
    }
    catch(...)
    {
        return 5;
    }
    /// Output execution result to terminal
    std::multimap<size_t, FileInfo> resultContainerData =
            facade.GetResult()->GetData();
    if(!resultContainerData.empty())
    {
        const Color::TextColor fileMaxSizeColor(
                    Color::TextColorCode::FG_RED);      ///< File max size color
        const Color::TextColor fileMinSizeColor(
                    Color::TextColorCode::FG_GREEN);    ///< File min size color
        const Color::TextColor fileOtherColor(
                    Color::TextColorCode::FG_YELLOW);   ///< Other files color
        const Color::TextColor defaultTerminalColor(
                    Color::TextColorCode::FG_DEFAULT);  ///< Default terminal color
        const Color::TextColor tableHeaderColor(
                    Color::TextColorCode::FG_BLUE);     ///< Table header info color
        const size_t fileSizeMax = resultContainerData.rbegin()->first;
        const size_t fileSizeMin = resultContainerData.begin()->first;
        /// Output colorized header info
        std::cout << tableHeaderColor
                  << "SIZE" << '\t'
                  << "HASH" << "\t\t"
                  << "FILE URL" << std::endl;
        std::multimap<size_t, FileInfo>::reverse_iterator it;
        for (it = resultContainerData.rbegin(); it != resultContainerData.rend(); ++it)
        {
            /**
             * Output colorized file info:
             * 0: file absolute URL
             * 1: file content adler32 hash
             * 2: file size in bytes
             *
             * Output file information format:
             * File size | File content adler32 hash | File absolute URL
             */
            std::cout << (it->first == fileSizeMax ? fileMaxSizeColor :
                          it->first == fileSizeMin ? fileMinSizeColor : fileOtherColor)
                      << std::dec << it->second.GetSize() << '\t'
                      << std::hex << it->second.GetAdler32Hash() << '\t'
                      << std::dec << it->second.GetURL() << std::endl;
        }
        /// Reset terminal color
        std::cout << defaultTerminalColor;
    }
    return 0;
}
