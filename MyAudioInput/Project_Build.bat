@echo off

python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" build Windows_vc170 -c Debug -x x64
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" build Windows_vc170 -c Profile -x x64
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" build Windows_vc170 -c Release -x x64
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" build Authoring -c Release -x x64 -t vc170


