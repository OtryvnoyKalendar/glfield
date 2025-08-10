deps_pkges=(gcc ninja-build cmake python3 build-essential pkg-config curl zip unzip tar git)
sudo apt update
sudo apt install -y "${deps_pkges[@]}"

source vcpkg-from-source.sh
