![Possible NinjaPilot Logo?](https://pbs.twimg.com/media/COadvoiUEAALEe-.png)
(Image credits to: velezvelez)

What is NinjaPilot all about? 
-----------------------------

NinjaPilot is a slimed down OpenPilot release featuring ONLY CopterControl based (OPCC/CC3D/Atom) support. 
The code is actually based on the last commit of 15.02 before the CC3D was disabled / depreciated in the 
codebase. The original OpenPilot git hash was: fe04a9b63c4b62fbf50647cfffc22095ae8be86d  

FlyingF4, Revo, Revo Nano, and anything NOT CopterControl, CC3D, or Atom are explicitly NOT supported. We 
will be working to bring the code up to 15.05.x We've had enough people ask us about flying CC3D that we 
decided to resurrect the code before it full on died. We have zero interest in supporting a navigation 
capable codebase. 

OPLink code is included for connectivity purposes. 

Camera Stabilization has been removed from the build. 

NinjaPilot is sponsored by Ratemode.ninja - http://ratemode.ninja/preview/
a division of Sasquatch Labs / Team Sasquatch - http://sasquatchlabs.org

Bear with us as we make the *branding* switch, and pull out all the legacy "OpenPilot" logos and references. 

ALL credits go to the legacy OpenPilot team. 

Note: ALL code changes are largely untested. No Flight Test Team work has occurred, nor regression testing. 
Fly at your own risk. 

SLA (Service Level Agreement): There isn't one! You are only guaranteed to have fun, and that isn't even 
*really* guaranteed either FWIW... (for the time being *I* am doing this for my own fun, and edification. 
Things will be done at my own pace, and on MY schedule). 

You will NOT find the guarantee fairy here, don't look. 
https://www.youtube.com/watch?v=a5dpBpaFiMo


What *was* OpenPilot all about?
----------------------------

The project aimed at implementing the best features of all existing similar systems developed by
enthusiasts and combines them into a single, easy-to-use software/hardware package. The ease-of-use
in this case does not imply functional simplicity or compromises. There were no rigidly defined
constraints and settings, but a full-fledged programming language configuration loaded via a
Ground Control Station and other advanced features. OpenPilot was developed as a powerful platform
for all types of vehicles.

It was a non-profit project of the OpenPilot Foundation
--------------------------------------------------------

OpenPilot was a project using only volunteer personnel who have donated enormous amounts of time, money
and effort. Please respect the people that were part of the project and their generosity. OpenPilot
was funded entirely at the expense of those who spend their time and money in the development of the
public project which helped it grow. Giving complete and correct references to all their work is not
only a legal requirement of the CC-BY-SA license, but also simple respect for their work. The people
who create the project, really deserve it for their very hard work.

The OpenPilot project web sites
-------------------------------

The project provided a feature-rich development and collaboration environment using advanced tools such
as GCC compilers, git, Atlassian JIRA, Confluence, FishEye, Crucible, Bamboo, Crowd, forums and blogs.

Main project web site:	http://www.openpilot.org/
Project forums:		http://forums.openpilot.org/
Wiki, docs and manuals:	http://wiki.openpilot.org/ (defunct)
Bug and issue tracker:	http://progress.openpilot.org/ (defunct)
Source code repository:	http://git.openpilot.org/ (defunct)
Crucible code reviews:	http://reviews.openpilot.org/cru (defunct)
Project build server:	http://bamboo.openpilot.org/ (defunct)
Community blogs:	http://forums.openpilot.org/blogs/ 
Software downloads:	https://www.openpilot.org/download/

How to build from source?
-------------------------

make all_sdk_install
make all

The project supported Windows, Linux and Mac OS X platforms as well as Android.
Formerly you could check the wiki for more details: http://wiki.openpilot.org/display/Doc/OpenPilot+Developer+Manual (defunct)
