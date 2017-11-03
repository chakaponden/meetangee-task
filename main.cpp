#include <iostream>
#include <string>
#include <map>
#include <tuple>

#include "DownloaderString.h"
#include "DownloaderParallel.h"
#include "HTMLParser.h"
#include "Adler32Generator.h"
#include "TextColor.hpp"
#include "URI.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "You must specify:" << std::endl
                  << "source HTML file URL as first cmd argument." << std::endl
                  << "Example: ./itransition-task http://www.meetangee.com" << std::endl;
        return 1;
    }
    const std::string rootURL(argv[1]);
    // source HTML file URL validation
    URI rootURI(rootURL);
    if(!rootURI.IsValid())
    {
        std::cerr << "Error! Source HTML file URL is invalid." << std::endl
                  << "Specify valid HTML file URL as first cmd argument." << std::endl
                  << "Example: ./itransition-task http://www.meetangee.com" << std::endl;
        return 2;
    }
    // download html file content as string
    DownloaderString downloaderRoot;
    downloaderRoot.SetURL(rootURI.GetURL());
    downloaderRoot();

    HTMLParser parcer;
    std::vector<DownloaderStringShp> downloaders;
    DownloaderParallel downloaderParallel;
    for(std::string hrefValue : parcer.Parse(downloaderRoot.GetContent(), downloaderRoot.GetURL()))
    {
        DownloaderStringShp downloaderSimple = std::make_shared<DownloaderString>();
        downloaderSimple->SetURL(hrefValue);
        downloaders.push_back(downloaderSimple);
        downloaderParallel.AddDownloader(downloaderSimple.get());
    }
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
      Adler32Generator adler32;
      std::string contentRefFile = simpleDownloader->GetContent();
      downloadedFiles.insert(
        std::pair<size_t, FileInfo>(contentRefFile.size(),
                                    std::make_tuple(simpleDownloader->GetURL(),
                                                    adler32.Generate(contentRefFile),
                                                    contentRefFile.size())));
    }

    if(!downloadedFiles.empty())
    {
        const Color::TextColor red(Color::TextColorCode::FG_RED);
        const Color::TextColor green(Color::TextColorCode::FG_GREEN);
        const Color::TextColor yellow(Color::TextColorCode::FG_YELLOW);
        const Color::TextColor def(Color::TextColorCode::FG_DEFAULT);
        const Color::TextColor blue(Color::TextColorCode::FG_BLUE);
        const size_t fileSizeMax = downloadedFiles.rbegin()->first;
        const size_t fileSizeMin = downloadedFiles.begin()->first;
        // header info blue color
        std::cout << blue << "SIZE" << '\t' << "HASH" << "\t\t" << "FILE URL" << std::endl;
        std::map<size_t, FileInfo>::reverse_iterator it;
        for (it = downloadedFiles.rbegin(); it != downloadedFiles.rend(); ++it)
        {
            /** 
             * 0: file absolute URL
             * 1: file content adler32 hash
             * 2: file size in bytes
             */
            // file max size - red color
            // file min size - green color
            // other files   - yellow color 
            std::cout << (it->first == fileSizeMax ? red :
                            it->first == fileSizeMin ? green : yellow)
                      << std::dec << std::get<2>(it->second) << '\t'
                      << std::hex << std::get<1>(it->second) << '\t'
                      << std::dec << std::get<0>(it->second) << std::endl;
        }
        // reset terminal coloring
        std::cout << def;
    }
    return 0;
}