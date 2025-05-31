cd /home/git-projects/INFORMATICA_1/GitGithubByExample && find . -name "README.md" | sort

cd /home/git-projects/INFORMATICA_1/GitGithubByExample && bash scripts/course-complete-analyzer.sh | grep "❌.*README.md"

cd /home/git-projects/INFORMATICA_1/GitGithubByExample && echo "=== MISSING FILES SUMMARY ===" && echo "" && echo "Files with ❌ in the analysis:" && bash scripts/course-complete-analyzer.sh | grep "❌" | sort | uniq
cd /home/git-projects/INFORMATICA_1/GitGithubByExample && ./scripts/course-complete-analyzer.sh | grep "❌.*FILE MANCANTE"

#stringa multinea con le modifiche da apportare
modifiche="Modifiche da apportare:\n\n"
Module 02: Missing 1 example (has 3, needs 4)
Module 03: Missing 1 example (has 3, needs 4)
Module 10: Missing 1 exercise (has 3, needs 4)
Module 11: Missing 1 exercise (has 3, needs 4)
Module 17: Missing 1 exercise (has 3, needs 4)
Module 18: Missing 1 exercise (has 3, needs 4)
Module 19: Missing 1 exercise (has 3, needs 4)
Module 20: Missing 1 exercise (has 3, needs 4)
Module 21: Missing 2 exercises (has 2, needs 4) and 1 example (has 3, needs 4)
Module 24: Missing 2 examples (has 2, needs 4)
Module 25: Missing 1 exercise (has 3, needs 4)
Module 27: Missing 2 exercises (has 2, needs 4) and 1 example (has 3, needs 4)
Module 28: Missing 3 exercises (has 2, needs 4) and 2 examples (has 2, needs 4)