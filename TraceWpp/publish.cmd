@echo off
setlocal

set VERSION=1.0.1

set OUTPUT=c:\NuGet\

%OUTPUT%nuget.exe push %OUTPUT%Packages\MMaitre.TraceWpp.%VERSION%.nupkg