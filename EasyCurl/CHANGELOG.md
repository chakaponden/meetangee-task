# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [Todo]
- download all files in parallel using I/O event notification facility [epool()](https://linux.die.net/man/4/epoll)

## [1.1.1] - 2017-11-19
### Fixed
- possible crashes, when curl is not initialized - handle by check and throw exceptions

## [1.1.0] - 2017-11-11
### Changed
- class DownloaderParallel using POSIX select call() renamed to DownloaderParallelSelect class

### Add
- parallel download using curl_multi_wait(): DownloaderParallel class (has no limitation of 1024 maximum downloads at once)

### Fixed
- remove limitation of 1024 maximum downloads at once in old DownloaderParallel class, that used POSIX select call() - use new DownloaderParallel implementation based on curl_multi_wait()

## [1.0.0] - 2017-10-08
### Added
- download files using [curl](https://github.com/curl/curl)
- download all files in parallel using [curl](https://github.com/curl/curl) and synchronous I/O multiplexing [select()](https://linux.die.net/man/2/select)
- OOP code reuse for Downloader classes
- doxygen documentation generation