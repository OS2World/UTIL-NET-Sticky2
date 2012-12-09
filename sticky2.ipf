.*==============================================================*\
.*                                                              *
.* Sticky/2.ipf - Information Tag Language file for Sticky/2    *
.*                                                              *
.*==============================================================*/
:userdoc.

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1000 name=PANEL_MAIN.Sticky/2
:i1 id=Sticky.Sticky/2 Main Screen
:p.Sticky/2 is a program to send those yellow sticky notes
across a TCP/IP network.  From this screen you can send sticky
notes or configure the Sticky/2 Program

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1010 name=PANEL_MAIN_SEND.Send
:i2 refid=Sticky.Send
:p.Send will display the screen to allow you to select a
name in your list, and send that host a sticky note.

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1020 name=PANEL_MAIN_CONFIG.Config
:i2 refid=Sticky.Config
:p.Config will display the screen to allow you to set up the
Sticky/2 program.  From this screen you can add/delete/modify
names of users of the Sticky suite of programs.

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1030 name=PANEL_MAIN_CLEAR.Clear
:i2 refid=Sticky.Clear
:p.Clear will remove ALL the Received & AutoResponse windows from
screen.  This is the quick way of removing the sticky windows.

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1040 name=PANEL_MAIN_EXIT.Exit
:i2 refid=Sticky.Exit
:p.Exit will terminate the Sticky/2 program and save the main screen
position.

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=1050 name=PANEL_MAIN_ABOUT.About
:i2 refid=Sticky.About
:p.About will display the About screen.  The About screen has
information about the Version number, and the address to send money
to.  It also has the WWW home page for Sticky/2 and the E-Mail address
for support.

.*-- Import the Send menu help file --*
.im s_send.ipf

.*-- Import the Config menu help file --*
.im s_config.ipf

.*-- Import the Receive screens help file --*
.im s_recv.ipf

:euserdoc.
