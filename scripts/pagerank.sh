echo ""
echo ""
"${build_dir}/pagerank" "${input_dir}/${pagerank_graph}.txt" "${output_dir}/pagerank"
python3 "${build_dir}/pagerank.py" "${output_dir}/pagerank"
