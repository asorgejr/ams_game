# copies headers to modules directory and renames them to .cppm
$script_dir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$project_dir = Split-Path -Parent "$script_dir"
$core_dir = "$project_dir/ams_core"
$spatial_dir = "$project_dir/ams_spatial"
$game_dir = "$project_dir/ams_game"

$core_headers = Get-ChildItem -Path "${core_dir}/include" -Filter *.hpp -Recurse
foreach ($header in $core_headers) {
    $header_dir = Split-Path -Parent $header
    # replace 'include' with 'modules' in path
    $module_dir = $header_dir.Replace("include", "include/modules")
    # invoke python script to convert header to cppm
    python "${script_dir}/header2module.py" --input "${header}" --dest "${module_dir}"
    echo "Processing '${header}'"
}

# recursively search for headers in spatial
$spatial_headers = Get-ChildItem -Path "${spatial_dir}/include/ams" -Filter *.hpp -Recurse
foreach ($header in $spatial_headers) {
    $header_dir = Split-Path -Parent $header
    # replace 'include' with 'modules' in path
    $module_dir = $header_dir.Replace("include", "include/modules")
    # invoke python script to convert header to cppm
    python "${script_dir}/header2module.py" --input "${header}" --dest "${module_dir}"
    echo "Processing '${header}'"
}

# recursively search for headers in game
$game_headers = Get-ChildItem -Path "${game_dir}/include/ams" -Filter *.hpp -Recurse
foreach ($header in $game_headers) {
    $header_dir = Split-Path -Parent $header
    # replace 'include' with 'modules' in path
    $module_dir = $header_dir.Replace("include", "include/modules")
    # invoke python script to convert header to cppm
    python "${script_dir}/header2module.py" --input "${header}" --dest "${module_dir}"
    echo "Processing '${header}'"
}

echo "Finished"