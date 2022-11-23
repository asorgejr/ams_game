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
# Include preprocessors using the angle bracket syntax (#include <foo.h>) are
# implicitly converted to import statements. If this behavior is not desired,
# use the -x/--no_implicit flag.
#
# The metadata tags are replaced with valid c++20+ module syntax in the output file.
# The comment tags are:
# /*[module]*/ -- global module fragment
# /*[export]*/ -- exports a code block to the module
# /*[export ...]*/ -- exports a global module fragment named "..."
# /*[import ...]*/ -- imports a module named "..."
# /*[import <...>]*/ -- imports a legacy header named "..."
# /*[exclude begin]*/ -- everything in an exclude block is removed
# /*[exclude end]*/ -- everything in an exclude block is removed
# /*[ignore begin]*/ -- everything in an ignore block is left as-is
# /*[ignore end]*/ -- everything in an ignore block is left as-is
# /*[[ ... ]]*/ -- everything in a double bracket block is copied as-is

import os
import re
from argparse import ArgumentParser
from copy import copy
from typing import List, Tuple

bc = r'/*'  # comment block start
ec = r'*/'  # comment block end
bc_expr = bc[0] + '\\' + bc[1]
ec_expr = '\\' + ec
bb = '['  # begin block
eb = ']'  # end block
bb_expr = '\\' + bb
eb_expr = '\\' + eb
tb_expr = bc_expr + bb_expr + r'(?!\*\/)'  # /*[  and checks that the expression is not immediately escaped
te_expr = eb_expr + ec_expr  # ]*/
tb_raw = bc + bb  # /*[
te_raw = eb + ec  # ]*/
tag_pad_size = 3  # /*[ == 3  and  ]*/ == 3

tb_rgx = re.compile(tb_expr)
te_rgx = re.compile(te_expr)

mod_name_expr = r'[a-zA-Z_][a-zA-Z0-9_.:]*[a-zA-Z0-9_]'  # module name regex

ignore_begin_tag = re.compile(tb_expr + r'ignore begin' + te_expr)  # /*[ignore begin]*/
ignore_end_tag = re.compile(tb_expr + r'ignore end' + te_expr)  # /*[ignore end]*/

