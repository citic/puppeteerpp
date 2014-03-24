
Setting the development environment
===================================

Puppeteer++ is a multi-platform video game built over Cocos2d-x version 3. This document explains how to setup the development environment on each supported platform.


All platforms
-------------

1. Download the `Cocos2d-x-x.y.z.zip` from official web site to the root directory of Puppeteer++. Extract it and rename the folder `cocos2d-x-x.y.z/` to `cocos2d/`. If you want to share the Cocos2d-x library with other games extracting the zip file to other place of your system, just make a symbolic link named `cocos2d` in the root of Puppeteer++ pointing to the directory where Cocos2d-x is. *Note*: On Linux/Mac you may require change root folder permissions to 755.

2. <del>Set `COCOS2DX_ROOT` environment variable to point the folder where Cocos2d-x was extracted in step 1. Make this variable permanent in your `~/.profile` for Linux/Mac or "System | Properties | Advanced |Environment variables" for Microsoft Windows. Log-out and log-in again in your system to make the environment variables available in Linux/Mac</del>.

3. On Linux install Cocos2d-x required libraries calling `build/install-deps-linux.sh`. On Windows open `cocos2d-win32.vc2012.sln` and compile anything. On Mac OS X do nothing, Cocos2d-x is compiled each time your game is compiled.

The following script pseudo-code briefs these steps for Linux:

	cd <any-folder-of-your-file-system>
	wget <url-to-cocos2d-x-x.y.z.zip>
	unzip <cocos2d-x-x.y.z.zip>
	#rm -rf __MACOSX
	#chmod 755 <cocos2d-x-x.y.z>/
	cd <cocos2d-x-x.y.z>/build
	sudo aptitude update
	sudo ./install-deps-linux.sh
	#echo export COCOS2D_ROOT=`pwd` >> $HOME/.profile
	#echo export COCOS2DX_ROOT=`pwd` >> $HOME/.profile
	# remember log-out and log-in


Linux
-----
In order to build Puppeteer++, go to the folder where the game is. Create a `build` directory. Create makefiles, compile them and run the game:

	cd <puppeteerpp>
	mkdir -p build
	cd build
	cmake ..
	make -j4
	
	bin/MyGame


Android
-------

Download [Android SDK](http://developer.android.com/sdk/index.html) and extract it to any folder of your hard drive. Set an environment variable called `ANDROID_SDK_ROOT` to that folder.

	wget <url-adt-bundle-version>
	unzip <adt-bundle-version>
	cd adt-bundle-*
	echo export ANDROID_SDK_ROOT=`pwd` >> $HOME/.profile
	cd ..


Download [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) and extract it to any folder of your hard drive. Set two environment variables: `ANDROID_NDK_ROOT` and `NDK_ROOT`, both to that folder. <!--- Note: it seems Cocos2d-x is able to work only with NDK v8 or older, get the files for [Mac OS X 64bits](http://dl.google.com/android/ndk/android-ndk-r8e-darwin-x86_64.tar.bz2), and [Linux/Windows](http://mirror.thebasementserver.com/soft/android-ndk/r8/). -->

	wget <url-android-ndk-r9>
	tar -xjf android-ndk-r9-*
	cd android-ndk-r9
	echo export ANDROID_NDK_ROOT=`pwd` >> $HOME/.profile
	echo export NDK_ROOT=`pwd` >> $HOME/.profile
	cd ..


Include both, NDK and SDK installation folders in your PATH environment variable:

	echo 'export PATH=$PATH:$ANDROID_NDK_ROOT:$ANDROID_SDK_ROOT' >> $HOME/.profile

You also require [Apache Ant](http://ant.apache.org/). If you already have installed [Mac Ports](http://www.macports.org/):

	sudo port install apache-ant

