#!/usr/bin/env zsh
# copies headers to modules directory and renames them to .cppm
# get directory of this script

script_dir="$(dirname "$0")"
# get the root directory of the project ../
project_dir="$(dirname $script_dir)"

core_dir="$project_dir/ams_core"
spatial_dir="$project_dir/ams_spatial"
game_dir="$project_dir/ams_game"


core_headers=(${(f)"$(find "$core_dir"/include -name '*.hpp')"})
for header in $core_headers; do
  header_dir="$(dirname $header)"
  # replace dirname "include" with "include/modules" in the path using sed
  module_dir="$(echo $header_dir | sed 's/include/include\/modules/')"
  echo "Processing '$header'"
  # invoke python script to convert to modules
 python3 "$script_dir/CopyModules.py" --input "$header" --dest "$module_dir"
done

spatial_headers=(${(f)"$(find "$spatial_dir"/include/ams -name '*.hpp')"})
for header in $spatial_headers; do
  header_dir="$(dirname $header)"
  # replace dirname "include" with "include/modules" in the path using sed
  module_dir="$(echo $header_dir | sed 's/include/include\/modules/')"
  echo "Processing '$header'"
  # invoke python script to convert to modules
 python3 "$script_dir/CopyModules.py" --input "$header" --dest "$module_dir"
done

game_headers=(${(f)"$(find "$game_dir"/include/ams -name '*.hpp')"})
for header in $game_headers; do
  header_dir="$(dirname $header)"
  # replace dirname "include" with "include/modules" in the path using sed
  module_dir="$(echo $header_dir | sed 's/include/include\/modules/')"
  echo "Processing '$header'"
  # invoke python script to convert to modules
 python3 "$script_dir/CopyModules.py" --input "$header" --dest "$module_dir"
done

echo "Finished"
