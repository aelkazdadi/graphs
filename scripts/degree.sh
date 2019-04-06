mkdir -p ${output_dir}/degree
for i in "${graphs[@]}"
do
	${build_dir}/ex4 "${output_dir}/processed/${i}.txt" "${output_dir}/degree/${i}.dat"
done
