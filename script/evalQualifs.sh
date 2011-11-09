#!/bin/sh 

# Genere les resultats pour les pre-qualifs de decembre
# Les variables ci dessous peuvent etre modifiees au besoin
# (en pratique, le besoin de les modifier devrait etre assez minime)

PATH_BINAIRE=../fast/
PATH_EVALUATEUR=../solution_checker/solution_checker
TEMPS=300
FICHIER_SORTIE=resultats.txt

rm -f $FICHIER_SORTIE
date > $FICHIER_SORTIE

for i in 1 2; do
    for j in $(seq 1 5); do
      echo "Lancement du run $i $j(" $(date) ")"

    SOL_INIT=../instances/assignment_a${i}_${j}.txt
    MODEL=../instances/model_a${i}_${j}.txt

    #Afin que le fichier existe meme si on ne trouve pas de solution
    rm -f benchOut.txt
    cp $SOL_INIT benchOut.txt

    #Lancement du run
    ${PATH_BINAIRE}/machineReassignment -t ${TEMPS} -i $SOL_INIT -p $MODEL -s 0 -o benchOut.txt &
    sleep ${TEMPS}
    killall machineReassignment

    #Evaluation du score et log
    echo -n "\tFin du run $i $j"
    SCORE_INITIAL=$(${PATH_EVALUATEUR} $MODEL $SOL_INIT $SOL_INIT | \grep "Solution is valid" | cut -d " " -f 8)

    SCORE_FINAL=$(${PATH_EVALUATEUR} $MODEL $SOL_INIT benchOut.txt | \grep "Solution is valid" | cut -d " " -f 8)

    if [ "x$SCORE_FINAL" = "x" ]; then
    {
      echo ""
      echo "*********************************************************"
      echo "!!! ATTENTION : une solution non valide a ete fournie !!!"
      echo "*********************************************************"
      SCORE_FINAL=$SCORE_INITIAL
    }
    else
    {
      echo " : Evolution du score : $SCORE_INITIAL -> $SCORE_FINAL"
    }
    fi

    echo "$SOL_INIT $MODEL : $SCORE_INITIAL -> $SCORE_FINAL" >> $FICHIER_SORTIE

  done
done

rm benchOut.txt
