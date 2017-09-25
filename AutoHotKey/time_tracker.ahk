; time_tracker.ahk
; simple loop to test the time-tracking inside Todolist
;    The basic operation would be:
;    
;    1. Within an indefinite loop
;    2. Wait some random amount of time between 10 and 20 minutes
;    3. Select a known task ID using -tid ...
;    4. Start time tracking using -cmd 32967
;    
;    I could then run this within a VM and leave it for a few hours.



#NoEnv
#Singleinstance force


MsgBox This software needs:`n- One (1!) running instance of TDL,`n- with opened time_tracker.tdl,`n- which needs the Task-IDs 1-10.`nThe AHK should be in the same folder as the TDL`nEvery random 10-20 min a new TASK-ID is selected and started the time-tracking.`nThe infinite loop has to be broken via the system-tray.
    
Loop
{
    Random, timespan, 10,20     ; timespan between 10 and 20 min
    Random, taskid, 1,10     ; timespan between 10 and 20 min
    MsgBox,,,curr. timespan: %timespan% `ncurr. Task-ID: %taskid% `n`nThis message will fade away after 5 sec., 5

    if WinExist("ahk_exe todolist.exe")
    {
        WinActivate, ahk_exe todolist.exe   ; activate it always
       
       RunWait C:\Program Files (x86)\Todolist\ToDoList.exe -tid %taskid%, %A_WorkingDir%
;        MsgBox TASK-ID selected

       RunWait C:\Program Files (x86)\Todolist\ToDoList.exe -cmd 32967, %A_WorkingDir%
;       MsgBox Tracker activated
    }
    else
        msgbox Todolist is not running.
        
    sleep, % timespan * 1000 ; 60000 millisec = 1 min
}

    