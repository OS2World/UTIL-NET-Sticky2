.*==============================================================*\
.*                                                              *
.* CONFIG.IPF- Information Tag Language file for the screens    *
.*           for Config on the dialog boxes.                    *
.*                                                              *
.*==============================================================*/


.*--------------------------------------------------------------*\
.*  Help for Product information                                *
.*      res = PANEL_CONFIG                                      *
.*--------------------------------------------------------------*/
:h1 res=1200 name=PANEL_CONFIG.Configure Sticky/2
:i1 id=Config.Configure Sticky/2
:p.This dialog is the heart of tailoring Sticky/2 to act the way
you want.  The only option you :hp2.must:ehp2. change from the original install
is your name.  All other options will be self defined,  but from this
dialog, you can change any of the options the way you want.
An alternative is to change the
STICKY2.INI file.
:p.The options that you can change are:
:ul.
:li.:link reftype=hd res=2100 group=10.User:elink.
:li.:link reftype=hd res=2200 group=20.Debug:elink.
:li.:link reftype=hd res=2300 group=30.Setup:elink.
:li.:link reftype=hd res=2400 group=40.Names:elink.
:li.:link reftype=hd res=2500 group=50.Auto Reply:elink.
:eul.
:p.After all changes have been made to the Configure screen you can
can press the :hp1.Done:ehp1. button to save your changes.

.*--------------------------------------------------------------*\
.*  Configure Dialog                                            *
.*      res = PANEL_CONFIG_USER m                               *
.*--------------------------------------------------------------*/
:h1 hide res=2100 name=PANEL_CONFIG_USER.User
:i2 refid=Config.User
:p.The Sticky/2 program requires that a user name be entered.
In this field enter your name.
This is the name that will be sent along with the sticky note you
send.

.*--------------------------------------------------------------*\
.*  Configure Dialog                                            *
.*      res = PANEL_CONFIG_DEBUG                                *
.*--------------------------------------------------------------*/
:h1 hide res=2200 name=PANEL_CONFIG_DEBUG.Debug
:i2 refid=Config.Debug
:p.The Debug screen allows you to turn on/off logging of information.
:dl.
:dt.Log Sent & Received Sticky's to file
:dd.Checking this box will log all Sticky notes you Send or Receive
to the STICKY2.LOG file.  This file will be created in the same directory
where the STICKY2.EXE program is found.  It is an ASCII file that can
be viewed with E, EPM or TEDIT.  The default is ON
:dt.Debug Log
:dd.This option should only be checked when you are having problems with
Sticky/2.  It will log information about the steps it is doing in the program
and the two thread.  It will only log up to 10,000 lines per execution
of the program, after that it
will automatically stop logging. The default if OFF
:note.STICKY2.DBG will be deleted every time the program is run.  So if
you are logging information for debug purposes, make sure you backup
the file before running the program again.
:dt.Sticky Status
:dd.This option if turned on will show send status on the main Sticky/2
screen.  It doesn't take much, so it is recommended to be left on.
From the status screen you can review which sticky's have been sent.
The default is ON.
:edl.

.*--------------------------------------------------------------*\
.*  Configure Dialog                                            *
.*      res = PANEL_CONFIG_SETUP                                *
.*--------------------------------------------------------------*/
:h1 hide res=2300 name=PANEL_CONFIG_SETUP.Setup
:i2 refid=Config.Setup
:p.The Setup screen allows you to turn on/off lots of options. Below is
brief description of each option.
:dl.
:dt.Close window after Send
:dd.This option if checked will automatically close the Send window when
the Send button is pressed.  This option is good if you only send out an
occasional sticky.  This way you don't have to close the window by pressing
the Close button. The default if OFF.
:dt.Close Window after Reply
:dd.This option if checked will automatically close the Reply window when
the Send button is pressed.  This option is recommended since you should only
be replying to a sticky with one sticky back. The default is ON.
:dt.Popup Sticky on Receive
:dd.This option when checked will force the Sticky Note Receive screen to
the forground.  That is, it will pop up the Sticky screen over whatever you
are doing.  If this doesn't bother you then go for it.  If NOT checked
then the Received Sticky note is display but the window is forced to
the background.
The default is OFF.
:dt.Are You Sure Prompts
:dd.If checked then a warning screen will be displayed before deleting
data. The default is ON.
:dt.Mini ICON when shrunk
:dd.This option is used to reduce the Sticky program to a Yellow sticky
pad and a Title bar.  The Title bar is left so you can drag it around the
screen.  To get to the options you can click the Right mouse to popup a
menu of options.  If this option is Off, then the Sticky program will be
displayed as a bar, with buttons for Send, Config, Clear, Exit and About.
In either case when Maximized the screen is the same, Its in the Restore
mode that the screen will be displayed as a yellow sticky pad or a bar.
The default if OFF.
:dt.Beep on Receive
:dd.This option when selected will beep when a sticky note is received.
:dl.
:dt.Frequency
:dd.The Frequency of the beep.  You can change the Frequency of the
beep with this spin Control.  Default is 2000
:dt.Duration
:dd.The length of the beep in miliseconds.  500= 1/2 second
The default is 500
:edl.
:edl.

