#!/usr/bin/python

import sys
import os

#=============================================================================
#  Returns a list of keywords which represent supported libraries
#=============================================================================
def GetSupportList( conf_file ):
    list = []
    for line in open( conf_file, 'r' ):

        if line.startswith('KVS_SUPPORT'):
            tag, val = line.split('=')
            tag = tag.strip()
            val = val.strip()

            if val == '1':
                tag = tag[4:]
                tag = tag.replace('_','')
                list.append( tag )

    return list

#=============================================================================
#  Returns a list of target directories.
#=============================================================================
def GetDirectoryList( find_path, support_list ):
    list = []
    for root, dirs, files in os.walk( find_path ):

        for filename in files:

            file_path = os.path.join( root, filename )
            if os.path.splitext( filename )[1] == ".cpp":

                if not root in list:
                    if root.count('Support') > 0:
                        root_upper = root.upper()
                        for support in support_list:
                            if root_upper.count( support ) > 0:
                                list.append( root )
                    else:
                        list.append( root )

    return list

#=============================================================================
#  Executes kvsmake command for every example codes.
#=============================================================================
def KVSMake( dir_list, option ):
    make_option  = ('','')
    if   option == 'build':     make_option = ("make;", "kvsmake;")
    elif option == 'clean':     make_option = ("make clean;", "kvsmake clean;")
    elif option == 'distclean': make_option = ("make distclean; rm *.pro;", "kvsmake distclean;")
    elif option == 'rebuild':   make_option = ("make clean; make;", "kvsmake rebuild;")
    else:
        print "Error: Unknown option '" + option + "'"
        print "Usage: python kvsmake.py [clean|rebuild|distclean]"
        sys.exit()

    curdir = os.getcwd()
    for dir in dir_list:
        command =  "cd " + dir + ";"
        if dir.count('SupportQt') > 0:
            projname = dir.replace('\\','/').rpartition('/')[2]
            command += "kvsmake -qt " + projname + "; qmake;"
            command += make_option[0]
        else:
            command += "kvsmake -G;"
            command += make_option[1]
        command += "cd " + curdir
        os.system( command )

#=============================================================================
#  Main process.
#=============================================================================
if __name__=='__main__':
    support_list = GetSupportList( '../kvs.conf' )
    dir_list = GetDirectoryList( '.', support_list )

    argc = len( sys.argv )
    argv = sys.argv
    if   argc == 1: KVSMake( dir_list, 'build' )
    elif argc == 2: KVSMake( dir_list, argv[1] )
