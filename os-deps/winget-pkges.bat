$deps_pkges = @(
    "MSYS2.Mingw-w64-x86_64-gcc",
    "Ninja.Msft",
    "Kitware.CMake",
    "Microsoft.Vcpkg",
    "Python.Python.3"
)

foreach ($pkg in $deps_pkges) {
    winget install --id=$pkg --accept-source-agreements --accept-package-agreements
}
