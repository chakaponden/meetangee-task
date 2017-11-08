#include "Controller.h"

#include <iostream>
#include <string>
#include <map>
#include <tuple>

// EasyCurl lib source files
#include "DownloaderString.h"
#include "DownloaderParallel.h"

#include "HTMLParser.h"
#include "Adler32Generator.h"
#include "TextColor.h"
#include "URI.h"
#include "FileInfo.h"

Controller::Controller() noexcept
{
}

Controller::Controller(const std::string& HTMLFileURL) noexcept :
    _HTMLFileURL(HTMLFileURL)
{
}

void Controller::SetHTMLFileURL(const std::string& value) noexcept
{
    _HTMLFileURL = value;
}

std::string Controller::GetHTMLFileURL() const noexcept
{
    return _HTMLFileURL;
}

FileInfoContainerShp Controller::Execute() throw (std::runtime_error, std::invalid_argument)
{
    FileInfoContainerShp resultContainer =
            std::make_shared<FileInfoContainer>();
    // reset previous result
    _result = resultContainer;
    /// source HTML file URL validation
    URI rootURI(_HTMLFileURL);
    if(!rootURI.IsValid())
    {
        throw std::invalid_argument("HTML file URL is invalid");
    }
    /// download source HTML file content as string
    EasyCurl::DownloaderString downloaderRoot;
    downloaderRoot.SetURL(rootURI.GetURL());
    try
    {
        downloaderRoot();
    }
    catch(const std::runtime_error& exception)
    {
        // pass current exception to the top
        throw;
    }
    HTMLParser parcer;
    std::vector<EasyCurl::DownloaderStringShp> downloaders;
    EasyCurl::DownloaderParallel downloaderParallel;
    /// parse download source HTML file content and loop for each parced link
    for(std::string hrefValue : parcer.Parse(downloaderRoot.GetContent(),
                                             downloaderRoot.GetURL()))
    {
        EasyCurl::DownloaderStringShp downloaderSimple =
                std::make_shared<EasyCurl::DownloaderString>();
        downloaderSimple->SetURL(hrefValue);
        downloaders.push_back(downloaderSimple);
        /**
         * simple downloader pass to parallel downloader
         * for download all files in parallel
         */
        downloaderParallel.AddDownloader(downloaderSimple.get());
    }
    /// execute download all files in parallel
    try
    {
        downloaderParallel();
    }
    catch(const std::runtime_error& exception)
    {
        // pass current exception to the top
        throw;
    }

    /**
    * 0: file absolute URL
    * 1: file content adler32 hash
    * 2: file size in bytes
    */
    std::map<size_t, FileInfo> downloadedFiles;
    for(EasyCurl::DownloaderStringShp simpleDownloader : downloaders)
    {
        const std::string contentRefFile = simpleDownloader->GetContent();
        // collect files information for output
        resultContainer->Add(FileInfo(simpleDownloader->GetURL(),
                                      contentRefFile.size(),
                                      /// generate adler32 hash of file content
                                      Adler32Generator::Generate(contentRefFile)));
    }
    return resultContainer;
}

FileInfoContainerShp Controller::GetResult() const
{
    return _result;
}
