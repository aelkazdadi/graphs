mkdir -p ${output_dir}/distribution
for i in "${graphs[@]}"
do
	python3 "${build_dir}/ex6.py" "${output_dir}/degree/${i}.dat" \
	"${output_dir}/distribution/${i}.dat" "${output_dir}/distribution/${i}.pdf"
done
