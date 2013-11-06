TARGET = puppeteerpp
TEMPLATE = app
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt core

CONFIG(debug, debug|release) {
DESTDIR = bin/debug/
}

CONFIG(release, debug|release) {
DESTDIR = bin/release/
}


RESOURCES =


SOURCES += main.cpp \
	../Classes/AppDelegate.cpp \
	../Classes/HelloWorldScene.cpp

HEADERS += \
	../Classes/AppDelegate.h \
	../Classes/HelloWorldScene.h

# set a variable for config cocos2dx modules
# --------------------------------------------
# the simple audio engine
COCOS2D-X_MODULES += CocosDenshion
# some extensions eg: CCTableView
# COCOS2D-X_MODULES += extensions
# the box2d physics engine
# COCOS2D-X_MODULES += box2d
# the chipmunk physics engine
# COCOS2D-X_MODULES += chipmunk
# --------------------------------------------

COCOS2DX_ROOT = $$system(echo $COCOS2DX_ROOT)

# set include path and depend path
COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/cocos2dx \
	$$COCOS2DX_ROOT/cocos2dx/include \
	$$COCOS2DX_ROOT/cocos2dx/cocoa \
	$$COCOS2DX_ROOT/cocos2dx/kazmath/include \
	$$COCOS2DX_ROOT/cocos2dx/platform

contains(COCOS2D-X_MODULES,CocosDenshion) {
	COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/CocosDenshion/include
}

contains(COCOS2D-X_MODULES,extensions) {
	COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/extensions
}

contains(COCOS2D-X_MODULES,box2d) {
	COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/external
}

contains(COCOS2D-X_MODULES,chipmunk) {
	COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/external/chipmunk/include/chipmunk
}

#set the platform depended include and depend path
unix:!macx {
	DEFINES += LINUX

	COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/cocos2dx/platform/linux \
		$$COCOS2DX_ROOT/cocos2dx/platform/third_party/linux/libpng \
		$$COCOS2DX_ROOT/cocos2dx/platform/third_party/linux/libjpeg \
		$$COCOS2DX_ROOT/cocos2dx/platform/third_party/linux/libtiff/include \
		$$COCOS2DX_ROOT/cocos2dx/platform/third_party/linux/libwebp

	LBITS = $$system(getconf LONG_BIT)

		contains(LBITS,64) {
		COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/platform/third_party/linux/include64
		STATICLIBS_DIR += $$COCOS2DX_ROOT/cocos2dx/platform/third_party/linux/libraries/lib64
		contains(COCOS2D-X_MODULES,CocosDenshion) {
			SHAREDLIBS_DIR += $$COCOS2DX_ROOT/CocosDenshion/third_party/fmod/lib64/api/lib
			SHAREDLIBS += -L$$SHAREDLIBS_DIR -lfmodex64
		}

	} else {
		COCOS_INCLUDE_DEPEND_PATH += $$COCOS2DX_ROOT/platform/third_party/linux
		STATICLIBS_DIR += $$COCOS2DX_ROOT/cocos2dx/platform/third_party/linux/libraries
		contains(COCOS2D-X_MODULES,CocosDenshion) {
			SHAREDLIBS_DIR += $$COCOS2DX_ROOT/CocosDenshion/third_party/fmod/api/lib
			SHAREDLIBS += -L$$SHAREDLIBS_DIR -lfmodex
		}
	}

	STATICLIBS += $$STATICLIBS_DIR/libfreetype.a \
		$$STATICLIBS_DIR/libpng.a \
		$$STATICLIBS_DIR/libjpeg.a \
		$$STATICLIBS_DIR/libtiff.a \
		$$STATICLIBS_DIR/libwebp.a
		#$$STATICLIBS_DIR/libcurl.a \

	contains(CONFIG,debug) {
		DEFINES += DEBUG

		SHAREDLIBS += -L$$COCOS2DX_ROOT/lib/linux/debug -Wl,-rpath,$$COCOS2DX_ROOT/lib/linux/debug

		contains(COCOS2D-X_MODULES,box2d) {
			STATICLIBS += $$COCOS2DX_ROOT/lib/linux/debug/libbox2d.a
		}
		contains(COCOS2D-X_MODULES,chipmunk) {
			STATICLIBS += $$COCOS2DX_ROOT/lib/linux/debug/libchipmunk.a
		}
	} else {
		DEFINES += NDEBUG

		SHAREDLIBS += -L$$COCOS2DX_ROOT/lib/linux/release -Wl,-rpath,$$COCOS2DX_ROOT/lib/linux/release

		contains(COCOS2D-X_MODULES,box2d) {
			STATICLIBS += $$COCOS2DX_ROOT/lib/linux/release/libbox2d.a
		}
		contains(COCOS2D-X_MODULES,chipmunk) {
			STATICLIBS += $$COCOS2DX_ROOT/lib/linux/release/libchipmunk.a
		}
	}

	SHAREDLIBS += -lcocos2d -lrt -lz
	contains(COCOS2D-X_MODULES,CocosDenshion) {
		SHAREDLIBS += -lcocosdenshion
	}

	SHAREDLIBS += -lglfw -lGL
	SHAREDLIBS += -Wl,-rpath,$${SHAREDLIBS_DIR}

	SHAREDLIBS += -Wl,-rpath,$$STATICLIBS_DIR

	# if need curl , open this
	#SHAREDLIBS += -lcurl

	LIBS +=	$${STATICLIBS}
	LIBS += $${SHAREDLIBS}
}

INCLUDEPATH += $${COCOS_INCLUDE_DEPEND_PATH}
DEPENDPATH += $${COCOS_INCLUDE_DEPEND_PATH}

QMAKE_CXXFLAGS += -std=gnu++0x
