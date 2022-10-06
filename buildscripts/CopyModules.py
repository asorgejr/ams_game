# Copyright 2022 - Anthony Sorge
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
# BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
# OR OTHER DEALINGS IN THE SOFTWARE.
#
# CopyModules.py
#
# Description: Converts a c++ header file to a c++ module using comment metadata
#  and copies the result(s) to a destination directory with the *.cppm extension.
#  This allows one to maintain a single file for use as both a header and a module.
#
# Usage: python CopyModules.py -i <input file(s)> -o <destination directory>
#
# Note: This script does not support .cpp source files, only .h header files.
#  If your header has a paired .cpp file, you must use preprocessor directives
#  to determine whether to include the header or import the module.
#
# The metadata tags are replaced with valid c++20+ module syntax in the output file.
# The comment tags are:
# /*[module]*/ -- global module fragment
# /*[export]*/ -- exports a code block to the module
# /*[export <module name>]*/ -- exports a global module fragment
# /*[import <module name>]*/ -- imports a module
# /*[exclude begin]*/ -- everything in an exclude block is removed
# /*[exclude end]*/ -- everything in an exclude block is removed
import os
import re
from argparse import ArgumentParser

bc = r'/*'  # comment block start
bc_expr = r'/\*'
ec = r'*/'  # comment block end
ec_expr = r'\*/'
bb = '['  # begin block
bb_expr = r'\['
eb = ']'  # end block
eb_expr = r'\]'
tb_expr = bc_expr + bb_expr  # /*[
te_expr = eb_expr + ec_expr  # ]*/
tag_pad_size = 3  # /*[  and  ]*/

tb_rgx = re.compile(tb_expr)
te_rgx = re.compile(te_expr)

mod_name_expr = r'[a-zA-Z_.][a-zA-Z0-9_.]*[a-zA-Z0-9_]'  # module name regex
module_tag = re.compile(tb_expr + r'(module;?)' + te_expr)  # /*[module]*/ -> module;
export_symbol_tag = re.compile(tb_expr + r'export' + te_expr)  # /*[export]*/ -> export
export_sig = r'export +module +({0});?'.format(mod_name_expr)
# /*[export module <name>]*/ -> export module <name>;
export_module_name_tag = re.compile(tb_expr + export_sig + te_expr)
import_sig = r'import +(?:{0}|<{0}>);?'.format(mod_name_expr)
# /*[import <name>]*/ -> import <name>;
import_name_block_tag = re.compile(tb_expr + import_sig + te_expr)
exclude_begin_tag = re.compile(tb_expr + r'exclude begin' + te_expr)  # /*[exclude begin]*/
exclude_end_tag = re.compile(tb_expr + r'exclude end' + te_expr)  # /*[exclude end]*/


include_header_rgx = re.compile(r'#include +<([a-z_]+)>')

std_modules = [
    'algorithm', 'any', 'array', 'atomic', 'barrier', 'bit',
    'bitset', 'charconv', 'chrono', 'cmath', 'codecvt', 'compare',
    'complex', 'concepts', 'condition_variable', 'coroutine',
    'deque', 'exception', 'execution', 'filesystem', 'format',
    'forward_list', 'fstream', 'functional', 'future',
    'initializer_list', 'iomanip', 'ios', 'iosfwd', 'iostream',
    'istream', 'iterator', 'latch', 'limits', 'list', 'locale',
    'map', 'memory', 'memory_resource', 'mutex', 'new', 'numbers',
    'numeric', 'optional', 'ostream', 'queue', 'random', 'ranges',
    'ratio', 'regex', 'scoped_allocator', 'semaphore', 'set',
    'shared_mutex', 'span', 'sstream', 'stack', 'stdexcept',
    'stop_token', 'streambuf', 'string', 'string_view', 'strstream',
    'syncstream', 'system_error', 'thread', 'tuple', 'typeindex',
    'typeinfo', 'type_traits', 'unordered_map', 'unordered_set',
    'utility', 'valarray', 'variant', 'vector', 'version'
]


def exclude_block(contents: str) -> (str, int):
    count = 0
    # find location of begin strip block
    begin = exclude_begin_tag.search(contents)
    if begin is None:
        return contents, count
    # find location of paired end strip block
    end = exclude_end_tag.search(contents, begin.end())
    if end is None:
        return contents, count
    # remove each exclude block
    while begin is not None and end is not None:
        # remove the block and newline
        if begin.start() > 0 and contents[begin.start() - 1] == '\n':
            contents = contents[:begin.start() - 1] + contents[end.end():]
        else:
            contents = contents[:begin.start()] + contents[end.end():]
        begin = exclude_begin_tag.search(contents)
        if begin is None:
            return contents, count
        end = exclude_end_tag.search(contents, begin.end())
    return contents, len(contents) - count


def unwrap_tag(tag: str) -> str:
    return tag[tag_pad_size:-tag_pad_size].strip()


