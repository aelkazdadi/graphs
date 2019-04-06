echo ""
for i in "${graphs[@]}"
do
    echo ""
    echo ${i}
	"${build_dir}/core" "${output_dir}/processed/${i}.txt"
done
