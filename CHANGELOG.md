# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [Todo]
- remove dependence from [cpp-netlib](https://github.com/cpp-netlib): create absolute URL and source URL validation without usage [boost::network::uri](https://github.com/cpp-netlib/uri/blob/master/src/uri.cpp)
- thread safe HTTPDownloader
- download all files in parallel
- OOP code reuse

## [1.1.0] - 2017-11-02
### Added
- user must specify URI scheme manually
- OOP code reuse for Downloader classes

## [1.0.0] - 2017-10-31
### Added
- download files using [curl](https://github.com/curl/curl)
- parce HTML structure using [google gumbo](https://github.com/google/gumbo-parser) + [gumbo easy API](https://github.com/RPG-18/EasyGumbo)
- generate adler32 hash using [zlib](https://github.com/madler/zlib)
- create absolute URL using [boost::network::uri](https://github.com/cpp-netlib/uri/blob/master/src/uri.cpp) from [cpp-netlib](https://github.com/cpp-netlib)
- customize terminal text color