mkdir -p ${output_dir}/processed
echo ""
for i in "${graphs[@]}"
do
    echo ""
    echo ${i}
	${build_dir}/clean_data "${input_dir}/${i}.txt" "${output_dir}/processed/${i}.txt"
done
