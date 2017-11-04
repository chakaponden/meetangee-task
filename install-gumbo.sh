# bash
# install google gumbo parcer from git sources
git clone https://github.com/google/gumbo-parser
cd ./gumbo-parser
./autogen.sh
./configure
make
sudo make install
cd ..
rm ./gumbo-parser -R