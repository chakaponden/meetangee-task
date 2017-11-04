# bash
# install google gumbo parcer from git sources
rm ./gumbo-parser -R -f
git clone https://github.com/google/gumbo-parser
cd ./gumbo-parser
./autogen.sh --quiet
./configure --quiet
make --silent
sudo make install --silent
cd ..
rm ./gumbo-parser -R