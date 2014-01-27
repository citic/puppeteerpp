
Setting the development environment
===================================

Puppeteer++ is a multi-platform video game built over Cocos2d-x version 3. This document explains how to setup the development environment on each supported platform.


All platforms
-------------

1. Download the `Cocos2d-x-x.y.z.zip` from official web site.

2. Extract it to any folder of your system. *Advice*: On Linux/Mac change root folder permissions to 755.

3. Set `COCOS2DX_ROOT` environment variable to point the folder where Cocos2d-x was extracted in step 1. Make this variable permanent in your `~/.profile` for Linux/Mac or "System | Properties | Advanced |Environment variables" for Microsoft Windows.

4. Compile the Cocos2d-x library. On Linux call `./make-all-linux-project.sh`. On Windows open `cocos2d-win32.vc2012.sln` and compile anything. On Mac OS X do nothing (Cocos2d-x is compiled each time the game is compiled!).

5. Log-out and log-in again in your system to make the environment variables available in Linux/Mac.

6. XCode on Mac OS X requires the Cocos2d-x folder is inside the Puppeteer++ root folder. Just create a symbolic link in the Puppeteer++ root folder called `cocos2dx` pointing to the real directory where Cocos2d-x is "installed", that is, a symbolic link to the content of the `$COCOS2DX_ROOT` environment variable. Create another symbolic link called `cocos2d` to the same folder.

The following script pseudo-code briefs these steps for Linux:

	cd <any-folder-of-your-file-system>
	wget <url-to-cocos2d-x-x.y.z.zip>
	unzip <cocos2d-x-x.y.z.zip>
	rm -rf __MACOSX
	chmod 755 <cocos2d-x-x.y.z>/
	cd <cocos2d-x-x.y.z>/
	./make-all-linux-project.sh
	echo export COCOS2D_ROOT=`pwd` >> $HOME/.profile
	echo export COCOS2DX_ROOT=`pwd` >> $HOME/.profile
	# remember log-out and log-in


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

