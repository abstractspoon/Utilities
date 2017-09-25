;; Programm: TDL_Reminderlist.ahk

;; Function: searches inside the Todolist.ini all sections [*\Reminders\*] and displays
;; them in a list to delete them

;; Funktion: Sucht aus der Todolist.ini allle Sektionen mit [*\Reminders\*] und bietet
;; sie in einer Auswahlliste zum Löschen an

;; Version 1 vom 15.02.2016 11:58:55
;; *************************************
;; Änderungen:
;; Version X vom 
;; Art der Änderungen: 
;; **********************************************************
;; **********************************************************


    FileInstall, logo_cadraktiv_20.png, logo_cadraktiv_20.png, 0

    #SingleInstance,Force
;    Menu, Tray, Tip, TDL Cleaner
    ;; -->> -->> -->> -->> -->> -->>
    GoSub, ShowStartDialog
    ;; <<-- <<-- <<-- <<-- <<-- <<--
    return

;; **********************************************************
ShowStartDialog:
    
    Gui,Font, s10, Verdana  ; Set x-point Verdana.

    Gui, Add, Text, Section    , INI: 
    Gui, Add, Text, x+10 w350 vIniname,   ----


    Gui, Add, ListView, xs y+10 r12 w400 Grid, Date|ID|File|INI-Value

    Gui,Add,Button,xp y+20 w110 h20     vDateiwahl gDateiwahl ,Select INI ...
    Gui,Add,Button, x+10 yp w110 h20   vBeendebutton gBeenden,Quit
    Gui,Add,Picture,x+10 yp w136 h-1  gWebseite vWebseite,logo_cadraktiv_20.png

    Gui, Color, C8FAFB, F4F4F4
    Gui,Show,,TDL Reminderlist - made by cadraktiv
return
;; **********************************************************
;; INI wählen
Dateiwahl: ; DMSEingang
    FileSelectFile, dateiangabe , 3, Todolist.ini, Please select the INI to read, (*.ini)
    GuiControl, Enable1, startbutton
    GuiControl, Enable1, TDL_Liste
    Gosub, sectionleser
return
;; **********************************************************
; suche nach sections mit Reminders : [FileStates\test.tdl\Reminders\Reminder0]
sectionleser:

;    tdl_liste_ges :=
;    tdl_liste_neu :=
    sectionlist :=
    LV_Delete()       ; alles im List_view löschen
    LV_ModifyCol(2, "Float Right")  ; ID rechtsbündig und Float
    LV_ModifyCol(3, "Text Right")  ; File rechtsbündig und Text
    IfExist, %dateiangabe%
    {
        IniRead, sectionlist, %dateiangabe%, 
        Loop, Parse, sectionlist, `n, `r            ; zerhacke jeweils am Zeilenende
        {                                               ; 
            StringSplit, sectionname, A_LoopField, `\ 
;            If sectionname1 = FileStates
;            {
                IfInString,A_LoopField, `\Reminders`\
                {
                    ; MsgBox % A_LoopField
                    IniRead, dez_datum, %dateiangabe%, %A_LoopField%, AbsoluteDate, 

                    IfNotEqual, dez_datum, ERROR
                    {
                        ; MsgBox % dez_datum
                        ; days:=41689
                        tage := Floor(dez_datum)
                        stunden := (dez_datum - tage) * 24
                        start:=19000101000000
                        EnvAdd, start, tage-2, d ;subtract 2 from days due to Excel bug
                        EnvAdd, start, stunden, H ; add calculated hour-value from decimal part
                        FormatTime, datum, % start, dd.MM.yyyy, HH:mm
                        ; MsgBox % datum
                    }
                    Else
                    {
                        datum = relative
                    }
                    
                    IniRead, id, %dateiangabe%, %A_LoopField%, TaskID
                    ; MsgBox,%sectionname2%
                    ; msgbox
                    LV_Add("",datum,id,sectionname2,A_LoopField)
                }
        }
        ; Spaltenbreite, ob Inhalt vorhanden oder nicht
        LV_GetText(OutputVar, 1, 1)
        If OutputVar
        {
            LV_ModifyCol()  ; Auto-size each column to fit its contents.
        }
        Else
        {
            LV_ModifyCol(1, 50) 
            LV_ModifyCol(2, 30) 
            LV_ModifyCol(3, 50) 
            LV_ModifyCol(4, 100) 
        }



        GuiControl +Background8080C0,TDL_liste
        
        
        StringLen, Pfadlaenge, dateiangabe
        IfGreater, Pfadlaenge, 45
        {
            StringTrimLeft, dateiangabe, dateiangabe, Pfadlaenge-47
            dateiangabe = ...%dateiangabe%
        }

        GuiControl, Text, Ininame, %dateiangabe%
    }
return
;;; **********************************************************
;; öffnet nach Klick auf das Bild die Webseite
Webseite:
    Run, http://www.cadraktiv.ch/index_eng.html
Return
;; **********************************************************
;=== BEGIN Quit SUBROUTINE =================================
Beenden:
GuiClose:
GuiEscape:
ExitApp
