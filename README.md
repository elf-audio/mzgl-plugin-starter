# mzgl-plugin-starter

template for mzgl based audio plugins

To use, clone it, then also clone mzgl, and at the top of the CMakeLists.txt, change the line

```
set(MZGL_ROOT "../koala/lib/mzgl")
```

to point to the mzgl folder you created.

to build:

```
cmake -Bbuild -GXcode
cmake --build build --config Release

```
Note that you need xcode to build - you can actually do it with CLion if you click "Debug" or "Release" dropdown in the 
title bar of CLion, then "Edit CMake profiles" and set the generator to "Xcode". That should embed the framework and do 
the signing