# finds an opening block tag with a matching closing block tag and returns the contents
# does not support nested tags. If a block is malformed, this will return None
def get_tag_block(contents: str, start: int):
    # find comment opening tag from start
    cmstart = contents.find(bc, start)
    if cmstart == -1:
        return None
    # find comment closing tag
    cmend = contents.find(ec, cmstart)
    if cmend == -1 or cmend == cmstart + len(ec) + 2:
        return None
    tb = cmstart + len(bc) if contents[cmstart+1] == bc else -1
    if tb == -1:
        return None
    # find the closing block tag
    te = cmend - len(ec) if contents[cmend-1] == ec else -1
    if te == -1:
        return None
    # return the contents of the block
    return contents[tb:te]


def replace_module_tag(contents: str) -> (str, int):
    # replace /*[module]*/ with module;
    # return modified contents and the change in character count
    count = len(contents)
    tag = module_tag.search(contents)
    if tag is not None:
        contents = contents[:tag.start()] + 'module;' + contents[tag.end():]
    return contents, len(contents) - count


def replace_export_symbol_tag(contents: str) -> (str, int):
    # replace /*[export]*/ <symbol_name> with export <symbol_name>
    # return modified contents and the change in character count
    # find all export tags and unwrap them, then replace them, adding a trailing space if needed
    count = len(contents)
    tag = export_symbol_tag.search(contents)
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        offset = tag.end() + len(unwrapped) - len(tag.group())
        repl = contents[:tag.start()] + unwrapped
        if not contents[tag.end()].isspace():
            repl = repl[:offset] + ' '
            offset += 1
        contents = repl + contents[tag.end():]
        tag = export_symbol_tag.search(contents, offset)
    return contents, len(contents) - count


def replace_export_module_tag(contents: str) -> (str, int):
    # replace /*[export module <module_name>]*/ with export module <module_name>;
    # return modified contents and the change in character count
    # find all export module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    count = len(contents)
    tag = export_module_name_tag.search(contents)
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        offset = tag.end() + len(unwrapped) - len(tag.group())
        repl = contents[:tag.start()] + unwrapped
        if contents[offset-1] != ';':
            repl = repl[:offset] + ';'
            offset += 1
        contents = repl + contents[tag.end():]
        tag = export_module_name_tag.search(contents, offset)
    return contents, len(contents) - count


def replace_import_module_tag(contents: str) -> (str, int):
    # replace /*[import module <module_name>]*/ with import <module_name>;
    # return modified contents and the change in character count
    # find all import module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    count = len(contents)
    tag = import_name_block_tag.search(contents)
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        offset = tag.end() + len(unwrapped) - len(tag.group())
        repl = contents[:tag.start()] + unwrapped
        if contents[offset-1] != ';':
            repl = repl[:offset] + ';'
            offset += 1
        contents = repl + contents[tag.end():]
        tag = import_name_block_tag.search(contents, offset)
    return contents, len(contents) - count


def replace_std_include(contents: str) -> (str, int):
    # replace #include <module> with import <module>; if module is a standard module
    # return modified contents and the change in character count
    count = len(contents)
    match = include_header_rgx.search(contents)
    while match is not None:
        if match.group(1) in std_modules:
            contents = contents[:match.start()] + 'import <{0}>;'.format(match.group(1)) + contents[match.end():]
        match = include_header_rgx.search(contents, match.end())
    return contents, len(contents) - count


def modify_file(filename) -> str:
    if not os.path.isfile(filename):
        return None
    # begin by reading the file
    with open(filename, 'r') as f:
        contents: str = f.read()
    # remove all strip blocks
    contents, count = exclude_block(contents)
    # find a module tag if it exists
    contents, count = replace_module_tag(contents)
    # find all export tags and unwrap them, then replace them, adding a trailing space if needed
    contents, count = replace_export_symbol_tag(contents)
    # find all export module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    contents, count = replace_export_module_tag(contents)
    # find all import module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    contents, count = replace_import_module_tag(contents)
    # replace std includes with import statements
    contents, offset = replace_std_include(contents)
    return contents


def main(argv):
    parser = ArgumentParser(description='Converts a c++ header file to a c++ module using comment tags')
    parser.add_argument('-i', '--input', help='input file(s)', nargs='+', required=True)
    parser.add_argument('-o', '--dest', help='output directory', required=True)
    args = parser.parse_args(argv)
    if not os.path.exists(args.dest):
        os.makedirs(args.dest)
    for file in args.input:
        if not os.path.isfile(file):
            print('File not found: ' + file)
            continue
        contents: str = modify_file(file)
        if contents is None:
            print('Error reading file: ' + file)
            continue
        # get filename with .cppm extension
        filename = os.path.splitext(os.path.basename(file))[0] + '.cppm'
        # write the file
        with open(os.path.join(args.dest, filename), 'w') as f:
            f.write(contents)


if __name__ == '__main__':
    import sys
    main(sys.argv[1:])
