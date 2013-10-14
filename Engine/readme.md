SquareCubed - InDev 0.2
=======================
SquareCubed is a 2D multiplayer top-down indie game and game engine written in C++ on top of OpenGL, based on RakNet for networking. If you find this file locally or part of another project, go to the official [github page](http://laylconway.github.io/SquareCubed/) for the latest version of this project. If SquareCubed is used in a way that doesn't comply with the licenses available, please notify the maintainer.

Features
--------
This engine is currently "InDev" meaning we're still working hard on even getting the basic structure in the game engine. We're still so early in development that even sound isn't a priority for us currently. We'll try to keep people up to date on what we're working on in the Issue/Task tracker on github. The current list of features supported by our engine is:
- Tile based map rendering
- Client/Server based player position synchronization
- Agent-based NPC/Player rendering

Run Requirements
----------------
No minimum required system specs yet. Binaries should run on any Windows 7 machine with [Visual C++ 2013 Redistributable](http://www.microsoft.com/en-us/download/details.aspx?id=40007) installed. (x86 for 32-bit binaries, x64 for 64-bit binaries)

Build Requirements
------------------
- C++11 compiler (Any version of VC++ 2012 won't work. We use VC++ 2013 RC, Express works as well)
- RakNet Hobby License (Library not distributed with the repository, read the README.md in libraries for more information)

Included Dependencies
---------------------
- GLFW - An OpenGL library
- GLEW - The OpenGL Extension Wrangler Library
- DevIL - A full featured cross-platform Image Library
- Google Test - Google C++ Testing Framework

Licenses
--------
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a copy of this license, visit (this page)[http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US]. For commercial licenses contact the project maintainer.