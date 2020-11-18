#!/bin/bash

TARGET=forca.out
TARGET_BKP="${TARGET}.bkp"
# echo "TARGET [${TARGET}] TARGET_BKP [${TARGET_BKP}]"

clear

if [[ -e ${TARGET} ]]; then
    if [[ -e ${TARGET_BKP} ]]; then
        echo "Apagando backup..."
        rm ${TARGET_BKP}
    fi
    echo "Realizando backup..."
    mv ${TARGET} ${TARGET_BKP}
fi

gcc forca.c -o ${TARGET}

ret_comp=$?
# echo "result compilacao [${ret_comp}]"

if [[ ${ret_comp} -eq 0 ]]; then
    echo "Compilacao ok"
    echo -e "\n\n"
    if [[ -e ${TARGET} ]]; then
        ./${TARGET}
    fi
else
    echo "\nErro na compilacao"
fi
