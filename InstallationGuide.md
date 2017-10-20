# A brief description of how to install the plugin.

We have tried to keep it as simple as possible. So here it is!

First of all, be sure that you have downloaded and installed [Pidgin](http://pidgin.im) and [Adobe Flash Player](http://get.adobe.com/flashplayer/).

## Installation from source code

### Requirements

You will need these packages to be installed before compiling the plugin on your machine:

  * pidgin-dev
  * libglib2.0-dev
  * libcurl3-dev
  * libwebkit-dev >= 1.1.12

On Ubuntu Karmic you may type the following in a terminal to install the dependencies...
```
sudo apt-get install pidgin-dev libglib2.0-dev libcurl3-dev libwebkit-dev
```

On other Ubuntu versions, if you don't see the right version of the libwebkit-dev package in the repositories, you can find it [here](https://launchpad.net/~webkit-team/+archive/ppa). This page will tell you how to install it on your machine in just a few steps:

  * Write in a terminal...
```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 2D9A3C5B
```
  * Open _System > Administration > Software Sources_.
  * Click on the _Third-Party Software_ tab.
  * Click on the _Add_ button.
  * Paste the line below and click on the _Add Source_ button.
```
deb http://ppa.launchpad.net/webkit-team/ppa/ubuntu YOUR_UBUNTU_VERSION main
```
where `YOUR_UBUNTU_VERSION` is `jaunty` for Jaunty (9.04), `intrepid` for Intrepid (8.10) or `hardy` for Hardy (8.04). Then click _Close_.
  * Open _System > Administration > Synaptic Package Manager_, press the _Reload_ button and get the latest version of the libwebkit-dev package.

### Compilation

Extract the archive you have downloaded. The compilation should be easy like...

```
./configure
make
make install
```

Restart Pidgin, activate Pidgin Embedded Video under the _"Plugins"_ menu and have fun! ;)

As a side note, you can uninstall the plugin with...
```
make uninstall
```
