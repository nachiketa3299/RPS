param(
    [string]$workspaceRoot,
    [string]$fileBasenameNoExtension,
    [string]$file
)

$devenvPath = """E:\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"""
$outputPath = "$workspaceRoot\bin\$fileBasenameNoExtension\"

Write-Output $outputPath

$compileCommands = "cl.exe /Zi /EHsc /std:c++20 /utf-8 /Fe:$outputPath /Fo:$outputPath $file"

cmd.exe /c "$devenvPath && $compileCommands"