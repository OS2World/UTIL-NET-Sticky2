.*==============================================================*\
.*                                                              *
.* S_AUTO.IPF- Information Tag Language file for the screens    *
.*                                                              *
.*==============================================================*/


.*--------------------------------------------------------------*\
.*  Help for Product information                                *
.*      res = PANEL_AUTO                                        *
.*--------------------------------------------------------------*/
:h1 res=1600 name=PANEL_AUTO.Auto Reply
:i1 id=AutoReply.AutoReply
:p.This dialog is displayed when the host you connected to sends
an AutoReply message.  This message can contain text that the other
system sends, along with
:sl.
:li.Their Name
:li.The version of Sticky they are using
:li.The local time of their machine
:esl.
:p.The only option here is to close the window by pressing the
Close button.

.*--------------------------------------------------------------*\
.*  Help for Product information                                *
.*      res = PANEL_AUTO                                        *
.*--------------------------------------------------------------*/
:h1 res=1800 name=PANEL_STICKY.Sticky Note
:i1 id=StickyNote.Sticky Note
:p.This screen is displayed when another user of Sticky sends you
a sticky note.  Depending on the options set in the :hp1.Setup:ehp1.
screen will depend on if this screen will be popped up infront of
all the other screens or be kept in the back ground.
This screen will display the Host IP address in the Note From: field.
Their name, and text of the note.
:p.From this screen you have a couple of options, you can close the
screen by pressing the :hp1.Close:ehp1. button, or reply back to the
user by pressing the :hp1.Reply:ehp1. button.  If the reply button
is pressed you will be given a chance to enter in text and press a
Send button, or you can press the close button to cancel out.

