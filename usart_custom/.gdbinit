set remotetimeout 20
shell start /B D:/Program Files/Zentri/ZentriOS_SDK/tools/OpenOCD/Win32/zentrios_sdk_openocd.exe -s D:/Program Files/Zentri/ZentriOS_SDK/tools/OpenOCD/scripts -f platform/AMW136.cfg -c gdb_init -l C:/Users/gp190/AppData/Roaming/SPB_Data/Zentri/workspace/usart_custom/openocd.log