class ModifiedText:
    MAX_STACK_SIZE = 100

    def __init__(self, text: str):
        self._original: str = text
        """The current text with modifications"""
        self._change_stack: List[str] = [self._original]
        """A stack of all changes made to the text"""
        self._ignore_blocks: List[Tuple[int, int]] = []
        """A list of tuples containing the start and end indices of all ignore blocks. Indices are correlative to the original text"""
        self._find_ignored_blocks()
        self._remove_ignore_block_tags()
        self._remove_block_tags()

    def __str__(self):
        return self._change_stack[0]

    def set(self, text: str):
        """Sets the current text to the given text"""
        if len(self._change_stack) > self.MAX_STACK_SIZE:
            self._change_stack.pop()
        self._change_stack.insert(0, text)

    def text(self):
        """Returns the current text"""
        return self._change_stack[0]

    def original(self):
        """Returns the original text"""
        return self._original

    def offset(self):
        """Returns the offset of the current modified text from the original text"""
        return len(self._change_stack[0]) - len(self._original)

    def delta(self):
        """Returns the offset of the previous modified text and the current modified text"""
        return len(self._change_stack[0]) - len(self._change_stack[1]) if len(self._change_stack) > 1 else 0

    def changes(self):
        """Returns the number of changes made to the text"""
        return len(self._change_stack) - 1

    def _find_ignored_blocks(self):
        """Finds all ignore blocks in the text"""
        ibtag = re.compile(tb_expr + r'\s*ignore begin\s*' + te_expr)
        ietag = re.compile(tb_expr + r'\s*ignore end\s*' + te_expr)
        self._ignore_blocks = []
        txt = self._original
        startpos = 0
        while True:
            start = ibtag.search(txt, startpos)
            if not start: break
            startpos = start.start()
            end = ietag.search(txt, startpos)
            if not end: break
            endpos = end.start()
            bstartpos = startpos if startpos == 0 or txt[startpos-1] != '\n' else startpos - 1
            estartpos = endpos if endpos == 0 or txt[endpos-1] != '\n' else endpos - 1
            self._ignore_blocks.append((bstartpos, estartpos - len(start.group())))
            startpos = endpos - (len(start.group())) - (len(end.group()))
        btag = re.compile(tb_expr + bb_expr + r'((.(?<!\*/))*)' + eb_expr + te_expr, re.DOTALL)
        bbsize = len(tb_raw + bb)
        ebsize = len(eb + te_raw)
        startpos = 0
        while True:
            start = btag.search(txt, startpos)
            if not start: break
            startpos = start.start()
            endpos = startpos + len(start.group())
            bstartpos = startpos  # if startpos == 0 or txt[startpos-1] != '\n' else startpos - 1
            estartpos = endpos - ebsize
            self._ignore_blocks.append((self.offset() + bstartpos, self.offset() + (estartpos - bbsize)))
            startpos = endpos - (bbsize + ebsize)

    def _remove_ignore_block_tags(self):
        """Finds all ignore blocks in the text, removing the tags from the text and storing the start and end indices of the blocks"""
        ibtag = re.compile(tb_expr + r'\s*ignore begin\s*' + te_expr)
        ietag = re.compile(tb_expr + r'\s*ignore end\s*' + te_expr)
        result = self._original
        offset = 0
        startpos = 0
        while True:
            size = len(result)
            start = ibtag.search(result, startpos)
            if not start: break
            startpos = start.start()
            end = ietag.search(result, startpos)
            if not end: break
            endpos = end.start()
            bstartpos = startpos if startpos == 0 or result[startpos-1] != '\n' else startpos - 1
            estartpos = endpos if endpos == 0 or result[endpos-1] != '\n' else endpos - 1
            result = '{0}{1}{2}'.format(result[:bstartpos],
                                        result[bstartpos + len(start.group())+1:estartpos],
                                        result[estartpos + len(end.group())+1:])
            offset += len(result) - size
            startpos = endpos - (len(start.group())) - (len(end.group()))
        self.set(result)

    def _remove_block_tags(self):
        """Finds all block tags in the text, removing the tags from the text and storing the start and end indices of the blocks"""
        btag = re.compile(tb_expr + bb_expr + r'((.(?<!\*/))*)' + eb_expr + te_expr, re.DOTALL)
        result = self._change_stack[0]
        bbsize = len(tb_raw + bb)
        ebsize = len(eb + te_raw)
        offset = 0
        startpos = 0
        while True:
            size = len(result)
            start = btag.search(result, startpos)
            if not start: break
            startpos = start.start()
            endpos = startpos + len(start.group())
            bstartpos = startpos  # if startpos == 0 or result[startpos-1] != '\n' else startpos - 1
            estartpos = endpos - ebsize
            result = '{0}{1}{2}'.format(result[:bstartpos],
                                        result[bstartpos + bbsize:estartpos],
                                        result[endpos:])
            offset += len(result) - size
            startpos = endpos - (bbsize + ebsize)
        self.set(result)


    def is_ignored(self, index: int, s: str) -> bool:
        """Returns whether the given index is in an ignore block"""
        if not self._ignore_blocks or len(self._ignore_blocks) == 0:
            self._remove_ignore_block_tags()
        for start, end in self._ignore_blocks:
            # ofst = len(self._change_stack[1]) - len(self._original)
            # todo: inefficient and prone to false-positives in cases where there is code duplication
            for change in self._change_stack[::-1][0:-1]:
                found = change.find(s, start)
                if found != -1 and start <= found - (len(change) - len(self._original)) < end:
                    return True
        return False



def unwrap_tag(tag: str) -> str:
    return tag[tag_pad_size:-tag_pad_size].strip()


