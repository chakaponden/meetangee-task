#!/bin/bash
# install google gumbo parcer from git sources
git clone https://github.com/google/gumbo-parser
cd ./gumbo-parser
./autogen.sh --quiet
./configure --quiet
make --silent
sudo make install --silent
cd ..
rm -f ./gumbo-parser -R