.*--------------------------------------------------------------*\
.*  Configure Dialog                                            *
.*      res = PANEL_CONFIG_NAMES                                *
.*--------------------------------------------------------------*/
:h1 hide res=2400 name=PANEL_CONFIG_NAMES.Names
:i2 refid=Config.Names
:i1 id=Names.Names Add/Delete/Modify
:p.The Names screen allows you to add/delete/modify names you keep.
These are the names you can send Sticky/2 Notes to.  You must add names
before you can send a Sticky/2 note to them.
:dl.
:dt.Sort
:dd.This option when checked will sort the names in the list.  It will
use the characters from Left to Right.  That is why there is the
Last name first option.
:dt.Last name first
:dd.This option will list the names in Last_Name, First_Name.  Since all
names are entered 'FirstName LastName'  This feature will allow you to
list the names either way.  The default is ON.
:dt.Port 6711
:dd.Lets face it.  Almost all of the people you will be sending sticky notes
to will be listening on Port 6711.  If for some reason 1 user is listening
on a different port then you MUST NOT select this option.  Selecting this
option forces all names in the Names database to default to port 6711.
:edl.
:p.The next fields allow you to Add/Modify a name.
:dl.
:dt.Add
:dd. To add a Name, just
key in the name, host and port (if you don't select PORT 6711 option), and
press the Add button.  The program will check the HOST to see if its already
in the list.  If the HOST already exsists in the list an error message will
be display and the name will not be added.  If all the data checks out okay
then the name will be added to the list, and sorted if Sorted is selected.
:dt.Modify
:dd.To modify a name you first have to Double Click the name in the NAME list.
This will copy the Name, Host, and Port information to the edit fields and
set an internal flag.  Once you make changes to the information, you can
click on the Modify button to update the information in the Name list.
:dt.Delete
:dd.To delete one name or a group of names, just highlite the names
in the list that you want deleted and press the Delete button.
If the 'Are You Sure' option is
set then a popup screen will be displayed warning you that the names will
be deleted.  If not then the names are deleted from the list.
On the popup scren you can press YES to delete the names, or NO to cancel
the delete.
:edl.

.*--------------------------------------------------------------*\
.*  Configure Dialog                                            *
.*      res = PANEL_CONFIG_AUTOREPLY                            *
.*--------------------------------------------------------------*/
:h1 hide res=2500 name=PANEL_CONFIG_AUTOREPLU.Auto Reply
:i2 refid=Config.Auto Reply
:p.The Auto Reply screen is a feature you can set to Automatically
reply to a received sticky note.  That is if you are away from your
desk for awhile or on vacation, you can notify the host that contacted
you with that information.
:dl.
:dt.Enable Auto Reply
:dd.This option turns ON/OFF the autoreply feature.  If not checked
then NO autoreply information will be sent.  If on, then you have a
bunch of options you can set. In future releases these options may
be defaulted to always on if AutoReply is turned on.  Since I see no
reason to not send the Program infomation to the connecting host.
The default if OFF
:dl.
:dt.Include Version number
:dd.The windows version of Sticky has a way of sending information about itself
to the connecting host.  If this option is checked then the Version number
of Sticky/2 OS/2 is sent to the other host.  If you are using AutoReply then
it is recommended to select this option.  The default is ON
:dt.Include Local Time Received
:dd.This option will send to the connecting host the Local time of your
machine.  It is a good feature for connecting to hosts around the world.
The default is ON.
:dt.Include Your Name
:dd.This option if checked will send your 'User' name to the connecting host.
It is good to select this option and let the connecting host know who they
are connecting to. The default is ON
:dt.reply message
:dd.This is a message you can automatically send back to the connecting
host when they send you a Sticky note.  It is limited to 255 characters
since I don't think you want to send your life story to everyone that
sends you a sticky note.
:edl.
:edl.