exclude_begin_tag = re.compile(tb_expr + r'exclude begin' + te_expr)  # /*[exclude begin]*/
exclude_end_tag = re.compile(tb_expr + r'exclude end' + te_expr)  # /*[exclude end]*/
def exclude_block(contents: ModifiedText) -> ModifiedText:
    ret = contents
    # find location of begin strip block
    begin = exclude_begin_tag.search(ret.text())
    if begin is None:
        return ret
    # find location of paired end strip block
    end = exclude_end_tag.search(ret.text(), begin.end())
    if end is None:
        return ret
    # remove each exclude block
    while begin is not None and end is not None:
        # remove the block and newline
        if begin.start() > 0 and ret.text()[begin.start() - 1] == '\n':
            ret.set(ret.text()[:begin.start() - 1] + ret.text()[end.end():])
        else:
            ret.set(ret.text()[:begin.start()] + ret.text()[end.end():])
        begin = exclude_begin_tag.search(ret.text())
        if begin is None:
            return ret
        end = exclude_end_tag.search(ret.text(), begin.end())
    return ret


double_bracket_block = re.compile(tb_expr + bb_expr + r'(.*?)' + eb_expr + te_expr, re.MULTILINE)  # /*[[ ... ]]*/
def double_bracket_block_include(contents: ModifiedText) -> ModifiedText:
    ret = contents
    # find location of begin strip block
    begin = double_bracket_block.search(ret.text())
    if begin is None:
        return ret
    # find location of paired end strip block
    end = double_bracket_block.search(ret.text(), begin.end())
    if end is None:
        return ret
    # remove each exclude block
    while begin is not None and end is not None:
        # remove the block and newline
        if begin.start() > 0 and ret.text()[begin.start() - 1] == '\n':
            ret.set(ret.text()[:begin.start() - 1] + ret.text()[end.end():])
        else:
            ret.set(ret.text()[:begin.start()] + ret.text()[end.end():])
        begin = double_bracket_block.search(ret.text())
        if begin is None:
            return ret
        end = double_bracket_block.search(ret.text(), begin.end())
    return ret


# finds an opening block tag with a matching closing block tag and returns the contents
# does not support nested tags. If a block is malformed, this will return None
def get_tag_block(contents: ModifiedText, start: int):
    ret = contents
    # find comment opening tag from start
    cmstart = ret.text().find(bc, start)
    if cmstart == -1:
        return None
    # find comment closing tag
    cmend = ret.text().find(ec, cmstart)
    if cmend == -1 or cmend == cmstart + len(ec) + 2:
        return None
    tb = cmstart + len(bc) if ret.text()[cmstart + 1] == bc else -1
    if tb == -1:
        return None
    # find the closing block tag
    te = cmend - len(ec) if ret.text()[cmend - 1] == ec else -1
    if te == -1:
        return None
    # return the contents of the block
    return ret.text()[tb:te]


def find_ignore_blocks(contents: ModifiedText) -> Tuple[ModifiedText, List[Tuple[int, int]]]:
    ret = contents
    ignore_blocks = []
    result = ret.text()
    start = 0
    while True:
        # find location of begin ignore block
        begin = ignore_begin_tag.search(result, start)
        if begin is None:
            break
        # find location of paired end ignore block
        end = ignore_end_tag.search(result, begin.end())
        if end is None:
            break
        beginstartpos = begin.start() if begin.start() != 0 and result[begin.start()-1] != '\n' else begin.start() - 1
        endstartpos = end.start() if end.start() != 0 and result[end.start()-1] != '\n' else end.start() - 1
        result = result[:beginstartpos] + result[begin.end():endstartpos] + result[end.end():]
        # add the block to the list
        ignore_blocks.append((beginstartpos + (begin.end()-beginstartpos),
                              endstartpos + (end.end()-endstartpos)))
        start = end.end()
    # for i in range(len(ignore_blocks)):
    #     ignore_blocks[i] = (ignore_blocks[i][0] - count, ignore_blocks[i][1] - count)
    ret.set(result)
    return ret, ignore_blocks


