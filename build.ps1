if(-Not (Test-Path -Path ./.build.config -PathType Leaf))
{
    $path_to_native_tools = Read-Host -Prompt "Enter the path to your x64 Native Tools bat script location"
    $path_to_native_tools | out-file -filepath "./.build.config" -append -width 200        
}
else
{
    $path_to_native_tools = Get-Content "./.build.config"
}

Push-Location build
cmake ..
cmake --build . -j 6
$build_path = $PWD
cmd.exe /k "cd $path_to_native_tools & vcvars64.bat & cd $build_path & msbuild launchy.sln -t:patcher -m:6 /p:Configuration=Debug & msbuild launchy.sln -t:patcher -m:6 /p:Configuration=Release &  msbuild launchy.sln -t:launchy -m:6 /p:Configuration=Release &  msbuild launchy.sln -t:launchy -m:6 /p:Configuration=Debug &  exit"

Pop-Location