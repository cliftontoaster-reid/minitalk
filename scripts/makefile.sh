#!/bin/bash

TEMPLATE_PATH="template/Makefile"
OUTPUT_PATH="Makefile"

# Check if template exists
if [ ! -f "$TEMPLATE_PATH" ]; then
	echo "Error: Template file not found at $TEMPLATE_PATH"
	exit 1
fi

# Extract directory variables from template
SRCS_DIR=$(grep -oP 'SRCS_DIR\s*=\s*\K[^\n]+' "$TEMPLATE_PATH" | tr -d '"'\' || echo "src/")

# Handle variable references
[[ $SRCS_DIR =~ ^\$\(.*\)$ ]] && SRCS_DIR="src/"

# Generate SRCS list
generate_srcs() {
	echo "SRCS = \\"
	find "$SRCS_DIR" -type f -name "*.c" | sort | while read -r file; do
		# Convert path to use forward slashes and remove leading src/
		file=$(echo "$file" | sed "s|^${SRCS_DIR}||" | tr '\\' '/')
		echo -e "\t\$(SRCS_DIR)${file} \\"
	done
	echo
}

# Create backup of existing Makefile if it exists
if [ -f "$OUTPUT_PATH" ]; then
	cp "$OUTPUT_PATH" "${OUTPUT_PATH}.backup"
	echo "Created backup of existing Makefile at ${OUTPUT_PATH}.backup"
fi

# Create new Makefile content
{
	# Process the template line by line
	while IFS= read -r line || [ -n "$line" ]; do
		if [[ $line =~ ^SRCS[[:space:]]*= ]]; then
			# Insert generated SRCS list
			generate_srcs
			# Skip lines until we find one that doesn't end with \
			while IFS= read -r skip_line && [[ $skip_line =~ \\$ ]]; do
				continue
			done
		else
			echo "$line"
		fi
	done <"$TEMPLATE_PATH"
} >"$OUTPUT_PATH"

echo "Successfully generated new Makefile at $OUTPUT_PATH"
