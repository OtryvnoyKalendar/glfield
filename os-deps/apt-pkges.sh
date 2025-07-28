deps_pkges=(gcc ninja-build cmake python3 git build-essential pkg-config zip unzip)
sudo apt update
sudo apt install -y "${deps_pkges[@]}"

source vcpkg-from-source.sh
