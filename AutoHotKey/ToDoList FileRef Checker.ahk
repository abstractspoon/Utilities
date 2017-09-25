;; Programm: ToDoList FileRef Checker.ahk

;; Function: searches inside the TDL-file all entries <FILEREFPATH>*</FILEREFPATH> and checks if they exist

;; Funktion: Sucht aus einer TDL-Datei alle Einträge <FILEREFPATH>*</FILEREFPATH> und
;; prüft, ob die Dateien vorhanden sind

;; Version 1 vom 08.07.2015 16:00:58
;; *************************************
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

    Gui, Add, ListBox,  x30   y20   w650  h320  hscroll vfundliste ,    Use the button bottom-left to select the TDL-file you want to check
    Gui, Add, Button,   x30   y340  w110  h40   vDateiwahl gDateiwahl , Select TDL ...
    Gui, Add, Button,   x150  y340  w110  h40   vWriteButton gWrite   , Write to file
    Gui, Add, Button,   x270  y340  w110  h40   vInfo gInfo ,           Information...
    Gui, Add, Button,   x390  y340  w110  h40   vBeendebutton gBeenden, Quit

    Gui,Add,Picture,    x550  y340  w136  h-1   gWebseite vWebseite,    logo_cadraktiv_20.png

    Gui, Color, 196FCD, F5F5F5
    Gui, Show,  w710,   ToDoList FileRef Checker - made by cadraktiv
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
    MsgBox, 64, ToDoList FileRef Checker, Info about this program:`n`n- It checks if files from FILEREFPATH can be found.`n- The tasklists themselves will not be affected by this process.`n- Use software at your own risk. No warranty, no liability.
return
;; **********************************************************
;; TDL wählen
Dateiwahl: ; 
    FileSelectFile, dateiangabe , 3, *.tdl, Please select the TDL to check, (*.tdl)
    fundliste_exist :=  ;
    fundliste_miss :=  ;
    fundliste_spec :=  ;
    fundliste_ges :=  ;
    GuiControl ,, fundliste, |---- ; Pipe, um Inhalt neu aufzubauen
    Gosub, stringsucher
