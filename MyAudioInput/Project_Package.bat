@echo off


set plugin_ver="2025.1.3.1"
set package_dir="MyAudioInput_"%plugin_ver%

del /F /Q *tar.xz
rmdir /Q /S %package_dir%

python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" package Common --version=%plugin_ver%
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" package Windows_vc170 --version=%plugin_ver%
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" package Authoring --version=%plugin_ver%
python "%WWISEROOT%/Scripts/Build/Plugins/wp.py" generate-bundle --version=%plugin_ver%

mkdir %package_dir%
move *.tar.xz %package_dir%
move bundle.json %package_dir%
