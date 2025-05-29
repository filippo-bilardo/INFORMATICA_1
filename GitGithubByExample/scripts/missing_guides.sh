cd /home/git-projects/INFORMATICA_1/GitGithubByExample && find . -name "README.md" -path "./[0-9]*" | while read readme; do
  echo "=== Checking $readme ==="
  module_dir=$(dirname "$readme")
  
  # Extract expected guides from README
  expected_guides=$(grep -o '\[0[0-9] - [^]]*\](./guide/[^)]*\.md)' "$readme" 2>/dev/null | cut -d'(' -f2 | cut -d')' -f1 | sed 's|^./||')
  
  if [ -n "$expected_guides" ]; then
    echo "Expected guides:"
    echo "$expected_guides"
    echo "Actual guides:"
    if [ -d "$module_dir/guide" ]; then
      ls "$module_dir/guide/" | grep '\.md$' || echo "No guides found"
    else
      echo "No guide directory"
    fi
    echo "Missing guides:"
    for guide in $expected_guides; do
      if [ ! -f "$module_dir/$guide" ]; then
        echo "  Missing: $guide"
      fi
    done
  fi
  echo ""
done