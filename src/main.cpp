/**
 * @file main.cpp
 * @brief A program entry point
 */

#include <iostream>
#include <string>
#include <map>
#include <tuple>

#include "DownloaderString.h"
#include "DownloaderParallel.h"
#include "HTMLParser.h"
#include "Adler32Generator.h"
#include "TextColor.h"
#include "URI.h"

int main(int argc, char *argv[])
{
    /// check input args for count
    if(argc < 2)
    {
        std::cerr << "You must specify:" << std::endl
                  << "source HTML file URL as first cmd argument." << std::endl
                  << "Example: ./itransition-task http://www.meetangee.com" << std::endl;
        return 1;
    }
    const std::string rootURL(argv[1]);
    /// source HTML file URL validation
    URI rootURI(rootURL);
    if(!rootURI.IsValid())
    {
        std::cerr << "Error! Source HTML file URL is invalid." << std::endl
                  << "Specify valid HTML file URL as first cmd argument." << std::endl
                  << "Example: ./itransition-task http://www.meetangee.com" << std::endl;
        return 2;
    }
    /// download source HTML file content as string
    DownloaderString downloaderRoot;
    downloaderRoot.SetURL(rootURI.GetURL());
    downloaderRoot();

    HTMLParser parcer;
    std::vector<DownloaderStringShp> downloaders;
    DownloaderParallel downloaderParallel;
    /// parse download source HTML file content and loop for each parced link
    for(std::string hrefValue : parcer.Parse(downloaderRoot.GetContent(),
                                             downloaderRoot.GetURL()))
    {
        DownloaderStringShp downloaderSimple =
                std::make_shared<DownloaderString>();
        downloaderSimple->SetURL(hrefValue);
        downloaders.push_back(downloaderSimple);
        /**
         * simple downloader pass to parallel downloader
         * for download all files in parallel
         */
        downloaderParallel.AddDownloader(downloaderSimple.get());
    }
    /// execute download all files in parallel
    downloaderParallel();

    /**
    * 0: file absolute URL
    * 1: file content adler32 hash
    * 2: file size in bytes
    */
    using FileInfo = std::tuple<std::string, unsigned long, size_t>;
    std::map<size_t, FileInfo> downloadedFiles;
    for(DownloaderStringShp simpleDownloader : downloaders)
    {
        std::string contentRefFile = simpleDownloader->GetContent();
        // collect files information for output
        downloadedFiles.insert(
                    std::pair<size_t, FileInfo>(contentRefFile.size(),
                                                std::make_tuple(simpleDownloader->GetURL(),
                                                                /// generate adler32 hash of file content
                                                                Adler32Generator::Generate(contentRefFile),
                                                                contentRefFile.size())));
    }

    if(!downloadedFiles.empty())
    {
        const Color::TextColor fileMaxSizeColor(
                    Color::TextColorCode::FG_RED);      ///< file max size color
        const Color::TextColor fileMinSizeColor(
                    Color::TextColorCode::FG_GREEN);    ///< file min size color
        const Color::TextColor fileOtherColor(
                    Color::TextColorCode::FG_YELLOW);   ///< other files color
        const Color::TextColor defaultTerminalColor(
                    Color::TextColorCode::FG_DEFAULT);  ///< default terminal color
        const Color::TextColor tableHeaderColor(
                    Color::TextColorCode::FG_BLUE);     ///< table header info color
        const size_t fileSizeMax = downloadedFiles.rbegin()->first;
        const size_t fileSizeMin = downloadedFiles.begin()->first;
        /// output colorized header info
        std::cout << tableHeaderColor
                  << "SIZE" << '\t' <<
                     "HASH" << "\t\t" <<
                     "FILE URL" << std::endl;
        std::map<size_t, FileInfo>::reverse_iterator it;
        for (it = downloadedFiles.rbegin(); it != downloadedFiles.rend(); ++it)
        {
            /**
             * output colorized file info:
             * 0: file absolute URL
             * 1: file content adler32 hash
             * 2: file size in bytes
             *
             * output file information format:
             * file size | file content adler32 hash | file absolute URL
             */
            std::cout << (it->first == fileSizeMax ? fileMaxSizeColor :
                          it->first == fileSizeMin ? fileMinSizeColor : fileOtherColor)
                      << std::dec << std::get<2>(it->second) << '\t'
                      << std::hex << std::get<1>(it->second) << '\t'
                      << std::dec << std::get<0>(it->second) << std::endl;
        }
        /// reset terminal color
        std::cout << defaultTerminalColor;
    }
    return 0;
}
