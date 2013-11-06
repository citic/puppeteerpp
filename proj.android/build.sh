#!/bin/bash

# Compile Cocos2d-x for Android
./build_native.sh

android update project -p ./ --target 1
android update project -p ${COCOS2DX_ROOT}/cocos2dx/platform/android/java --target 1
ant debug #install
#cd bin
#adb install Aquita-debug.apk
