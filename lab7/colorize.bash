#!/bin/bash
< $1 | while read -n 1 x
do
        case $x in
            1)
                echo -ne '\033[0;34m' + $x
            ;;
            2)
                echo -ne '\033[0;32m' + $x
            ;;
            3)
                echo -ne '\033[0;31m' + $x
            ;;
            x)
                echo -ne '\033[0;33m' + $x
            ;;

        esac
    done
    echo -e '\033[0m'
    exit 0

