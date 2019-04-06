echo ""
for i in "${graphs[@]}"
do
    echo ""
    echo ${i}
    ${build_dir}/size "${data_dir}/${i}.txt"
done
