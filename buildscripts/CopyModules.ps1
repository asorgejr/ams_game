# copies headers to modules directory and renames them to .cppm
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

$headers = Get-ChildItem -Path "${scriptDir}/../include/ams" -Filter *.hpp
foreach ($header in $headers) {
    # invoke python script to convert header to cppm
    python "${scriptDir}\CopyModules.py" --input "${header}" --dest "${scriptDir}/../modules/ams"
}
