#!/usr/bin/env python3

#====================================================================
# Syntax      : makeDocs.py
# Description : Generate documentation based on individual project
#               files. For now only the one README.md file is
#               generated as top level document.
# Author      : AP
# Created     : 08 Jan 2016
#--------------------------------------------------------------------


#====================================================================
# Imports
#--------------------------------------------------------------------
import glob
import re
import os.path
import subprocess


#====================================================================
# Globals
#--------------------------------------------------------------------
Boards = {}


#====================================================================
# Functions
#--------------------------------------------------------------------
def print_site_readme(boards):
    with open("README.md", "w") as of:
        # Print a static header
        of.write('''
# Overview
A collection of examples for getting started in the Internet of Things (IoT). This includes code, wiring diagrams and documentation. In the description of each example, we list supported/tested boards. The same code may work on other boards with no or minimal changes. Files are organized in the following manner:

* `admin`: Utilities for maintaining this repo.
* `Arduino`: Projects on Arduino and Energia. Most examples are about Arduino Uno and TI LaunchPadF5529.
* `NodeMCU`: Projects on NodeMCU including those that can be programmed via Arduino IDE.
* `RaspberryPi`: Projects on mostly Raspberry Pi 2, although examples may work with other variants.

Examples using other platforms such as Intel Edison, Broadcom WICED or ARM mbed may be added in future.\n\n''')

        # Print the content extracted earlier
        for board in sorted(boards.keys()):
            projs = boards[board]
            of.write('# {} ({:d} projects)\n'.format(board, len(projs)))
            of.write('<table><tr>\n');
            for proj in projs:
                of.write('<tr>\n');
                of.write('<td style="width:200px"><a href="{}{}">{}</a></td>\n'.format(board, proj[0], proj[0]));
                of.write('<td><pre>{}</pre></td>\n'.format(proj[1]));
                of.write('</tr>\n');
            of.write('</table>\n\n');


def get_project_fields(sketch, images):
    with open(sketch, 'r') as sk:
        content = sk.read()

    # Extract fields from sketch content
    found = re.findall(r'Purpose\s*:\s*(.*?)Date\s*:\s*.*?Boards\s*:\s*(.*?)\n', content, re.S)
    if not found: return None

    purpose, boards = found[0]
    purpose = re.sub(r'\n\s*', r'\n', purpose) # remove leading spaces in each line
    name = os.path.splitext(os.path.basename(sketch))[0]

    # Filter relevant images for this sketch
    prefix = sketch[:-4:]
    skimgs = [x for x in images if prefix in x]

    return dict(zip(('name', 'purpose', 'boards', 'images'), (name, purpose, boards, skimgs)))


def append_project_summary(boards, board, fields):
    if board not in boards: boards[board] = []
    boards[board].append((fields['name'], fields['purpose']))


def print_project(board, fields):
    if not fields: return

    with open("{}{}/README.md".format(board, fields['name']), "w") as of:
        of.write('# {}\n'.format(fields['name']));
        of.write('<table><tr>\n');
        of.write('<td>\n');
        for img in sorted(fields['images']):
            of.write('''<br><img src="{}" width=320px>\n'''.format(img.replace('\\', '/')))
        of.write('</td>\n');
        of.write('<td>\n');
        of.write('<b>Boards</b><p><pre>{}</pre></p>\n'.format(fields['boards']));
        of.write('<b>Description</b><p><pre>{}</pre></p>\n'.format(fields['purpose']));
        of.write('</td>\n');
        of.write('</tr></table>\n');
        of.write('\n');


#====================================================================
# Main processing
#--------------------------------------------------------------------
# Find out the untracked git folders
git_cmd = 'git ls-files --others --directory'
untracked = subprocess.check_output(git_cmd.split(), universal_newlines=True).split('\n')
boards = [b for b in sorted(glob.glob('*/')) if all(b!=u for u in untracked)] # only top-level tracked folders

# Descend and process each tracked folder
for board in boards:
    images = glob.glob(board+'**/*_bb.png')
    for sketch in sorted(glob.iglob(board+'**/*')):
        if os.path.dirname(sketch)+'/' in untracked:
            continue
        if os.path.splitext(sketch)[1] in ['.ino', '.py']:
            # accept Arduino sketches or Python code (RaspberryPi)
            fields = get_project_fields(sketch, images)
            append_project_summary(Boards, board, fields)
            print_project(board, fields)

# Print main readme file
print_site_readme(Boards)

