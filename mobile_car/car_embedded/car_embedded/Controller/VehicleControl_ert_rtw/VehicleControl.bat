
set MATLAB=D:\Matlab2021b\MatlabR2021b

cd .

if "%1"=="" ("D:\MATLAB~2\MATLAB~1\bin\win64\gmake"  -f VehicleControl.mk all) else ("D:\MATLAB~2\MATLAB~1\bin\win64\gmake"  -f VehicleControl.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1