def in_ignore_block(pos: int, ignore_blocks: List[Tuple[int, int]]) -> bool:
    if not ignore_blocks:
        return False
    for block in ignore_blocks:
        if block[0] <= pos < block[1]:
            return True
    return False


mod_decl_expr = r'(module( *:? *{0})?;?)'.format(mod_name_expr)
module_tag = re.compile(tb_expr + mod_decl_expr + te_expr)  # /*[module]*/ -> module;
def replace_module_tag(contents: ModifiedText) -> ModifiedText:
    # replace /*[module]*/ with module;
    # return modified text object
    ret = contents
    tag = module_tag.search(ret.text())
    if tag is not None:
        unwrapped = unwrap_tag(tag.group())
        ofst = tag.end() + (len(unwrapped) - len(tag.group()))
        repl = ret.text()[:tag.start()] + unwrapped
        if repl[-1] != ';':
            repl = repl[:ofst] + ';'
            ofst += 1
        ret.set(repl + ret.text()[tag.end():])
    return ret


export_decl_tag = re.compile(tb_expr + r'export' + te_expr)  # /*[export]*/ -> export
def replace_export_decl_tag(contents: ModifiedText) -> ModifiedText:
    # replace /*[export]*/ <symbol_name> with export <symbol_name>;
    # return modified text object
    # find all export tags and unwrap them, then replace them, adding a trailing space if needed
    ret = contents
    tag = export_decl_tag.search(ret.text())
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        ofst = tag.end() + len(unwrapped) - len(tag.group())
        repl = ret.text()[:tag.start()] + unwrapped
        if not ret.text()[tag.end()].isspace():
            repl = repl[:ofst] + ' '
            ofst += 1
        ret.set(repl + ret.text()[tag.end():])
        tag = export_decl_tag.search(ret.text(), ofst)
    return ret


export_import_tag = re.compile(tb_expr + r'export import {0}'.format(mod_name_expr) + te_expr)  # /*[export import <module name>]*/ -> export import
def replace_export_import_tag(contents: ModifiedText) -> ModifiedText:
    # replace /*[export import <module name>]*/ with export import <module name>;
    # return modified text object
    ret = contents
    tag = export_import_tag.search(ret.text())
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        ofst = tag.end() + len(unwrapped) - len(tag.group())
        repl = ret.text()[:tag.start()] + unwrapped
        if repl[-1] != ';':
            repl = repl[:ofst] + ';'
            ofst += 1
        ret.set(repl + ret.text()[tag.end():])
        tag = export_import_tag.search(ret.text(), ofst)
    return ret


export_sig = r'export +module +({0});?'.format(mod_name_expr)
export_module_name_tag = re.compile(tb_expr + export_sig + te_expr)  # /*[export module <name>]*/ -> export module <name>;
def replace_export_module_tag(contents: ModifiedText) -> ModifiedText:
    # replace /*[export module <module_name>]*/ with export module <module_name>;
    # return modified text object
    # find all export module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    ret = contents
    tag = export_module_name_tag.search(ret.text())
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        ofst = tag.end() + len(unwrapped) - len(tag.group())
        repl = ret.text()[:tag.start()] + unwrapped
        if ret.text()[ofst - 1] != ';':
            repl = repl[:ofst] + ';'
            ofst += 1
        ret.set(repl + ret.text()[tag.end():])
        tag = export_module_name_tag.search(ret.text(), ofst)
    return ret


import_sig = r'import +<?{0}>?;?'.format(mod_name_expr)
import_name_block_tag = re.compile(tb_expr + import_sig + te_expr)  # /*[import <name>]*/ -> import <name>;
def replace_import_module_tag(contents: ModifiedText) -> ModifiedText:
    # replace /*[import <module_name>]*/ with import <module_name>;
    # return modified text object
    # find all import module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    ret = contents
    tag = import_name_block_tag.search(ret.text())
    while tag is not None:
        unwrapped = unwrap_tag(tag.group())
        ofst = tag.end() + len(unwrapped) - len(tag.group())
        repl = ret.text()[:tag.start()] + unwrapped
        if ret.text()[ofst - 1] != ';':
            repl = repl[:ofst] + ';'
            ofst += 1
        ret.set(repl + ret.text()[tag.end():])
        tag = import_name_block_tag.search(ret.text(), ofst)
    return ret


