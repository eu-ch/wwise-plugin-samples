@echo off

python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" premake Authoring
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" premake Windows_vc170
