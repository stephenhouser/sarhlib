
https://stackoverflow.com/questions/53111082/how-to-install-clang-tidy-on-macos

```bash
brew install clang-format
```



Use this one:
Striaght old cmake
https://github.com/ttroy50/cmake-examples/blob/master/07-package-management/C-external-project-add/README.adoc




Using workflows
https://github.com/msvetkin/cpp-project-template/tree/main


```
# Apple silicon w/gcc
cmake --workflow --preset=arm64-darwin-gcc

# Apple silicon w/clang
cmake --workflow --preset=arm64-darwin-clang

```