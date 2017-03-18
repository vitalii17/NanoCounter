# NanoCounter
The Qt-based small application for Symbian that allow to count the number of clicks. 
If you perform many of monotonous work it help you to count number of actions.

## Features:
* Counting by taping to the screen and/or pressing volume keys.
* Always keeps backlight is on if you need.
* Saves all settings including latest counter value when you close application.
* Works from Symbian 9.4 to Belle FP2.

## Tools to build
* Qt Creator 2.4.1 or earlier.
* Latest Symbian toolchain.
* Qt 4.7.3 if you want to build from Symbian 9.4.
* Qt 4.7.4 if you want to build for only later then Symbian 9.4.
* SISContents to add icon to an application package. Only for Qt 4.7.3!

## Known issues
* If you build with Qt 4.7.3 you should to add application icon manually because it works incorrect.
* Built-in QtSDK developer certificate is valid to 2019 year. I use SISContents self-signed certificate.

All tools without Qt 4.7.3 and SISContents available in the QtSDK 1.2.1. Qt 4.7.3 available in QtSDK 1.1.2.
Link to download all developer resources: https://www.mediafire.com/folder/79jhy594xb3uk/Symbian_Development