return
;; **********************************************************
; suche nach Einträgen ..
; Format ab TDL 7.0 RC3? multiple file: <FILEREFPATH>*</FILEREFPATH>
; Format früher:  COMMENTSTYPE="PLAIN_TEXT" FILEREFPATH=".\2014\2014 VM BERNARD.pdf" CREATEDBY="patrice"
stringsucher:
    IfExist, %dateiangabe% ; wenn Ziel-TDL existiert
    {
        ; Entscheidung über fehlende Dateien
        listMissing := 0
        MsgBox , 36, ToDoList FileRef Checker, Do you want to list the MISSING files?
        IfMsgBox Yes
            listMissing := 1

        ; Entscheidung über vorhandene Dateien
        listExisting := 0
        MsgBox , 36, ToDoList FileRef Checker, Do you want to list the EXISTING files?
        IfMsgBox Yes
            listExisting := 1
            
        ; Entscheidung über vorhandene Dateien
        listSpecial := 0
        MsgBox , 36, ToDoList FileRef Checker, Do you want to list SPECIAL references?
        IfMsgBox Yes
            listSpecial := 1
        
        ; Zählschleifen auf Null setzen
        existcounter := 0
        misscounter := 0
        speccounter := 0
        taskcounter := 0
        ; zerlege Angaben der Ziel-TDL
        SplitPath, dateiangabe , OutFileName, OutDir, OutExtension, OutNameNoExt, OutDrive
        ; einlesen in Variable "Dateiinhalt"
        dateiinhalt :=      ;
        FileRead, dateiinhalt, %dateiangabe%
;        if Dateiinhalt
;            msgbox, File could be read.
;        Else
;            msgbox, File could NOT be read.
            
        if ErrorLevel <> 0
            MsgBox, Errorlevel for FileRead: %errorlevel%

        Loop, Parse, dateiinhalt, `n, `r            ; zerhacke jeweils am Zeilenende
        {                                               ; 
            fundpfad :=     ; löschen
            specialpfad :=  ; löschen
                
            ; zähle die Anzahl der Aufgaben über den Searchstring <TASK TITLE="
            RegExMatch(A_LoopField, "<TASK TITLE=(.*)", taskid)
            If %taskid%
                taskcounter+=1
            ; setze das Suchergebnis in die Variable "fundpfad"

            ; suche zuerst nach neuer Logik
            RegExMatch(A_LoopField, "<FILEREFPATH>(.*)</FILEREFPATH>", fundpfad)

            ; wenn nichts gefunden, suche nach alter Logik , Hochkomma escaped
            If !fundpfad
            {
;;;;                ; Notlösung: Suche zuerst den ganzen String, ersetze Hochkomma durch spitze Klammern suche dann in spitzen Klammern
;;;;                RegExMatch(A_LoopField, "U)FILEREFPATH=(.*)[=]", provwert) ; Ergebnisse ab FILEREFPATH bis zum Ende
;;;;;                MsgBox %provwert%
;;;;                StringReplace, provwert1, provwert, =`", <, All
;;;;                StringReplace, provwert1, provwert1, `", >, All
;;;;                RegExMatch(provwert1, "FILEREFPATH<(.*)>", fundpfad) ; Fundpfad: FILEREFPATH<.\2014\2014 VM BERNARD.pdf>; Fundpfad1: .\2014\2014 VM BERNARD.pdf
;;;;;                RegExMatch(A_LoopField, "U)FILEREFPATH=(.*)(.")", fundpfad) ; ? für non-greedy: nur bis erstem Leerzeichen
;;;;;                msgbox %A_LoopField%
                ; Hochkommas doppelt zum Escapen, \K Ergenis ab hier, ^ beginne ab Hochkomma, + für one or more
                RegExMatch(A_LoopField, "FILEREFPATH=""\K[^""]+", fundpfad)
                fundpfad1 := fundpfad   ; um gleiche Auswerung wie obige Suche zu ermöglichen
            }
            
            ; Aufarbeitung und Suche
            If fundpfad
            {
;                MsgBox, %fundpfad%
                mergeflag := 0
                outdir2 := outdir
                ; Vorschritt A -------------
                ; Fundpfade können auch relativ sein:  ..\..\Internes\Kunden\Signon\SIG-STW-000-ARB-025.pdf
                ; a) Für jedes vorne entfernte ".." entferne hinten beim Outdir der TDL einen Ordner
                ; b) Füge gekürztes Outdir und gekürzten Fundpfad zusammen
                While SubStr(fundpfad1, 1,3) = "..\" ; solange links "..\" steht, kürze es weg
                {
                    fundpfad1 := SubStr(fundpfad1, 4)
                    ; suche beim Outdir den letzten Backslash und schneide ab  dort weg
                    StringGetPos, Fundort, Outdir2, \ , R1
                    OutDir2 := SubStr(OutDir2, 1, Fundort)
                    mergeflag := 1
                }
                ; Vorschritt B -------------
                ; Fundpfade können auch kurz-relativ sein:  .\Internes\Kunden\Signon\SIG-STW-000-ARB-025.pdf
                While SubStr(fundpfad1, 1,2) = ".\" ; solange links ".\" steht, kürze es weg - kann nur einmal sein
                {
                    fundpfad1 := SubStr(fundpfad1, 3)
                    mergeflag := 1
                        ; outdir muss nicht geändert werden
;                        msgbox,a
                }
                ; -------------

                If mergeflag = 1
                    fundpfad1 = %outdir2%\%fundpfad1%
;MsgBox,
                ; Vorschritt C -------------
                ; Entferne die Sonderreferenzen wie 
                ; mailto: / tdl:// outlook:\\ onenote:\\
                ; manche Sonderreferenzen bleiben aber bestehen
                IfInString, fundpfad1, mailto
                {
                    specialpfad := fundpfad1
                    fundpfad1 :=    ; löschen
                }
                IfInString, fundpfad1, \\   ; alles mit Doppelbackslash
                {
                    specialpfad := fundpfad1
                    fundpfad1 :=    ; löschen
                }
                IfInString, fundpfad1, //   ; alles mit Doppelslash
                {
                    specialpfad := fundpfad1
                    fundpfad1 :=    ; löschen
                }

                ; Prüfung
                if fundpfad1 ; falls existent
                {
                    IfExist, %fundpfad1%
                    {
                        existcounter+=1
                        if listExisting = 1
                        {
                            fundliste_exist = %fundliste_exist%|yes`t%fundpfad1%
                            sort, fundliste_exist
    ;                        MsgBox,%fundpfad1%\tyes
                        }
                    }
                    IfNotExist, %fundpfad1%
                    {
                        misscounter+=1
                        if listMissing = 1
                        {
                            fundliste_miss = %fundliste_miss%|no`t%fundpfad1%
                            sort, fundliste_miss
    ;                       MsgBox,%fundpfad1%\tno
                        }
                    }
                }
                if specialpfad  ; falls existent
                {
                    speccounter+=1
                    if listSpecial = 1
                    {
                        fundliste_spec = %fundliste_spec%|???`t%specialpfad%
                        sort, fundliste_spec
                    }
                }
            }
        }
;        Sort, fundliste_exist, 
        GuiControl +Background8080C0,   fundliste
        If (fundliste_exist or fundliste_miss or fundliste_spec)
        {
            GuiControl ,, fundliste, |       ; leeren
            If %taskcounter%
                fundliste_ges = %fundliste_ges%|Number of Tasks: %taskcounter%|------
            If %fundliste_exist%
                fundliste_ges = %fundliste_ges%|%fundliste_exist%|Total: %existcounter%|------|
;                GuiControl ,, fundliste,        %fundliste_exist%|Total: %existcounter%|------|
            If %fundliste_miss%
                fundliste_ges = %fundliste_ges%|%fundliste_miss%|Total: %misscounter%|------|
;                GuiControl ,, fundliste,        %fundliste_miss%|Total: %misscounter%|------|
            If %fundliste_spec%
                fundliste_ges = %fundliste_ges%|%fundliste_spec%|Total: %speccounter%|------|
;                GuiControl ,, fundliste,        %fundliste_spec%|Total: %speccounter%|------|
             GuiControl ,, fundliste,        %fundliste_ges%
        }
        else
            GuiControl ,, fundliste,  |File %dateiangabe% checked|Number of Tasks: %taskcounter%|no (defined) links found.
    }
return
;;; **********************************************************
; beginnt die Ausgabe
Write:
    Gui,Submit, NoHide
    If (fundliste_exist or fundliste_miss or fundliste_spec)
    {
        FileSelectFile, outputfile , 2, *.txt, Please select the TXT for output, (*.txt)
        If %outputfile%
        {
            ; Achtung: Binary mode: To append in binary mode rather than text mode, 
            ; prepend an asterisk to the filename. This causes each linefeed character (`n) 
            ; to be written as a single linefeed (LF) rather than the Windows standard of CR+LF. 
            ; For example: *C:\My Unix File.txt.
            FormatTime, TimeString, time, dddd, dd. MMMM yyyy; HH:mm:ss
            FileAppend , `r`n`r`nAnalyzed file:`t%dateiangabe%`r`nDate:`t%TimeString%`r`n----`r`n, *%outputfile%

            If fundliste_exist
            {
                StringReplace, OutputVar, fundliste_exist, |, `r`n, All
                Sort, OutputVar
                FileAppend , Found files:`r`n%OutputVar%`r`nTotal: %existcounter%`r`n------------------`r`n, *%outputfile%
            }
    
            If fundliste_miss
            {
                StringReplace, OutputVar, fundliste_miss, |, `r`n, All
                Sort, OutputVar
                FileAppend , Missing files:`r`n%OutputVar%`r`nTotal: %misscounter%`r`n------------------`r`n, *%outputfile%
            }
            
            If fundliste_spec
            {
                StringReplace, OutputVar, fundliste_spec, |, `r`n, All
                Sort, OutputVar
                FileAppend , Special Links:`r`n%OutputVar%`r`nTotal: %speccounter%`r`n------------------`r`n, *%outputfile%
            }

            MsgBox, 64, ToDoList FileRef Checker, Output`n%outputfile%`ncreated.
        }
        Else
        {
            MsgBox, 16, ToDoList FileRef Checker, No file selected - nothing done.
        }
    }
    Else
    {
        MsgBox, 16, ToDoList FileRef Checker, No file list - nothing done.
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
