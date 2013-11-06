
1. SETTING THE DEVELOPMENT ENVIRONMENT

1.1. All

1. Download the Cocos2d-x-x.y.z.zip from official web site
2. Extract it to any folder of your system
   Optional: On Linux/Mac change permissions to 755
3. Set COCOS2DX_ROOT environment variable to point to the folder where Cocos2d-x was extracted
   Use ~/.profile for Linux/Mac and System|Properties|Advanced|Environment variables for Windows
4. Log-out and log-in again in your system
5. XCode on Mac requires a folder relative to the project, not the COCOS2D_ROOT variable.
   Create a symbolic link in each game folder called cocos2dx to $COCOS2D_ROOT

	wget <url-to-cocos2d-x-x.y.z.zip>
	unzip cocos2d-x-x.y.z.zip
	rm -rf __MACOSX
	chmod 755 cocos2d-x-x.y/
	cd cocos2d-x-x.y.z/
	./make-all-linux-project.sh
	echo export COCOS2D_ROOT=`pwd` >> $HOME/.profile
	echo export COCOS2DX_ROOT=`pwd` >> $HOME/.profile
	# remember log-out and log-in


1.2. Android

1. Download Android SDK and extract it to any folder of your hard drive

	wget <url-adt-bundle-version>
	unzip <adt-bundle-version>
	cd adt-bundle-*
	echo export ANDROID_SDK_ROOT=`pwd` >> $HOME/.profile
	cd ..

2. Download Android NDK and extract it to any folder of your hard drive

	wget <url-android-ndk-r9>
	tar -xjf android-ndk-r9-*
	cd android-ndk-r9
	echo export ANDROID_NDK_ROOT=`pwd` >> $HOME/.profile
	echo export NDK_ROOT=`pwd` >> $HOME/.profile
	cd ..

3. Include those in PATH

	echo 'export PATH=$PATH:$ANDROID_NDK_ROOT:$ANDROID_SDK_ROOT' >> $HOME/.profile



2. CREATING A NEW GAME

	From http://www.cocos2d-x.org/projects/cocos2d-x/wiki/How_to_create_a_multi-platform_project_in_one_command_line

	Run 'python --version' and make sure it is 2.7.3 or newer but 3.x.x

	cd $COCOS2DX_ROOT/tools/project-creator/
	python create_project.py -project MyGame -package com.mycompany.games.mygame -language cpp
	cd $COCOS2DX_ROOT/projects/
	mv MyGame /some/folder/under/version/control
	rm -r proj.no-intendent-platform

	# Mac and iOS projects
	cd proj.mac
	ln -s $COCOS2DX_ROOT cocosd2x
	edit MyGame.xcodeproj
	replace '../../../' by '../cocos2dx/'
	commit to your version control ignoring 'xcuserdata' folders
