# mere-xdg-lib
`mere-xdg` is a tiny library that exposes api to grab information based on xdg specifications.

A library that exposes api to grab informaiton according to xdg specifications. As we need cache, data, icon, themes directoty almost all the applications, so we bundled it in a common lib to share among the applications. 

In addition of exposing directories, it also provides a way to traverse directories and parse desktop entry(.desktop) files.

**specifications**
- [Desktop Entry Specification](https://specifications.freedesktop.org/)
- [XDG Base Directory Specification](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html)
- [Desktop Application Autostart Specification](https://specifications.freedesktop.org/autostart-spec/autostart-spec-latest.html)

### requires
`mere-xdg` requires following componnets
- C++11 
- QtCore
- mere-utils

### required
`mere-utils` is required by following app, utility and libaries,
- [mere-xdg](https://github.com/merelabs/mere-xdg-lib)
- [mere-finder-lib](https://github.com/merelabs/mere-finder-lib)
- [mere-launch](https://github.com/merelabs/mere-launch)

### build ##
```
$ git clone https://github.com/merelabs/mere-utils-lib.git
$ qmake
$ make 
$ make release
```
### install ##
```
$ make install
```
### support
If you find a bug, or have a feature suggestion, please [log an issue](https://github.com/merelabs/mere-xdg/issues). If you'd like to
contribute, please read [How to Contribute](CONTRIBUTING.md).

### license
All the code in this repository is licensed under a [BSD-2-Clause License](LICENSE).
