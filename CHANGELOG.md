# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [Todo]
- download all files in parallel using I/O event notification facility [epool()](https://linux.die.net/man/4/epoll)
- coverity scan travis configuration

## [1.5.1] - 2017-11-08
### Fixed
- SonarCloud integration

## [1.5.0] - 2017-11-08
### Changed
- refactoring Gumbo Easy API to EasyGumbo static lib
- refactoring to EasyCurl static lib
- OOP code reuse
- individual namespace for task classes
- migration from error codes to c++ exceptions

### Added
- doxygen documentation generation EasyGumbo lib

## [1.4.0] - 2017-11-07
### Added
- doxygen documentation generation

## [1.3.0] - 2017-11-03
### Changed
- work with URL using [libsoup](https://github.com/GNOME/libsoup) - wrapper [URI](https://github.com/chakaponden/itransition-task/blob/dev/URI.h)

### Removed
- dependence from [cpp-netlib](https://github.com/cpp-netlib/uri)

### Fixed
- invalid absolute URL creation if HTML link value is already absolute URL
- memory leaks with boost::network::uri

## [1.2.0] - 2017-11-03
### Added
- download all files in parallel using [curl](https://github.com/curl/curl) and synchronous I/O multiplexing [select()](https://linux.die.net/man/2/select)

## [1.1.0] - 2017-11-02
### Added
- user must specify URI scheme manually
- OOP code reuse for Downloader classes

## [1.0.0] - 2017-10-31
### Added
- download files using [curl](https://github.com/curl/curl)
- parce HTML structure using [google gumbo](https://github.com/google/gumbo-parser) + [gumbo easy API](https://github.com/RPG-18/EasyGumbo)
- generate adler32 hash using [zlib](https://github.com/madler/zlib)
- create absolute URL using [boost::network::uri](https://github.com/cpp-netlib/uri/blob/master/src/uri.cpp) from [cpp-netlib](https://github.com/cpp-netlib/uri)
- customize terminal text color