echo ""
for i in "${graphs[@]}"
do
    echo ""
    echo ${i}
	"${build_dir}/bfs" "${output_dir}/processed/${i}.txt"
done
