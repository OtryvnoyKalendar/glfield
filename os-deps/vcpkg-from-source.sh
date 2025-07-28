# vcpkg installing
git clone https://github.com/Microsoft/vcpkg.git

cd vcpkg
./bootstrap-vcpkg.sh

sudo ln -s $(pwd)/vcpkg /usr/local/bin/vcpkg
