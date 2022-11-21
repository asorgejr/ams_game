# initializes powershell environment to include util exes (if they have been built)
# get script dir
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$projectDir = Split-Path -Parent $scriptDir

# array of util exes
$exes=@(
    "convmesh.exe",
    "meshpp.exe"
)

# get PATH as array
$path = $env:PATH -split ";"

$foundexes = @()

# search for exes recursively in project dir
foreach ($exe in $exes) {
    $path = $env:PATH -split ";"
    # recursively search for exe and get absolute path if found
    $exePath = Get-ChildItem -Path $projectDir -Recurse -Filter $exe -ErrorAction SilentlyContinue | Select-Object -ExpandProperty FullName
    $exeDir = Split-Path -Parent $exePath
    $dirNotInPath = $path -notcontains $exeDir
    $newFoundExe = $foundexes -notcontains $exe
    # only add to path if not already in path and exe is not in foundexes
    if ($exePath -and $dirNotInPath -and $newFoundExe) {
        $env:PATH += ";$exeDir"
        echo "adding $exeDir to path"
        $foundexes += $exe
    } else {
        echo "parent dir of '$exe' already in path"
    }
}
