-BLAM-
======

This is the beginning of a Lua scripted OpenGL-based 2D game engine I started
working on in my spare time in 2009.  The demonstration Lua program in it is
the start of a psychology/vision test program for which I used the engine in
some of my graduate research; the project was to test whether people could tell
the difference between two scenes presented briefly several seconds apart in the
presence of various distractions, and it was to be paired with an early VR
goggles system.  The funding for the project was terminated, so it only got as
far as a technology demonstration.

The engine is for Mac OS X, and I've updated the project file and a few source
files to fix incompatibilities with the latest version of XCode (previously, it
ran on XCode 3.1 and Mac OS X 10.5/10.6, so there were some updates needed).
The engine builds and runs with XCode 7 and Mac OS 10.11, at least; I haven't
tested the build product on previous versions yet.

The sprites for the demo application were borrowed (with permission) from Eric
Ruth, a friend of mine with considerable 2D graphic design and game development
prowess.  They were standins for the real icons that would have been used in the
eventual study.



Notes
=====

This engine was definitely in its infancy when it was abandoned (mainly due to
personal time constraints), but I could see reviving it some time if I ever have
the personal time to write games again.  Integrating the Lua engine was a fun
treat; Lua integrates very nicely into C and C++ code, executes reasonably fast,
and doesn't take up a lot of memory (all of which are reasons it's become a
popular embedded scripting language).

Current state
-------------

The engine as it stands can render sprites at various locations (for example,
the cursor is a sprite which tracks the location of the mouse when a mouse event
comes in) and rotations under the control of the Lua game script.  Events are
passed into the Lua environment through method calls to a Lua event type handler
table.

The code runs under OS X using a Cocoa shell to perform the OS specific bits
(e.g. application startup, event handling, OpenGL context setup) using the
standard Objective-C routines (actually, it's using Objective-C++, but only to
bridge to the cross-platform game engine logic).  The C++-based game engine
logic should be reasonably portable to most platforms as long as the appropriate
shell is developed in the native platform's language of choice (which must be
able to instantiate C++ objects and call their methods, a la Objective-C++).


Future work
-----------

Several improvements could be made in the short term to help things run a bit
faster or more intuitively:

- The Lua code is called for every frame, which is a bit excessive and probably
  incurs a performance hit (though it does give a lot of control to the script).
  The better approach would be to hand control to the Lua environment when the
  script indicated it was necessary and use native code to handle e.g. frame
  interpolation, timer queues, etc. as most modern game engines do.

- The OS abstraction would probably work well enough to port to Linux without
  a lot of trouble, but Windows would take some more work; there are enough
  embedded UNIXisms in the C++ code that it would take at least a bit of
  cleanup to compile and run.

- The Lua code isn't very well commented, since it was written hastily to create
  the demo app for the research project.

- No unit tests or anything of the like (in fairness, unit testing graphics code
  is actually pretty challenging).

- Timers should operate on priority queues, probably with a native
  implementation instead of checking every frame in Lua to see if a count had
  been reached.

- All the cool kids are programming in Swift these days for OS X, I should check
  it out.  I still like Objective-C for some reason.
