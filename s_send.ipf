.*==============================================================*\
.*                                                              *
.* SEND.IPF- Information Tag Language file for the screens      *
.*           for Send on the dialog boxes.                      *
.*                                                              *
.*==============================================================*/


.*--------------------------------------------------------------*\
.*  Help for Product information                                *
.*      res = PANEL_SEND                                        *
.*--------------------------------------------------------------*/
:h1 res=1100 name=PANEL_SEND.Send Sticky/2 Note
:i1 id=Send.Send Sticky/2 Note
:p.This dialog allows you to select a :hp1.Note to: :ehp1. host/name
of a sticky user, then enter in the :hp1.Note to Send:ehp1., and
when entered, press the :hp1.Send:ehp1. button to send the note.
:note.If you want to cancel the note, just press the :hp1.Close:ehp1. button.
:p.If the :hp1.Close window after send:ehp1. is not checked.  Status
as to the current sending message will be displayed in the lower left
portion of the screen.  This information is also send to the Sticky/2
main screen in the status window.
:p.If the :hp1.Close window after send:ehp1.
is checked then the Send dialog window will close as soon as the message
is sent off to the Send Thread to be delivered.  You can check the status
of the send on the Sticky/2 main window status scroll box.
:note.The program limit of a Sticky/2 note is 2048 characters.  This is
my limit, if you need more than 2K then send an E-Mail!.

.*--------------------------------------------------------------*\
.*  About Box Dialog Ok button                                  *
.*      res = PANEL_PRODUCTINFO_OK                              *
.*--------------------------------------------------------------*/
:h1 res=1110 name=PANEL_SEND_SEND.Send button
:i2 refid=Send.Send button
:p.The Send button will send the entered message to the host
selected.

.*--------------------------------------------------------------*\
.*  About Box Dialog Ok button                                  *
.*      res = PANEL_PRODUCTINFO_OK                              *
.*--------------------------------------------------------------*/
:h1 res=1120 name=PANEL_SEND_CLOSE.Close button
:i2 refid=Send.Close button
:p.The Close button will close the Send dialog.  If a name was selected
and a message entered, then close acts like a cancel and will not send
the message.

.*--------------------------------------------------------------*\
.*  About Box Dialog Ok button                                  *
.*      res = PANEL_PRODUCTINFO_OK                              *
.*--------------------------------------------------------------*/
:h1 res=1130 name=PANEL_SEND_NOTETO.Note to:
:i2 refid=Send.Note to:
:p.The Note to: field is used to select a name from the list of hosts
that you have entered as Sticky users.  You can select more than one
host to send Sticky Notes to by pressing the Ctrl key while pressing
the Left button on the mouse.
:p.To add names to the list, you must go to the Config screen - Names.

.*--------------------------------------------------------------*\
.*--------------------------------------------------------------*\
.*--------------------------------------------------------------*\
.*      res = PANEL_REPLY                                       *
.*--------------------------------------------------------------*/
:h1 res=1700 name=PANEL_REPLYTO.Reply to:
:i1 id=ReplyTo.Reply to:
:p.The Reply to screen allows you to reply directly to a host that
has sent you a Sticky note.  The nice thing about this option is that
the host you are replying to does NOT have to be in your names list.
Since they have already sent you a Sticky note, then Sticky/2 already knows
the host name and number.  From this screen you can enter in the
text you want to send, and press the :hp1.Send:ehp1. button.  When you
are complete you can press the Close button to close the screen if
the Close after Reply option is not turned on.  Else if you don't want
to send a reply sticky note, you can press the Close button before you
press the Send Button.  This will close the Reply screen.

