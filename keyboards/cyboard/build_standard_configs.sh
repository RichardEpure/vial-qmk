#!/usr/bin/env bash
set -euo pipefail

KEYBOARDS=(
  "imprint/imprint_letters_only_2key_bottom_row"
  "imprint/imprint_letters_only_5key_bottom_row"
  "imprint/imprint_letters_only_no_bottom_row"
  "imprint/imprint_number_row_2key_bottom_row"
  "imprint/imprint_number_row_5key_bottom_row"
  "imprint/imprint_function_row_2key_bottom_row"
  "imprint/imprint_function_row_5key_bottom_row"
  "dactyl/manuform_letters_only"
  "dactyl/manuform_number_row"
  "dactyl/manuform_function_row"
  "dactyl/dual_arcs_letters_only"
  "dactyl/dual_arcs_number_row"
  "dactyl/dual_arcs_function_row"
  "dactyl/single_arc_letters_only"
  "dactyl/single_arc_number_row"
  "dactyl/single_arc_function_row"
)

for keyboard in "${KEYBOARDS[@]}"; do
    echo "Building keyboard: $keyboard"
    make "cyboard/${keyboard}:vial" &
done

wait
echo "All builds completed."
