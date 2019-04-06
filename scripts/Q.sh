echo ""
for i in "${graphs[@]}"
do
    echo ""
    echo ${i}
	"${build_dir}/ex5" "${output_dir}/processed/${i}.txt"
done
