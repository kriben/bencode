Bencode parser
==============

Bencode parser in c++. Bencode is used in torrent files. See http://en.wikipedia.org/wiki/Bencode for details.

Currently only decoding, and still a very much a work in progress.


Inspired by http://effbot.org/zone/bencode.htm

Uses boost: http://www.boost.org


Licensed under the FreeBSD License (aka the "Simplified BSD License"). See the LICENSE file for details.

Author: Kristian Bendiksen <kristian.bendiksen@gmail.com>


Build instructions
==================

On Ubuntu 10.10:

Building the library:
1: Install Scons build system (http://scons.org):
sudo apt-get install scons

2: Install boost (http://boost.org):
sudo apt-get install libboost-regex1.42.0-dev
(apt-get will take care of the dependencies).

3: Build the library:
scons libbencode.so

Building the tests:
1: Install cppunit:
sudo apt-get install libcppunit-dev

2: Build the tests:
scons tester
