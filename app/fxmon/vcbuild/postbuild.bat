SET CONFIG=%1
echo "Copying ForexConnectAPI to %CONFIG%"
copy ..\..\..\world\ForexConnectAPI\win32\bin\*.dll   "%CONFIG%"
copy ..\..\..\world\ForexConnectAPI\win32\samples\cpp\sample_tools\bin\*.dll  "%CONFIG%"