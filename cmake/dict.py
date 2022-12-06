#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Parses piped input from the command line via CMake and outputs a valid JSON string
from argparse import ArgumentParser
import json
import sys
from typing import Union

def remove_redundant_quotes(value: str):
    """Removes redundant quotes from a string."""
    if value.startswith('"') and value.endswith('"'):
        return value[1:-1]
    return value

def parse_cmake_value(value: list):
    # if value is a list, convert to a list
    for i in range(len(value)):
        if isinstance(value[i], str):
            value[i] = remove_redundant_quotes(value[i])
        # NULL
        if value[i] == 'NOTFOUND':
            value[i] = None
        # JSON
        try:
            value[i] = json.loads(value[i])
            continue
        except json.decoder.JSONDecodeError:
            pass
        # number from string
        if value[i].isdigit():
            value[i] = int(value[i])
        # boolean from string
        elif value[i] == 'TRUE' or value[i] == 'ON':
            value[i] = True
        elif value[i] == 'FALSE' or value[i] == 'OFF':
            value[i] = False
    if len(value) == 1:
        return value[0]
    return value

def parse_keypath(keypath: str):
    """Parses a keypath into a list of keys."""
    return keypath.split('.')

def get_value(keypath: str, dictionary: dict):
    """Gets a value from a dictionary using a keypath."""
    keys = parse_keypath(keypath)
    value = dictionary
    for key in keys:
        if key not in value:
            return None
        value = value[key]
    return value

def set_value(keypath: str, value, dictionary: dict):
    """Sets a value in a dictionary using a keypath."""
    keys = parse_keypath(keypath)
    for key in keys[:-1]:
        if key not in dictionary:
            dictionary[key] = {}
        elif not isinstance(dictionary[key], dict):
            dictionary[key] = {}
        dictionary = dictionary[key]
    dictionary[keys[-1]] = value

def del_entry(keypath: str, dictionary: dict):
    """Deletes a value from a dictionary using a keypath."""
    keys = parse_keypath(keypath)
    for key in keys[:-1]:
        if key not in dictionary:
            return
        dictionary = dictionary[key]
    del dictionary[keys[-1]]

def find_entry(keypath: str, dictionary: dict):
    """Finds a value in a dictionary using a keypath."""
    keys = parse_keypath(keypath)
    for key in keys:
        if key not in dictionary:
            return None
        dictionary = dictionary[key]
    return dictionary

def json_val_to_cmake(value):
    if isinstance(value, bool):
        if value:
            return 'TRUE'
        return 'FALSE'
    # recursive call
    if isinstance(value, list):
        return ';'.join([json_val_to_cmake(v) for v in value])
    if isinstance(value, dict):
        return json.dumps(value)
    return str(value)

def main():
    parser = ArgumentParser()
    parser.add_argument('-i', '--input', help='Input file', required=True)
    parser.add_argument('-o', '--output', help='Output file', required=True)
    parser.add_argument('-k', '--key', help='Key to use. A keypath can be used to access nested values '
                        '(e.g. "key1.key2.key3")')
    # value can be a string, number, boolean, or list
    parser.add_argument('-v', '--value', help='Value to use', nargs='+')
    # command flags (mutually exclusive)
    parser.add_argument('-n', '--new', help='Creates new dictionary', action='store_true')
    parser.add_argument('-d', '--delete', help='Deletes dictionary element', action='store_true')
    parser.add_argument('-a', '--add', help='Adds dictionary element. Error if key is already present.', action='store_true')
    parser.add_argument('-s', '--set', help='Sets dictionary element', action='store_true')
    parser.add_argument('-g', '--get', help='Gets dictionary element', action='store_true')
    parser.add_argument('-c', '--count',
                        help='Gets the number of elements for the specified key. Non-list values will return 1. '
                        'Empty lists and null will return 0. When this flag is present, other flags are ignored.',
                        action='store_true')
    parser.add_argument('--exists', help='Checks if a key exists. A keypath can be used to access nested values ', action='store_true')
    parser.add_argument('--keys', help='Gets the keys for the specified dict. If --key is present, tries to find the '
                                       'keys from the value at that keypath. When this flag is present, other flags are '
                                       'ignored.', action='store_true')
    args = parser.parse_args()
    command_flags = ['add', 'set', 'delete', 'new', 'get', 'count', 'keys', 'exists']
    if sum([getattr(args, flag) for flag in command_flags]) > 1:
        parser.error('Only one of the following flags can be used: ' + ', '.join(command_flags))
    infile = args.input
    data = None  # the resulting output to file. If None at end of execution, assume we are dumping dict to file, else dump value
    cmake_json = {}
    done = False
    # get input file
    with open(infile, 'r') as f:
        try:
            cmake_json = json.load(f)
        except ValueError:
            pass
        except FileNotFoundError:
            raise FileNotFoundError('Input file not found: ' + infile)

    # begin executing command
    if args.new:
        cmake_json = {}
        done = True

    if args.keys:  # get keys
        if args.key:
            cmake_json = get_value(args.key, cmake_json)
        if not isinstance(cmake_json, dict):
            cmake_json = {}
        data = ';'.join(cmake_json.keys())
        done = True

    # key required for any command after this point.
    if not done and args.key is None:
        raise ValueError('Key is required for this command')

    if args.count:
        value = get_value(args.key, cmake_json)
        nelem = 1
        if isinstance(value, list): nelem = len(value)
        elif value is None: nelem = 0
        else: nelem = 1
        data = nelem
        done = True

    if args.exists:
        result = find_entry(args.key, cmake_json) is None
        data = result
        done = True

    if args.delete:
        del_entry(args.key, cmake_json)
        done = True

    if args.get:
        if not find_entry(args.key, cmake_json):
            raise ValueError('Key not found: ' + args.key)
        value = get_value(args.key, cmake_json)
        value = json_val_to_cmake(value)
        data = value
        done = True

    # value required for any command after this point.
    if not done and args.value is None:
        raise ValueError('Value is required for this command')

    if args.add:
        if not find_entry(args.key, cmake_json):
            set_value(args.key, parse_cmake_value(args.value), cmake_json)
        else:
            raise ValueError('Key already exists: {}'.format(args.key))
        done = True

    if args.set:
        set_value(args.key, parse_cmake_value(args.value), cmake_json)
        done = True

    # write output file
    if data is None:
        data = json.dumps(cmake_json)
    else:
        data = str(data)
    with open(args.output, 'w') as f:
        f.write(data)
    return 0


if __name__ == '__main__':
    main()


