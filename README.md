# child-learn
Learning programs for children

# Clone

```
git clone git@github.com:srogatch/child-learn.git
cd child-learn
git submodule update --init --recursive
```

# Build

```
mkdir build
cd build
cmake ..
cmake --build .
```
On Linux, the executables like `add` and `mul` will be in the `build` directory. On Windows, they will be in the build configuration directory like `build\Debug` or `build\Release`.
