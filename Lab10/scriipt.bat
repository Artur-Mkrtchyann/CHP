@echo off
:menu
cls
echo ===================================
echo       Utility Script Menu
echo ===================================
echo 1. Show IPv4 and IPv6 Addresses
echo 2. Trace Network Route to Host
echo 3. Resolve IP Address of Host
echo 4. Encrypt File/Text
echo 5. Decrypt File/Text
echo 6. Compress File
echo 7. Decompress File
echo 8. Calculate File Cost (Hashing)
echo 0. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto show_ip
if "%choice%"=="2" goto trace_route
if "%choice%"=="3" goto resolve_ip
if "%choice%"=="4" goto encrypt
if "%choice%"=="5" goto decrypt
if "%choice%"=="6" goto compress
if "%choice%"=="7" goto decompress
if "%choice%"=="8" goto calculate_cost
if "%choice%"=="0" goto exit
goto menu

:show_ip
cls
echo Displaying IPv4 and IPv6 addresses:
ipconfig | findstr "IPv4"
ipconfig | findstr "IPv6"
pause
goto menu

:trace_route
cls
set /p target="Enter hostname or IP address: "
echo Tracing route to %target%...
tracert %target%
pause
goto menu

:resolve_ip
cls
set /p dns_name="Enter hostname or URL: "
echo Resolving IP address for %dns_name%...
nslookup %dns_name%
pause
goto menu

:encrypt
cls
set /p input="Enter text or file path to encrypt: "
echo Encryption functionality is not supported natively in Batch.
echo Use external tools or scripts for Blowfish/Caesar encryption.
pause
goto menu

:decrypt
cls
set /p input="Enter text or file path to decrypt: "
echo Decryption functionality is not supported natively in Batch.
echo Use external tools or scripts for Blowfish/Caesar decryption.
pause
goto menu

:compress
cls
set /p file="Enter file path to compress: "
echo File compression (LZ77) requires external tools or scripts.
pause
goto menu

:decompress
cls
set /p file="Enter file path to decompress: "
echo File decompression (LZ77) requires external tools or scripts.
pause
goto menu

:calculate_cost
cls
set /p file="Enter file path to calculate cost (hashing): "
if exist "%file%" (
    echo Calculating hash values for %file%...
    certutil -hashfile %file% > hash_default.txt
    echo Hashing with MD5...
    certutil -hashfile %file% MD5 >> hash_default.txt
    echo Hashing with SHA256...
    certutil -hashfile %file% SHA256 >> hash_default.txt
    echo Hash results saved in hash_default.txt.
) else (
    echo File %file% not found.
)
pause
goto menu

:exit
cls
echo Exiting... Goodbye!
exit
