# {current_dir}/scripts
scripts_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )/scripts"
mkdir -p "${output_dir}"
source "./config.sh"
source "${scripts_dir}/size.sh"
source "${scripts_dir}/clean.sh"
source "${scripts_dir}/degree.sh"
source "${scripts_dir}/Q.sh"
source "${scripts_dir}/distribution.sh"
source "${scripts_dir}/bfs.sh"
source "${scripts_dir}/coredecomposition.sh"

source "${scripts_dir}/pagerank.sh"

source "${scripts_dir}/community.sh"
