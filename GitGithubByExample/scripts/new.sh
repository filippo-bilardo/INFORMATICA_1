cd /home/git-projects/INFORMATICA_1/GitGithubByExample && find . -name "README.md" | sort

cd /home/git-projects/INFORMATICA_1/GitGithubByExample && bash scripts/course-complete-analyzer.sh | grep "❌.*README.md"

cd /home/git-projects/INFORMATICA_1/GitGithubByExample && echo "=== MISSING FILES SUMMARY ===" && echo "" && echo "Files with ❌ in the analysis:" && bash scripts/course-complete-analyzer.sh | grep "❌" | sort | uniq
cd /home/git-projects/INFORMATICA_1/GitGithubByExample && ./scripts/course-complete-analyzer.sh | grep "❌.*FILE MANCANTE"