mod_incl_file_expr = r'[a-zA-Z_][a-zA-Z0-9_/]*[a-zA-Z0-9_](\.[a-zA-Z]{1,4})?'
include_header_expr = r'#include *(<{0}>)'.format(mod_incl_file_expr)
include_header_rgx = re.compile(include_header_expr, re.MULTILINE)
def replace_include_header(contents: ModifiedText) -> ModifiedText:
    # replace #include <...> with import <...>;
    # return modified text object
    ret = contents
    result = ret.text()
    match = include_header_rgx.search(result)
    offset = 0
    i = 0
    while match is not None:
        # tst = ret.original[match.start()-ret.offset():match.start()-ret.offset() + 16]
        # check if the match is in an ignore block
        size = len(result)
        if contents.is_ignored(match.start(), match.group()):
            match = include_header_rgx.search(result, match.end() + offset)
            continue
        # replace the match with import <module>;
        module = match.group(1)
        repl = result[:match.start()]
        repl += 'import {0};'.format(module)
        repl += result[match.end():]
        result = repl
        offset = len(result) - size
        match = include_header_rgx.search(result, match.end() + offset)
        ret.set(result)
        i += 1
    ret = contents
    ret.set(result)
    return ret


metatag_prompt = \
    r"\s*\/\/\s*This file uses metatags to convert headers to module-interfaces using header2module\.py\.\s*\n" \
    r"\s*\/\/\s*Any block comment formatted as\: \/\*\[\s*\]\*\/ is a metatag and other code may depend on it\.\s*\n" \
    r"\s*\/\/\s*Proceed with caution when modifying such comments\.\s*"
def rem_metatag_prompt(contents: ModifiedText) -> ModifiedText:
    # remove metatag prompt from the top of the file
    # return modified text object
    ret = contents
    result = ret.text()
    match = re.search(metatag_prompt, result)
    if match is not None:
        result = result[:match.start()] + '\n' + result[match.end():]
        ret.set(result)
    return ret


def modify_file(filename, no_implicit=False) -> str:
    if not os.path.isfile(filename):
        return None
    contents: ModifiedText
    # begin by reading the file
    with open(filename, 'r') as f:
        text = f.read()
    contents = ModifiedText(text)
    # contents, ignore_blocks = find_ignore_blocks(contents)
    # remove all exclude blocks
    contents = exclude_block(contents)
    # find a module tag if it exists
    contents = replace_module_tag(contents)
    # find all export tags and unwrap them, then replace them, adding a trailing space if needed
    contents = replace_export_decl_tag(contents)
    # find all export module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    contents = replace_export_module_tag(contents)
    # find all export-import tags and unwrap them, then replace them, adding a trailing semicolon if needed
    contents = replace_export_import_tag(contents)
    # find all import module tags and unwrap them, then replace them, adding a trailing semicolon if needed
    contents = replace_import_module_tag(contents)
    # replace std includes with import statements
    if not no_implicit:
        contents = replace_include_header(contents)
    contents = rem_metatag_prompt(contents)
    return contents.text()


def main(argv):
    parser = ArgumentParser(description='Converts a c++ header file to a c++ module using comment tags')
    parser.add_argument('-i', '--input', help='input file(s)', nargs='+', required=True)
    parser.add_argument('-o', '--dest', help='output directory', required=True)
    parser.add_argument('-x', '--no_implicit',
                        help='do not implicitly convert angle-bracket includes (#include <foo.h>) to import statements',
                        action='store_true')
    args = parser.parse_args(argv)
    if not os.path.exists(args.dest):
        os.makedirs(args.dest)
    for file in args.input:
        if not os.path.isfile(file):
            print('File not found: ' + file)
            continue
        contents: str = modify_file(file, args.no_implicit)
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
