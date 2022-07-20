# A LLVM Pass Plugin for NDK on macOS

You should follow these instructions to setup a LLVM Plugin environment for NDK

1. Download ZIP version NDK for macOS. Just simply modify the URL in NDK official website. e.g. to download ndk-r25, we
   could use this url `https://dl.google.com/android/repository/android-ndk-r25-darwin.zip`. DO NOT use the DMG version
   of NDK, since you cannot sign your plugin file with Google's certificate.
2. Check downloaded Clang version by `clang --version`. You may find these string `Android (8490178, based on r450784d)`
   . Remember the version `r450784d`.
3. Download the prebuilt toolchains on AOSP. The repository of toolchain is
   on `https://android.googlesource.com/platform/prebuilts/clang/host/darwin-x86`. We must checkout the branch to the
   correct one. e.g. for ndk-25, we should use branch `ndk-r25-release`. Recall the version above, we are able to find a
   directory with same name. We can either download the tgz from website or clone the whole repository with branch.
4. Copy `bin/clang` of AOSP toolchain to corresponding NDK path (maybe toolchains/llvm/prebuilt/darwin-x86_64/bin). This
   is important since the Clang of NDK version is missing so much symbols due to a bug of strip on
   mac ([check here](https://issuetracker.google.com/issues/143160164)).
5. Now the environment for NDK Plugin is almost done. Next we should give CMAKE a ENV VARIABLES `LLVM_HOME` equal to
   AOSP toolchain location.
6. Try `cmake -S . -B build && cmake --build build`, the plugin is at `build/NdkSamplePass/libNdkSamplePass.so`.
7. Add these flag to your NDK project: `LOCAL_CFLAGS += -fpass-plugin=/path/to/lib.so`.