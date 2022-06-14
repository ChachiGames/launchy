param(
    [Parameter()]
    [String]$configuration = "Debug"
)

if(-Not (Test-Path -Path ./.build.config -PathType Leaf))
{
    $path_to_native_tools = Read-Host -Prompt "Enter the path to your x64 Native Tools bat script location"
    $path_to_native_tools | out-file -filepath "./.build.config" -append -width 200        
}
else
{
    $path_to_native_tools = Get-Content "./.build.config"
}

if($configuration -eq 'Debug') 
{
    Write-Output "------ [Debug build selected] -------"
    $build_commands = "msbuild launchy.sln -t:patcher -m /p:Configuration=Debug &  msbuild launchy.sln -t:launchy -m /p:Configuration=Debug" 
}
elseif($configuration -eq "Release")
{
    Write-Output "------ [Release build selected] -------"
    $build_commands = "msbuild launchy.sln -t:patcher -m /p:Configuration=Release &  msbuild launchy.sln -t:launchy -m /p:Configuration=Release"
}
else
{
    Write-Output "Incompatible configuration type '"$configuration"'"
    exit 1
}


Push-Location build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON .. 
cmake --build . -j 6
$build_path = $PWD
cmd.exe /k "cd $path_to_native_tools & vcvars64.bat & cd $build_path  & $build_commands &  exit"
Pop-Location