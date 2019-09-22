#!/bin/bash
file="salidas_generador/salida_pd_w_var_$1_$2_$3_$4_$5_$6_$7_$8_$9.out"
echo 'Creando salida generador...'
./generador_entradas_pd_n_fijo $1 $2 $3 $4 $5 $6 $7 $8 $9 >$file
echo "$file correctamente creado."
echo "Corriendo tiempos de $file..."
tiempo="salidas_tiempos/salida_pd_w_var_$1_$2_$3_$4_$5_$6_$7_$8_$9.csv"
./tiempos_pd <$file >$tiempo
echo "$tiempo correctamente creado."



