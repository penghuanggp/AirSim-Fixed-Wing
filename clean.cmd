rd /s/q AirLib\lib
rd /s/q AirLib\deps\MavLinkCom
rd /s/q AirLib\deps\rpclib
rd /s/q AirLib\deps\JSBSim
rd /s/q external\rpclib\build
rd /s/q external\jsbsim\jsbsim-1.1.2\build

msbuild /p:Platform=x64 /p:Configuration=Debug AirSim.sln /t:Clean
if ERRORLEVEL 1 goto :buildfailed
msbuild /p:Platform=x64 /p:Configuration=Release AirSim.sln /t:Clean
if ERRORLEVEL 1 goto :buildfailed
goto :eof

:buildfailed
echo #### Build failed
goto :eof
