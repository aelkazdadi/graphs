declare -a graphs=(
                   "email-Eu-core"
                   "com-amazon.ungraph"
                   #"com-lj.ungraph"
                   #"com-orkut.ungraph"
                   #"com-friendster.ungraph"
                   )

pagerank_graph="alr21--dirLinks--enwiki-20071018"

scripts_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )/scripts"
build_dir="/home/aamr/graphs/build/"

input_dir="/media/aamr/HDD/data/raw/"
output_dir="/media/aamr/HDD/data/"

mkdir -p "${output_dir}"
source "${scripts_dir}/size.sh"
source "${scripts_dir}/clean.sh"
source "${scripts_dir}/degree.sh"
source "${scripts_dir}/Q.sh"
source "${scripts_dir}/distribution.sh"
source "${scripts_dir}/bfs.sh"
source "${scripts_dir}/coredecomposition.sh"

source "${scripts_dir}/pagerank.sh"
