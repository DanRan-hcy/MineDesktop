;  __  __               ____             __       __       ___
; /\ \/\ \  __         /\  _`\          /\ \     /\ \     /\_ \
; \ \ \ \ \/\_\    ____\ \ \L\ \  __  __\ \ \____\ \ \____\//\ \      __
;  \ \ \ \ \/\ \  /',__\\ \  _ <'/\ \/\ \\ \ '__`\\ \ '__`\ \ \ \   /'__`\
;   \ \ \_/ \ \ \/\__, `\\ \ \L\ \ \ \_\ \\ \ \L\ \\ \ \L\ \ \_\ \_/\  __/
;    \ `\___/\ \_\/\____/ \ \____/\ \____/ \ \_,__/ \ \_,__/ /\____\ \____\
;     `\/__/  \/_/\/___/   \/___/  \/___/   \/___/   \/___/  \/____/\/____/
;
; @author Malody Hoe / GitHub: undefinist / Twitter: undefinist
; http://undefinist.deviantart.com/art/VisBubble-for-Rainmeter-488601501
; UNIVERSAL SETTINGS
; You can override individual settings in the .ini files.
;========================================================================
;
; General FAQ:
; - HAVING PROBLEMS WITH AUDIO FREEZING?
; --- Reduce the FFTDecay value below.
; - USING TOO MUCH CPU?
; --- Reduce the NumOfItems, or FFTSize & FFTOverlap, or even increase the Update rate in individual files
;
[Variables]
; CHANGE PLAYER HERE! http://docs.rainmeter.net/manual/plugins/nowplaying
; This is to hide the visualizer when no music player is playing
Player=CAD
HideWhenNotPlaying=0
;
; The size of the circle, to make it into an ellipse just give RadiusY a number
Radius=160
RadiusY=160
;
; Color of shapes/lines/bars. ItemColor2 is for MultiLineExtrude
; You can also input gradient in the format COLOR:PCT|COLOR2:PCT2
; example: 255,255,255,255:0|0,0,0,255:100 = white to black
; example: FF0000|FFFF00:16|00FF00:33|00FFFF:50|0000FF:67|FF00FF:84|FF0000 = rainbow
ItemColor=255,246,245,255
ItemColor2=77,255,122,255
;
; Width of shapes/lines/bars
ItemWidth=4
;
; Number of shapes/lines/bars
NumOfItems=83
;
; How much to extrude line/bar/shape or max shape size for ShapeBubble
ExtrudeMax=36
ExtrudeMin=0
;
; Whether the line/bar/shape extrudes inwards or not
Inward=0
;
; Value of 0 to 1, indicating how much to smooth the points
Smoothing=1
;
; NOTE: VALUES ARE ALWAYS CLOCKWISE, STARTING FROM 0 WHICH FACES RIGHT
; What angle does the lowest freq start at?
AngleStartDeg=234
AngleStart=(Rad(#AngleStartDeg#))
; How much angle the items fill
AngleTotalDeg=360
AngleTotal=(Rad(#AngleTotalDeg#))
;
; Set to 0 for counterCW, 1 for CW (DOES NOT affect AngleStart/AngleTotal)
ClockWise=0
;
; FFT Options: For more detailed info, read http://docs.rainmeter.net/manual-beta/plugins/audiolevel#FFTOptions
FFTSize=1024
FFTOverlap=(#FFTSize#/2)
FFTAttack=184
FFTDecay=79
FreqMin=30
FreqMax=11050
Sensitivity=51
AudioDeviceID=
AudioDevicePort=Output




;=
; constants (don't edit!)
;============================
SCRIPT=#@#scripts/
INC=#@#includes/
=
