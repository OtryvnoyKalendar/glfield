deps_pkges=(gcc ninja cmake vcpkg python base-devel curl zip unzip tar git)
sudo pacman -S --needed --noconfirm "${deps_pkges[@]}"
