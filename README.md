# CodeAndTheGang

> Computer scientists team aimed to build video games

## Build Android application from repository

### Pull project
Pull one of the above project and build it using the * **Prerequisites** * section

###### Space game example
This project is based on the [space game cocos2d-x tutorial](http://www.raywenderlich.com/33752/cocos2d-x-tutorial-for-ios-and-android-space-game)

###### Base project
It's a clean HelloWorld project for Android

To create a new cocos2d-x project for Android, you can simply copy this [base project](https://github.com/Drusy/CodeAndTheGang/tree/master/BaseProject)

### Prerequisites
Once you have downloaded some cocos2d-x project from this repository, you will have to tune it a bit to compile the sources on your devices.

###### Windows users : Install cygwin
+ Download [Cygwin](http://cygwin.com/install.html)
+ Install cygwin adding the  `make` component
+ Add cygwin bin dir (`C:\cygwin64\bin\`) to your path
+ Add `GNUMAKE` environment variable on windows and set it to `/cygdrive/c/cygwin64/bin/make.exe` or equivalent

###### Import your android project
In Eclipse (from [Android ADT Bundle](http://developer.android.com/sdk/index.html)), use `File > new > Android > Android Project from Existing Code` option

###### Add `build_native.sh`
Add a `build_native.sh` file to your `proj.android` folder. An example file is provided in the [prerequisites folder](https://github.com/Drusy/CodeAndTheGang/tree/master/Prerequisites) of the git repository.

+ Copy this `build_native_example.sh` file in your `proj.android` folder and rename it into `build_native.sh`
+ Change the value of the `NDK_ROOT` variable to your Android NDK path
+ Change the value of the `COCOS2DX_ROOT` variable to your cocos2d-x installation dir

**If you are under Windows, use `/cygdrive/c/` instead of `C:/`**

**For example : `NDK_ROOT="/cygdrive/c/android/ndk"`**

###### Replace `.project`
+ Copy this `example.project` file in your `proj.android` folder and rename it into `.project`
+ Change the `<name>....</name>` tag at the top of the file to fit your project name
+ Change the associated `<location>...</location>` tags at the bottom of the file corresponding to your project and your cocos2d-x path

### Compile
+ Clean your project (Project > Clean...)
+ Refresh your project (Riglt Click > Refresh)
+ Build your project

### Potential problem (Windows / on build)
###### Error message
"make: *** Android NDK: Aborting. . Stop" 
or 
"build-binary.mk:386: *** target pattern contains no '%'. Stop."
###### Origin
The program `make.exe` of Cygwin is outdated. This can occur with the Cygwin installer.
###### Solution
to get the latest version of the `make.exe`, download the program at http://geant4.cern.ch/support/extras/cygwin/make.exe and paste it into your Cygwin folder (`/cygdrive/c/cygwin64/bin/make.exe` or equivalent).

## Create a new project from scratch with cocos2d-x

### Download needed components

###### Cocos2d-x
Download [cocos2d-x v2.2](http://cdn.cocos2d-x.org/cocos2d-x-2.2.zip)

###### Download Android Bundle
Download the [Android ADT Bundle](http://developer.android.com/sdk/index.html)

###### Download Android NDK
Download the [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) to build C++ application on your Android device

###### Windows components
If you are running on Windows, you will probably need [Cygwin](http://cygwin.com/install.html) to run shell scripts

### Create a new project
To create a new project on various platforms, launch the cocos2d-x Python script :

    $COCOS2DX/tools/project-creator/create_project.py

Use sample :

    $COCOS2DX/tools/project-creator/create_project.py -project ProjectName -package com.MyCompany.MyGame -language cpp
