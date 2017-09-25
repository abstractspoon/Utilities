;; Programm: TDL_INI_Cleaner.ahk

;; Function: searches inside the Todolist.ini all sections [FileStates\*.tdl*] and displays
;; them in a list to delete them

;; Funktion: Sucht aus der Todolist.ini allle Sektionen [FileStates\*.tdl*] und bietet
;; sie in einer Auswahlliste zum Löschen an

;; Version 1 vom 18.02.2015 10:30:55
;; *************************************
;; Änderungen: ToDoList Preference File Cleaner
;; Version X vom 
;; Art der Änderungen: 
;; **********************************************************
;; **********************************************************


    FileInstall, logo_cadraktiv_20.png, logo_cadraktiv_20.png, 0

    #SingleInstance,Force
    GoSub, ShowStartDialog
    return

;; **********************************************************
ShowStartDialog:
    
    Gui,Font, s10, Verdana  ; Set x-point Verdana.

    Gui,Add,Button,x30 y20 w150 h40     vInfo gInfo ,Information...
    Gui,Add,Button,x30 y80 w150 h40     vDateiwahl gDateiwahl ,Select INI ...
    Gui,Add,Text,x30 y130 w150 h200  vInfotext   ,Select the INI-file you want to clean
    
    Gui, Add, ListBox, x210 y20 w340 h300 multi sort vTDL_Liste , ----

    Gui,Add,Button, x30 y340 w150 h40    disabled vStartButton gStarten   ,Remove selected

    Gui,Add,Button, x210 y340 w150 h40   vBeendebutton gBeenden,Quit

    Gui,Add,Picture,x390 y340 w136 h-1  gWebseite vWebseite,logo_cadraktiv_20.png

    Gui, Color, C8FAFB, F4F4F4
    Gui,Show,w600,ToDoList Preference File Cleaner - made by cadraktiv
return
;; **********************************************************
; Subroutine zur Anzeige der Tooltips über die ausgelesenen v-Labels der Controls
WM_MOUSEMOVE() {
    static CurrControl, PrevControl, _TT  ; _TT is kept blank for use by the ToolTip command below.
    CurrControl := A_GuiControl
    If (CurrControl != PrevControl && !InStr(CurrControl, " ")) {
        ToolTip  ; Turn off any previous tooltip.
        SetTimer, DisplayToolTip, -1000
        PrevControl := CurrControl
    }
    return

    DisplayToolTip:
    if (!InStr(CurrControl, " "))
        ToolTip % %CurrControl%_TT  ; The leading percent sign tell it to use an expression.
    SetTimer, RemoveToolTip, -3000
    return

    RemoveToolTip:
   ToolTip
    return
}
;; **********************************************************
;; Information anzeigen
Info: ; 
    MsgBox, 64, ToDoList Preference File Cleaner, Info about this program:`n`nTo remove obsolete 'file-state' information from your ini file, select one or more file names from the list and click 'Remove Selected'.`n`nNote:`n- The tasklists themselves will not be affected by this process.`n- A new file with the cleaned content will be created; the original file will stay unmodified.`n`nUse software at your own risk. No warranty, no liability.
return
;; **********************************************************
;; INI wählen
Dateiwahl: ; 
    FileSelectFile, dateiangabe , 3, Todolist.ini, Please select the INI to clean, (*.ini)
    GuiControl, Enable1, startbutton
    GuiControl, Enable1, TDL_Liste
    Gosub, sectionleser
return
;; **********************************************************
; suche nach sections mit Filestates: [FileStates\Introduction.tdl\SortColState]
sectionleser:
    tdl_liste_ges :=
    sectionlist :=
    IfExist, %dateiangabe%
    {
        IniRead, sectionlist, %dateiangabe%, 
        Loop, Parse, sectionlist, `n, `r            ; zerhacke jeweils am Zeilenende
        {                                               ; 
            StringSplit, sectionname, A_LoopField, `\ 
            If sectionname1 = FileStates
            {
                IfInString,sectionname2, .tdl
                {
                    IfNotInString, tdl_liste_ges, %sectionname2%
                        tdl_liste_ges = %tdl_liste_ges%|%sectionname2%
    ;            MsgBox,%sectionname2%
                }
            }
        }
        GuiControl +Background8080C0,TDL_liste
        GuiControl ,, TDL_liste, %tdl_liste_ges%
        Guicontrol,, Infotext, Select (multiple) file-states from the listbox on the right side and press 'Remove selected'
    }
return
;;; **********************************************************
; beginnt die Säuberung
Starten:
    Gui,Submit, NoHide

    If TDL_Liste
    {
        SplashTextOn,300,100,ToDoList Preference File Cleaner,Program started. Please wait...
        SplitPath, dateiangabe , OutFileName, OutDir, OutExtension, OutNameNoExt, OutDrive
        filecounter := 1
        newfile = %OutDir%\%OutNameNoExt%_cleaned_%filecounter%.ini

        while FileExist(newfile)
        {
            IfExist, %newfile%
            {
                filecounter := filecounter + 1
                StringGetPos, pos, newfile, _cleaned_
                new := SubStr(newfile, 1, pos)
                newfile = %new%_cleaned_%filecounter%.ini
            }
            else
                break
        }


        FileCopy, %dateiangabe%, %newfile%
        Loop, Parse, TDL_liste, |            ; zerhacke jeweils am Zeilenende
        {                                               ; 
            suchstring = Filestates\%A_LoopField%
            IfExist, %newfile%
            {
            ; suche nach sections mit Filestates: [FileStates\Introduction.tdl\SortColState]
                IniRead, sectionlist, %newfile%, 
                Loop, Parse, sectionlist, `n, `r            ; zerhacke jeweils am Zeilenende
                {                                               ; 
                    IfInString, A_LoopField, %suchstring%
                    {
    ;                    msgbox, %A_LoopField%
                        IniDelete, %newfile%, %A_LoopField%
                    }
                }
            }
        }
        SplashTextOff
        dateiangabe := newfile
        Gosub, sectionleser
        MsgBox, 64, ToDoList Preference File Cleaner, Job done.`nNew file created:`n`n%newfile%
        GuiControl, Enable0, TDL_Liste
        GuiControl, Enable0, startbutton
        Guicontrol,, Infotext, Select the INI-file you want to clean
    }
    Else
    {
        MsgBox, 64, ToDoList Preference File Cleaner, No entry selected - nothing done.
    }
return
;;; **********************************************************
;; öffnet nach Klick auf das Bild die Webseite
Webseite:
    Run, http://www.cadraktiv.ch/redirect_from_cleaner.html
Return
;; **********************************************************
;=== BEGIN Quit SUBROUTINE =================================
Beenden:
GuiClose:
GuiEscape:
ExitApp
