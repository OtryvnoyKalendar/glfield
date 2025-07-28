deps_pkges=(gcc ninja cmake vcpkg python)
sudo pacman -S --needed --noconfirm "${deps_pkges[@]}"
