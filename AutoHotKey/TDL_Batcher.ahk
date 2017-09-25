;; Programm: Flexstart_for_AutoCAD.ahk

;; Function: a Kind of batch-processing for Todolist
;; Reads a DEF-File which contains commands for TDL and fires Todolist.exe with each of this commands

;; Funktion: Arbeitet Textdateien je Zeile über Todolist.exe ab


;; Version 1 vom 13.03.2016 21:10:11
;; *************************************
;; Änderungen: 
;; Version X vom 
;; Art der Änderungen: 
;; **********************************************************
;; **********************************************************


;;;;;@Ahk2Exe-SetMainIcon       cadraktiv.ico
    #SingleInstance,Force
    #NoEnv
;    #NoTrayIcon
    ; Festlegen des Programmdatenverzeichnisses
    EnvGet, myfolder , TMP

    logfile := myfolder "\TDL_Batcher.log"

    ; Übernahme der Parameter; max. 2 erlaubt
    If 0 > 1 ; 0 ist die Variable!!, die die Anzahl der Parameter enthält
    {
        MsgBox, 16, TDL_Batcher, This program accepts only 1 incoming parameter, but it received %0%.`nYou should Try quoted strings like "my profile".
        ExitApp
    }
    
    Loop, %0%   ; for each parameter
    {
        MydefFile := %A_Index%
        MyDefFile = % A_ScriptDir "\" MydefFile    ; 1 ist die Variable für den Parameter
        IfExist, %MyDefFile%
        Loop
        {
            FileReadLine, line, %MyDefFile%, %A_Index%
            if ErrorLevel
                break
            
            ; skip line if first character is a ; semicolon
            StringLeft, OutputVar, line, 1
            IfNotEqual, OutputVar, `; ; run if no comment
            {
                startcommand := "c:\Program Files (x86)\Todolist\ToDoList.exe " line
                FileAppend, %startcommand%`n, %logfile%
                    MsgBox %startcommand%
                RunWait, %startcommand%
            }
            Else
            {
                MsgBox Line %line% is skipped because its a comment.
            }
        }
        Else
        {
            MsgBox, 16, TDL_Batcher, The file %MyDefFile% with commands could not be found
        }
    }
    MsgBox See %logfile% for logs.
return

