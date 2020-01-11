[Rainmeter]
Update=16
DefaultUpdateDivider=-1
Group=#SkinGroup#
OnCloseAction=[!RefreshGroup #SkinGroup#]

ContextTitle="Open settings window"
ContextAction=#OpenSettingsWindow#
ContextTitle2="Edit variables"
ContextAction2=["#@#Variables.inc"]

[Variables]

; Since each skin file has some specific settings, they should be written to the global Variables file for access
EnvSlant=[!WriteKeyValue Variables Slant #Slant# "#@#Variables.inc"]
EnvInvert=[!WriteKeyValue Variables Invert #Invert# "#@#Variables.inc"]
EnvChannel=[!WriteKeyValue Variables Channel #Channel# "#@#Variables.inc"]
EnvPort=[!WriteKeyValue Variables Port #Port# "#@#Variables.inc"]
EnvID=[!WriteKeyValue Variables ID "#ID#" "#@#Variables.inc"]
EnvConfig=[!WriteKeyValue Variables Config "#CURRENTCONFIG#" "#@#Variables.inc"]
EnvConfigPath=[!WriteKeyValue Variables ConfigPath "#CURRENTPATH##CURRENTFILE#" "#@#Variables.inc"]
EnvSettingsWindow=#EnvSlant##EnvInvert#EnvChannel##EnvPort##EnvID##EnvConfig##EnvConfigPath#
OpenSettingsWindow=#EnvSettingsWindow#[!ActivateConfig "#ROOTCONFIG#\SettingsWindow"][!Refresh "#ROOTCONFIG#\SettingsWindow"]

[DisableProcessCheck]
Measure=String
String=#MusicPlayer#
IfMatch="None"
IfMatchAction=[!SetOption DisableProcessCheck String 1][!UpdateMeasure DisableProcessCheck]
IfNotMatchAction=[!SetOption MeasureProcess UpdateDivider 62.5]

[MeasureProcess]
Measure=Plugin
Plugin=Process
ProcessName=#MusicPlayer#.exe

[IdleAudioTimeout]
Measure=Calc
Formula=(IdleAudioTimeout + 1)
IfCondition=(IdleAudioTimeout = (Floor(62.5 * #IdleAudioTimeout#)))
IfTrueAction=[!DisableMeasure MeasureAudio][!DisableMeasureGroup Audio][!DisableMeasure DynamicSensitivity][!DisableMeasure IdleAudioTimeout]
UpdateDivider=1

[IdleAudioTimeout2]
Measure=Calc
Formula=(IdleAudioTimeout2 + 1)
IfCondition=(IdleAudioTimeout2 = (Floor(62.5 * #IdleAudioTimeout#)))
IfTrueAction=[!DisableMeasure ScriptRainyDays][!HideMeterGroup Rotators][!SetOptionGroup Rotators Y 0][!HideMeter BoundingBox][!DisableMeasure IdleAudioTimeout2]
UpdateDivider=1

[Standby]
Measure=Plugin
Plugin=AudioLevel
Port=#Port#
ID=#ID#
RMSAttack=0
RMSDecay=0
RMSGain=1
PeakAttack=0
PeakDecay=0
PeakGain=1
UpdateDivider=1

; Toggle measures/meters based on idle audio, music player running status, and constant falling
IfCondition=((Standby > 0.00001) && ((DisableProcessCheck = 1) || (MeasureProcess = 1)) && (#RainConstant# = 0))
IfTrueAction=[!DisableMeasure IdleAudioTimeout2][!EnableMeasure ScriptRainyDays][!ShowMeterGroup Rotators][!ShowMeter BoundingBox]
IfFalseAction=[!EnableMeasure IdleAudioTimeout2]
IfCondition2=(#RainConstant# <> 0)
IfTrueAction2=[!DisableMeasure IdleAudioTimeout2][!EnableMeasure ScriptRainyDays][!ShowMeterGroup Rotators][!ShowMeter BoundingBox]
IfCondition3=((Standby > 0.00001) && ((DisableProcessCheck = 1) || (MeasureProcess = 1)))
IfTrueAction3=[!DisableMeasure IdleAudioTimeout][!EnableMeasure MeasureAudio][!EnableMeasureGroup Audio][!EnableMeasure DynamicSensitivity]
IfFalseAction3=[!EnableMeasure IdleAudioTimeout]

[MeasureAudio]
Measure=Plugin
Plugin=AudioLevel
Port=#Port#
ID=#ID#
RMSAttack=0
RMSDecay=0
RMSGain=1
PeakAttack=0
PeakDecay=0
PeakGain=1
FFTSize=#FFTSize#
FFTOverlap=(Min(#FFTOverlap#, (#FFTSize#-512)))
FFTAttack=#FFTAttack#
FFTDecay=#FFTDecay#
Bands=#Bands#
FreqMin=#FreqMin#
FreqMax=#FreqMax#
Sensitivity=#Sensitivity#
UpdateDivider=1

[DynamicSensitivity]
Measure=Calc
Formula=(Max(#Sensitivity#, Min(Abs(20 * Log(MeasureAudio)) + Abs(20 * Log(0.5)), 0.5 * Abs(20 * Log(1/65535)))))
IfCondition=(#LoudnessEqualization# = 1)
IfTrueAction=[!SetOption MeasureAudio Sensitivity [DynamicSensitivity]]
IfConditionMode=1
UpdateDivider=1
; Average over the past 0.5 seconds to prevent stuttering
AverageSize=31

@Include=#@#Bands.inc

[SetMeasureOptions]
Measure=Calc
OnUpdateAction=[!SetOptionGroup Audio Channel #Channel#][!SetOptionGroup Audio AverageSize #AverageSize#][!SetOptionGroup Audio UpdateDivider 1][!UpdateMeasureGroup Audio]

[SetMeterOptions]
Measure=Script
ScriptFile=#@#SetMeterOptions.lua

[ScriptRainyDays]
Measure=Script
ScriptFile=#@#RainyDays.lua
MeasureBaseName=MeasureAudio
MeterBaseName=MeterRotator
LowerLimit=#FirstBandIndex#
UpperLimit=(#Bands#-1)
Multiplier=#RainSpeed#
Constant=#RainConstant#
Cover=#RainCover#
MeterHeight=#BarHeight#
UpdateDivider=1
OnUpdateAction=[!Redraw]

; Reveal the transformation by expanding the skin window through an invisible meter
[BoundingBox]
Meter=Image
H=#RainCover#

[MeasureDummy]
Measure=Calc